#include "user_info.h"


#include <string>
#include <iostream>
#include "communicate_client.h"
#include "../json_lib/json.h"


int send_user_info(User user_info,const char* request_type){
	Json::Reader reader;
	Json::Value request_root,feedback_root;

	request_root["request"] = request_type;
	request_root["username"] = user_info.username;
	request_root["password"] = user_info.password;

	char buf[100];
	client_sendstr(request_root.toStyledString().c_str(),buf);
	reader.parse(buf, feedback_root);
	std::cout<<buf<<std::endl;

	if (feedback_root["result"]!="pass")
	{
		return 1;
	}else {
		return -1;
	}
}

int user_login(User user_info){
	return send_user_info(user_info,"login");
}

int user_register(User user_info){
	return send_user_info(user_info,"register");
}

int user_modify(User user_info){
	return send_user_info(user_info,"modify");
}

int main(int argc, char const *argv[])
{

	User user_info;
	strcpy(user_info.username,"gongswh");
	strcpy(user_info.password,"gsw1992");
	user_modify(user_info);
	return 0;
}