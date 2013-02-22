/*
文件:controller_user.cpp
作者:龚世伟
日期:2013.02.19
描述:处理用户登陆、注册和修改信息的控制器
*/

#include "controller_user.h"
#include <cstring>
#include <cstdio>
#include "../json_lib/json.h"
#include "business_user.h"

void get_user(const char* request,char* username, char* password, char* real_name){
	Json::Reader reader; 
	Json::Value request_root; 
	reader.parse(request, request_root);
	strcpy(username, request_root["username"].asCString());
	strcpy(password, request_root["password"].asCString());
	strcpy(real_name, request_root["real_name"].asCString());
}

extern "C" void handle_login(const char* request,char* feedback){
	Json::Value	feedback_root; 
	char username[32],password[32],real_name[32];
	get_user(request,username,password,real_name);
	
	bool result = user_login(username, password, real_name);

	if (result)
	{
		feedback_root["result"] = "pass";
		feedback_root["message"] = "login seccess!";
		feedback_root["real_name"] = real_name;
	} else 
	{
		feedback_root["result"] = "fail";
		feedback_root["message"] = "wrong username or password!";
	}
	
	strcpy(feedback,feedback_root.toStyledString().c_str());
}

extern "C" void handle_register(const char* request,char* feedback){
	Json::Value	feedback_root; 
	char username[32],password[32],real_name[32];
	get_user(request,username,password,real_name);

	int user_exist = user_check_exist(username);

	if (user_exist)
	{
		feedback_root["result"] = "fail";
		feedback_root["message"] = "username exists!";
		strcpy(feedback,feedback_root.toStyledString().c_str());
	} else 
	{
		user_register(username, password, real_name);
		feedback_root["result"] = "pass";
		feedback_root["message"] = "register success!";
		strcpy(feedback,feedback_root.toStyledString().c_str());
	}
}

extern "C" void handle_modify(const char* request,char* feedback){
	Json::Value	feedback_root; 
	char username[32],password[32],real_name[32];
	get_user(request,username,password,real_name);

	int user_exist = user_check_exist(username);
	
	if (!user_exist)
	{
		feedback_root["result"] = "fail";
		feedback_root["message"] = "user do not exists!";
		strcpy(feedback,feedback_root.toStyledString().c_str());
	} else 
	{
		user_modify(username,password,real_name);
		feedback_root["result"] = "pass";
		feedback_root["message"] = "modify success!";
		strcpy(feedback,feedback_root.toStyledString().c_str());
	}
}
