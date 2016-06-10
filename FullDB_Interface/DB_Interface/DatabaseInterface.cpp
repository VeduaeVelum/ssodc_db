#include <iostream>
#include "DatabaseInterface.hpp"

namespace ssodc {
namespace database_controller {

DatabaseInterface::DatabaseInterface()
{
    this->db_name = "dbname=testdb ";
    this->user_name = " user=";
    this->user_password = " password=";
    this->hostaddr = " hostaddr=";
    this->port = " port=";
}

DatabaseInterface::DatabaseInterface(const std::string& user_name, const std::string& user_password, 
	const std::string& hostaddr, const std::string& port)
{
    this->db_name = "dbname=testdb";
    this->user_name = " user=" + user_name;
    this->user_password = " password=" + user_password;
    this->hostaddr = " hostaddr=" + hostaddr;
    this->port = " port=" + port;
    this->connection_string = this->db_name + this->user_name + \
        this->user_password + this->hostaddr + this->port;
}

std::string DatabaseInterface::GetTableCharact(TableType type) 
{
	return this->tables_charact[static_cast<int>(type)];
}

void DatabaseInterface::ContainConnStr(const std::string& user_name, 
    const std::string& user_password, const std::string& hostaddr, const std::string& port)
{
    this->db_name = "dbname=testdb";
    this->user_name = " user=" + user_name;
    this->user_password = " password=" + user_password;
    this->hostaddr = " hostaddr=" + hostaddr;
    this->port = " port=" + port;
    this->connection_string = this->db_name + this->user_name + \
        this->user_password + this->hostaddr + this->port;
}

DatabaseInterface::~DatabaseInterface()
{
}

}    /*namespace database_controller*/
}    /*namespace ssodc*/