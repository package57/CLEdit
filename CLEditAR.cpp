#include "CLEditAR.h"
using namespace std;
CLEditAR::CLEditAR()
{
    // constructor
}

CLEditAR::~CLEditAR()
{
    // destructor
}
int CLEditAR::ActReact()
{

    init();

    if (abend)
    {
        goto actreactexit;
    }

    if (Logging)
    {
        LogFile << "ActReact " << std::endl;
    }

// do stuff
// get the currrent date
	GetDate();
// open a file for input
	OpenI();

// it will have a single record, containing a date and a number as a string
    if  (ActFile.is_open())
	{
 // the file should be 19 bytes: "ccyymmdd0000000000\n"
 // file was opened with std::ios::ate 'at the end'
	    lrecl = ActFile.tellg();
	    if (lrecl == 19)
        {
            OldFile();
        }
        else
    	{
    	    Close();
            NewFile();
        }
    }
    else
	{
	    NewFile();
    }

actreactexit:

    eop();

    return abendi;

}
void CLEditAR::GetDate()
{

    if (Logging)
    {
        LogFile << "GetDate " << std::endl;
    }

    timestamp = time(NULL);

    datetime  = *localtime(&timestamp);

    datetime.tm_year += 1900;                       // years since 1900!

    datetime.tm_mon++;                              // 0 thru 11

    CurrentAR.date += to_string(datetime.tm_year);  // "ccyy"

    if (datetime.tm_mon < 10)
    {
        CurrentAR.date += "0";
        CurrentAR.date += to_string(datetime.tm_mon);
    }
    else
    {
        CurrentAR.date += to_string(datetime.tm_mon);
    }

    CurrentAR.date += to_string(datetime.tm_mday);   // "dd"

}
void CLEditAR::OldFile()
{

    if (Logging)
    {
        LogFile << "Old File " << std::endl;
    }

// point back to the beginning of the file
    ActFile.seekg(0);

    for (i = 0; i < 8; i++)
    {
// read 'the' record
        Read();
// gather the date
        NewAR.date += fileic;
    }

    for (i = 0; i < 10; i++)
    {
// read 'the' record
        Read();
// gather the number
        NewAR.seq += fileic;
    }

// close the file
    Close();

    if (CurrentAR.date == NewAR.date)
    {
        DateMatch();
    }
    else
	{
	    NewFile();
    }

}
std::string CLEditAR::ToString(int u)
{

    if (Logging)
    {
        LogFile << "ToString " << std::endl;
    }

// make 10 look like 000010 etc
    ostringstream os;
    os<<setfill('0')<<setw(10)<<seq;

    return os.str();

}
void CLEditAR::DateMatch()
{

    if (Logging)
    {
        LogFile << "DateMatch " << std::endl;
    }
// convert string to int
    seq = std::stoi(NewAR.seq);
// increase the number by 1
    seq++;
// convert int to string, pad width
    NewAR.seq = ToString(seq);
//  open the file as output
    OpenO();

    if (abend)
    {
        return;
    }

    FormatRec();

// write the record
    Write();
// close the file
    Close();

}
void CLEditAR::FormatRec()
{

    if (Logging)
    {
        LogFile << "FormatRec " << std::endl;
    }

    for (i = 0; i < 8; i++)
    {
        Actrec[i] = NewAR.date[i];
    }

    j = 8;
    for (i = 0; i < 10; i++)
    {
        Actrec[j] = NewAR.seq[i];
        j++;
    }

    Actrec[18] = '\n';

}
void CLEditAR::NewFile()
{

    if (Logging)
    {
        LogFile << "NewFile " << std::endl;
    }

// open the file as output
    OpenO();

    if (abend)
    {
        return;
    }

// set the date
    NewAR.date = CurrentAR.date;
// set the number to 1
    NewAR.seq = "0000000001";

    FormatRec();
// write the record
    Write();
// close the file
    Close();

}
void CLEditAR::OpenI()
{

    if (Logging)
    {
        LogFile << "OpenI " << std::endl;
    }

    ActFile.open("CLEditAR.txt", std::ios::in | std::ios::ate);

}

void CLEditAR::Read()
{

    if (Logging)
    {
        LogFile << "Read " << std::endl;
    }

    fileic = ActFile.get();   // one byte at a time

}
void CLEditAR::Close()
{

    if (Logging)
    {
        LogFile << "Close " << std::endl;
    }

    ActFile.close();

}
void CLEditAR::OpenO()
{

    if (Logging)
    {
        LogFile << "OpenO " << std::endl;
    }

    ActFile.open("CLEditAR.txt", std::ios::out);

    if  (!ActFile.is_open())
    {
        msg = "ActFile file Open error";
        abendi = 3500;
        abend = true;
        return;
    }

}
void CLEditAR::Write()
{

    if (Logging)
    {
        LogFile << "Write " << std::endl;
    }


    ActFile << Actrec;

}
void CLEditAR::init()
{

    start_s = std::clock();

    OpenErr();

    if (abend)
    {
        return;
    }

    DateSeq.date = "";
    DateSeq.seq  = "";
    CurrentAR.date = "";
    CurrentAR.seq = "";
    NewAR.date = "";
    NewAR.seq = "";

    OpenLog();

    if (abend)
    {
        return;
    }

    if (Logging)
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

}
void CLEditAR::OpenLog()
{

    LogFile.open("CLEditARLog.txt", ios_base::out | ios_base::app);

    if  (!LogFile.is_open())
    {
        msg = "Log file Open error";
        abendi = 3501;
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
void CLEditAR::OpenLogn()
{

    LogFile.open("CLEditARLog.txt", ios_base::out);

    if  (!LogFile.is_open())
    {
        msg = "Log file Open error";
        abendi = 3502;
        abend = true;
        std::cout << msg << abendi << std::endl;    // better than flying blind
        return;
    }

}
void CLEditAR::OpenErr()
{

    ErrFile.open("CLEditARErr.txt", std::ios::out | ios_base::app);

    if  (!ErrFile.is_open())
    {
        msg = "Error file Open error";
        abendi = 3503;
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
void CLEditAR::OpenErrn()
{

    ErrFile.open("CLEditARErr.txt", std::ios::out);

    if  (!ErrFile.is_open())
    {
        msg = "Error file Open error";
        abendi = 3504;
        abend = true;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

}
void CLEditAR::OpenStat()
{

    StatFile.open("CLEditARStat.txt", std::ios::out | ios_base::app);

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
        OpenStatn();
    }

    if (Logging)
    {
        LogFile << "Stat file size " << to_string(bytecnt) << std::endl;
    }

}
void CLEditAR::OpenStatn()
{

    StatFile.open("CLEditARStat.txt", std::ios::out);

    if  (!StatFile.is_open())
    {
        msg = "Stat file Open error";
        abendi = 3506;
        abend = true;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

}
void CLEditAR::eop()
{

    DateSeq.date = NewAR.date;
    DateSeq.seq  = NewAR.seq;


    stop_s = std::clock();

    StatFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

    CloseErr();

    CloseLog();

    CloseStat();

}
void CLEditAR::CloseErr()
{

    ErrFile.close();

}
void CLEditAR::CloseLog()
{

    LogFile.close();

}
void CLEditAR::CloseStat()
{

    StatFile.close();

}

