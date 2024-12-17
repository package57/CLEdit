#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <ctype.h>
#define FILE_SIZE 102400
using namespace std;
class CLEditCF
{
    public:

        CLEditCF();
        virtual ~CLEditCF();

        std::string fileiname;
        std::string fileoname;

        int reccnt;

        struct InputFile
        {
            std::string IFCode; // the line of code
        };
        InputFile inputfile[25000];  // 23,000 line is the biggest single block of code I've ever seen aka "203"

        int copyfile(std::string, std::string);

        int openfile(std::string);  // open file - load into InputFile structure

        int savefile(std::string);  // save / save as file - from InputFile structure

    protected:

    private:

        std::fstream LogFile;
        std::fstream ErrFile;
        std::fstream filei;
        std::fstream fileo;

        int bytecnt;        // bytes in a file
        int fileireccnt;
        int fileibytecnt;
        int fileoreccnt;
        int fileobytecnt;

        int fileitellg;
        int fileoi;
        int fileotellg;
        int i;
        int j;
        int k;
        int l;
        int Outreccnt;
        int start_s;
        int stop_s;
        int abendi;

        char fileic;
        char fileoc;
        char fileir[253];  // the largest record allowed for IBM TSO PDS BIM
        char arr[253];     // the largest record allowed for IBM TSO PDS BIM
        char tick;
        char tack;

        std::string str;
        std::string msg;
        std::string action;

        bool abend;

        void init();
        void OpenLog();
        void OpenLogn();
        void CloseLog();
        void OpenErr();
        void OpenErrn();
        void CloseErr();
        void openfo();
        void openfi();
        void closefo();
        void closefi();
//      File Input Record
        void processfiropen();
        void processfircopy();
        void readfir();
//      File Output Record
        void processforopen();
        void processforcopy();
        void writefor();
        void initfileir();
        void initsavefileir();
        void stringtochar();
        void eop();

};
