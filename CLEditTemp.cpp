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

    LogFile << "Do Stuff " << std::endl;


//  do stuff here


    action = "Do Stuff ";

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

    LogFile << "init " << std::endl;

    currentdatetime = std::time(nullptr);

    LogFile << "Welcome " << std::ctime(& currentdatetime);

    OpenErr();

    if (abend)
    {
        return;
    }

}
void CLEditTemp::OpenLog()
{

    LogFile.open("CLEditTempLogFile.txt", ios_base::out | ios_base::app);

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
        abendi = ETL.ETL();
        if (abend)
        {
            msg = "Log file ETL error";
            abendi = 3503;
            abend = true;
            std::cout << msg << abendi << std::endl;    // better than flying blind
            return;
        }
        else
        {
            OpenLogn();
        }
    }

    LogFile << "Log file size " << to_string(bytecnt) << std::endl;

}
void CLEditTemp::OpenLogn()
{

    LogFile.open("CLEditTempLogFile.txt", ios_base::out);

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

    LogFile << "Open Error " << std::endl;

    ErrFile.open("CLEditTempErrFile.txt", std::ios::out | ios_base::app);

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
void CLEditTemp::OpenErrn()
{

    LogFile << "Open Error new " << std::endl;

    ErrFile.open("CLEditTempErrFile.txt", std::ios::out);

    if  (!ErrFile.is_open())
    {
        msg = "Error file Open error";
        abendi = 3506;
        abend = true;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

}
void CLEditTemp::eop()
{

    CloseErr();

    stop_s = std::clock();

    LogFile << action << "elapsed time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

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

