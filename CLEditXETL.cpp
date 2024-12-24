#include "CLEditXETL.h"
using namespace std;
CLEditXETL::CLEditXETL()
{
    // constructor
}
CLEditXETL::~CLEditXETL()
{
    // destructor
}
int CLEditXETL::ETL()
{

//  init
    Init();

    if (abend)
    {
        return abendi;
    }
// 	open file
    OpenFile();

    if (abend)
    {
        return abendi;
    }

    LogFile << "ETL " << std::endl;

// 	bind and connect to database
    Bind();

    if (abend)
    {
        return abendi;
    }

// read byte by byte
    ReadFile();
// loop,process until end of file, aka eof
    while (fileitellg > 0)  // at end of file the read returns -1
    {
        ProcessFile();
    }

// 	Free the database reqources
    Free();

    if (abend)
    {
        return abendi;
    }

// eop
// 	close log file
    EoP();

    return abendi;

}
void CLEditXETL::Init()
{

    start_s = std::clock();

    OpenLog();

    if (abend)
    {
        return;
    }

    LogFile << "Init " << std::endl;

    OpenErr();

    if (abend)
    {
        return;
    }

    for (l = 0; l < 253; l++)
    {
        fileir[l] = '\0';     // set to null
    }

    for (l = 0; l < 253; l++)
    {
        arr[l] = '\0';     // set to null
    }

// stringstream
//    sql = ""; No!

// int
    rowcnt = 0;
    abendi = 0;
    errorcode = 0;
    reccnt = 0;
    bytecnt = 0;        // bytes in a file
    fileireccnt = 0;
    fileibytecnt = 0;
    fileitellg = 0;
    fileoi = 0;
    fileotellg = 0;
    InsertCnt = 0;
    UpdateCnt = 0;
    CodeId = 0;
    CodeStrl = 0;
    j = 0;
    k = 0;
    l = 0;
    u = 0;
    i = 0;
    n = 0;

// char
    fileic = ' ';

// strings
//  fileiname = ""; No!
    str = "";
    msg = "";
    action = "";

    what = "";
    state = "";
    Query = "";
    CodeStr = "";
    CodeNew = "";

// boolean
    abend = false;
    elapsed = false;
    tbexists = true;
    OnOne = true;
    OnOneWelcome = true;
    OnOneUser = true;
    OnOneCommand = true;
    OnOneParameterone = true;
    OnOneParametertwo = true;
    OnOneUsageDate = true;
    OnOneElapsed = true;
    OnOneSelect = true;
    OnOneGetRes = true;
    OnOneUpdate = true;
    OnOneInsert = true;
    OnOneInitRecord = true;
    OnOneInitLA = true;

}
void CLEditXETL::OpenLog()
{

    LogFile.open("CLEditXETLLogFile.txt", ios_base::out | ios_base::app);

    if  (!LogFile.is_open())
    {
        msg = "Log file Open error";
        abendi = 3503;
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

    LogFile << "Log file size " << to_string(bytecnt) << std::endl;

}
void CLEditXETL::OpenLogn()
{

    LogFile.open("CLEditXETLLogFile.txt", ios_base::out);

    if  (!LogFile.is_open())
    {
        msg = "Log file Open error";
        abendi = 3504;
        abend = true;
        std::cout << msg << abendi << std::endl;    // better than flying blind
        return;
    }

}
void CLEditXETL::OpenErr()
{

    ErrFile.open("CLEditXETLErrFile.txt", std::ios::out | ios_base::app);

    if  (!ErrFile.is_open())
    {
        msg = "Error file Open error";
        abendi = 3505;
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

    LogFile << "Error file size " << to_string(bytecnt) << std::endl;

}
void CLEditXETL::OpenErrn()
{

    ErrFile.open("CLEditXETLErrFile.txt", std::ios::out);

    if  (!ErrFile.is_open())
    {
        msg = "Error file Open error";
        abendi = 3506;
        abend = true;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

}
void CLEditXETL::OpenFile()
{

    LogFile << "Open File " << std::endl;
// keep trying to open the file for output, until you can
// you won't be able to do that if the file is not complete or available
    fileoi = 0;
    do
    {
        filei.open(fileiname, std::ios::out | std::ios::app);
        fileoi++;
        if (fileoi > 2)
        {
            break;
        }
    }
    while (!filei.is_open());

    if (fileoi > 2)
    {
        msg = "input file unavailable";
        abendi = 3501;
        abend = true;
        ErrFile << msg << abendi << std::endl;
        return;
    }

    CloseFile();

// now you can open the file
    filei.open(fileiname, std::ios::in );

    if  (!filei.is_open())
    {
        msg = "input file Open error";
        abendi = 3502;
        abend = true;
        ErrFile << msg << abendi << std::endl;
        return;
    }

}
void CLEditXETL::Bind()
{

    LogFile << "Bind " << std::endl;

    Driver();

    if  (abend)
    {
        return;
    }

    Connect();

    if  (abend)
    {
        return;
    }

    Statement();

    if  (abend)
    {
        return;
    }

    UseDb();

    if  (abend)
    {
        return;
    }

    tbexists = Exists();

    if (tbexists)
    {
        return;
    }

    DropTable();

    if  (abend)
    {
        return;
    }

    CreateTable();

    if  (abend)
    {
        return;
    }


}
void CLEditXETL::Driver()
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
        abend = true;
    }

}
void CLEditXETL::Connect()
{

    LogFile << "Connect " << std::endl;

    DataBase = "mydb";

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
void CLEditXETL::Statement()
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
        abend = true;
    }

}
void CLEditXETL::UseDb()
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
        abend = true;
    }

}
bool CLEditXETL::Exists()
{

    LogFile << "Exists " << std::endl;

    TableName = "editxetl";

    try
    {
        Query = "";
        Query += "SHOW TABLE STATUS FROM mydb WHERE Name = 'editxetl'";
        Query += ";";
        res = stmt->executeQuery(Query);
        if (res->next())
        {
            tbexists = true;
        }
        else
        {
            tbexists = false;
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

    return tbexists;

}
void CLEditXETL::DropTable()
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
        abend = true;
    }

}
void CLEditXETL::CreateTable()
{

    LogFile << "Create Table " << std::endl;

    try
    {
        Query = "";
        Query += "CREATE TABLE ";
        Query += TableName;
        Query += " (";
        Query += "dateseq  VARCHAR(18) NOT NULL PRIMARY KEY, ";
        Query += "usercode VARCHAR(08), ";
        Query += "timecode VARCHAR(08), ";
        Query += "action   VARCHAR(20), ";
        Query += "input    VARCHAR(30), ";
        Query += "inrec    INT, ";
        Query += "inbyte   INT, ";
        Query += "output   VARCHAR(30), ";
        Query += "outrec   INT, ";
        Query += "outbyte  INT, ";
        Query += "rowcnt   INT, ";
        Query += "dbname   VARCHAR(08), ";
        Query += "tbname   VARCHAR(08), ";
        Query += "elapseda INT, ";
        Query += "elapsedr INT);";
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
void CLEditXETL::Error()
{

    LogFile << "Error " << std::endl;

    ErrFile << std::endl;
    ErrFile << "CLEditXETL - Error " << errorcode;
    ErrFile << std::endl;
    ErrFile << "# ERR: SQLException in " << __FILE__;
    ErrFile << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
    ErrFile << "# ERR: " << what;
    ErrFile << " (MySQL error code: " << errorcode;
    ErrFile << ", SQLState: " << state << " )" << std::endl;

}
void CLEditXETL::ProcessFile()
{

    if (fileireccnt == 0)
    {
        LogFile << "ProcessFile " << std::endl;
    }

    j++;

    fileir[i] = fileic;

    i++;

    if  (fileic == '\n')
    {
        fileireccnt++;
        ProcessRecord();
        InitRecord();
    }

    ReadFile();

}
void CLEditXETL::ReadFile()
{

    if (fileibytecnt == 0)
    {
        LogFile << "ReadFile " << std::endl;
    }

    fileic = filei.get();   // one byte at a time

    fileitellg = filei.tellg();

    if  (filei.tellg() > 0)
    {
        fileibytecnt = filei.tellg();
    }

}
void CLEditXETL::ProcessRecord()
{

    if (fileireccnt == 1)
    {
        LogFile << "Process Record " << std::endl;
    }

// look for words and gather meta data
// between welcome and elapsed
    Gather();

// elapsed is the end of a block of meta data
    if  (elapsed)
    {
        elapsed = false;
        Select();
        if (res->next())
        {
            GetRes();
            Update();
            UpdateCnt++;
        }
        else
        {
            Insert();
            InsertCnt++;
        }

        InitLA();
    }

}
void CLEditXETL::InitRecord()
{

    if (OnOneInitRecord)
    {
        LogFile << "InitRecord " << std::endl;
        OnOneInitRecord = false;
    }

    for (i = 0; i < j; i++)   // i < j to save time
    {
        fileir[i] = '\0';     // set to null
    }

    i = 0;
    j = 0;

}
void CLEditXETL::Gather()
{

    if (fileireccnt == 1)
    {
        LogFile << "Gather " << std::endl;
    }

// in each record, look for key words like Welcome, Usage, elapsed etc
// you made these up to help yourself
// gather those keywords into a structure
// at lapsed from any log
//      look for row
//      update or
//      insert

// what is the first word from the log record
    LookforWord();
// welcome is the beginning of a block of meta data
// Sun Dec 22 03:21:05 2024  LA.Time
    if (Word == "Welcome")
    {
        Welcome();
        return;
    }

// Welcome pierre Sun Dec 22 03:21:05 2024
// LA.User
    if (Word == "User")
    {
        User();
        return;
    }

// Command fromstage
// LA.Action
    if (Word == "Command")
    {
        Command();
        return;
    }

// Parameterone mydb
// LA.DataBase or LA.InputFile
    if (Word == "Parameterone")
    {
        Parameterone();
        return;
    }

// Parameter two testones
// LA.TableName /  LA.OutputFile
    if (Word == "Parametertwo")
    {
        Parametertwo();
        return;
    }

// Usage Date 20241222 0000000003
// LA.Date / LA.Seq
    if (Word == "Usage")
    {
        UsageDate();
        return;
    }

// FileInBytes 0
// LA.Inputbytes
    if (Word == "FileInBytes")
    {
        FileInBytes();
        return;
    }
// FileInRecords 26
// LA.Inputrecs
    if (Word == "FileInRecords")
    {
        FileInRecords();
        return;
    }
// FileOutBytes 337
// LA.Outputbytes
    if (Word == "FileOutBytes")
    {
        FileInBytes();
        return;
    }
// FileOutRecords 41
// LA.Outputrecs
    if (Word == "FileOutRecords")
    {
        FileInRecords();
        return;
    }

// Elapsed 14.376
// LA.ElapsedTime
    if  (Word == "Elapsed")
    {
        Elapsed();
        elapsed = true;
        return;
    }

}
void CLEditXETL::LookforWord()
{

    if (fileireccnt == 1)
    {
        LogFile << "Look for Word " << std::endl;
    }

    Word = "";
    CodeStr = fileir;
    CodeStrl = CodeStr.length();

    for (i = 0; i < CodeStrl; i++)
    {
        if  (CodeStr[i] == ' ')
        {
            break;
        }
        else
        {
            Word += CodeStr[i];
        }
    }

}
void CLEditXETL::Welcome()
{

    if (OnOneWelcome)
    {
        LogFile << "Welcome " << std::endl;
        OnOneWelcome = false;
    }

// Welcome Sun Dec 22 03:21:05 2024  LA.Time
// 01234567891123456789212345678931234

    Word = "";

    for (i = 19; i < CodeStrl; i++)
    {
        if  (CodeStr[i] == ' '
        ||   CodeStr[i] == '\n')
        {
            break;
        }
        else
        {
            Word += CodeStr[i];
        }
    }

    LA.Time = Word;

}
void CLEditXETL::User()
{

    if (OnOneUser)
    {
        LogFile << "User " << std::endl;
        OnOneUser = false;
    }
// User Pierre  LA.User
// 01234567891123456789212345678931234
    Word = "";

    for (i = 5; i < CodeStrl; i++)
    {
        if  (CodeStr[i] == ' '
        ||   CodeStr[i] == '\n')
        {
            break;
        }
        else
        {
            Word += CodeStr[i];
        }
    }

    LA.User = Word;

}
void CLEditXETL::Command()
{

    if (OnOneCommand)
    {
        LogFile << "Command " << std::endl;
        OnOneCommand = false;
    }

// Command fromstage    LA.Action
// 01234567891123456789212345678931234
    Word = "";

    for (i = 8; i < CodeStrl; i++)
    {
        if  (CodeStr[i] == ' '
        ||   CodeStr[i] == '\n')
        {
            break;
        }
        else
        {
            Word += CodeStr[i];
        }
    }

    LA.Action = Word;

}
void CLEditXETL::Parameterone()
{

    if (OnOneParameterone)
    {
        LogFile << "Parameterone " << std::endl;
        OnOneParameterone = false;
    }

// Parameterone mydb    LA.DataBase or LA.InputFile
// 01234567891123456789212345678931234
    Word = "";

    for (i = 13; i < CodeStrl; i++)
    {
        if  (CodeStr[i] == ' '
        ||   CodeStr[i] == '\n')
        {
            break;
        }
        else
        {
            Word += CodeStr[i];
        }
    }

    if  (LA.Action == "FromStage"
    ||   LA.Action == "ToStage"
    ||   LA.Action == "CreateTable")
    {
        LA.DataBase = Word;
    }
    else
    {
        LA.InputFile = Word;
    }

}
void CLEditXETL::Parametertwo()
{

    if (OnOneParametertwo)
    {
        LogFile << "Parametertwo " << std::endl;
        OnOneParametertwo = false;
    }

// Parametertwo testones    LA.TableName /  LA.OutputFile
// 01234567891123456789212345678931234
    Word = "";

    for (i = 13; i < CodeStrl; i++)
    {
        if  (CodeStr[i] == ' '
        ||   CodeStr[i] == '\n')
        {
            break;
        }
        else
        {
            Word += CodeStr[i];
        }
    }

    if (Word == "")
    {
        return;
    }

    if  (LA.Action == "FromStage"
    ||   LA.Action == "ToStage"
    ||   LA.Action == "CreateTable")
    {
        LA.TableName = Word;
    }
    else
    {
        LA.OutputFile = Word;
    }

}
void CLEditXETL::UsageDate()
{

    if (OnOneUsageDate)
    {
        LogFile << "UsageDate " << std::endl;
        OnOneUsageDate = false;
    }

// Usage Date 20241222 0000000003   LA.Date / LA.Seq
// 01234567891123456789212345678931234
    Word = "";

    for (i = 11; i < CodeStrl; i++)
    {
        if  (CodeStr[i] == ' '
        ||   CodeStr[i] == '\n')
        {
            break;
        }
        else
        {
            Word += CodeStr[i];
        }
    }

    LA.DateSeq = Word;

    Word = "";

    for (i = 20; i < CodeStrl; i++)
    {
        if  (CodeStr[i] == ' '
        ||   CodeStr[i] == '\n')
        {
            break;
        }
        else
        {
            Word += CodeStr[i];
        }
    }

    LA.DateSeq += Word;

}
void CLEditXETL::FileInBytes()
{

    if (OnOneInBytes)
    {
        LogFile << "FileInBytes " << std::endl;
        OnOneUser = false;
    }

// FileInBytes 0
// 01234567891123456

    Word = "";

    for (i = 12; i < CodeStrl; i++)
    {
        if  (CodeStr[i] == ' '
        ||   CodeStr[i] == '\n')
        {
            break;
        }
        else
        {
            Word += CodeStr[i];
        }
    }

    LA.Inputbytes = std::stoi(Word);

}
void CLEditXETL::FileInRecords()
{

    if (OnOneInRecords)
    {
        LogFile << "FileInRecords " << std::endl;
        OnOneUser = false;
    }
// FileInRecords 26
// 01234567891123456

    Word = "";

    for (i = 14; i < CodeStrl; i++)
    {
        if  (CodeStr[i] == ' '
        ||   CodeStr[i] == '\n')
        {
            break;
        }
        else
        {
            Word += CodeStr[i];
        }
    }

    LA.Inputrecs = std::stoi(Word);

}
void CLEditXETL::FileOutBytes()
{

    if (OnOneOutBytes)
    {
        LogFile << "FileOutBytes " << std::endl;
        OnOneUser = false;
    }

// FileOutBytes 337
// 01234567891123456

    Word = "";

    for (i = 13; i < CodeStrl; i++)
    {
        if  (CodeStr[i] == ' '
        ||   CodeStr[i] == '\n')
        {
            break;
        }
        else
        {
            Word += CodeStr[i];
        }
    }

    LA.Outputbytes = std::stoi(Word);

}
void CLEditXETL::FileOutRecords()
{

    if (OnOneOutRecords)
    {
        LogFile << "FileOutRecords " << std::endl;
        OnOneUser = false;
    }

// FileOutRecords 41
// 01234567891123456

    Word = "";

    for (i = 15; i < CodeStrl; i++)
    {
        if  (CodeStr[i] == ' '
        ||   CodeStr[i] == '\n')
        {
            break;
        }
        else
        {
            Word += CodeStr[i];
        }
    }

    LA.Outputrecs = std::stoi(Word);

}
void CLEditXETL::Elapsed()
{

    if (OnOneElapsed)
    {
        LogFile << "Elapsed " << std::endl;
        OnOneElapsed = false;
    }

// Elapsed 14.376   LA.ElapsedTime
// 01234567891123456789212345678931234
    Word = "";

    for (i = 8; i < CodeStrl; i++)
    {
        if  (CodeStr[i] == ' '
        ||   CodeStr[i] == '\n')
        {
            break;
        }
        else
            if  (CodeStr[i] == '.')
            {
                continue;
            }
            else
            {
                Word += CodeStr[i];
            }
    }

// Main actions in upper case
    if  (LA.Action == "FromStage"
    ||   LA.Action == "ToStage"
    ||   LA.Action == "CreateTable"
    ||   LA.Action == "CopyFile"
    ||   LA.Action == "OpenFile"
    ||   LA.Action == "SaveFile"
    ||   LA.Action == "SaveAsFile"
    ||   LA.Action == "CreateFile")
    {
        LA.ElapsedAct = std::stoi(Word);
    }
    else
    {
        LA.ElapsedRes = std::stoi(Word);
    }

}
void CLEditXETL::Select()
{

    if  (OnOneSelect)
    {
        LogFile << "Select " << std::endl;
        OnOneSelect = false;
    }

    try
    {
        Query = "";
        Query += "SELECT usercode, ";
        Query += "timecode, ";
        Query += "action, ";
        Query += "input, ";
        Query += "inrec, ";
        Query += "inbyte, ";
        Query += "output, ";
        Query += "outrec, ";
        Query += "outbyte, ";
        Query += "rowcnt, ";
        Query += "dbname, ";
        Query += "tbname, ";
        Query += "elapseda, ";
        Query += "elapsedr FROM ";
        Query += DataBase;
        Query += ".";
        Query += TableName;
        Query += "WHERE dateseq = ";
        Query += LA.DateSeq;
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
void CLEditXETL::GetRes()
{

    if (OnOneGetRes)
    {
        LogFile << "GetRes " << std::endl;
        OnOneGetRes = false;
    }

// key / primary index
//  LA.Date = res->getString("datecode");
//  LA.Seq  = res->getString("dateseq");

// replace values you don't have
// with values you might have
    if (LA.User == "")
    {
        LA.User = res->getString("usercode");
    }

    if (LA.Action == "")
    {
        LA.Action = res->getString("action");
    }

    if (LA.InputFile == "")
    {
        LA.InputFile = res->getString("input");
    }

    if (LA.Inputrecs == 0)
    {
        LA.Inputrecs = res->getInt("inrec");
    }

    if (LA.Inputbytes == 0)
    {
        LA.Inputbytes = res->getInt("inbyte");
    }

    if (LA.OutputFile == "")
    {
        LA.OutputFile = res->getString("output");
    }

    if (LA.Outputrecs == 0)
    {
        LA.Outputrecs = res->getInt("outrec");
    }

    if (LA.Outputbytes == 0)
    {
        LA.Outputbytes = res->getInt("outbyte");
    }

    if (LA.RowCnt == 0)
    {
        LA.RowCnt = res->getInt("rowcnt");
    }

    if (LA.DataBase == "")
    {
        LA.DataBase =res->getString("dbname");
    }

    if (LA.TableName == "")
    {
        LA.TableName = res->getString("tbname");
    }

    if (LA.ElapsedAct == 0)
    {
        LA.ElapsedAct = res->getInt("elapseda");
    }

    if (LA.ElapsedRes == 0)
    {
        LA.ElapsedRes = res->getInt("elapsedr");
    }

}
void CLEditXETL::Update()
{

    if (OnOneUpdate)
    {
        LogFile << "Update " << std::endl;
        OnOneUpdate = false;
    }

    try
    {
        sql.str("");
        sql << "UPDATE ";
        sql << TableName;
        sql << " SET ";
        sql << ", usercode = ";
        sql << LA.User;
        sql << ", timecode = ";
        sql << LA.Time;
        sql << ", action = ";
        sql << LA.Action;
        sql << ", input = ";
        sql << LA.InputFile;
        sql << ", inrec = ";
        sql << LA.Inputrecs;
        sql << ", inbyte = ";
        sql << LA.Inputbytes;
        sql << ", output = ";
        sql << LA.OutputFile;
        sql << ", outrec = ";
        sql << LA.Outputrecs;
        sql << ", outbyte = ";
        sql << LA.Outputbytes;
        sql << ", rowcnt = ";
        sql << LA.RowCnt;
        sql << ", dbname = ";
        sql << LA.DataBase;
        sql << ", tbname = ";
        sql << LA.TableName;
        sql << ", elapseda = ";
        sql << LA.ElapsedAct;
        sql << ", elapsedr = ";
        sql << LA.ElapsedRes;
        sql << " WHERE dateseq = ";
        sql <<LA.DateSeq;
        sql << ";";
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
void CLEditXETL::Insert()
{

    if (OnOneInsert)
    {
        LogFile << "Insert " << std::endl;
        OnOneInsert = false;
    }

    try
    {
        sql.str("");
        sql << "INSERT INTO ";
        sql << TableName;
        sql << " (dateseq, ";
        sql << "usercode, ";
        sql << "timecode, ";
        sql << "action, ";
        sql << "input, ";
        sql << "inrec, ";
        sql << "inbyte, ";
        sql << "output, ";
        sql << "outrec, ";
        sql << "outbyte, ";
        sql << "rowcnt, ";
        sql << "dbname, ";
        sql << "tbname, ";
        sql << "elapseda, ";
        sql << "elapsedr) VALUES (";
        sql << "'" << LA.DateSeq << "', ";
        sql << "'" << LA.User << "', ";
        sql << "'" << LA.Time << "', ";
        sql << "'" << LA.Action << "', ";
        sql << "'" << LA.InputFile << "', ";
        sql << LA.Inputrecs << ", ";
        sql << LA.Inputbytes << ", ";
        sql << "'" << LA.OutputFile << "', ";
        sql << LA.Outputrecs << ", ";
        sql << LA.Outputbytes << ", ";
        sql << LA.RowCnt << ", ";
        sql << "'" << LA.DataBase << "', ";
        sql << "'" << LA.TableName << "', ";
        sql << LA.ElapsedAct << ", ";
        sql << LA.ElapsedRes << ")";
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
void CLEditXETL::InitLA()
{

    if (OnOneInitLA)
    {
        LogFile << "InitLA " << std::endl;
        OnOneInitLA = false;
    }

    LA.DateSeq = "";
    LA.User = "";
    LA.Time = "";
    LA.Action = "";
    LA.InputFile = "";
    LA.Inputrecs = 0;
    LA.Inputbytes = 0;
    LA.OutputFile = "";
    LA.Outputrecs = 0;
    LA.Outputbytes = 0;
    LA.RowCnt = 0;
    LA.DataBase = "";
    LA.TableName = "";
    LA.ElapsedAct = 0;
    LA.ElapsedRes = 0;

}
void CLEditXETL::Free()
{

    LogFile << "Free " << std::endl;

    Freecon();

    Freestmt();

    Freepstmt();

    Freeres();

    CloseLog();

    CloseErr();

}
void CLEditXETL::Freecon()
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
        abend = true;
    }

}
void CLEditXETL::Freestmt()
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
        abend = true;
    }

}
void CLEditXETL::Freepstmt()
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
        abend = true;
    }

}
void CLEditXETL::Freeres()
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
        abend = true;
    }

}

void CLEditXETL::EoP()
{

    LogFile << "EoP " << std::endl;
    LogFile << "Inserts " << InsertCnt << std::endl;
    LogFile << "Updates " << UpdateCnt << std::endl;
    LogFile << "File in Bytes " << fileibytecnt << std::endl;
    LogFile << "File in Records " << fileireccnt << std::endl;

    CloseFile();

    CloseErr();

    stop_s = std::clock();

    LogFile << action << "elapsed time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

    CloseLog();

}
void CLEditXETL::CloseFile()
{

    LogFile << "CloseFile " << std::endl;

    filei.close();

}
void CLEditXETL::CloseLog()
{

    LogFile.close();

}

void CLEditXETL::CloseErr()
{

    ErrFile.close();

}
