#include "message.h"

/*!
@brief init Message
@param[in] socket_fd accepted socket file descriptor
@param[in] client_address ip address of client
*/
Message::Message(int socket_fd, const string &client_address) {

    this->socket_fd_ = socket_fd;
    this->client_address_ = client_address;

    this->imencode_params_.push_back(cv::IMWRITE_JPEG_QUALITY);
    this->imencode_params_.push_back(100);

    this->Clear();
}

/*!
@brief get the image char[] array and its length
@param[out] output_content image char[] array for output
@param[in] output_length length of char[]
*/
void Message::GetImageBufferResult(unsigned char *&output_content, long &output_length) {
    output_content = this->image_buffer_;
    output_length = this->image_buffer_length_;
}

/*!
@brief init variables of Message Class
*/
void Message::Clear() {

    this->is_response_created_ = false;
    this->is_json_text_loaded_ = false;
    this->is_image_buffer_loaded_ = false;

    this->recv_buffer_length_ = 0;
    this->send_buffer_length_ = 0;
    this->json_text_length_ = 0;
    this->image_buffer_length_ = 0;

    memset(this->recv_buffer_, 0, sizeof(this->recv_buffer_));
    memset(this->send_buffer_, 0, sizeof(this->send_buffer_));
    memset(this->image_buffer_, 0, sizeof(this->image_buffer_));

    this->json_object_.clear();

}

/*!
@brief Read socket message and analytical it to image data
*/
bool Message::Read() {

    while (!this->is_image_buffer_loaded_) {

        // read buffer from socket
        long recv_length = this->SocketRead();

        cout << "." << endl;

        // -1 means error
        if (recv_length <= 0)
        {
            cout << "socket received length: " << recv_length << ", remote socket closed, BREAK while loop" << endl;
            return false;
        }

        // read protocol header to get json header length
        if (this->json_text_length_ == 0) {
            this->ProcessProtocolHeader();
        }

        // if we got json_header' s length, we read json_header to get image_file length
        if (this->json_text_length_ > 0) {
            if (!this->is_json_text_loaded_) {
                this->ProcessJsonText();
            }
        }

        // if we have read json_header, we process the image_file
        if (this->is_json_text_loaded_) {
            if (!this->is_image_buffer_loaded_) {
                this->ProcessContent();
            }
        }
    }
    return true;
}

/*!
 * @brief write image data to socket
 * @param[in] write mat_image write cv:Mat image object to socket
 * @return true=succeed, false=failed
*/
bool Message::WriteImage(const cv::Mat& mat_image) {
    if (!this->is_response_created_) {
        CreateResponseBuffer(mat_image);

        if (this->is_response_created_)
        {
           if(this->SocketWrite())
           {
               return true;
           }
           else
           {
               return false;
           }
        }
    }
    return false;
}

/*!
 * @brief read data from socket
 * @return recv_length length of the data
*/
long Message::SocketRead() {

    // define a temp buffer
    char data[Message::max_socket_buffer_size_];
    memset(data, 0, sizeof(data));

    // read socket to temp buffer
    // -1 means error
    int recv_length = recv(this->socket_fd_, data, Message::max_socket_buffer_size_, 0);

    // check whether recv_length is out of range
    if (recv_length > 0 && (recv_length + this->recv_buffer_length_) <= max_buffer_size_) {
        // copy socket message from the temp buffer to recv_buffer_
        memcpy(&this->recv_buffer_[this->recv_buffer_length_], data, recv_length * sizeof(char));
        // increase length of recv_buffer_
        this->recv_buffer_length_ += recv_length;
    }

    return recv_length;
}

/*!
 * @brief write data to socket
 * @return true=succeed, false=failed
*/
bool Message::SocketWrite() {
    long sent = send(this->socket_fd_, this->send_buffer_, this->send_buffer_length_, 0);
    if (sent > 0) {
        cout << "sent " << sent << " buffers to " << this->client_address_ << endl;
        return true;
    } else {
        return false;
    }
}

/*!
 * @brief create char[] from cv::Mat object
 * @param [in] mat_image cv::Mat object
 * @return true=succeed, false=failed
*/
void Message::CreateResponseBuffer(const cv::Mat& mat_image) {

    std::vector<uchar> vector_image;
    auto is_image_file = imencode(".jpg", mat_image, CV_OUT vector_image, this->imencode_params_);

    if (is_image_file) {

        std::string json_string =
                R"({"byteorder": "little", "content-type": "binary/image","content-encoding": "binary", "content-length": )" +
                to_string(vector_image.size()) + "}";

        const char *json_chars = json_string.c_str();
        short short_json_length = json_string.size();

        unsigned char header_chars[sizeof(short_json_length)];
        Short2Char(header_chars, short_json_length);

        long header_length = sizeof(header_chars);

        memcpy(&this->send_buffer_[this->send_buffer_length_], header_chars, header_length * sizeof(header_chars[0]));
        this->send_buffer_length_ += header_length;

        memcpy(&this->send_buffer_[this->send_buffer_length_], json_chars, short_json_length * sizeof(json_chars[0]));
        this->send_buffer_length_ += short_json_length;

        memcpy(&this->send_buffer_[this->send_buffer_length_], &vector_image[0],
               vector_image.size() * sizeof(vector_image[0]));
        this->send_buffer_length_ += vector_image.size();

        this->is_response_created_ = true;
    }

    vector_image.clear();
    vector<uchar>().swap(vector_image);

}

