#include <iostream>
#include "server.h"

using namespace std;


int main() {
    cout << "socket server is starting..." << endl;

    string host1 = "0.0.0.0";
    Server server = Server(host1, 65432, 10);
    server.Start();

    return 0;
}
