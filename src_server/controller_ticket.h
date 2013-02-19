/*
文件:controller_user.h
作者:龚世伟
日期:2013.02.19
描述:处理用户查票、订票和改签的控制器
*/

/*
设计思想:
为了分离主控模块(server_comtroller)和各个分控制模块的耦合,
各个主控模块并没有直接得到分控制模块的函数声明,而是通过函数名检索需要的函数指针。
例如在处理"login"这个请求时,主控模块会检索函数"handle_login",得到函数指针并调用。
关于具体的设计,见文档:doc/Design of server controller.pdf。
*/

#ifndef TTSS_SERVER_CONTROLLER_TICKET_H_
#define TTSS_SERVER_CONTROLLER_TICKET_H_

extern "C" void handle_query(const char* request,char* feedback);
extern "C" void handle_order(const char* request,char* feedback);
extern "C" void handle_change(const char* request,char* feedback);

#endif //TTSS_SERVER_CONTROLLER_TICKET_H_
