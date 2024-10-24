#include "CLEditDB.h"
using namespace std;
CLEditDB::CLEditDB()
{
    std::cout << std::endl;
    std::cout << "Running CLEditDB - Constructor";
    std::cout << std::endl;
}

CLEditDB::~CLEditDB()
{
    std::cout << std::endl;
    std::cout << "Running CLEditDB - Destructor";
    std::cout << std::endl;
}
void CLEditDB::Driver()
{
    std::cout << std::endl;
    std::cout << "Running CLEditDB - Driver";
    std::cout << std::endl;

    try
    {
        driver = get_driver_instance();
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
    }

}
void CLEditDB::Connect()
{
    std::cout << std::endl;
    std::cout << "Running CLEditDB - Connect";
    std::cout << std::endl;
    try
    {
        con = driver->connect("localhost", "root", "root");
        con->setSchema("mydb");
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
    }

}
void CLEditDB::Statement()
{
    std::cout << std::endl;
    std::cout << "Running CLEditDB - Statement";
    std::cout << std::endl;
    try
    {
        stmt = con->createStatement();
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
    }

}
int CLEditDB::Cursor()
{
    std::cout << std::endl;
    std::cout << "Running CLEditDB - Cursor count";
    std::cout << std::endl;
    try
    {
        res = stmt->executeQuery("SELECT COUNT(*) FROM mydb.CLEdit ");
        //rowcnt = ROW_RESULT;
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
    }

    std::cout << std::endl;
    std::cout << "Running CLEditDB - Cursor select";
    std::cout << std::endl;
    try
    {
        res = stmt->executeQuery("SELECT * FROM mydb.CLEdit ");
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
    }

    return rowcnt;
}
void CLEditDB::Process()
{
    std::cout << std::endl;
    std::cout << "Running CLEditDB - Process";
    std::cout << std::endl;
    try
    {
        while (res->next())
        {
            std::cout << "CLEdit ";
            std::cout << " id "      << res->getInt("idCLEdit");
            std::cout << " line " << res->getString("CLEditcol");
            std::cout << endl;
        }
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
    }

}
void CLEditDB::Free()
{
    std::cout << std::endl;
    std::cout << "Running CLEditDB - Free";
    std::cout << std::endl;

    try
    {
        delete con;
        delete stmt;
        delete res;
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
    }
}
void CLEditDB::Error()
{
    std::cout << std::endl;
    std::cout << "Running CLEditDB - Error " << errorcode;
    std::cout << std::endl;
    std::cout << "# ERR: SQLException in " << __FILE__;
    std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
    std::cout << "# ERR: " << what;
    std::cout << " (MySQL error code: " << errorcode;
    std::cout << ", SQLState: " << state << " )" << std::endl;

    exit(abendi);

}
