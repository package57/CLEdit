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

    LogFile << "Report " << std::endl;

// the log files roll over at different rates
// the Main log file contains actions other than
// file actions or database actions
// process Main log file, create anchor points
// open Main log file for input
// read byte by byte
// process until end of file, aka eof
// close Main log file
// process CF log file, connect to anchor point
// open Main log file for input
// read byte by byte
// process until end of file, aka eof
// close Main log file
// process DB log file, connect to anchor point
// open Main log file for input
// read byte by byte
// process until end of file, aka eof
// close Main log file

//  Main
/*
Welcome pierre Sat Dec 21 06:54:11 2024
Command open
Parameter one objects.h
Usage Date 20241221 0000000001
Open File
Open File elapsed time: 11.565
*/
// CF
/*
Welcome Sat Dec 21 06:54:11 2024
Open File objects.h
Usage Date 20241221 0000000001
File In Bytes 506
File In Records 23
Open File elapsed time: 1.101
*/
// DB
/*
Welcome pierre Sat Dec 21 06:54:26 2024
Command fromstage
Parameter one mydb
Parameter two testones
Usage Date 20241221 0000000002
rows 1
From Stage elapsed time: 22.44
*/


    action = "Report ";

    eop();

reportexit:

    return abendi;

}
void CLEditRP::init()
{

    start_s = std::clock();

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
void CLEditRP::OpenLog()
{

    LogFile.open("CLEditRPLogFile.txt", ios_base::out | ios_base::app);

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

    LogFile.open("CLEditRPLogFile.txt", ios_base::out);

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

    ErrFile.open("CLEditRPErrFile.txt", std::ios::out | ios_base::app);

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

    ErrFile.open("CLEditRPErrFile.txt", std::ios::out);

    if  (!ErrFile.is_open())
    {
        msg = "Error file Open error";
        abendi = 3506;
        abend = true;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

}
void CLEditRP::eop()
{

    LogFile << "eop " << std::endl;

    CloseErr();

    stop_s = std::clock();

    LogFile << action << "elapsed time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

    CloseLog();

}
void CLEditRP::CloseLog()
{

    LogFile.close();

}
void CLEditRP::CloseErr()
{

    ErrFile.close();

}
