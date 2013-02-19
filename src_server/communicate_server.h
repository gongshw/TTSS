/*
文件:communicate_server.h
作者:龚世伟
日期:2013.02.18
描述:服务器通讯响应的接口定义
*/

/*
设计说明:
	为了分离业务逻辑和通讯接口，这里使用了依赖倒置的设计方法。
	核心控制模块在调用start_server函数启动监听之前，必须先调用set_handle函数
	绑定处理来自客户端请求的方法。这个方法需要传入满足类型handle_func的函数指针。
	当接收到来自客户端的请求,本模块会调用之前绑定的函数on_server_。
*/


#ifndef TTSS_SERVER_COMMUNICATE_H_
#define TTSS_SERVER_COMMUNICATE_H_

/* 最大消息长度 */
#ifndef MAX_MSG_SIZE
#define MAX_MSG_SIZE 1024
#endif //MAX_MSG_SIZE

//消息的结构
struct Message
{
	long msg_type;					/* 消息标识符 */
	char msg_text[MAX_MSG_SIZE];	/* 消息内容 */
};

/* 定义处理函数的类型 */
typedef void(*handle_func)(const char*,char*);


/* 开始监听来自客户端的请求 */
void start_server();

/* 传入一个函数来处理来自客户端的消息 */
void set_handle(handle_func);

#endif // TTSS_SERVER_COMMUNICATE_H_