#ifndef CLEDITAR_H
#define CLEDITAR_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <ctype.h>
#include <chrono>
#include <iomanip>
#define FILE_SIZE 1000
//#define FILE_SIZE 102400
using namespace std;
class CLEditAR
{
    public:

        CLEditAR();
        virtual ~CLEditAR();

        struct dateseq
        {
            std::string date;
            std::string seq;
        };
        dateseq DateSeq;

        int ActReact();

    protected:

    private:

        std::fstream LogFile;
        std::fstream ErrFile;
        std::fstream ActFile;

        std::time_t currentdatetime;

        std::time_t timestamp;
/* struct */  tm datetime;

        int start_s;
        int stop_s;
        int abendi;
        int bytecnt;
        int lrecl;
        char fileic;
        int i;
        int j;
        int seq;
        char Actrec[19];

        std::string str;
        std::string msg;
        std::string action;
        std::string ToString(int);
        dateseq CurrentAR;
        dateseq NewAR;

        bool abend;

        void init();
        void OpenLog();
        void OpenLogn();
        void CloseLog();
        void OpenErr();
        void OpenErrn();
        void CloseErr();
        void eop();

        void GetDate();
        void OpenI();
        void OldFile();
        void Read();
        void Close();
		void OpenO();
		void Write();
        void NewFile();
        void DateMatch();
        void FormatRec();


};

#endif // CLEDITAR_H
