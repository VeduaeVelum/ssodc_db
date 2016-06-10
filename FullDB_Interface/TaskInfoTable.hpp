#pragma once 

#include <iostream>
#include <string>
#include <list>
#include <pqxx/pqxx> 
#include "TaskInfo/TaskInfo.hpp"
#include "DB_Interface/DatabaseInterface.hpp"

namespace ssodc {
namespace database_controller {

typedef unsigned const int UCI;

class TaskInfoTable : public DatabaseInterface
{
private: 
    std::unique_ptr<pqxx::connection> m_connection;

public:
    TaskInfoTable();
    TaskInfoTable(const std::string&, const std::string&, const std::string&, const std::string&);

    void create_user(const std::string&, const std::string&, const std::string&, const std::string&);
    void create_table(const std::string&);
    void insert_to_table(ssodc::utils::TaskInfo&);
    std::list<ssodc::utils::TaskInfo> select_from_table();
    ssodc::utils::TaskInfo select_by_id(UCI);
    void update_table(UCI, ssodc::utils::TaskInfo&);
    void delete_from_table(UCI);
    void drop_table();
    //TODO: make method for changing only task status

    void Connect_to_();
    void Disconnect_from_();

    ~TaskInfoTable();
};

}
}