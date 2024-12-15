#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <ctype.h>
#include <sstream>

#include "mysql.h"
#include "mysql_driver.h"
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
using namespace std;
class CLEditDB
{
    public:

        CLEditDB();
        virtual ~CLEditDB();

        int errorcode = 0;
        int rowcnt = 0;
        int abendi;
        int u;
        int i;
        int n;
        bool OnOne;

        std::string what = "";
        std::string state = "";

        std::string DataBase;
        std::string TableName;
        std::string Query;
        std::string CodeStr;
        int         CodeStrl;
        std::string CodeNew;
        int         CodeId;
       	stringstream sql;

        struct InputFile
        {
            std::string IFCode; // the line of code
        };
        InputFile inputfile[25000];  // 23,000 line is the biggest single block of code I've ever seen aka "203"

        sql::Driver * driver;
        sql::Connection * con;
        sql::Statement * stmt;
        sql::PreparedStatement * pstmt;
        sql::ResultSet * res;

        void Initialize();
        void InitInputFile();
        void Driver();
        void Connect();
        void Statement();
        int  Count();
        void Cursor();
        void FromStage();
        void ToStage();
        void UseDb();
        void DropTable();
        void CreateTable();
        void InsertRow();
        void FixQuote();
        void Error();
        void Free();

    protected:

    private:

        std::fstream LogFile;
        std::fstream ErrFile;

};
