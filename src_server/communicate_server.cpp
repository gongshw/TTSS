#include "communicate_server.h"

#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/* 消息类型 请求 */
#ifndef TYPE_REQUEST
#define TYPE_REQUEST 'r'
#endif

/* 消息类型 反馈 */
#ifndef TYPE_FEEDBACK
#define TYPE_FEEDBACK 'f'
#endif

//测试用的处理函数
void handle(char* rqst,char* fdbk){
	strcpy(fdbk,"success!");
}

//开始监听
void start_server(){
	key_t key;
	int msgqueue_id;
	key = ftok("/",'m');
	msgqueue_id = msgget(key, IPC_CREAT|0660);
	printf("%s,msgqueue_id is %d\n", "server start!",msgqueue_id);

	while(1){
		Message request_msg,feedback_msg;
		msgrcv(msgqueue_id, (void *) &request_msg,MAX_MSG_SIZE, TYPE_REQUEST,0);
		printf("receive msg: %s\n", request_msg.msg_text);
		on_server_(request_msg.msg_text,feedback_msg.msg_text);		/* 调用on_server_指针指向的函数处理请求 */
		feedback_msg.msg_type = TYPE_FEEDBACK;
		msgsnd(msgqueue_id,(void *)&feedback_msg,strlen(feedback_msg.msg_text)+1,0);
		printf("return feedback: %s\n\n", feedback_msg.msg_text);
	}

}

/* 传入一个函数来处理来自客户端的消息 */
void set_handle(handle_func func ){
	on_server_ = func;
}

/* test func*/
int main(int argc, char const *argv[])
{
	set_handle(handle);
	start_server();
	return 0;
}