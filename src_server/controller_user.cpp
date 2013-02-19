/*
文件:controller_user.cpp
作者:龚世伟
日期:2013.02.19
描述:处理用户登陆、注册和修改信息的控制器
*/

#include "controller_user.h"
#include <string>
#include "../json_lib/json.h"

extern "C" void handle_login(const char* request,char* feedback){
	Json::Value request_root,feedback_root; 
	request_root["result"] = "pass";
	request_root["message"] = "get request login!";
	strcpy(feedback,request_root.toStyledString().c_str());
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
