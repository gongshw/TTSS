#include "user_info.h"


#include <string>
#include <iostream>
#include "communicate_client.h"
#include "../json_lib/json.h"

int user_login(User user_info){
	Json::Value root;

	root["request"] = "login";
	root["username"] = user_info.username;
	root["password"] = user_info.password;

	//char buf[100];
	//client_sendstr(root.asString().c_str(),buf);

	//printf("%s\n", root.asString().c_str());
	std::string out = root.toStyledString();
   	std::cout << out << std::endl;

	return -1;
}

int user_register(User user_info){
	return -1;
}

int user_modify(User user_info){
	return -1;
}

int main(int argc, char const *argv[])
{

	User user_info;
	strcpy(user_info.username,"gongswh");
	strcpy(user_info.password,"gsw1992");
	user_login(user_info);
	return 0;
}