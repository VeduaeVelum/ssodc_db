#include "FullDB_Interface/TaskPathesTable.hpp"
#include "FullDB_Interface/MapInfoTable.hpp"
#include "FullDB_Interface/TaskInfoTable.hpp"
#include "FullDB_Interface/ClasterStateTable.hpp"

/*int main()
{

	
	return 0;
}*/

int main()
{
	ssodc::database_controller::TaskPathesTable B("test_postgres", "cohondob", "127.0.0.1", "5432");

	B.CreateUser("test_postgres", "cohondob", "127.0.0.1", "5432");
	
    //B.CreateTable(B.GetTableCharact(ssodc::database_controller::TableType::CLUSTER_STATUS));

    //B.InsertToTable(1, "/home/erick_vb/SAVEFILES/task1.txt");
    //B.InsertToTable(2, "/home/erick_vb/SAVEFILES/task2.bmp");
	//B.InsertToTable(3, "/home/erick_vb/SAVEFILES/task3.txt");
	
	//std::cout << B.SelectById(2) << std::endl;

    /*ssodc::utils::ClasterState obj1(1, "3E-5D-3D-5D-AD-2S", 2, 0.55, 8, 0.7, 500);
    ssodc::utils::ClasterState obj2(2, "3D-5D-3D-5D-AD-2S", 3, 0.35, 4, 0.95, 100);
    ssodc::utils::ClasterState obj3(3, "3B-5D-3D-5D-AD-2S", 2, 0.55, 8, 0.8, 200);
    ssodc::utils::ClasterState obj4(4, "3A-5D-3D-5D-AD-2S", 1, 0.7, 4, 0.9, 50);*/
    
    //B.InsertToTable(obj1);
    //B.InsertToTable(obj2);
    //B.InsertToTable(obj3);

    std::map<int, std::string> objects1 = B.SelectFromTable();

    for (auto it = objects1.begin(); it != objects1.end(); ++it)
    {
        std::cout << (*it).first<< " : " << (*it).second << std::endl;
    }
    
    std::cout << "\n-----------------------------\n";

    /*B.UpdateTable(obj2.GetId(),obj4);

    ssodc::utils::ClasterState temp = B.SelectById(obj2.GetId());

    std::cout << temp.GetId() << " : " << temp.GetMacAddress() << " : ";
    std::cout << temp.GetCpuFreq() << " : " << temp.GetCpuWorkload() << " : ";
    std::cout << temp.GetRamWorkload() << " : " << temp.GetRomFreespace() << std::endl;

    B.DeleteFromTable(obj2.GetId());

    std::cout << "\n-----------------------------\n";

    std::list<ssodc::utils::ClasterState> objects2 = B.SelectFromTable();

    for (auto it = objects2.begin(); it != objects2.end(); ++it)
    {
        std::cout << (*it).GetId() << " : " << (*it).GetMacAddress() << " : ";
        std::cout << (*it).GetCpuFreq() << " : " << (*it).GetCpuWorkload() << " : ";
        std::cout << (*it).GetRamWorkload() << " : " << (*it).GetRomFreespace() << std::endl;
    }*/

    //B.DropTable();

    return 0;
}