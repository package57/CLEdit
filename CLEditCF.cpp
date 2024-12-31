#include "CLEditCF.h"
using namespace std;
CLEditCF::CLEditCF()
{
    // constructor
}

CLEditCF::~CLEditCF()
{
    // destructor
}
int CLEditCF::copyfile(std::string fileiname, std::string fileoname)
{

    init();

    if (abend)
    {
        goto copyexit;
    }

    if (Logging)
    {
       LogFile << "copyfile " << std::endl;
    }

    currentdatetime = std::time(nullptr);

    StatFile << "Welcome " << std::ctime(& currentdatetime);

    StatFile << "Command copyfile " << fileiname << " " << fileoname << std::endl;

    StatFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;

    openfo();

    if (abend)
    {
        goto copyexit;
    }

    openfi();

    if (abend)
    {
        goto copyexit;
    }

    i = 0;  //used to track position
    j = 0;  //used for logical record length
    fileireccnt = 0;
    fileoreccnt = 0;

    readfir();

    while (fileitellg > 0)  // at end of file the read returns -1
    {
        processfircopy();
    }

    eop();

copyexit:

    return abendi;

}
int CLEditCF::openfile(std::string fileiname)
{

    init();

    if (abend)
    {
        goto openexit;
    }

    if (Logging)
    {
       LogFile << "openfile " << std::endl;
    }

    currentdatetime = std::time(nullptr);

    StatFile << "Welcome " << std::ctime(& currentdatetime);

    StatFile << "Command openfile " << fileiname << std::endl;

    StatFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;

    openfi();

    if (abend)
    {
        goto openexit;
    }

    inputfile[0].IFCode = "";
    for (i = 1; i < 25000; i++)
    {
        inputfile[i] = inputfile[0];
    }

    i = 0;  //used to track position
    j = 0;  //used for logical record length
    fileireccnt = 0;
    Outreccnt = 0;  // index not counter

    readfir();

    while (fileitellg > 0)  // at end of file the read returns -1
    {
        processfiropen();
    }

    reccnt = fileireccnt;

    eop();

openexit:

    return abendi;

}
int CLEditCF::savefile(std::string fileoname)
{

    init();

    if (abend)
    {
        goto saveexit;
    }

    if (Logging)
    {
       LogFile << "savefile " << std::endl;
    }

    currentdatetime = std::time(nullptr);

    StatFile << "Welcome " << std::ctime(& currentdatetime);

    if (Mode == "savefile")
    {
        StatFile << "Command savefile " << fileoname << std::endl;
    }

    if (Mode == "saveasfile")
    {
        StatFile << "Command saveasfile " << fileoname << std::endl;
    }

    if (Mode == "createfile")
    {
        StatFile << "Command createfile " << fileoname << std::endl;
    }

    StatFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;

    openfo();

    if (abend)
    {
        goto saveexit;
    }

    for (i = 0; i < reccnt; i++)
    {
        stringtochar();
        writefor();
        initsavefileir();
    }

    eop();

saveexit:

    return abendi;

}
void CLEditCF::eop()
{

    if (Logging)
    {
       LogFile << "EoP " << std::endl;
    }

    StatFile << "FileInBytes " << fileibytecnt << std::endl;

    StatFile << "FileInRecords " << fileireccnt << std::endl;

    StatFile << "FileOutBytes " << fileobytecnt << std::endl;

    StatFile << "FileOutRecords " << fileoreccnt << std::endl;

    closefi();

    closefo();

    CloseErr();

    stop_s = std::clock();

    StatFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

    CloseLog();

    CloseStat();

}
void CLEditCF::stringtochar()
{

    for (l = 0; l < 253; l++)
    {
        arr[l] = '\0';     // set to null
    }

    strcpy(arr, inputfile[i].IFCode.c_str());

    k = inputfile[i].IFCode.length();

    fileobytecnt += k;

    for (l = 0; l < k; l++)
    {
        fileir[l] = arr[l];
    }

}
void CLEditCF::init()
{

    start_s = std::clock();

    fileibytecnt = 0;
    fileobytecnt = 0;
//  fileireccnt  = 0;  // no
//  fileoreccnt  = 0;  // no

    OpenStat();

    if (abend)
    {
        return;
    }

    OpenLog();

    if (abend)
    {
        return;
    }

    if (Logging)
    {
       LogFile << "init " << std::endl;
    }

    OpenErr();

    if (abend)
    {
        return;
    }

    for (l = 0; l < 253; l++)
    {
        arr[l] = '\0';     // set to null
    }

    str = "";

}
void CLEditCF::openfo()
{

    fileo.open(fileoname, std::ios::out);

    if  (!fileo.is_open())
    {
        msg = "TO file Open error";
        abendi = 3500;
        abend = true;
        ErrFile << msg << abendi << std::endl;
        return;
    }

}
void CLEditCF::closefo()
{

    fileo.close();

}
void CLEditCF::openfi()
{
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
        msg = "FROM file unavailable";
        abendi = 3501;
        abend = true;
        ErrFile << msg << abendi << std::endl;
        return;
    }

    closefi();

