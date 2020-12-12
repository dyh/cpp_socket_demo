#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

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


class Server {

public:
    Server(const string &host, int port, int timeout);

    [[noreturn]] void Start();

private:
    // host address
    const char *host_;

    //port number
    int port_;

    // seconds of timeout
    int timeout_seconds_;

    // vector of socket threads
    vector<thread> vector_threads_;

    // record the flag of loop and latest std::clock of each socket message, <thread_name, ticks_value>
    map<long, long> map_latest_message_timestamp_;

    // daemon thread of timeout
    thread thread_timeout_daemon_;

    // socket function in thread
    void SocketHandle(int connection_fd, const string &client_address, long thread_name);

    // timeout function in thread
    [[noreturn]] void TimeoutHandle();

    // get current time ticks
    static long GetCurrentTimestamp();
};

#endif //SERVER_SERVER_H
