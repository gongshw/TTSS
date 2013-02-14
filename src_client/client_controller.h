/*
用户逻辑
*/

struct User
{
	char* username;
	char* password;
};

struct Feedback
{
	unsigned char state_code;
	char* message;
};

Feedback user_login(User);

Feedback user_register(User);

Feedback user_modify(User);