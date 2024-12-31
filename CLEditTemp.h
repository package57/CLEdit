#ifndef CLEDITTEMP_H
#define CLEDITTEMP_H
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
class CLEditTemp
{
    public:

        CLEditTemp();
        virtual ~CLEditTemp();

// action reaction
        struct dateseq
        {
            std::string date;
            std::string seq;
        };
        dateseq DateSeq;

        bool Logging;

        int DoStuff();


    protected:

    private:

        CLEditXETL ETL;

        std::fstream LogFile;
        std::fstream ErrFile;
        std::fstream StatFile;

        std::time_t currentdatetime;

        int bytecnt;

        int start_s;
        int stop_s;
        int abendi;
        int res;

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
        void eop();

};

#endif // CLEDITTEMP_H
