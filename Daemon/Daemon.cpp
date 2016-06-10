#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Daemon.hpp"

namespace ssodc {
namespace utils {

bool Daemon::m_terminate;

Daemon::Daemon() 
{
    struct sigaction terminateAction;
    sigset_t terminateSet;
    terminateAction.sa_flags = 0;

    sigemptyset(&terminateAction.sa_mask);

    sigfillset(&terminateSet);
    sigdelset(&terminateSet, SIGTERM);
    sigprocmask(SIG_SETMASK, &terminateSet, 0);

    terminateAction.sa_handler = &TerminateHandler;
    sigaction(SIGTERM, &terminateAction, 0);

    pid_t pid = fork();
    if (pid != 0) {
        // TODO: Change this stuff, when exception model will be implemented
        exit(pid > 0 ? EXIT_SUCCESS : EXIT_FAILURE);
    }

    setsid();
    chdir("/");
    umask(0);

    pid = fork();
    if (pid != 0) {
        // TODO: Change this stuff, when exception model will be implemented
        exit(pid > 0 ? EXIT_SUCCESS : EXIT_FAILURE);
    }
    
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void Daemon::TerminateHandler(int i) 
{
    m_terminate = true;
}

int Daemon::Start() 
{
    Run();
    return 0;
}

Daemon::~Daemon() 
{
}

} /* namespace utils */
} /* namespace ssodc */