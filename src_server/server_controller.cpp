/*
文件:server_controller.h
作者:龚世伟
日期:2013.02.18
描述:请求解析转发和反馈

说明:这是服务器核心的控制器。
*/

#include "server_controller.h"

extern "C"{
	#include <dlfcn.h>
}
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include "../json_lib/json.h"
#include "communicate_server.h"



void * lib_handle;

//跟据函数名返回函数的函数指针。
//可以通过这样的方法检索到的函数需要在动态库./lib_handle.so中。
//这个部分的设计，详见文档:doc/Design of server controller.pdf。
handle_func get_handle_fanction(std::string function_name){
	handle_func function;
	function=(handle_func)dlsym(lib_handle,function_name.c_str());
	//dlclose(lib_handle);
	if (function!=NULL)
		return function;
	else 
		return NULL;
}


void load_lib_handle(const char* lib_name){
	std::string lib_pathname = "./"+std::string(lib_name);
	lib_handle=dlopen(lib_pathname.c_str(),RTLD_NOW);

   	if (lib_handle==NULL)
	{
		std::cout<<dlerror() <<std::endl;
		exit(-1);
	} else {
		std::cout<<"成功加载库:"<<lib_name <<std::endl;
	}

}

/*
程序入口
*/
int main(int argc, char const *argv[])
{
	print_compile_info(); /* 打印编译时间和编译器版本 */
	load_lib_handle("lib_handle.so");
	set_handle(handle_request);
	start_server();
	return 0;
}

/*
处理来自客户端的请求。这个请求被封装成json。
这个json的根节点下的request属性指明了请求类型。
解析出这个请求类型后,会调用对应的函数名形如"handle_request_type"的函数处理请求,
并构造反馈的json。
关于json的编码格式,详见设计文档。
关于检索对应处理函数的设计,详见文档:doc/Design of server controller.pdf。
*/
void handle_request(const char* request,char* feedback){

	Json::Reader reader;  
	Json::Value request_root,feedback_root; 
	reader.parse(request, request_root);
	std::string request_type =  request_root["request"].asString();
	std::cout<<"request_type:"<<request_type<<std::endl;

	std::string handle_function_name = "handle_"+request_type;
	handle_func function = get_handle_fanction(handle_function_name);
	if (function!=NULL)
	{
		std::cout<<"success find request function!"<<std::endl;
		//strcpy(feedback,"XXX");
		function(request,feedback);
	} else
	{
		feedback_root["result"] = "fail";
		feedback_root["message"] = "unknow request:"+request_type;
		strcpy(feedback,feedback_root.toStyledString().c_str());
	}
}

/*
使用预编译宏打印编译时间和编译器版本
*/
void print_compile_info(){
	std::cout<<"编译时间:"<<__DATE__<<" "<<__TIME__<<std::endl<<"编译器版本"<<__VERSION__<<std::endl;
}
