#include <stdlib.h>
#include <iostream>

#include "mysql.h"
#include "mysql_driver.h"
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
//#include <cppconn/connection.h>
//#include <cppconn/metadata.h>
//#include <cppconn/resultset_metadata.h>
//#include <cppconn/warning.h>
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

        std::string what = "";
        std::string state = "";

        struct InputFile
        {
            std::string IFCode; // the line of code
        };
        InputFile inputfile[25000];  // 23,000 line is the biggest single block of code I've ever seen aka "203"

        sql::Driver * driver;
        sql::Connection * con;
        sql::Statement * stmt;
        sql::ResultSet * res;

        void InitInputFile();
        void Driver();
        void Connect();
        void Statement();
        int  Cursor();
        void Process();
        void Free();

        void Error();

    protected:

    private:
};
