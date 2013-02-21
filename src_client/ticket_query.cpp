#include "ticket_query.h"

#include <cstdio>

#include "communicate_client.h"
#include "../json_lib/json.h"

void send_query(Json::Value & feedback_root,const char* query_type,const char* station_name,
	const char* another_station_name = 0,const char* date = 0){

	Json::Reader reader;
	Json::Value request_root;

	request_root["request"] = query_type;
	if(!another_station_name){
		request_root["station"] = station_name;
	} else {
		request_root["start_station"] = station_name;
		request_root["arrival_station"] = another_station_name;
	}
	if (date)
	{
		request_root["date"] = date;
	}
	char buf[2048];
	
	client_sendstr(request_root.toStyledString().c_str(),buf);

	printf("%s\n", buf);

	reader.parse(buf, feedback_root);
}

/* 查询车次 */
int query_train(const char* start,const char* arrival,std::vector<Train>&){
	Json::Value feedback_root;
	send_query(feedback_root,"query_train",start,arrival);
	return 0;
}

/* 查询发车 */
int query_depart(const char* start,const char* arrival,
	Date date,std::vector<Depart> &){

	Json::Value feedback_root;
	send_query(feedback_root,"query_depart",start,arrival,date);

	return 0;
}

/* 订票 */
Ticket order_ticket(Depart deprt){
	Ticket ticket;
	ticket.deprt = deprt;
	
	return Ticket();
}

/* 改签 */
Ticket change_ticket(Ticket,Date);