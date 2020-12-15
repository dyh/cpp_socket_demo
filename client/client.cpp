#include <dirent.h>
#include "client.h"

Client::Client(const string& server_address, int port) {
    this->address_ = server_address.c_str();
    this->port_ = port;
}

void Client::Start(const string& folder_path) {
    // record begin time
    auto timestamp_ms_1 = Client::GetCurrentTimestamp();

    int client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    if (client_fd == -1) {
        perror("Error: socket");
    }

    // connect
    struct sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(this->port_);
    serverAddr.sin_addr.s_addr = inet_addr(this->address_);

    auto is_connected = connect(client_fd, (struct sockaddr *)& serverAddr, sizeof(serverAddr));
    if (is_connected < 0) {
        perror("Error: connect");
    }

    // target image list
    vector<string> vector_filename_list;
    // load and fill the path of files to vector
    GetFileList(folder_path, vector_filename_list);

    long i_file_count = vector_filename_list.size();

//    std::vector<int> imencode_params;
//    imencode_params.push_back(cv::IMWRITE_JPEG_QUALITY);
//    imencode_params.push_back(100);

    auto message = Message(client_fd, this->address_);

    auto i_file_index = 0;

    // resize our input images to fit with model
    cv::Size dSize = cv::Size(800, 800);

    for (const auto& image_path : vector_filename_list) {
        // load image from file path, the size of image maybe w:2050 h:2411
        Mat mat_temp = imread(image_path, IMREAD_COLOR);

        // define a new Mat object with w:800 h:800
        Mat mat_image(dSize, CV_32F);

        // resize input image, from w:2050 h:2411 to w:800 h:800
        resize(mat_temp, mat_image, dSize, INTER_LINEAR);

        // release the image matrix from imread
        mat_temp.release();

        message.Clear();
        message.WriteImage(mat_image);

        unsigned char *output_buffer;
        long output_length = 0;

        // if the socket works well
        if (message.Read()) {

            message.GetImageBufferResult(output_buffer, output_length);

            if (output_length > 0) {

                std::vector<uchar> vector_image(output_buffer, output_buffer + output_length);

                cout << "# received " << output_length << " bytes from server " << this->address_ << endl;

                cv::Mat mat_image_show;
                cv::imdecode(vector_image, cv::ImreadModes::IMREAD_COLOR, &mat_image_show);

                cv::imshow("client", mat_image_show);
                cv::waitKey(1);

                mat_image_show.release();

                // release vector
                vector_image.clear();
                vector<uchar>().swap(vector_image);

                cout << "# " << i_file_index << " / " << i_file_count << " files sent" << endl;
                i_file_index++;
            }
        } else {
            break;
        }

        mat_image.release();

        usleep(1);
    }

//    imencode_params.clear();
//    vector<int>().swap(imencode_params);

    auto timestamp_ms_2 = Client::GetCurrentTimestamp() - timestamp_ms_1;
    cout << "times: " << timestamp_ms_2 / 1000 << " seconds" << endl;

    shutdown(client_fd, SHUT_RDWR);

    cout << "done" << endl;
}

/*!
 * @brief load and fill the path of files to vector
 * @param[in] path folder path
 * @param[out] vector_filename vector of filename
*/
void Client::GetFileList(const string& path, vector<string>& vector_filename) {
    DIR *pDir;
    struct dirent *ptr;
    if (!(pDir = opendir(path.c_str()))) {
        cout << "Folder doesn't Exist!" << endl;
        return;
    }
    while ((ptr = readdir(pDir)) != nullptr) {
        if (strstr(ptr->d_name, ".jpg") != nullptr) {
            vector_filename.push_back(path + "/" + ptr->d_name);
        }
    }
    //排序
    sort(vector_filename.begin(), vector_filename.end());

    closedir(pDir);
}


/*!
 * @brief get current time ticks
 * @return ticks long
*/
long Client::GetCurrentTimestamp() {
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now());
    return tp.time_since_epoch().count();
}