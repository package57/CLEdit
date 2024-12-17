#include "CLEditDB.h"
using namespace std;
CLEditDB::CLEditDB()
{
    //ctor
}
CLEditDB::~CLEditDB()
{
    //dtor
}
int CLEditDB::Bind()
{

    Initialize();

    if  (abendi != 0)
    {
        return abendi;
    }

    Driver();

    if  (abendi != 0)
    {
        return abendi;
    }

    Connect();

    if  (abendi != 0)
    {
        return abendi;
    }

    Statement();

    if  (abendi != 0)
    {
        return abendi;
    }

    return abendi;

}
void CLEditDB::Initialize()
{
    abendi = 0;

    OpenLog();

    OpenErr();

    LogFile << "Initialize " << std::endl;

    OnOne = true;

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
        abendi = 3500;
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
        abendi = 3501;
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
        abendi = 3502;
    }

}
int CLEditDB::Count()
{

    start_s = clock();

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
        abendi = 3503;
    }

    stop_s = clock();

    action = "Count ";

    LogFile << action << "elapsed time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

    return rowcnt;

}
void CLEditDB::Cursor()
{

    start_s = clock();

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
        abendi = 3504;
    }

    stop_s = clock();

    action = "Cursor ";

    LogFile << action << "elapsed time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

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

    start_s = clock();

    LogFile << "To Stage " << std::endl;

    UseDb();

    DropTable();

    CreateTable();

    CodeId = 0;
    for (u = 0; u < rowcnt; u++)
    {
        InsertRow();
    }

    stop_s = clock();

    action = "To Stage ";

    LogFile << action << "elapsed time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

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
        abendi = 3505;
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
        abendi = 3506;
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
        Query += " (id INT, code VARCHAR(255));";
        stmt->execute(Query);
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
        abendi = 3507;
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
    CodeStrl = CodeStr.length();
    CodeNew = "";

    for (i = 0; i < CodeStrl; i++)
    {
        FixQuote();
    }

    CodeStr = "";
    CodeStr = CodeNew;
    CodeId++;

    try
    {
        sql.str("");
        sql << "INSERT INTO ";
        sql << TableName;
        sql << "(id, code) VALUES (";
        sql << CodeId << ", '" << CodeStr << "')";
        stmt->execute(sql.str());
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
        abendi = 3508;
    }

}
void CLEditDB::FixQuote()
{

    if (CodeStr[i] == '\'')
    {
    //  add an extra quote
        CodeNew += CodeStr[i];
        CodeNew += '\'';
    }
    else
    {
    //  just copy the byte
        CodeNew += CodeStr[i];
    }

}
void CLEditDB::FromStage()
{

    start_s = clock();

    LogFile << "From Stage " << std::endl;

    InitInputFile();

    try
    {
        int i = 0;
        while (res->next())
        {
            LogFile << "CLEdit ";
            LogFile << " id "   << res->getInt("id");
            LogFile << " code " << res->getString("code");
            LogFile << std::endl;
            inputfile[i].IFCode = res->getString("code");
            i++;
        }
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
        abendi = 3509;
    }

    stop_s = clock();

    action = "From Stage ";

    LogFile << action << "elapsed time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

}
void CLEditDB::Free()
{

    LogFile << "Free " << std::endl;

    Freecon();

    Freestmt();

    Freepstmt();

    Freeres();

    CloseLog();

    CloseErr();

}
void CLEditDB::Freecon()
{

    LogFile << "Free con " << std::endl;

    try
    {
        delete con;
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
        abendi = 3510;
    }

}
void CLEditDB::Freestmt()
{

    LogFile << "Free stmt " << std::endl;

    try
    {
        delete stmt;
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
        abendi = 3511;
    }

}
void CLEditDB::Freepstmt()
{

    LogFile << "Free pstmt " << std::endl;

    try
    {
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
        abendi = 3512;
    }

}
void CLEditDB::Freeres()
{

    LogFile << "Free res " << std::endl;

    try
    {
        delete res;
    }
    catch (sql::SQLException &e)
    {
        errorcode = e.getErrorCode();
        what = e.what();
        state = e.getSQLState();
        Error();
        abendi = 3513;
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

//  exit(abendi);

}
void CLEditDB::OpenLog()
{

    LogFile.open("CLEditDBLogFile.txt", ios_base::out | ios_base::app);

    if  (!LogFile.is_open())
    {
        msg = "Log file Open error";
        abendi = 3514;
        std::cout << msg << abendi << std::endl;    // better than flying blind
        return;
    }

    bytecnt = LogFile.tellg();

    if  (bytecnt > FILE_SIZE)
    {
        CloseLog();
        OpenLogn();
    }

    LogFile << "Log file size " << to_string(bytecnt) << std::endl;

}
void CLEditDB::OpenLogn()
{

    LogFile.open("CLEditDBLogFile.txt", ios_base::out);

    if  (!LogFile.is_open())
    {
        msg = "Log file Open error";
        abendi = 3515;
        std::cout << msg << abendi << std::endl;    // better than flying blind
        return;
    }

}
void CLEditDB::CloseLog()
{

    LogFile.close();

}
void CLEditDB::OpenErr()
{
    ErrFile.open("CLEditDBErrFile.txt", std::ios::out | ios_base::app);

    if  (!ErrFile.is_open())
    {
        msg = "Error file Open error";
        abendi = 3516;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

    bytecnt = ErrFile.tellg();

    if  (bytecnt > FILE_SIZE)
    {
        CloseErr();
        OpenErrn();
    }

    LogFile << "Error file size " << to_string(bytecnt) << std::endl;

}
void CLEditDB::OpenErrn()
{
    ErrFile.open("CLEditDBErrFile.txt", std::ios::out);

    if  (!ErrFile.is_open())
    {
        msg = "Error file Open error";
        abendi = 3517;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

}
void CLEditDB::CloseErr()
{

    ErrFile.close();

}
