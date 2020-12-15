#include <iostream>
#include "client.h"

using namespace std;


int main() {
    cout << "socket client is starting..." << endl;

    string address1 = "127.0.0.1";
    Client client = Client(address1, 65432);

    cout << address1 << endl;

//    client.Start("/home/dyh/workspace/datasets/coco/val2017");
    client.Start("/home/dyh/workspace/unbox/unbox_cpp_caffe2/python_project/images/train");

    return 0;
}
