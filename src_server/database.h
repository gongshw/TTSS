#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
class DAO
{
public:
    DAO();
    bool initDB(string server_host , string user, string password, string db_name);
    MYSQL_RES* executeSQL(string sql_str);
    bool get_column(MYSQL_ROW, MYSQL_RES*,const char*,string &);
	bool get_first_row_column(MYSQL_RES*,const char*,string&);
    ~DAO();
private:
    MYSQL *connection;
};

extern DAO dao;