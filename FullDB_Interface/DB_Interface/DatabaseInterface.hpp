#pragma once 

#include <string>

namespace ssodc {
namespace database_controller {

const int NUM_OF_CHARACT = 5;
const int NUM_OF_TABLES = 5;

typedef unsigned const int UCI;

enum TableType {
    MAIN_TASKS = 0,
    TASK_INFO,
    PICTURE_MAP,
    CLUSTER_STATUS,
    SUB_ALERTS
};

class DatabaseInterface 
{
protected:

    const std::string tables_names[NUM_OF_TABLES] = { "MAIN_TASKS",
        "TASK_INFO",
        "PICTURE_MAP",
        "CLUSTER_STATUS",
        "SUB_ALERTS"
    };

    const std::string tables_charact[NUM_OF_TABLES] = { 
        "CREATE TABLE MAIN_TASKS("  \
        "ID INT PRIMARY KEY     NOT NULL," \
        "SOURCE_PATH    CHAR(80) );",

        "CREATE TABLE TASK_INFO(" \
        "ID INT PRIMARY KEY     NOT NULL," \
        "TASK_TYPE INT," \
        "TASK_STATUS INT," \
        "SOURCE_PATH    CHAR(80)," \
        "CODE_PATH    CHAR(80)," \
        "EXEC_PATH    CHAR(80) );",

        "CREATE TABLE PICTURE_MAP(" \
        "ID INT PRIMARY KEY     NOT NULL," \
        "SOURCE_PATH    CHAR(80),"
        "X0 INT, "
        "Y0 INT,"
        "X1 INT,"
        "Y1 INT );",

        "CREATE TABLE CLUSTER_STATUS(" \
        "ID INT PRIMARY KEY     NOT NULL," \
        "MAC_ADDRESS    CHAR(18)," \
        "CPU_FREQ INT," \
        "CPU_WORKLOAD DECIMAL," \
        "RAM INT," \
        "RAM_WORKLOAD DECIMAL," \
        "ROM_FREESPACE INT );", 

        "CREATE TABLE SUB_ALERTS(" \
        "ID INT PRIMARY KEY     NOT NULL," \
        "ORIGIN    CHAR(30)," \
        "TYPE    CHAR(30)," \
        "PRIORITY    CHAR(30)," \
        "SEVERITY    CHAR(30)," \
        "STATE    CHAR(30)," \
        "DAY INT," \
        "MONTH INT," \
        "YEAR INT," \
        "SEC INT," \
        "MIN INT," \
        "HOUR INT," \
        "MESSAGE    CHAR(300)," 
    };

    std::string db_name;
    std::string user_name;
    std::string user_password;
    std::string hostaddr;
    std::string port;
    std::string connection_string;
    std::string sql_command;

public:    

    DatabaseInterface();
    DatabaseInterface(const std::string&, const std::string&, const std::string&, const std::string&);

    virtual void CreateUser(const std::string&, const std::string&, const std::string&, const std::string&) = 0;
    virtual void CreateTable(const std::string&) = 0;
    virtual void DeleteFromTable(UCI) = 0;
    virtual void DropTable() = 0;

    virtual void Connect_to_() = 0;
    virtual void Disconnect_from_() = 0;

    std::string GetTableCharact(TableType); 
    void ContainConnStr(const std::string&, const std::string&, const std::string&, const std::string&);

    virtual ~DatabaseInterface();
    //TODO: point rotation
};

}    /*namespace database_controller*/
}    /*namespace ssodc*/