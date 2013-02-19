#include "communicate_client.h"

#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

/* 消息类型 请求 */
#ifndef TYPE_REQUEST
#define TYPE_REQUEST 'r'
#endif

/* 消息类型 反馈 */
#ifndef TYPE_FEEDBACK
#define TYPE_FEEDBACK 'f'
#endif

/*
实现函数:client_sendstr
声明头文件:communicate_client.h
描述:向服务器发送字符串,记录服务器的反馈。
参数:
	request 请求字符串
	feedbak 存储服务器的反馈字符串
*/
void client_sendstr(const char* request,char* feedback){
	key_t key;
	int msgqueue_id;
	key = ftok("/",'m');
	msgqueue_id = msgget(key, IPC_CREAT|0660);
	Message request_msg,feedback_msg;

	request_msg.msg_type = TYPE_REQUEST;
	strcpy(request_msg.msg_text,request);
	msgsnd(msgqueue_id,(void *)&request_msg,strlen(request_msg.msg_text)+1,0);
	msgrcv(msgqueue_id, (void *) &feedback_msg,MAX_MSG_SIZE, TYPE_FEEDBACK,0);
	strcpy(feedback,feedback_msg.msg_text);
} 
