#pragma once

#include <string>

namespace ssodc {
namespace utils {

enum TaskType {
    Text = 1,
    Image
};

enum TaskStatus {
    Unknown = 0,
    Waiting,
    Mapping,
    Processing,
    Reducing,
    Finished
};

class TaskInfo {
private:
    int m_id;
    TaskType m_type;
    TaskStatus m_status;
    std::string m_datapath;
    std::string m_codepath;
    std::string m_executablepath;

public:
    TaskInfo();
    TaskInfo(int id, TaskType type, TaskStatus status, std::string datapath,
             std::string codepath = "", std::string executablepath = "");

    int GetId();
    TaskType GetType();
    TaskStatus GetStatus();
    std::string GetDataPath();
    std::string GetCodePath();
    std::string GetExecutablePath();

    void SetId(int);
    void SetType(TaskType);
    void SetStatus(TaskStatus);
    void SetDataPath(const std::string&);
    void SetCodePath(const std::string&);
    void SetExecutablePath(const std::string&);

    ~TaskInfo();
};

} /* namespace utils */
} /* namespace ssodc */
