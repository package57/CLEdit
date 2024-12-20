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

        int DoStuff();

    protected:

    private:

        std::fstream LogFile;
        std::fstream ErrFile;

        std::time_t currentdatetime;

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
