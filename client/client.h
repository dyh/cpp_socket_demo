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
#include "message.h"

using namespace std;
using namespace cv;
using namespace std::chrono;


#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H


class Client {

public:

    Client(const string& server_address, int port);

    void Start(const string& folder_path);

private:
    // host address
    const char *address_;

    //port number
    int port_;

    static void GetFileList(const string& path, vector<string>& vector_filename);

    // get current time ticks
    static long GetCurrentTimestamp();
};


#endif //CLIENT_CLIENT_H
