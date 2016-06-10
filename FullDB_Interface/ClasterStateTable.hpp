#pragma once 

#include <iostream>
#include <string>
#include <list>
#include <pqxx/pqxx> 
#include "ClasterState/ClasterState.hpp"
#include "DB_Interface/DatabaseInterface.hpp"

namespace ssodc {
namespace database_controller {

typedef unsigned const int UCI;

class ClasterStateTable : public DatabaseInterface
{
private: 
    std::unique_ptr<pqxx::connection> m_connection;

public:
    ClasterStateTable();
    ClasterStateTable(const std::string&, const std::string&, const std::string&, const std::string&);

    void CreateUser(const std::string&, const std::string&, const std::string&, const std::string&);
    void CreateTable(const std::string&);
    void InsertToTable(ssodc::utils::ClasterState&);
    std::list<ssodc::utils::ClasterState> SelectFromTable();
    ssodc::utils::ClasterState SelectById(UCI);
    void UpdateTable(UCI, ssodc::utils::ClasterState&);
    void DeleteFromTable(UCI);
    void DropTable();

    void Connect_to_();
    void Disconnect_from_();

    ~ClasterStateTable();
};

}    /*namespace database_controller*/
}    /*namespace ssodc*/