// now you can open the file
    filei.open(fileiname, std::ios::in );

    if  (!filei.is_open())
    {
        msg = "FROM file Open error";
        abendi = 3502;
        abend = true;
        ErrFile << msg << abendi << std::endl;
        return;
    }

}
void CLEditCF::closefi()
{

    filei.close();

}
void CLEditCF::processfiropen()
{

    j++;

    fileir[i] = fileic;

    i++;

    if  (fileic == '\n')
    {
        fileireccnt++;
        processforopen();
    }

    readfir();

}
void CLEditCF::processfircopy()
{

    j++;

    fileir[i] = fileic;

    i++;

    if  (fileic == '\n')
    {
        fileireccnt++;
        processforcopy();
    }

    readfir();

}
void CLEditCF::readfir()
{

    fileic = filei.get();   // one byte at a time

    fileitellg = filei.tellg();

    if  (filei.tellg() > 0)
    {
        fileibytecnt = filei.tellg();
    }

}
void CLEditCF::processforopen()
{

    inputfile[Outreccnt].IFCode = fileir;

    Outreccnt++;

    initfileir();

}
void CLEditCF::processforcopy()
{

    writefor();

    initfileir();

}
void CLEditCF::writefor()
{

    fileo << fileir;

    fileoreccnt++;

}
void CLEditCF::initfileir()
{

    for (i = 0; i < j; i++)   // i < j to save time
    {
        fileir[i] = '\0';     // set to null
    }

    i = 0;
    j = 0;

}
void CLEditCF::initsavefileir()
{

    for (l = 0; l < k; l++)
    {
        fileir[l] = '\0'; //set to null
    }

}
void CLEditCF::OpenLog()
{

    LogFile.open("CLEditCFLog.txt", ios_base::out | ios_base::app);

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

    if (Logging)
    {
        LogFile << "Log file size " << to_string(bytecnt) << std::endl;
    }

}
void CLEditCF::OpenLogn()
{

    LogFile.open("CLEditCFLog.txt", ios_base::out);

    if  (!LogFile.is_open())
    {
        msg = "Log file Open error";
        abendi = 3504;
        abend = true;
        std::cout << msg << abendi << std::endl;    // better than flying blind
        return;
    }

}
void CLEditCF::CloseLog()
{

    LogFile.close();

}
void CLEditCF::OpenErr()
{
    ErrFile.open("CLEditCFErr.txt", std::ios::out | ios_base::app);

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

    if (Logging)
    {
        LogFile << "Error file size " << to_string(bytecnt) << std::endl;
    }

}
void CLEditCF::OpenErrn()
{

    ErrFile.open("CLEditCFErr.txt", std::ios::out);

    if  (!ErrFile.is_open())
    {
        msg = "Error file Open error";
        abendi = 3506;
        abend = true;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }

}
void CLEditCF::CloseErr()
{

    ErrFile.close();

}
void CLEditCF::OpenStat()
{

    StatFile.open("CLEditCFStat.txt", ios_base::out | ios_base::app);

    if  (!StatFile.is_open())
    {
        msg = "Stat file Open error";
        abendi = 3507;
        abend = true;
        std::cout << msg << abendi << std::endl;    // better than flying blind
        return;
    }

    bytecnt = StatFile.tellg();

    if  (bytecnt > FILE_SIZE)
    {
        CloseStat();
        ETL.Logging = Logging;
        ETL.fileiname = "CLEditCFStat.txt";
        rc = ETL.ETL();
        OpenStatn();
    }

    if (Logging)
    {
        LogFile << "Stat file size " << to_string(bytecnt) << std::endl;
    }

}
void CLEditCF::OpenStatn()
{

    StatFile.open("CLEditCFStat.txt", ios_base::out);

    if  (!StatFile.is_open())
    {
        msg = "Stat file Open error";
        abendi = 3508;
        abend = true;
        std::cout << msg << abendi << std::endl;    // better than flying blind
        return;
    }

}
void CLEditCF::CloseStat()
{

    StatFile.close();

}
