#include "business_user.h"

#include <cstring>

#include "database.h"


bool user_check_exist(const char* username){
	char sql_buf[512];
	sprintf(sql_buf,"SELECT * FROM `USER` WHERE UNAME = \"%s\"",
		username);
	std::string sql__check_exist_string = sql_buf;
	MYSQL_RES* result_check = dao.executeSQL(sql__check_exist_string);
	int result;

	std::string real_name;

	if (dao.get_first_row_column(result_check,"REAL_NAME",real_name))
	{
		result = true;
	} else {
		result = false;
	}
	mysql_free_result(result_check);
	return result;
}

bool user_login(const char* username, const char* password,
	char * real_name_buf){

	char sql_buf[512];
	sprintf(sql_buf,"SELECT * FROM `USER` WHERE UNAME = \"%s\" AND PASSWORD = \"%s\"",
		username,password);
	std::string sql_string = sql_buf;
	MYSQL_RES* result = dao.executeSQL(sql_string);
	bool login_result;

	std::string real_name;

	if ( dao.get_first_row_column(result,"real_name",real_name))
	{
		strcpy(real_name_buf,real_name.c_str());
		login_result = true;
	} else 
	{
		login_result = false;
	}
	mysql_free_result(result);
	return login_result;
}

bool user_register(const char* username, const char* password, const char* real_name){
	char sql_buf[512];
	sprintf(sql_buf,"INSERT INTO `USER`(UNAME,PASSWORD,REAL_NAME) VALUES(\"%s\",\"%s\",\"%s\")",
		username,password,real_name);
	std::string sql_string = sql_buf;
	MYSQL_RES* result = dao.executeSQL(sql_string);
	mysql_free_result(result);
	return true;
}

bool user_modify(const char* username, const char* password, const char* real_name){
	char sql_buf[512];
	sprintf(sql_buf,"UPDATE `USER` SET PASSWORD = \"%s\", REAL_NAME = \"%s\" WHERE UNAME = \"%s\"",
		password,real_name,username);
	std::string sql_string = sql_buf;
	MYSQL_RES* result = dao.executeSQL(sql_string);
	mysql_free_result(result);
}