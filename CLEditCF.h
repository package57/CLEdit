#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <ctype.h>
using namespace std;
class CLEditCF
{
    public:

        CLEditCF();
        virtual ~CLEditCF();

        std::string fileiname;
        std::string fileoname;

        int fileibytecnt;
        int fileireccnt;
        int fileoreccnt;

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

        std::fstream filei;
        char fileic;
        int fileitellg;


        std::fstream fileo;
        char fileoc;
        int fileoi;
        int fileotellg;
        char fileir[201];

        std::string mode;
        std::string str;
        char arr[201];
        char tick;
        char tack;
        int i;
        int j;
        int k;
        int l;
        int Outreccnt;
        int start_s;
        int stop_s;
        std::string msg;
        int abendi;
        bool abend;

        void init();
        void openfo();
        void openfi();
        void closefi();
        void closefo();
        void eop();
        void processfir();
        void readfir();
        void processfor();
        void writefor();
        void initfileir();
        void initsavefileir();
        void stringtochar();

};
