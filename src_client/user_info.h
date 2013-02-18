#ifndef TTSS_ClIENT_USER_H_
#define TTSS_ClIENT_USER_H_


struct User
{
	char username[32];
	char password[32];
};

int user_login(User);

int user_register(User);

int user_modify(User);

#endif //TTSS_ClIENT_USER_H_