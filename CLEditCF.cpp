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

    if (abendi != 0)
    {
        goto copyexit;
    }

    openfo();

    if (abendi != 0)
    {
        goto copyexit;
    }

    openfi();

    if (abendi != 0)
    {
        goto copyexit;
    }

    i = 0;  //used to track position
    j = 0;  //used for logical record length

    readfir();

    while (fileitellg > 0)  // at end of file the read returns -1
    {
        processfir();
    }

    LogFile << "copy file " << std::endl;

    eop();

copyexit:

    return abendi;

}
int CLEditCF::openfile(std::string fileiname)
{

    init();

    if (abendi != 0)
    {
        goto openexit;
    }

    openfi();

    if (abendi != 0)
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
    Outreccnt = 0;

    readfir();

    while (fileitellg > 0)  // at end of file the read returns -1
    {
        processfir();
    }

    LogFile << "open file " << std::endl;

    eop();

openexit:

    return abendi;

}
int CLEditCF::savefile(std::string fileoname)
{

    init();

    if (abendi != 0)
    {
        goto saveexit;
    }

    openfo();

    if (abendi != 0)
    {
        goto saveexit;
    }

    for (i = 0; i < fileoreccnt; i++)
    {
        stringtochar();
        writefor();
        initsavefileir();
    }

    LogFile << "save file " << std::endl;

    eop();

saveexit:

    return abendi;

}
void CLEditCF::eop()
{

    stop_s = clock();

    LogFile << "elapsed time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

    LogFile << "File In Bytes " << fileibytecnt << std::endl;

    LogFile << "File In Records " << fileireccnt << std::endl;

    LogFile << "File Out Bytes " << fileobytecnt << std::endl;

    LogFile << "File Out Records " << fileoreccnt << std::endl;

    closefi();

    closefo();

    closelog();

    closeerr();

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

    start_s = clock();

    fileibytecnt = 0;
    fileobytecnt = 0;
//  fileireccnt  = 0;  // no
//  fileoreccnt  = 0;  // no

    openlog();

    if (abendi != 0)
    {
        return;
    }

    openerr();

    if (abendi != 0)
    {
        return;
    }

    LogFile << "init " << std::endl;

    std::time_t currentdatetime = std::time(nullptr);

    LogFile << "Welcome " << std::ctime(&currentdatetime) << std::endl;

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
        abendi = 3503;
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
        abendi = 3504;
        ErrFile << msg << abendi << std::endl;
        return;
    }

    closefi();

// now you can open the file
    filei.open(fileiname, std::ios::in );

    if  (!filei.is_open())
    {
        msg = "FROM file Open error";
        abendi = 3505;
        ErrFile << msg << abendi << std::endl;
        return;
    }

}
void CLEditCF::closefi()
{

    filei.close();

}
void CLEditCF::processfir()
{

    j++;

    fileir[i] = fileic;

    i++;

    if  (fileic == '\n')
    {
       processfor();
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
void CLEditCF::processfor()
{

    fileireccnt++;

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

    fileireccnt++;

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
void CLEditCF::openlog()
{

    LogFile.open("CLEditCFLogFile.txt", std::ios::out);

    if  (!LogFile.is_open())
    {
        msg = "Log file Open error";
        abendi = 3501;
        std::cout << msg << abendi << std::endl;    // better than flying blind
        return;
    }
}
void CLEditCF::closelog()
{

    LogFile.close();

}
void CLEditCF::openerr()
{
    ErrFile.open("CLEditCFErrFile.txt", std::ios::out);

    if  (!ErrFile.is_open())
    {
        msg = "Error file Open error";
        abendi = 3502;
        std::cout << msg << abendi << std::endl;   // better than flying blind
        return;
    }
}
void CLEditCF::closeerr()
{

    ErrFile.close();

}
