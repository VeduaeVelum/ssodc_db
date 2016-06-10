#pragma once

#include <memory>
#include <string>
#include <zmq.hpp>

#include "IProcessMQInterface.hpp"

namespace ssodc {
namespace ipc {

class IProcessMQ : public IProcessMQInterface {
public:
    IProcessMQ();
    IProcessMQ(const std::string&);
    ~IProcessMQ();

    int Recv(std::string&);
    int Bind(const std::string&);
    int Send(const std::string&);
    int Connect(const std::string&);
    int Listen(std::function<std::string(std::string)>);
private:
    std::unique_ptr<zmq::socket_t> m_socket;
    std::unique_ptr<zmq::context_t> m_context;
};
} /* namespace ipc */
} /* namespace ssodc */