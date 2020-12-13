#include <dirent.h>
#include "client.h"

Client::Client(const string& server_address, int port) {
    this->address_ = server_address.c_str();
    this->port_ = port;
}

void Client::Start(const string& folder_path) {
    int client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    if (client_fd == -1) {
        perror("Error: socket");
    }

    // connect
    struct sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(this->port_);
    serverAddr.sin_addr.s_addr = inet_addr(this->address_);

    auto is_connected = connect(client_fd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if (is_connected < 0) {
        perror("Error: connect");
    }

    // target image list
    vector<string> vector_filename_list;
    // target images folder
//    string folder_path = "/home/dyh/workspace/datasets/coco/val2017";
    // load and fill the path of files to vector
    GetFileList(folder_path, vector_filename_list);

    long i_file_count = vector_filename_list.size();

    std::vector<int> imencode_params;
    imencode_params.push_back(cv::IMWRITE_JPEG_QUALITY);
    imencode_params.push_back(100);

    auto message = Message(client_fd, this->address_);

    auto i_file_index = 0;

    for (const auto &image_path : vector_filename_list) {
        Mat mat_image = imread(image_path, IMREAD_COLOR);
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
                cv::waitKey(100);

                mat_image_show.release();

                // release vector
                vector_image.clear();
                vector<uchar>().swap(vector_image);

                cout << "# " << i_file_index << " / " << i_file_count << " files sent" << endl;
                i_file_index++;
            }
        }
        else
        {
            break;
        }

        mat_image.release();
    }

    imencode_params.clear();
    vector<int>().swap(imencode_params);

    cout << "shutdown client_fd" << endl;
    shutdown(client_fd, SHUT_RDWR);

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