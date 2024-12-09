#include "CLEditDB.h"
using namespace std;
CLEditDB::CLEditDB()
{

    LogFile.open("CLEditDBLogFile.txt", std::ios::out);
    ErrFile.open("CLEditDBErrFile.txt", std::ios::out);

    LogFile << "Constructor " << std::endl;

    OnOne = true;

}
CLEditDB::~CLEditDB()
{

    LogFile << "Destructor " << std::endl;

}
void CLEditDB::Driver()
{

    LogFile << "Driver " << std::endl;

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

    LogFile << "Connect " << std::endl;

    try
    {
        con = driver->connect("localhost", "CLEdit", "CLEdit");    //host,user,pass
        con->setSchema(DataBase);
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

    LogFile << "Statement " << std::endl;

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

    LogFile << "Count(*) " << std::endl;

    try
    {
        Query = "";
        Query += "SELECT COUNT(*) AS total FROM ";
        Query += DataBase;
        Query += ".";
        Query += TableName;
        Query += ";";
        res = stmt->executeQuery(Query);
        if (res->next())
        {
            rowcnt = res->getInt("total");
        }
        else
        {
            rowcnt = 0;
        }
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
    }

    LogFile << "Cursor " << std::endl;

    try
    {
        Query = "";
        Query += "SELECT * FROM ";
        Query += DataBase;
        Query += ".";
        Query += TableName;
        Query += ";";
        res = stmt->executeQuery(Query);
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
void CLEditDB::InitInputFile()
{

    LogFile << "Init Input File " << std::endl;

    inputfile[0].IFCode = "";

    for (u = 1; u < 25000; u++)
    {
        inputfile[u] = inputfile[0];
    }

}
void CLEditDB::ToStage()
{

    LogFile << "To Stage " << std::endl;

    UseDb();

    DropTable();

    CreateTable();

    CodeId = 0;
    for (u = 0; u < rowcnt; u++)
    {
        InsertRow();
    }

}
void CLEditDB::UseDb()
{

    LogFile << "UseDb " << std::endl;

    try
    {
        Query = "";
        Query += "USE ";
        Query += DataBase;
        Query += ";";
        stmt->execute(Query);
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
    }

}
void CLEditDB::DropTable()
{

    LogFile << "Drop Table " << std::endl;

    try
    {
        Query = "DROP TABLE IF EXISTS ";
        Query += TableName;
        Query += ";";
        stmt->execute(Query);
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
    }

}
void CLEditDB::CreateTable()
{

    LogFile << "Create Table " << std::endl;

    try
    {
        Query = "";
        Query += "CREATE TABLE ";
        Query += TableName;
        Query += " (idCLEdit INT, CLEditcode VARCHAR(255));";
        stmt->execute(Query);
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
    }

}
void CLEditDB::InsertRow()
{

    if (OnOne)
    {
        LogFile << "Insert Row " << std::endl;
        OnOne = false;
    }

    CodeStr = inputfile[u].IFCode;
    CodeId++;

    try
    {
        sql.str("");
        sql << "INSERT INTO ";
        sql << TableName;
        sql << "(idCLEdit, CLEditcode) VALUES (";
        sql << CodeId << ", '" << CodeStr << "')";
        stmt->execute(sql.str());
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
    }

}
void CLEditDB::FromStage()
{

    LogFile << "From Stage " << std::endl;

    InitInputFile();

    try
    {
        int i = 0;
        while (res->next())
        {
            std::cout << "CLEdit ";
            std::cout << " id "   << res->getInt("idCLEdit");
            std::cout << " line " << res->getString("CLEditcode");
            std::cout << endl;
            inputfile[i].IFCode = res->getString("CLEditcode");
            i++;
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

    LogFile << "Free " << std::endl;

    try
    {
        delete con;
        delete stmt;
        delete pstmt;
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

    LogFile << "Error " << std::endl;

    ErrFile << std::endl;
    ErrFile << "CLEditDB - Error " << errorcode;
    ErrFile << std::endl;
    ErrFile << "# ERR: SQLException in " << __FILE__;
    ErrFile << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
    ErrFile << "# ERR: " << what;
    ErrFile << " (MySQL error code: " << errorcode;
    ErrFile << ", SQLState: " << state << " )" << std::endl;

    exit(abendi);

}
