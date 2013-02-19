/*
文件:server_controller.h
作者:龚世伟
日期:2013.02.18
描述:请求解析转发和反馈
*/

#ifndef TTSS_SERVER_CONTROLLER_H_
#define TTSS_SERVER_CONTROLLER_H_

 //处理请求,返回反馈
void handle_request(const char*,char*);


//打印编译信息
void print_compile_info();
#endif // TTSS_SERVER_CONTROLLER_H_

//加载处理请求函数的动态库
void load_lib_handle(const char*);