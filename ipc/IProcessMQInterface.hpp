#pragma once

#include <string>

namespace ssodc {
namespace ipc {

class IProcessMQInterface {
public:
    virtual int Recv(std::string&) = 0;
    virtual int Bind(const std::string&) = 0;
    virtual int Send(const std::string&) = 0;
    virtual int Connect(const std::string&) = 0;  
};
} /* namespace ipc */
} /* namespace ssodc */