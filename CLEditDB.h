#pragma once
#ifndef CLEDITDB_H
#define CLEDITDB_H
#include <stdlib.h>
#include <iostream>

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

        std::string what = "";
        std::string state = "";

        sql::Driver * driver;
        sql::Connection * con;
        sql::Statement * stmt;
        sql::ResultSet * res;

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
#endif // CLEDITDB
