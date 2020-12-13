#include <iostream>
#include "client.h"

using namespace std;


int main() {
    cout << "socket client is starting..." << endl;

    string address1 = "127.0.0.1";
    Client client = Client(address1, 65432);

    cout << address1 << endl;

    client.Start("/home/dyh/workspace/datasets/coco/val2017");

    return 0;
}
