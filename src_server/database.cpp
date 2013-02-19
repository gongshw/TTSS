#include "database.h"

#include <iostream>
#include <fstream>

#include "../json_lib/json.h"

using namespace std;

DAO::DAO()
{  
	connection = mysql_init(NULL);

	Json::Reader reader;
	Json::Value config_root;
	fstream config_file("./config.json");
	reader.parse(config_file,config_root); 

	Json::Value database_config = config_root["database"];
	string server_host = database_config["host"].asString();
	string user = database_config["username"].asString();
	string password = database_config["password"].asString();
	string db_name = database_config["database_name"].asString();

	if(this->initDB(server_host,user,password,db_name))
		cout<<"连接到数据库:"<<db_name<<"@"<<server_host<<"。"<<endl;
		//cout<<"用户名"<<user<<" 密码:"<<password<<" 数据库:"<<db_name<<endl;
}
DAO::~DAO()
{  
	mysql_close(connection);

}

bool DAO::initDB(string server_host , string user, string password , string db_name )
{  
	
	if (!mysql_real_connect(connection , server_host.c_str() , user.c_str() , password.c_str() , db_name.c_str() , 0 , NULL , 0))
	{
		fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(connection));
		return false;
	} else
		return true;
}


MYSQL_RES* DAO::executeSQL(string sql_str)
{
	MYSQL_RES *res;
	//mysql_query(connection, "set names utf8");
	int t = mysql_query(connection,  sql_str.c_str());
	if(t)
	{
		printf("Error making query: %s\n" , mysql_error(connection));
		exit(1);
	}
	res = mysql_use_result(connection);
	return res;
}

DAO dao;