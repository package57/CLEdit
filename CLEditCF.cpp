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
    start_s = clock();

    CLEditCF::init();

    CLEditCF::openfo();   // exit on error

    CLEditCF::openfi();   // exit on error

    i = 0;  //used to track position
    j = 0;  //used for logical record length

    CLEditCF::readfir();

    while (fileitellg > 0)  // at end of file the read returns -1
    {
        CLEditCF::processfir();
    }

    CLEditCF::closefi();

    CLEditCF::closefo();

    CLEditCF::eop();

    stop_s = clock();
    std::cout << "elapsed time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

    return 0;

}

void CLEditCF::init()
{

    debug = false;

    if  (debug)
    {
        std::cout << "init" << std::endl;
    }

    std::time_t currentdatetime = std::time(nullptr);

    std::cout << "Welcome " << std::ctime(&currentdatetime) << std::endl;

}

void CLEditCF::openfo()
{

    if  (debug)
    {
        std::cout << "openfo" << std::endl;
    }

    fileo.open(fileoname, std::ios::out);

    if  (!fileo.is_open())
    {
        msg = "file Out Open error";
        abendi = 3500;
        CLEditCF::abnormal(); // exits program
    }
}

void CLEditCF::openfi()
{

    if  (debug)
    {
        std::cout << "openfi" << std::endl;
    }

     filei.open(fileiname, std::ios::in );

    if  (!filei.is_open())
    {
        msg = "file In Open error";
        abendi = 3501;
        CLEditCF::abnormal();   // exits program
    }

}

void CLEditCF::closefi()
{

    if  (debug)
    {
        std::cout << "closefi" << std::endl;
    }

    filei.close();

}

void CLEditCF::closefo()
{

    if  (debug)
    {
        std::cout << "closefo" << std::endl;
    }

    fileo.close();

}

void CLEditCF::eop()
{

    if  (debug)
    {
        std::cout << "eop" << std::endl;
    }

    std::cout << "File In Bytes " << fileibytecnt << std::endl;

    std::cout << "File In Records " << fileireccnt << std::endl;

}

void CLEditCF::processfir()
{

   if  (debug)
    {
        std::cout << "processfir" << std::endl;
        std::cout << "look " << fileic << std::endl;
    }

    j++;

    fileir[i] = fileic;

    i++;

    if  (fileic == '\n')
    {
       CLEditCF::processfor();
    }

    CLEditCF::readfir();

}

void CLEditCF::readfir()
{

    if  (debug)
    {
        std::cout << "readfir" << std::endl;
    }

    fileic = filei.get();   // one byte at a time

    fileitellg = filei.tellg();

    if  (filei.tellg() > 0)
    {
        fileibytecnt = filei.tellg();
    }

}

void CLEditCF::processfor()
{

    if  (debug)
    {
        std::cout << "processfor" << std::endl;
    }

    CLEditCF::writefor();

    CLEditCF::initfileir();

}

void CLEditCF::writefor()
{

    if  (debug)
    {
        std::cout << "writefor" << std::endl;
    }

    fileo << fileir;

    fileireccnt++;

}

void CLEditCF::initfileir()
{

    if  (debug)
    {
        std::cout << "initfileir" << std::endl;
    }

    for (i = 0; i < j; i++)   // i < j to save time
    {
        fileir[i] = '\0';     // set to null
    }

    i = 0;
    j = 0;

}

 void CLEditCF::abnormal()
 {

    std::cout << msg << " : " << abendi << std::endl;

    exit(abendi);

 }
