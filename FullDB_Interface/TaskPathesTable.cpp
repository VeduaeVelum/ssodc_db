#include <stdlib.h>
#include "TaskPathesTable.hpp"

namespace ssodc {
namespace database_controller {

TaskPathesTable::TaskPathesTable() : DatabaseInterface()
{
}

TaskPathesTable::TaskPathesTable(const std::string& user_name, const std::string& user_password, 
	const std::string& hostaddr, const std::string& port) : DatabaseInterface(user_name, user_password, hostaddr, port)
{
    this->ContainConnStr(user_name, user_password, hostaddr, port);
    try
    {
        this->m_connection = std::unique_ptr<pqxx::connection>(
            new pqxx::connection(this->connection_string));

        if(!this->m_connection->is_open()) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)

        }
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)    
            this->m_connection->disconnect();
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what) 
        this->m_connection->disconnect();
    }
}
void TaskPathesTable::CreateUser(const std::string& user_name, const std::string& user_password, 
    const std::string& hostaddr, const std::string& port)
{
    this->ContainConnStr(user_name, user_password, hostaddr, port);

    try 
    {
        this->m_connection = std::unique_ptr<pqxx::connection>(
            new pqxx::connection(this->connection_string));
        if(!this->m_connection->is_open()) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
            return;
        }
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
            this->m_connection->disconnect();
            return;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        this->m_connection->disconnect();
        return;
    }
}
void TaskPathesTable::CreateTable(const std::string& table_charact)
{
    try
    {
        if(!this->m_connection->is_open()) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
            return;
        }
        pqxx::work W(*this->m_connection);
        W.exec(table_charact);
        W.commit();
        std::cout << "Table created successfully" << std::endl;
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
            this->m_connection->disconnect();
            return;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        this->m_connection->disconnect();
        return;
    }
}
void TaskPathesTable::InsertToTable(UCI ID, const std::string& table_info) //SIC
{
    try
    {
        std::string str_ID = std::to_string(ID);
        this->sql_command = "INSERT INTO " + this->tables_names[0] + 
            " (ID,SOURCE_PATH) VALUES(" + str_ID + ", '" + table_info + "'); ";

        if(!this->m_connection->is_open()) 
        {
            return;
        }
        pqxx::work W(*this->m_connection);
        W.exec(this->sql_command);
        W.commit();
        std::cout << "Records created successfully" << std::endl;
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
            this->m_connection->disconnect();
            return;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        this->m_connection->disconnect();
        return;
    }
}
std::map<int, std::string> TaskPathesTable::SelectFromTable()
{
    std::map<int, std::string> pathes;
    try
    {
        if(!this->m_connection->is_open()) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
            return pathes;
        }
        this->sql_command = "SELECT * from " + this->tables_names[0];
        pqxx::nontransaction N(*this->m_connection);
    
        pqxx::result R(N.exec(this->sql_command));
     
        for (auto c = R.begin(); c != R.end(); c++) 
        {
            pathes[c[0].as<int>()] = c[1].as<std::string>();
        }
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
            this->m_connection->disconnect();
            return pathes;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        this->m_connection->disconnect();
        return pathes;
    }

    return pathes;
}
std::string TaskPathesTable::SelectById(UCI ID)
{
    std::string ret_str;
    try
    {
        std::string str_ID = std::to_string(ID);
        if(!this->m_connection->is_open()) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
            return NULL;
        }
        this->sql_command = "SELECT * from " + this->tables_names[0] + 
            + " where ID=" + str_ID;

        pqxx::nontransaction N(*this->m_connection);    
        pqxx::result R(N.exec(this->sql_command));

        pqxx::result::const_iterator c = R.begin();                
        ret_str = c[1].as<std::string>();
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
            this->m_connection->disconnect();
            return NULL;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        this->m_connection->disconnect();
        return NULL;
    }
    return ret_str;
}
void TaskPathesTable::UpdateTable(const std::string& changing_info, UCI ID) 
{
    try
    {
        std::string str_ID = std::to_string(ID);
        if(!this->m_connection->is_open()) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
            return;
        }
        pqxx::work W(*this->m_connection);
        this->sql_command = "UPDATE " + this->tables_names[0] + \
            " set SOURCE_PATH = '" + changing_info + "' where ID = " + str_ID;
        W.exec(this->sql_command);
        W.commit();
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
            this->m_connection->disconnect();
            return;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        this->m_connection->disconnect();
        return;
    }     
}
void TaskPathesTable::DeleteFromTable(UCI ID)
{
    try
    {
        std::string str_ID = std::to_string(ID);
        if(!this->m_connection->is_open()) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
        }
        pqxx::work W(*this->m_connection);
        this->sql_command = "DELETE from " + this->tables_names[0] 
            + " where ID=" + str_ID;
        W.exec(sql_command);
        W.commit();
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        exit(EXIT_FAILURE);
    }
}

void TaskPathesTable::DropTable()
{
    try
    {
        if(!this->m_connection->is_open()) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
            return;
        }
        pqxx::work W(*this->m_connection);
        this->sql_command = "DROP TABLE " + this->tables_names[0];
        W.exec(sql_command);
        W.commit();
    }
    catch(const pqxx::pqxx_exception &e)
    {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *sql = dynamic_cast<const pqxx::sql_error *>(&e.base());
        if(sql) 
        {
            std::cerr << "Query was: " << sql->query() << std::endl;
            //TODO: log system error(log sql server error)
            //TODO: subalert system error(send sql server error)
            this->m_connection->disconnect();
            return;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        this->m_connection->disconnect();
        return;
    }
}

void TaskPathesTable::Connect_to_()
{
    this->m_connection = std::unique_ptr<pqxx::connection>(
        new pqxx::connection(this->connection_string));
}
void TaskPathesTable::Disconnect_from_()
{
    this->m_connection->disconnect();
}

TaskPathesTable::~TaskPathesTable()
{
    this->m_connection->disconnect();
}

}    /*namespace database_controller*/
}    /*namespace ssodc*/
