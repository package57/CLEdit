#ifndef CLEDITRP_H
#define CLEDITRP_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <ctype.h>
#include <chrono>
#define FILE_SIZE 1000
//#define FILE_SIZE 102400
using namespace std;
class CLEditRP
{
    public:

        CLEditRP();
        virtual ~CLEditRP();

        int Report();

    protected:

    private:

        std::fstream LogFile;
        std::fstream ErrFile;

        std::time_t currentdatetime;

        struct cfaction
        {
            std::string User;
            std::string Date;
                    int Seq;
            std::string Time;
            std::string Action;
            std::string InputFile;
                    int Inputrecs;
                    int Inputbytes;
            std::string OutputFile;
                    int Outputrecs;
                    int Outputbytes;

        };
        cfaction CFAction;

        struct dbaction
        {
            std::string User;
            std::string Date;
                    int Seq;
            std::string Time;
            std::string Action;
                    int rowcnt;
            std::string DataBase;
            std::string TableName;
            std::string ElapsedTime;
        };
        dbaction DBAction;



        int bytecnt;
        int start_s;
        int stop_s;
        int abendi;

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
        void eop();

};

#endif // CLEDITRP_H
