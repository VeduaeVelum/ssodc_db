#include "IProcessMQ.hpp"
#include <string>
#include <iostream>
#include <unistd.h>

int main() {
	std::cout << "1" << std::endl;
    std::string message;
    std::cout << "2" << std::endl;
    ssodc::ipc::IProcessMQ ipc;
    ipc.Bind("tcp://0.0.0.0:6555");
    std::cout << "4" << std::endl;
    ipc.Recv(message);
    std::cout << "5" << std::endl;
    std::cout << message << std::endl;
    std::cout << "6" << std::endl;
    return 0;
}