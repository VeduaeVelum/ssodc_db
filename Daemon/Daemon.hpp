#pragma once

namespace ssodc {
namespace utils {

class Daemon 
{
private:
    static void TerminateHandler(int);

protected:
    static bool m_terminate;

public:
    Daemon();
    
    virtual int Run() = 0;
    int Start();

    virtual ~Daemon();

};

} /* namespace utils */
} /* namespace ssodc */
