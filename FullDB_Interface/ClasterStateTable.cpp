#include <stdlib.h>
#include "ClasterStateTable.hpp"

namespace ssodc {
namespace database_controller {

ClasterStateTable::ClasterStateTable() : DatabaseInterface()
{
}

ClasterStateTable::ClasterStateTable(const std::string& user_name, const std::string& user_password, 
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
void ClasterStateTable::CreateUser(const std::string& user_name, const std::string& user_password, 
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
void ClasterStateTable::CreateTable(const std::string& table_charact)
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
void ClasterStateTable::InsertToTable(ssodc::utils::ClasterState& claster_state_obj)
{
    try
    {
        std::string str_ID = std::to_string(claster_state_obj.GetId());
        std::string str_cpu_freq = std::to_string(claster_state_obj.GetCpuFreq());
        std::string str_cpu_workload = std::to_string(claster_state_obj.GetCpuWorkload());
        std::string str_ram = std::to_string(claster_state_obj.GetRam());
        std::string str_ram_worload = std::to_string(claster_state_obj.GetRamWorkload());        
        std::string str_rom_free = std::to_string(claster_state_obj.GetRomFreespace());

        this->sql_command = "INSERT INTO " + this->tables_names[3] + 
            " (ID,MAC_ADDRESS,CPU_FREQ,CPU_WORKLOAD,RAM,RAM_WORKLOAD,ROM_FREESPACE)" +
            " VALUES(" + str_ID + ", '" + claster_state_obj.GetMacAddress() + 
            "', " + str_cpu_freq + ", " + str_cpu_workload + ", " + str_ram + 
            ", " + str_ram_worload +  ", " + str_rom_free + "); ";

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
std::list<ssodc::utils::ClasterState> ClasterStateTable::SelectFromTable()
{
    std::list<ssodc::utils::ClasterState> claster_state_list;
    ssodc::utils::ClasterState temp;
    try
    {
        if(!this->m_connection->is_open()) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
            return claster_state_list;
        }
        this->sql_command = "SELECT * from " + this->tables_names[3];
        pqxx::nontransaction N(*this->m_connection);
    
        pqxx::result R(N.exec(this->sql_command));
     
        for (auto c = R.begin(); c != R.end(); c++) 
        {
            temp.SetId(c[0].as<int>());
            temp.SetMacAddress(c[1].as<std::string>());
            temp.SetCpuFreq(c[2].as<int>());
            temp.SetCpuWorkload(c[3].as<double>());
            temp.SetRam(c[4].as<int>());
            temp.SetRamWorkload(c[5].as<double>());
            temp.SetRomFreespace(c[6].as<int>());
            claster_state_list.push_back(temp);
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
            return claster_state_list;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        this->m_connection->disconnect();
        return claster_state_list;
    }

    return claster_state_list;
}
ssodc::utils::ClasterState ClasterStateTable::SelectById(UCI ID)
{
    std::string ret_str;
    ssodc::utils::ClasterState claster_state_obj;
    try
    {
        std::string str_ID = std::to_string(ID);
        if(!this->m_connection->is_open()) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
            return claster_state_obj;
        }
        this->sql_command = "SELECT * from " + this->tables_names[3] + 
            + " where ID=" + str_ID;

        pqxx::nontransaction N(*this->m_connection);    
        pqxx::result R(N.exec(this->sql_command));

        pqxx::result::const_iterator c = R.begin();
        claster_state_obj.SetId(c[0].as<int>());
        claster_state_obj.SetMacAddress(c[1].as<std::string>());
        claster_state_obj.SetCpuFreq(c[2].as<int>());
        claster_state_obj.SetCpuWorkload(c[3].as<double>());
        claster_state_obj.SetRam(c[4].as<int>());
        claster_state_obj.SetRamWorkload(c[5].as<double>());
        claster_state_obj.SetRomFreespace(c[6].as<int>());               
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
            return claster_state_obj;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        //TODO: log system error(set e.what to log source)
        //TODO: subalert system error(send e.what)
        this->m_connection->disconnect();
        return claster_state_obj;
    }
    return claster_state_obj;
}
void ClasterStateTable::UpdateTable(UCI ID, ssodc::utils::ClasterState& claster_state_obj)
{
    try
    {
        std::string str_ID = std::to_string(ID);
        std::string str_cpu_freq = std::to_string(claster_state_obj.GetCpuFreq());
        std::string str_cpu_workload = std::to_string(claster_state_obj.GetCpuWorkload());
        std::string str_ram = std::to_string(claster_state_obj.GetRam());
        std::string str_ram_worload = std::to_string(claster_state_obj.GetRamWorkload());        
        std::string str_rom_free = std::to_string(claster_state_obj.GetRomFreespace());

        if(!this->m_connection->is_open()) 
        {
            //TODO: log system error(set db opening error to log source)
            //TODO: subalert system error(send opening error)
            return;
        }

        pqxx::work W(*this->m_connection);
        this->sql_command = "UPDATE " + this->tables_names[3] + 
            " set MAC_ADDRESS = '" + claster_state_obj.GetMacAddress() + 
            "', CPU_FREQ = " + str_cpu_freq +
            ", CPU_WORKLOAD = " + str_cpu_workload + 
            ", RAM = " + str_ram + 
            ", RAM_WORKLOAD = " + str_ram_worload + 
            ", ROM_FREESPACE = " + str_rom_free +
            " where ID = " + str_ID;

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
void ClasterStateTable::DeleteFromTable(UCI ID)
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
        this->sql_command = "DELETE from " + this->tables_names[3] 
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
void ClasterStateTable::DropTable()
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
        this->sql_command = "DROP TABLE " + this->tables_names[3];
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

void ClasterStateTable::Connect_to_()
{
    this->m_connection = std::unique_ptr<pqxx::connection>(
        new pqxx::connection(this->connection_string));
}
void ClasterStateTable::Disconnect_from_()
{
    this->m_connection->disconnect();
}

ClasterStateTable::~ClasterStateTable()
{
    this->m_connection->disconnect();
}

}    /*namespace database_controller*/
}    /*namespace ssodc*/
