#include "ticket_query.h"

#include <cstdio>
#include <cstring>

#include "communicate_client.h"
#include "user_info.h"
#include "json.h"

#define _ITEM_TO_TRAIN_															\
	Train train;																\
	strcpy(train.number,train_item["number"].asCString());						\
	strcpy(train.start_station,train_item["start_station"].asCString());		\
	strcpy(train.start_tinme,train_item["start_time"].asCString());				\
	strcpy(train.arrival_station,train_item["arrival_station"].asCString());	\
	strcpy(train.arrival_tinme,train_item["arrival_time"].asCString());			\
	strcpy(train.price,train_item["price"].asCString());						\
	strcpy(train.amount_seats,train_item["totol_seats"].asCString());			\

#define _DEPART_WITH_TRAIN_														\
	Depart depart;																\
	depart.train = train;														\
	strcpy(depart.remain_seats,train_item["remain_seats"].asCString());			\
	strcpy(depart.date,train_item["date"].asCString());							\

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
int query_train(const char* start,const char* arrival,
	std::vector<Train>& train_vector){

	Json::Value feedback_root;
	send_query(feedback_root,"query_train",start,arrival);
	if(feedback_root["result"]=="pass"){
		Json::Value trains_array = feedback_root["trains"];
		int count = trains_array.size();
		for (int i = 0; i < count; ++i)
		{
			Json::Value train_item = trains_array[i];
			_ITEM_TO_TRAIN_;
			train_vector.push_back(train);
		}
		return count;
	} else {
		return 0;
	}
}

/* 查询发车 */
int query_depart(const char* start,const char* arrival,
	const char* date,std::vector<Depart> & depart_vector){

	Json::Value feedback_root;
	send_query(feedback_root,"query_depart",start,arrival,date);
	if(feedback_root["result"]=="pass"){
		Json::Value trains_array = feedback_root["departs"];
		int count = trains_array.size();
		for (int i = 0; i < count; ++i)
		{
			Json::Value train_item = trains_array[i];
			_ITEM_TO_TRAIN_;
			_DEPART_WITH_TRAIN_;
			depart_vector.push_back(depart);
		}
		return count;
	} else {
		return 0;
	}
	return 0;
}

/* 订票 */
bool order_ticket(const char* train_number,const char* date,Ticket & ticket){
	Json::Reader reader;
	Json::Value request_root;
	request_root["request"] = "order";
	request_root["train_number"] = train_number;
	request_root["date"] = date;
	request_root["username"] = current_user.username;
	char buf[1024];
	client_sendstr(request_root.toStyledString().c_str(),buf);
	printf("%s\n", buf);

	Json::Value train_item;
	reader.parse(buf, train_item);

	if (train_item["result"]=="pass")
	{	
		_ITEM_TO_TRAIN_;
		_DEPART_WITH_TRAIN_;
		ticket.depart = depart;
		strcpy(ticket.seat_number,train_item["seat_number"].asCString());
		return true;
	} else {
		return false;
	}
}

/* 查询我的车票 */
int query_ticket(std::vector<Ticket>& ticket_vector){
	Json::Reader reader;
	Json::Value request_root,feedback_root;
	request_root["request"] = "my_tickets";
	request_root["username"] = current_user.username;
	char buf[1024];
	client_sendstr(request_root.toStyledString().c_str(),buf);

	reader.parse(buf, feedback_root);

	if(feedback_root["result"]=="pass"){
		Json::Value ticket_array = feedback_root["tickets"];
		int count = ticket_array.size();
		for (int i = 0; i < count; ++i)
		{
			Json::Value train_item = ticket_array[i];
			_ITEM_TO_TRAIN_;
			_DEPART_WITH_TRAIN_;
			Ticket ticket;
			ticket.depart = depart;
			strcpy(ticket.seat_number,train_item["seat_number"].asCString());
			ticket_vector.push_back(ticket);
		}
		return count;
	} else {
		return 0;
	}
	return 0;
}

/* 改签 */
Ticket change_ticket(Ticket,Date);