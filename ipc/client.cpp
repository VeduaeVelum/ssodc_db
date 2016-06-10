#include "IProcessMQ.hpp"
#include <string>
#include <iostream>

int main() {
	std::cout << "1" << std::endl;
    std::string reply;
    std::cout << "2" << std::endl;
    ssodc::ipc::IProcessMQ ipc("tcp://192.168.1.2:6555");
    std::cout << "3" << std::endl;
    ipc.Send("Hello world!");
    std::cout << "4" << std::endl;
    return 0;
}