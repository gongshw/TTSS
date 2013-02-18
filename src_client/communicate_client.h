/*
文件:communicate_client.h
作者:龚世伟
日期:2013.02.18
描述:客户端与服务器通讯的接口定义
*/


#ifndef TTSS_ClIENT_COMMUNICATE_H_
#define TTSS_ClIENT_COMMUNICATE_H_

/* 最大消息长度 */
#ifndef MAX_MSG_SIZE
#define MAX_MSG_SIZE 1024
#endif //MAX_MSG_SIZE

//message quene中消息的结构
struct Message
{
	long msg_type;					/* 消息标识符 */
	char msg_text[MAX_MSG_SIZE];	/* 消息内容 */
};

/*
声明函数:client_sendstr
描述:向服务器发送字符串,记录服务器的反馈。
参数:
	request 请求字符串
	feedbak 存储服务器的反馈字符串
*/
void client_sendstr(const char* request,char* feedback); 

#endif //TTSS_ClIENT_COMMUNICATE_H_