/*!
 * @brief get the length of json text message
*/
void Message::ProcessProtocolHeader() {
    // make sure to load enough data to get protocol_header
    if(this->recv_buffer_length_ >= Message::protocol_header_length) {

        unsigned char temp_buffer[Message::protocol_header_length];
        memset(temp_buffer, 0, sizeof(temp_buffer));
        memcpy(temp_buffer, this->recv_buffer_, Message::protocol_header_length * sizeof(char));

        // convert char to short, to get json_text_length_
        this->json_text_length_ = Char2Short(temp_buffer);

        // change length of recv_buffer_length_
        this->recv_buffer_length_ -= Message::protocol_header_length;

        // remove protocol_header data from recv_buffer_
        memcpy(this->recv_buffer_, &this->recv_buffer_[Message::protocol_header_length],
               this->recv_buffer_length_ * sizeof(char));

        // cut off with \0
        // memset(&this->recv_buffer_[this->recv_buffer_length_], '\0', 1);
    }
}

/*!
 * @brief get the length of binary image data after the json
*/
void Message::ProcessJsonText() {

    if(this->recv_buffer_length_ >= this->json_text_length_) {

        char temp_buffer[this->json_text_length_];
        memset(temp_buffer, 0, sizeof(temp_buffer));

        memcpy(temp_buffer, this->recv_buffer_, this->json_text_length_ * sizeof(char));
        memset(&temp_buffer[this->json_text_length_], '\0', 1);

        string str_json(temp_buffer);

        // get json object from json string
        this->json_object_ = json::parse(str_json);

        // record the content length of image file
        this->image_buffer_length_ = (long)this->json_object_["content-length"];

        // change length of recv_buffer_length_
        this->recv_buffer_length_ -= this->json_text_length_;

        // remove json_text data from recv_buffer_
        memcpy(this->recv_buffer_, &this->recv_buffer_[this->json_text_length_],
               this->recv_buffer_length_ * sizeof(char));

        this->is_json_text_loaded_ = true;
    }
}

/*!
 * @brief load binary image data to char[] "recv_buffer_", and set the length value to "image_buffer_length_"
*/
void Message::ProcessContent() {

    if (this->image_buffer_length_ == 0) {
        this->image_buffer_length_ = (long) this->json_object_["content-length"];
    }

    // check data length
    if (this->image_buffer_length_ > this->recv_buffer_length_) {
        return;
    } else {
        string byteorder(this->json_object_["byteorder"]);
        string content_type(this->json_object_["content-type"]);

        if (content_type == "binary/image") {
            memset(this->image_buffer_, 0, sizeof(this->image_buffer_length_));
            memcpy(this->image_buffer_, this->recv_buffer_, this->image_buffer_length_ * sizeof(char));

            // change length of recv_buffer_length_
            this->recv_buffer_length_ -= this->image_buffer_length_;

            if(this->recv_buffer_length_ > 0)
            {
                // remove content data from recv_buffer_
                memcpy(this->recv_buffer_, &this->recv_buffer_[this->image_buffer_length_],
                       this->recv_buffer_length_ * sizeof(char));
            }

        } else {
            // else if(content_type == "text/json")
            // string content_encoding(this->json_object_["content-encoding"]);
            // char temp_buffer[this->image_buffer_length_];
            // memset(temp_buffer, 0, sizeof(temp_buffer));
            // memcpy(temp_buffer, this->recv_buffer_, this->image_buffer_length_ * sizeof(char));
            // string str_content(temp_buffer);
            // get another json object from json text
            // auto data = json::parse(str_json);
            cout << "unsupported content_type!" << endl;
        }

        this->json_object_.clear();
        this->is_image_buffer_loaded_ = true;
    }

}

/*!
 * @brief convert short to char
 * @param[out] char_str output char* variable
 * @param[in] short_str input short variable
*/
void Message::Short2Char(unsigned char *char_str, unsigned char short_str) {
    unsigned short s = short_str;
    for (int x = 0; x < 2; x++) {
        char_str[x] = s & 0xffu;
        s = s >> 8u;
    }
}

/*!
 * @brief convert char* to short
 * @param[in] char_str input char* variable
 * @return short value
*/
unsigned short Message::Char2Short(const unsigned char *char_str) {
    unsigned short s0 = char_str[0];
    unsigned short s1 = char_str[1];
//    unsigned short s0 = char_str[0] | 0xffu;
//    unsigned short s1 = char_str[1] | 0xffu;

    s1 = s1 << 8u;
    unsigned short s = (short) (s0 | s1);
    return s;
}

Message::~Message() {
    this->imencode_params_.clear();
    vector<int>().swap(this->imencode_params_);
}
