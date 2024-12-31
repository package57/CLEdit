#ifndef CLEDITCF_H
#define CLEDITCF_H

#include "CLEditXETL.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <ctype.h>
#include <chrono>
#define FILE_SIZE 102400
using namespace std;
class CLEditCF
{
    public:

        CLEditCF();
        virtual ~CLEditCF();

        struct dateseq
        {
            std::string date;
            std::string seq;
        };
        dateseq DateSeq;

        std::string fileiname;
        std::string fileoname;
        std::string Mode;       // save, saveas, create

        int reccnt;

        bool Logging;

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

    // gather log data
        CLEditXETL ETL;

        std::fstream LogFile;
        std::fstream ErrFile;
        std::fstream StatFile;
        std::fstream filei;
        std::fstream fileo;

        std::time_t currentdatetime;

        int rc;
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

        bool abend;

        void init();
        void OpenLog();
        void OpenLogn();
        void CloseLog();
        void OpenErr();
        void OpenErrn();
        void CloseErr();
        void OpenStat();
        void OpenStatn();
        void CloseStat();
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

#endif // CLEDITCF_H
