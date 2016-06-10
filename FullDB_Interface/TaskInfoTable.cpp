#include <stdlib.h>
#include "TaskInfoTable.hpp"

namespace ssodc {
namespace database_controller {

TaskInfoTable::TaskInfoTable() : DatabaseInterface()
{
}

TaskInfoTable::TaskInfoTable(const std::string& user_name, const std::string& user_password, 
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
void TaskInfoTable::create_user(const std::string& user_name, const std::string& user_password, 
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
void TaskInfoTable::create_table(const std::string& table_charact)
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
void TaskInfoTable::insert_to_table(ssodc::utils::TaskInfo& task_info_obj)
{
    try
    {
        std::string str_ID = std::to_string(task_info_obj.GetId());
        std::string str_type = std::to_string(static_cast<int>(task_info_obj.GetType()));
        std::string str_status = std::to_string(static_cast<int>(task_info_obj.GetStatus()));

        this->sql_command = "INSERT INTO " + this->tables_names[1] + 
            " (ID,TASK_TYPE,TASK_STATUS,SOURCE_PATH,CODE_PATH,EXEC_PATH)" +
            " VALUES(" + str_ID + ", " + str_type + ", " + str_status + ", '" +
            task_info_obj.GetDataPath() + "', '" + task_info_obj.GetCodePath() + 
            "', '" + task_info_obj.GetExecutablePath() + "'); ";

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
std::list<ssodc::utils::TaskInfo> TaskInfoTable::select_from_table()
{
    std::list<ssodc::utils::TaskInfo> task_info_list;
    ssodc::utils::TaskInfo temp;
    try
    {
        if(!this->m_connection->is_open()) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
            return task_info_list;
        }
        this->sql_command = "SELECT * from " + this->tables_names[1];
        pqxx::nontransaction N(*this->m_connection);
    
        pqxx::result R(N.exec(this->sql_command));
     
        for (auto c = R.begin(); c != R.end(); c++) 
        {
            temp.SetId(c[0].as<int>());
            temp.SetType(static_cast<ssodc::utils::TaskType>(c[1].as<int>()));
            temp.SetStatus(static_cast<ssodc::utils::TaskStatus>(c[2].as<int>()));
            temp.SetDataPath(c[3].as<std::string>());
            temp.SetCodePath(c[4].as<std::string>());
            temp.SetExecutablePath(c[5].as<std::string>());
            task_info_list.push_back(temp);
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
            return task_info_list;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        this->m_connection->disconnect();
        return task_info_list;
    }

    return task_info_list;
}
ssodc::utils::TaskInfo TaskInfoTable::select_by_id(UCI ID)
{
    std::string ret_str;
    ssodc::utils::TaskInfo task_info_obj;
    try
    {
        std::string str_ID = std::to_string(ID);
        if(!this->m_connection->is_open()) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
            return task_info_obj;
        }
        this->sql_command = "SELECT * from " + this->tables_names[1] + 
            + " where ID=" + str_ID;

        pqxx::nontransaction N(*this->m_connection);    
        pqxx::result R(N.exec(this->sql_command));

        pqxx::result::const_iterator c = R.begin();
        task_info_obj.SetId(c[0].as<int>());
        task_info_obj.SetType(static_cast<ssodc::utils::TaskType>(c[1].as<int>()));
        task_info_obj.SetStatus(static_cast<ssodc::utils::TaskStatus>(c[2].as<int>()));
        task_info_obj.SetDataPath(c[3].as<std::string>());
        task_info_obj.SetCodePath(c[4].as<std::string>());
        task_info_obj.SetExecutablePath(c[5].as<std::string>());                
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
            return task_info_obj;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        this->m_connection->disconnect();
        return task_info_obj;
    }
    return task_info_obj;
}
void TaskInfoTable::update_table(UCI ID, ssodc::utils::TaskInfo& task_info_obj)
{
    try
    {
        std::string str_ID = std::to_string(ID);
        std::string str_type = std::to_string(static_cast<int>(task_info_obj.GetType()));
        std::string str_status = std::to_string(static_cast<int>(task_info_obj.GetStatus()));
        if(!this->m_connection->is_open()) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
            return;
        }
        pqxx::work W(*this->m_connection);
        this->sql_command = "UPDATE " + this->tables_names[1] + 
            " set TASK_TYPE = " + str_type + ", TASK_STATUS = " + str_status +
            ", SOURCE_PATH = '" + task_info_obj.GetDataPath() + 
            "', CODE_PATH = '" + task_info_obj.GetCodePath() + 
            "', EXEC_PATH = '" + task_info_obj.GetExecutablePath() + 
            "' where ID = " + str_ID;

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
void TaskInfoTable::delete_from_table(UCI ID)
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
        this->sql_command = "DELETE from " + this->tables_names[1] 
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

void TaskInfoTable::drop_table()
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
        this->sql_command = "DROP TABLE " + this->tables_names[1];
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

void TaskInfoTable::Connect_to_()
{
    this->m_connection = std::unique_ptr<pqxx::connection>(
        new pqxx::connection(this->connection_string));
}
void TaskInfoTable::Disconnect_from_()
{
    this->m_connection->disconnect();
}

TaskInfoTable::~TaskInfoTable()
{
    this->m_connection->disconnect();
}

}    /*namespace database_controller*/
}    /*namespace ssodc*/
