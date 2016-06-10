#pragma once 

#include <iostream>
#include <string>
#include <map>
#include <pqxx/pqxx> 
#include "DB_Interface/DatabaseInterface.hpp"

namespace ssodc {
namespace database_controller {

typedef unsigned const int UCI;

class MapInfoTable : public DatabaseInterface
{
private: 
    std::unique_ptr<pqxx::connection> m_connection;
public:
    MapInfoTable();
    MapInfoTable(const std::string&, const std::string&, const std::string&, const std::string&);

    void CreateUser(const std::string&, const std::string&, const std::string&, const std::string&);
    void CreateTable(const std::string&);
    void InsertToTable(UCI, const std::string&);
    std::map<int, std::string> SelectFromTable();
    std::string SelectById(UCI);
    void UpdateTable(const std::string&, UCI);
    void DeleteFromTable(UCI);
    void DropTable();

    void Connect_to_();
    void Disconnect_from_();

    ~MapInfoTable();
};

}
}