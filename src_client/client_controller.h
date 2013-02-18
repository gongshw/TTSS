/*
文件:communicate_client.h
作者:龚世伟
日期:2013.02.18
描述:用户逻辑
*/


#ifndef MAX_MSG_SIZE
#define MAX_MSG_SIZE 1024
#endif

struct Feedback
{
	unsigned char state_code;
	char message[MAX_MSG_SIZE];
};

