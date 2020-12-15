#include "server.h"

std::mutex mutex_ticks_map;


/*!
 * @brief init server
 * @param[in] host
 * @param[in] port
 * @param[in] timeout in seconds
*/
Server::Server(const string& host, int port, int timeout) {
    this->host_ = host.c_str();
    this->port_ = port;
    this->timeout_seconds_ = timeout;

    // create the timeout daemon thread
    this->thread_timeout_daemon_ = thread(&Server::TimeoutHandle, this);
}

/*!
 * @brief start server
*/
[[noreturn]] void Server::Start() {

    int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    if (socket_fd == -1) {
        perror("Error: socket");
    }

    auto opt = 1;
    auto error_code = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (error_code == -1) {
        perror("Error: setsockopt");
    }

    // bind
    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->port_);
    server_addr.sin_addr.s_addr = inet_addr(this->host_);

    if (bind(socket_fd, (struct sockaddr *)& server_addr, sizeof(server_addr)) == -1) {
        perror("Error: bind");
    }

    // listen
    if (listen(socket_fd, 5) == -1) {
        perror("Error: listen");
    }

    while (true) {

        cout << "listening..." << endl;

        // accept
        struct sockaddr_in client_addr{};
        socklen_t client_addr_len = sizeof(client_addr);

        int new_connection_fd = accept(socket_fd, (struct sockaddr *)& client_addr, &client_addr_len);

        if (new_connection_fd < 0) {
            perror("Error: accept");
            continue;
        } else {
            char clientIP[INET_ADDRSTRLEN] = "";
            inet_ntop(AF_INET, &client_addr.sin_addr, clientIP, INET_ADDRSTRLEN);
            cout << "remote client from " << clientIP << ":" << ntohs(client_addr.sin_port) << endl;

            // generate a thread name
            long thread_name = std::clock();

            // add to timeout vector
            {
                std::lock_guard<std::mutex> lockGuard(mutex_ticks_map);
                this->map_latest_message_timestamp_[thread_name] = Server::GetCurrentTimestamp();
            }

            // 启动线程
            this->vector_threads_.emplace_back(
                    thread(&Server::SocketHandle, this, new_connection_fd, clientIP, thread_name));
        }

        // sleep 1 micro_seconds
        usleep(1);
    }

    shutdown(socket_fd, SHUT_RDWR);

    int thread_count = this->vector_threads_.size();

    for (int i = 0; i < thread_count; i++) {
        this->vector_threads_.at(i).join();
    }

    this->thread_timeout_daemon_.join();

    // release vector
    this->vector_threads_.clear();
    vector<thread>().swap(this->vector_threads_);

    // release map
    this->map_latest_message_timestamp_.clear();
    map<long, long>().swap(this->map_latest_message_timestamp_);

}


/*!
 * @brief to judge whether the socket has timeout
*/
void Server::TimeoutHandle() {

    auto timeout_value_ms = this->timeout_seconds_ * 1000;

    while (true) {

        auto timestamp_now = Server::GetCurrentTimestamp();

        long output_thread_name = -1;

        {
            std::lock_guard<std::mutex> lockGuard(mutex_ticks_map);

            if (find_if(this->map_latest_message_timestamp_.begin(),
                        this->map_latest_message_timestamp_.end(),

                        [timestamp_now, timeout_value_ms, &output_thread_name]
                        (map<long, long>::value_type& item) {
                            auto ret = ((timestamp_now - item.second) > timeout_value_ms);
                            if (ret) {
                                output_thread_name = item.first;
                            }
                            return ret;
                        })
                        != this->map_latest_message_timestamp_.end()) {

                cout << "# thread [" << output_thread_name << "] is timeout, removed from map_timestamp" << endl;
                this->map_latest_message_timestamp_.erase(output_thread_name);
            } else {
                // cout << "do not timeout: " << output_thread_name << endl;
            }
            // cout << "timestamp count: " << map_latest_message_timestamp_.size() << endl;
        }

//        cout << ".." << endl;

        // sleep in seconds
        sleep(this->timeout_seconds_);
    }

}

/*!
 * @brief function of handle socket
 * @param[in] connection_fd
 * @param[in] client_address
 * @param[in] thread_name
*/
void Server::SocketHandle(int connection_fd, const string& client_address, long thread_name) {

    cout << "accepted connection from " << client_address << endl;
    auto message = Message(connection_fd, client_address);

    // receive messages from socket client
    // flag of loop
    while (true) {
        // if this thread is not timeout
        {
            std::lock_guard<std::mutex> lockGuard(mutex_ticks_map);

            if (find_if(this->map_latest_message_timestamp_.begin(),
                        this->map_latest_message_timestamp_.end(),
                        [thread_name]
                                (map<long, long>::value_type& item) { return item.first == thread_name; })
                != this->map_latest_message_timestamp_.end()) {

            } else {
                cout << "do not find [" << thread_name << "] in map_loop, BREAK while loop" << endl;
                break;
            }
        }


        //clear buffer and response flag
        message.Clear();

        unsigned char *output_buffer;
        long output_length = 0;

        // if the socket works well
        if (message.Read()) {

            message.GetImageBufferResult(output_buffer, output_length);

            if (output_length > 0) {

                std::vector<uchar> vector_image(output_buffer, output_buffer + output_length);

                cout << "# received " << output_length << " bytes from client " << client_address << ", in thread [" << thread_name << "]"  <<  endl;

                cv::Mat mat_image;
                cv::imdecode(vector_image, cv::ImreadModes::IMREAD_COLOR, &mat_image);

                // release vector
                vector_image.clear();
                vector<uchar>().swap(vector_image);

                // TODO: process cv::Mat image object here

                // send cv::Mat image to client
                bool is_write_succeed = message.WriteImage(mat_image);

                // release cv::Mat image object
                mat_image.release();

                if (!is_write_succeed)
                {
                    // meet socket error
                    cout << "write socket error, remote socket maybe closed, BREAK while loop" << endl;
                    break;
                }

            }

        } else {
            // if we got error of socket, break while loop
            cout << "read socket error, remote socket maybe closed, BREAK while loop" << endl;

            break;
        }

        // judge whether the thread is not timeout

        {
            std::lock_guard<std::mutex> lockGuard(mutex_ticks_map);

            if (find_if(this->map_latest_message_timestamp_.begin(),
                        this->map_latest_message_timestamp_.end(),
                        [thread_name]
                                (map<long, long>::value_type& item) { return item.first == thread_name; })
                != this->map_latest_message_timestamp_.end()) {

                this->map_latest_message_timestamp_[thread_name] = Server::GetCurrentTimestamp();

            } else {
                cout << "do not find [" << thread_name << "] in map_loop, BREAK while loop" << endl;
                break;
            }
        }

        // sleep
        usleep(1);
    }

    cout << "shutdown connection_fd" << endl;
    shutdown(connection_fd, SHUT_RDWR);
}


/*!
 * @brief get current time ticks
 * @return ticks long
*/
long Server::GetCurrentTimestamp() {
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now());
    return tp.time_since_epoch().count();
}