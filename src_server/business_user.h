/*
文件:business_user.h
作者:龚世伟
日期:2013.02.20
描述:用户登陆、注册和修改信息的业务逻辑
*/


#ifndef TTSS_SERVER_BUSINESS_USER_H_
#define TTSS_SERVER_BUSINESS_USER_H_

bool user_login(const char* username, const char* password);
bool user_modify(const char* username, const char* password, const char* real_name);
bool user_register(const char* username, const char* password, const char* real_name);
bool user_check_exist(const char* username);


#endif //TTSS_SERVER_BUSINESS_USER_H_