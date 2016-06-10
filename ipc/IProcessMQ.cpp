#include <functional>

#include "IProcessMQ.hpp"

namespace ssodc {
namespace ipc {

IProcessMQ::IProcessMQ() {
    m_context = std::unique_ptr<zmq::context_t>(new zmq::context_t(1));
    m_socket = std::unique_ptr<zmq::socket_t>(new zmq::socket_t(*m_context, ZMQ_DEALER));
}

IProcessMQ::IProcessMQ(const std::string& address) : IProcessMQ() {
    (address.find("tcp://*") == std::string::npos)  ? Connect(address) : Bind(address);
}

IProcessMQ::~IProcessMQ() {
    m_socket->close();
    m_context->close();
}

int IProcessMQ::Bind(const std::string& address) {
    m_socket->bind(address.c_str());
    return 0;
}

int IProcessMQ::Recv(std::string& message) {
    zmq::message_t incomingMessage;
    m_socket->recv(&incomingMessage);
    message = static_cast<char*>(incomingMessage.data());
    return 0;
}

int IProcessMQ::Send(const std::string& message) {
    zmq::message_t outgoingMessage(message.size());
    memcpy(outgoingMessage.data(), message.c_str(), message.size());
    m_socket->send(outgoingMessage);
    return 0;
}

int IProcessMQ::Connect(const std::string& address) {
    m_socket->connect(address.c_str());
    return 0;
}

int IProcessMQ::Listen(std::function<std::string(std::string)> callback) {
    std::string incomingMessage;
    std::string outgoingMessage;
    Recv(incomingMessage);
    outgoingMessage = callback(incomingMessage);
    Send(outgoingMessage);
    return 0;
}

} /* namespace utils */
} /* namespace ssodc */