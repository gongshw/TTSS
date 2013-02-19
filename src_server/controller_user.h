/*
文件:controller_user.h
作者:龚世伟
日期:2013.02.19
描述:处理用户登陆、注册和修改信息的控制器
*/

/*
设计思想:
为了分离主控模块(server_comtroller)和各个分控制模块的耦合,
各个主控模块并没有直接得到分控制模块的函数声明,而是通过函数名检索需要的函数指针。
例如在处理"login"这个请求时,主控模块会检索函数"handle_login",得到函数指针并调用。
关于具体的设计,见文档:doc/Design of server controller.pdf。
*/

#ifndef TTSS_SERVER_CONTROLLER_USER_H_
#define TTSS_SERVER_CONTROLLER_USER_H_

#include <string>

extern "C" void handle_login(const char* request,char* feedback);
extern "C" void handle_modify(const char* request,char* feedback);
extern "C" void handle_register(const char* request,char* feedback);

void get_user(const char* request,std::string&,std::string&);

#endif //TTSS_SERVER_CONTROLLER_USER_H_