#include "client_controller.h"

#include <cstring>
#include <cstdio>

#include "user_info.h"
#include "ticket_query.h"

int main(int argc, char const *argv[])
{
	User user;

	strcpy(user.username,"gongshw");
	strcpy(user.password,"123");
	strcpy(user.real_name,"龚世伟");

	// user_login(user);

	// std::vector<Depart> train_vector;
	// query_depart("南京","扬州","2013-02-20",train_vector);

	//printf("%s\n", user_msg);


	order_ticket("K1123","2013-02-20");

	return 0;
}