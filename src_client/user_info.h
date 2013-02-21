#ifndef TTSS_ClIENT_USER_H_
#define TTSS_ClIENT_USER_H_

#ifndef MAX_MSG_SIZE
#define MAX_MSG_SIZE 1024
#endif

struct User
{
	char username[32];
	char password[32];
	char real_name[32];
};

extern char user_msg[MAX_MSG_SIZE];

int user_login(User);

int user_register(User);

int user_modify(User);

int send_user_info(User,const char*);

void get_feeedback_msg(char*);

#endif //TTSS_ClIENT_USER_H_