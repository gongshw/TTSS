#include "user_info.h"


#include <cstring>
#include <iostream>
#include "communicate_client.h"
#include "../json_lib/json.h"

char user_msg[MAX_MSG_SIZE];

void get_feeedback_msg(char* buf){
	strcpy(buf,user_msg);
}

int send_user_info(User user_info,const char* request_type){
	Json::Reader reader;
	Json::Value request_root,feedback_root;

	request_root["request"] = request_type;
	request_root["username"] = user_info.username;
	request_root["password"] = user_info.password;
	request_root["real_name"] = user_info.real_name;

	char buf[512];
	client_sendstr(request_root.toStyledString().c_str(),buf);
	reader.parse(buf, feedback_root);

	std::cout<<buf;

	strcpy(user_msg,feedback_root["message"].asString().c_str());

	if (feedback_root["result"]=="pass")
	{
		return 1;
	}else {
		return 0;
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
