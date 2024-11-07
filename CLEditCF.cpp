#include "CLEditCF.h"
using namespace std;
CLEditCF::CLEditCF()
{
    //ctor
}

CLEditCF::~CLEditCF()
{
    //dtor
}

int CLEditCF::copyfile(std::string fileiname, std::string fileoname)
{
    mode = "copy";

    start_s = clock();

    init();

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

    closefi();

    closefo();

    eop();

    stop_s = clock();
    std::cout << "elapsed time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

copyexit:

    return abendi;

}

int CLEditCF::openfile(std::string fileiname)
{
    mode = "open";

    start_s = clock();

    init();

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

    closefi();

    eop();

    stop_s = clock();
    std::cout << "elapsed time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

openexit:

    return abendi;

}
int CLEditCF::savefile(std::string fileoname)
{
    mode = "save";

    start_s = clock();

    init();

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

    closefo();

    eop();

    stop_s = clock();
    std::cout << "elapsed time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

saveexit:

    return abendi;

}
void CLEditCF::stringtochar()
{

    for (l = 0; l < 81; l++)
    {
        arr[l] = '\0';     // set to null
    }

    strcpy(arr, inputfile[i].IFCode.c_str());

    k = inputfile[i].IFCode.length();

    for (l = 0; l < k; l++)
    {
        fileir[l] = arr[l];
    }

}
void CLEditCF::init()
{

    std::time_t currentdatetime = std::time(nullptr);

    std::cout << "Welcome " << std::ctime(&currentdatetime) << std::endl;

    for (l = 0; l < 81; l++)
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
    }

}

void CLEditCF::openfi()
{

    filei.open(fileiname, std::ios::in );

    if  (!filei.is_open())
    {
        msg = "FROM file Open error";
        abendi = 3501;
    }

}

void CLEditCF::closefi()
{

    filei.close();

}

void CLEditCF::closefo()
{

    fileo.close();

}

void CLEditCF::eop()
{

    std::cout << "File In Bytes " << fileibytecnt << std::endl;

    std::cout << "File In Records " << fileireccnt << std::endl;

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

    if  (mode == "copy")
    {
        writefor();
    }
    else
    {
        if  (mode == "open")
        {
            fileireccnt++;
            inputfile[Outreccnt].IFCode = fileir;
            Outreccnt++;
        }
    }

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
