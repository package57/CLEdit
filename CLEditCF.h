#pragma once
#ifndef CLEDITCF_H
#define CLEDITCF_H
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <ctype.h>

class CLEditCF
{
    public:

        std::string fileiname;
        std::string fileoname;

        CLEditCF();
        virtual ~CLEditCF();

        int copyfile(std::string, std::string);

    protected:

    private:

        std::fstream filei;
        char fileic;
        int fileitellg;
        int fileibytecnt;
        int fileireccnt;

        std::fstream fileo;
        char fileoc;
        int fileoi;
        int fileotellg;
        char fileir[81];

        char tick;
        char tack;
        int i;
        int j;
        int k;
        int start_s;
        int stop_s;
        std::string msg;
        int abendi;
        bool abend;
        bool debug;

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
        void abnormal();

};
#endif // CLEDITCF_H
