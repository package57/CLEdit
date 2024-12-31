#include "CLEditRP.h"
using namespace std;
CLEditRP::CLEditRP()
{
    // constructor
}

CLEditRP::~CLEditRP()
{
    // destructor
}
int CLEditRP::Report()
{

    init();

    if (abend)
    {
        goto reportexit;
    }

    if (Logging)
    {
        LogFile << "Report " << std::endl;
    }

    StatFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;


// Do Stuff


    eop();

reportexit:

    return abendi;

}
void CLEditRP::init()
{

    abendi = 0;

    start_s = std::clock();

    OpenErr();

    if (abend)
    {
        return;
    }

    OpenLog();

    if (abend)
    {
        return;
    }

    OpenStat();

    if (abend)
    {
        return;
    }

    if (Logging)
    {
        LogFile << "Init " << std::endl;
    }

    currentdatetime = std::time(nullptr);

    StatFile << "Welcome " << std::ctime(& currentdatetime);

    rc = 0;

}
void CLEditRP::OpenLog()
{

    LogFile.open("CLEditRPLog.txt", ios_base::out | ios_base::app);

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
void CLEditRP::OpenLogn()
{

    LogFile.open("CLEditRPLog.txt", ios_base::out);

    if  (!LogFile.is_open())
    {
        msg = "Log file Open error";
        abendi = 3504;
        abend = true;
        std::cout << msg << abendi << std::endl;    // better than flying blind
        return;
    }

}
void CLEditRP::OpenErr()
{

    LogFile << "Open Error " << std::endl;

    ErrFile.open("CLEditRPErr.txt", std::ios::out | ios_base::app);

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
void CLEditRP::OpenErrn()
{

    LogFile << "Open Error new " << std::endl;

    ErrFile.open("CLEditRPErr.txt", std::ios::out);

    if  (!ErrFile.is_open())
    {
        msg = "Error file Open error";
        abendi = 3506;
        abend = true;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

}
void CLEditRP::OpenStat()
{

    StatFile.open("CLEditRPStat.txt", ios_base::out | ios_base::app);

    if  (!LogFile.is_open())
    {
        msg = "Stat file Open error";
        abendi = 3503;
        abend = true;
        std::cout << msg << abendi << std::endl;    // better than flying blind
        return;
    }

    bytecnt = StatFile.tellg();

    if  (bytecnt > FILE_SIZE)
    {
        CloseStat();
        ETL.Logging = Logging;
        ETL.fileiname = "CLEditRPStat.txt";
        rc = ETL.ETL();
        OpenStatn();
    }

    if (Logging)
    {
        LogFile << "Stat file size " << to_string(bytecnt) << std::endl;
    }

}
void CLEditRP::OpenStatn()
{

    StatFile.open("CLEditRPStat.txt", ios_base::out);

    if  (!StatFile.is_open())
    {
        msg = "Stat file Open error";
        abendi = 3504;
        abend = true;
        std::cout << msg << abendi << std::endl;    // better than flying blind
        return;
    }

}
void CLEditRP::eop()
{

    if (Logging)
    {
        LogFile << "eop " << std::endl;
    }

    CloseErr();

    stop_s = std::clock();

    StatFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

    CloseLog();

    CloseStat();


}
void CLEditRP::CloseLog()
{

    LogFile.close();

}
void CLEditRP::CloseErr()
{

    ErrFile.close();

}
void CLEditRP::CloseStat()
{

    StatFile.close();

}
