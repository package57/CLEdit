#ifndef CLEDITXETL_H
#define CLEDITXETL_H

// C++
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <ctype.h>
#include <chrono>
#include <sstream>
// MySQL
#include "mysql.h"
#include "mysql_driver.h"
#include "mysql_connection.h"
// Cpp Conn
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
//#define FILE_SIZE 102400
#define FILE_SIZE 1000
using namespace std;
class CLEditXETL
{
    public:

        CLEditXETL();
        virtual ~CLEditXETL();

        std::string fileiname;

        int ETL();

    protected:

    private:

// objects
        sql::Driver * driver;
        sql::Connection * con;
        sql::Statement * stmt;
        sql::PreparedStatement * pstmt;
        sql::ResultSet * res;

// structures
        struct logaction
        {
            std::string DateSeq;
            std::string User;
            std::string Time;
            std::string Action;
            std::string InputFile;
                    int Inputrecs;
                    int Inputbytes;
            std::string OutputFile;
                    int Outputrecs;
                    int Outputbytes;
                    int RowCnt;
            std::string DataBase;
            std::string TableName;
                    int ElapsedAct;
                    int ElapsedRes;
        };
        logaction LA;
        logaction DB;

        struct dateseq
        {
            std::string date;
            std::string seq;
        };
        dateseq DateSeq;

// file stream
        std::fstream LogFile;
        std::fstream ErrFile;
        std::fstream filei;
// SQL
       	stringstream sql;
// timestamp
        std::time_t currentdatetime;
// int
        int rowcnt;
        int start_s;
        int stop_s;
        int abendi;
        int errorcode;
        int u;
        int i;
        int n;
        int reccnt;
        int bytecnt;        // bytes in a file
        int fileireccnt;
        int fileibytecnt;
        int fileitellg;
        int fileoi;
        int fileotellg;
        int j;
        int k;
        int l;
        int InsertCnt;
        int UpdateCnt;
        int CodeId;
        int CodeStrl;

// char
        char fileic;
        char fileir[253];  // the largest record allowed for IBM TSO PDS BIM
        char arr[253];     // the largest record allowed for IBM TSO PDS BIM

// strings

        std::string str;
        std::string msg;
        std::string action;
        std::string DataBase;
        std::string TableName;
        std::string what;
        std::string state;
        std::string Query;
        std::string CodeStr;
        std::string CodeNew;
        std::string Word;

// boolean
        bool abend;
        bool elapsed;
        bool tbexists;
        bool welcome;
        bool OnOne;
        bool OnOneWelcome;
        bool OnOneUser;
        bool OnOneCommand;
        bool OnOneParameterone;
        bool OnOneParametertwo;
        bool OnOneUsageDate;
        bool OnOneElapsed;
        bool OnOneSelect;
        bool OnOneGetRes;
        bool OnOneUpdate;
        bool OnOneInsert;
        bool OnOneInitRecord;
        bool OnOneInitLA;
        bool OnOneInBytes;
        bool OnOneInRecords;
        bool OnOneOutBytes;
        bool OnOneOutRecords;

// file functions
        void Init();
        void InitLA();
        void OpenLog();
        void OpenLogn();
        void OpenErr();
        void OpenErrn();
// open input file
        void OpenFile();
// connect to database
        void Bind();
        void Error();
        void Driver();
        void Connect();
        void Statement();
        void UseDb();
        bool Exists();
        void DropTable();
        void CreateTable();

        void ReadFile();
//      File Input Record
        void ProcessFile();
        void ProcessRecord();
        void Select();
        void GetRes();
        void Update();
        void Insert();

        void Gather();
        void LookforWord();
        void Welcome();
        void User();
        void Command();
        void Parameterone();
        void Parametertwo();
        void UsageDate();
        void Elapsed();
        void FileInBytes();
        void FileInRecords();
        void FileOutBytes();
        void FileOutRecords();


        void InitRecord();
        void EoP();
        void CloseFile();
        void CloseLog();
        void CloseErr();
        void Free();
 /*     void Freedriver();    not allowed */
        void Freecon();
        void Freestmt();
        void Freepstmt();
        void Freeres();

};

#endif // CLEDITXETL_H
