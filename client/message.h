#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <ctime>
#include <iostream>
#include <thread>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <opencv2/opencv.hpp>
#include <mutex>

#include "json.hpp"

using namespace std;
using namespace cv;
using namespace std::chrono;
using json = nlohmann::json;


class Message {

public:
    Message(int socket_fd, const string& client_address);

    ~Message();

    void GetImageBufferResult(unsigned char *&output_content, long &output_length);

    void Clear();

    bool Read();

    bool WriteImage(const cv::Mat& mat_image);


private:

    static const long max_buffer_size_ = 1024000;

    static const long max_socket_buffer_size_ = max_buffer_size_ * 0.4;

    static const int protocol_header_length = 2;

    int socket_fd_;

    string client_address_;

    vector<int> imencode_params_;

    unsigned char recv_buffer_[max_buffer_size_]{};

    long recv_buffer_length_{};

    unsigned char send_buffer_[max_buffer_size_]{};

    long send_buffer_length_{};

    nlohmann::basic_json<map, vector, basic_string<char>, bool, int64_t, uint64_t, double, allocator, nlohmann::adl_serializer, vector<uint8_t>> json_object_;

    unsigned short json_text_length_{};

    long image_buffer_length_{};

    bool is_response_created_ = false;

    bool is_json_text_loaded_ = false;

    unsigned char image_buffer_[max_buffer_size_]{};

    bool is_image_buffer_loaded_ = false;

    long SocketRead();

    bool SocketWrite();

    void CreateResponseBuffer(const cv::Mat& mat_image);

    void ProcessProtocolHeader();

    void ProcessJsonText();

    void ProcessContent();

    static void Short2Char(unsigned char *char_str, unsigned char short_str);

    static unsigned short Char2Short(const unsigned char *char_str);

};


#endif //SERVER_MESSAGE_H
