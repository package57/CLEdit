#ifndef CLEDITDB_H
#define CLEDITDB_H

#include "CLEditXETL.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <ctype.h>
#include <sstream>
#include <chrono>

#include "mysql.h"
#include "mysql_driver.h"
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#define FILE_SIZE 1000
//#define FILE_SIZE 102400
using namespace std;
class CLEditDB
{
    public:

        CLEditDB();
        virtual ~CLEditDB();

// gather log data
        CLEditXETL ETL;

        struct dateseq
        {
            std::string date;
            std::string seq;
        };
        dateseq DateSeq;

        std::string DataBase;
        std::string TableName;
        std::string Mode;       // create or load

        int rowcnt;

        struct InputFile
        {
            std::string IFCode; // the line of code
        };
        InputFile inputfile[25000];  // 23,000 line is the biggest single block of code I've ever seen aka "203"

        int Bind();

        void Cursor();
        void FromStage();
        int  Count();
        void ToStage();

        void Free();

    protected:

    private:

        sql::Driver * driver;
        sql::Connection * con;
        sql::Statement * stmt;
        sql::PreparedStatement * pstmt;
        sql::ResultSet * res;

        std::time_t currentdatetime;

        int rc;
        int start_s;
        int stop_s;
        int abendi;
        int errorcode;
        int u;
        int i;
        int n;

        bool OnOne;
        bool abend;

        std::string what;
        std::string state;

        std::string Query;
        std::string CodeStr;
        int         CodeStrl;
        std::string CodeNew;
        int         CodeId;
       	stringstream sql;


        std::fstream LogFile;
        std::fstream ErrFile;

        int bytecnt;        // bytes in a file

        std::string msg;

        void Initialize();
        void Driver();
        void Connect();
        void Statement();

        void InitInputFile();
        void UseDb();
        void DropTable();
        void CreateTable();
        void InsertRow();
        void FixQuote();
        void Error();
        void OpenLog();
        void OpenLogn();
        void CloseLog();
        void OpenErr();
        void OpenErrn();
        void CloseErr();

 /*     void Freedriver();    not allowed */
        void Freecon();
        void Freestmt();
        void Freepstmt();
        void Freeres();

};

#endif // CLEDITDB_H
