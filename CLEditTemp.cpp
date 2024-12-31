#include "CLEditTemp.h"
using namespace std;
CLEditTemp::CLEditTemp()
{
    // constructor
}

CLEditTemp::~CLEditTemp()
{
    // destructor
}
int CLEditTemp::DoStuff()
{

    init();

    if (abend)
    {
        goto dostuffexit;
    }

    if  (Logging)
    {
        LogFile << "Do Stuff " << std::endl;
    }

    StatFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;


//  do stuff here


    eop();

dostuffexit:

    return abendi;

}
void CLEditTemp::init()
{

    start_s = std::clock();

    abend = false;
    abendi = 0;

    OpenLog();

    if (abend)
    {
        return;
    }

    if  (Logging)
    {
        LogFile << "init " << std::endl;
    }

    OpenStat();

    if (abend)
    {
        return;
    }

    currentdatetime = std::time(nullptr);

    StatFile << "Welcome " << std::ctime(& currentdatetime);

    OpenErr();

    if (abend)
    {
        return;
    }

}
void CLEditTemp::OpenLog()
{

    LogFile.open("CLEditTempLog.txt", ios_base::out | ios_base::app);

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

    if  (Logging)
    {
        LogFile << "Log file size " << to_string(bytecnt) << std::endl;
    }

}
void CLEditTemp::OpenLogn()
{

    LogFile.open("CLEditTempLog.txt", ios_base::out);

    if  (!LogFile.is_open())
    {
        msg = "Log file Open error";
        abendi = 3504;
        abend = true;
        std::cout << msg << abendi << std::endl;    // better than flying blind
        return;
    }

}
void CLEditTemp::OpenErr()
{

    if  (Logging)
    {
        LogFile << "Open Error " << std::endl;
    }

    ErrFile.open("CLEditTempErr.txt", std::ios::out | ios_base::app);

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

    if  (Logging)
    {
        LogFile << "Error file size " << to_string(bytecnt) << std::endl;
    }

}
void CLEditTemp::OpenErrn()
{

    if  (Logging)
    {
        LogFile << "Open Error new " << std::endl;
    }

    ErrFile.open("CLEditTempErr.txt", std::ios::out);

    if  (!ErrFile.is_open())
    {
        msg = "Error file Open error";
        abendi = 3506;
        abend = true;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

}
void CLEditTemp::OpenStat()
{

    if  (Logging)
    {
        LogFile << "Open Stat " << std::endl;
    }

    StatFile.open("CLEditTempStat.txt", std::ios::out | ios_base::app);

    if  (!StatFile.is_open())
    {
        msg = "Stat file Open error";
        abendi = 3505;
        abend = true;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

    bytecnt = StatFile.tellg();

    if  (bytecnt > FILE_SIZE)
    {
        CloseStat();
        ETL.Logging = Logging;
        ETL.fileiname = "CLEditTempStat.txt";
        res = ETL.ETL();
        OpenStatn();
    }

    if  (Logging)
    {
        LogFile << "Stat file size " << to_string(bytecnt) << std::endl;
    }

}
void CLEditTemp::OpenStatn()
{

    if  (Logging)
    {
        LogFile << "Open Stat new " << std::endl;
    }

    StatFile.open("CLEditTempStat.txt", std::ios::out);

    if  (!StatFile.is_open())
    {
        msg = "Stat file Open error";
        abendi = 3506;
        abend = true;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

}
void CLEditTemp::eop()
{

    CloseErr();

    CloseStat();

    stop_s = std::clock();

    StatFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

    CloseLog();

}
void CLEditTemp::CloseLog()
{

    LogFile.close();

}
void CLEditTemp::CloseErr()
{

    ErrFile.close();

}
void CLEditTemp::CloseStat()
{

    StatFile.close();

}

