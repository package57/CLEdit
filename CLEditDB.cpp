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

    if  (abend)
    {
        return abendi;
    }

    if (Logging)
    {
        LogFile << "Bind " << std::endl;
    }

    start_s = std::clock();

    Driver();

    if  (abend)
    {
        return abendi;
    }

    Connect();

    if  (abend)
    {
        return abendi;
    }

    Statement();

    if  (abend)
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

    OpenStat();

    if (Logging)
    {
        LogFile << "Initialize " << std::endl;
    }

    OnOne = true;

}
void CLEditDB::Driver()
{

    if (Logging)
    {
        LogFile << "Driver " << std::endl;
    }

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
        abend = true;
    }

}
void CLEditDB::Connect()
{

    if (Logging)
    {
        LogFile << "Connect " << std::endl;
    }

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
        abend = true;
    }

}
void CLEditDB::Statement()
{

    if (Logging)
    {
        LogFile << "Statement " << std::endl;
    }

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
        abend = true;
    }

}
int CLEditDB::Count()
{

    if (Logging)
    {
        LogFile << "Count " << std::endl;
    }

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
        abend = true;
    }

    return rowcnt;

}
void CLEditDB::Cursor()
{

    if (Logging)
    {
        LogFile << "Cursor " << std::endl;
    }

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
        abend = true;
    }

}
void CLEditDB::InitInputFile()
{

    if (Logging)
    {
        LogFile << "InitInputFile " << std::endl;
    }

    inputfile[0].IFCode = "";

    for (u = 1; u < 25000; u++)
    {
        inputfile[u] = inputfile[0];
    }

}
void CLEditDB::ToStage()
{

    if (Logging)
    {
        LogFile << "ToStage " << std::endl;
    }

    currentdatetime = std::time(nullptr);

    StatFile << "Welcome " << std::ctime(& currentdatetime);

    if (Mode == "tostage")
    {
        StatFile << "Command tostage " << DataBase << " " << TableName << std::endl;
    }

    if (Mode == "createtable")
    {
        StatFile << "Command createtable " << DataBase << " " << TableName << std::endl;
    }

    StatFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;

    UseDb();

    DropTable();

    CreateTable();

    CodeId = 0;
    for (u = 0; u < rowcnt; u++)
    {
        InsertRow();
    }

    StatFile << "RowCnt " << rowcnt << std::endl;

    stop_s = std::clock();

    StatFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

}
void CLEditDB::UseDb()
{

    if (Logging)
    {
        LogFile << "UseDb " << std::endl;
    }

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
        abend = true;
    }

}
void CLEditDB::DropTable()
{

    if (Logging)
    {
        LogFile << "DropTable " << std::endl;
    }

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
        abend = true;
    }

}
void CLEditDB::CreateTable()
{

    if (Logging)
    {
        LogFile << "CreateTable " << std::endl;
    }

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
        abend = true;
    }

}
void CLEditDB::InsertRow()
{

    if (OnOne)
    {
        if (Logging)
        {
            LogFile << "InsertRow " << std::endl;
        }
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
        abend = true;
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

    if (Logging)
    {
        LogFile << "FromStage " << std::endl;
    }

    currentdatetime = std::time(nullptr);

    StatFile << "Welcome " << std::ctime(& currentdatetime);

//  start_s = std::clock();     moved to Bind(), FromStage() is Bind(), Count(), Cursor() and FromStage()

    StatFile << "Command fromstage " << DataBase << " " << TableName << std::endl;

    StatFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;

    InitInputFile();

    try
    {
        int i = 0;
        while (res->next())
        {
            if (Logging)
            {
                LogFile << "CLEdit ";
                LogFile << " id "   << res->getInt("id");
                LogFile << " code " << res->getString("code");
                LogFile << std::endl;
            }
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
        abend = true;
    }

    StatFile << "RowCnt " << rowcnt << std::endl;

    stop_s = std::clock();

    StatFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

}
void CLEditDB::Free()
{

    if (Logging)
    {
        LogFile << "Free " << std::endl;
    }

    Freecon();

    Freestmt();

    Freepstmt();

    Freeres();

    CloseLog();

    CloseErr();

}
void CLEditDB::Freecon()
{

    if (Logging)
    {
        LogFile << "Freecon " << std::endl;
    }

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
        abend = true;
    }

}
void CLEditDB::Freestmt()
{

    if (Logging)
    {
        LogFile << "Freestmt " << std::endl;
    }

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
        abend = true;
    }

}
void CLEditDB::Freepstmt()
{

    if (Logging)
    {
        LogFile << "Freepstmt " << std::endl;
    }

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
        abend = true;
    }

}
void CLEditDB::Freeres()
{

    if (Logging)
    {
        LogFile << "Freeres " << std::endl;
    }

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
        abend = true;
    }

}
void CLEditDB::Error()
{

    if (Logging)
    {
        LogFile << "Error " << std::endl;
    }

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

    LogFile.open("CLEditDBLog.txt", ios_base::out | ios_base::app);

    if  (!LogFile.is_open())
    {
        msg = "Log file Open error";
        abendi = 3514;
        abend = true;
        std::cout << msg << abendi << std::endl;    // better than flying blind
        return;
    }

    bytecnt = LogFile.tellg();

    if  (bytecnt > FILE_SIZE)
    {
        CloseLog();

        OpenLogn();
    }

    if (Logging)
    {
        LogFile << "Log file size " << to_string(bytecnt) << std::endl;
    }

}
void CLEditDB::OpenLogn()
{

    LogFile.open("CLEditDBLog.txt", ios_base::out);

    if  (!LogFile.is_open())
    {
        msg = "Log file Open error";
        abendi = 3515;
        abend = true;
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
    ErrFile.open("CLEditDBErr.txt", std::ios::out | ios_base::app);

    if  (!ErrFile.is_open())
    {
        msg = "Error file Open error";
        abendi = 3516;
        abend = true;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

    bytecnt = ErrFile.tellg();

    if  (bytecnt > FILE_SIZE)
    {
        CloseErr();
        OpenErrn();
    }

    if (Logging)
    {
        LogFile << "Error file size " << to_string(bytecnt) << std::endl;
    }

}
void CLEditDB::OpenErrn()
{
    ErrFile.open("CLEditDBErr.txt", std::ios::out);

    if  (!ErrFile.is_open())
    {
        msg = "Error file Open error";
        abendi = 3517;
        abend = true;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

}
void CLEditDB::CloseErr()
{

    ErrFile.close();

}
void CLEditDB::OpenStat()
{
    StatFile.open("CLEditDBStat.txt", std::ios::out | ios_base::app);

    if  (!StatFile.is_open())
    {
        msg = "Stat file Open error";
        abendi = 3516;
        abend = true;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

    bytecnt = StatFile.tellg();

    if  (bytecnt > FILE_SIZE)
    {
        CloseStat();
        ETL.Logging = Logging;
        ETL.fileiname = "CLEditDBStat.txt";
        rc = ETL.ETL();
        OpenStatn();
    }

    if (Logging)
    {
        LogFile << "Stat file size " << to_string(bytecnt) << std::endl;
    }

}
void CLEditDB::OpenStatn()
{
    StatFile.open("CLEditDBStat.txt", std::ios::out);

    if  (!StatFile.is_open())
    {
        msg = "Stat file Open Stator";
        abendi = 3517;
        abend = true;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

}
void CLEditDB::CloseStat()
{

    StatFile.close();

}

