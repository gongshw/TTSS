/*
文件:controller_user.cpp
作者:龚世伟
日期:2013.02.19
描述:处理用户登陆、注册和修改信息的控制器
*/

#include "controller_user.h"
#include <cstring>
#include "../json_lib/json.h"
#include "database.h"

void get_user(const char* request,string & username_str,string & password_str){
	Json::Reader reader; 
	Json::Value request_root; 
	reader.parse(request, request_root);
	username_str = request_root["username"].asString();
	password_str = request_root["username"].asString();
}

extern "C" void handle_login(const char* request,char* feedback){
	Json::Value	feedback_root; 
	std::string username_str,password_str;
	get_user(request,username_str,password_str);


	std::string sql_string = "SELECT * FROM `USER` WHERE UNAME = \""+username_str+"\" AND PASSWORD = \""+password_str+"\";";
	MYSQL_RES* result = dao.executeSQL(sql_string);

	if (mysql_num_fields(result)>0)
	{
		feedback_root["result"] = "pass";
		feedback_root["message"] = "login seccess!";
	} else 
	{
		feedback_root["result"] = "fail";
		feedback_root["message"] = "wrong username or password!";
	}
	mysql_free_result(result);
	
	strcpy(feedback,feedback_root.toStyledString().c_str());
}

extern "C" void handle_register(const char* request,char* feedback){
	Json::Value request_root,feedback_root; 
	request_root["result"] = "pass";
	request_root["message"] = "get request 注册!";
	strcpy(feedback,request_root.toStyledString().c_str());
}

extern "C" void handle_modify(const char* request,char* feedback){
	Json::Value request_root,feedback_root; 
	request_root["result"] = "pass";
	request_root["message"] = "get request 修改信息!";
	strcpy(feedback,request_root.toStyledString().c_str());
}
