#include <iostream>
#include "server.h"

using namespace std;


int main() {
    cout << "socket server is starting..." << endl;

    try {
        Server server = Server("0.0.0.0", 65432, 10);
        server.Start();

    }
    catch (...) {
        cout <<"1" << endl;
    }

    return 0;
}
