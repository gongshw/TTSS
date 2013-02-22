/*
文件:controller_user.cpp
作者:龚世伟
日期:2013.02.19
描述:处理用户查票、订票和改签的控制器
*/

#include "controller_ticket.h"
#include <cstring>
#include <string>
#include <cstdio>
#include "business_ticket.h"
#include "../json_lib/json.h"

#define _INIT_READER_AND_VALUE_ROOT									\
	Json::Reader reader; 											\
	Json::Value request_root,feedback_root; 						\
	reader.parse(request, request_root);							\

#define _INSERT_TRAIN_INTO_VALUE_(value_item)						\
	value_item["number"] = train.number;							\
	value_item["start_station_name"] = train.start_station.name;	\
	value_item["start_time"] = train.start_tinme;					\
	value_item["arrival_station_city"] = train.start_station.city;	\
	value_item["arrival_time"] = train.arrival_tinme;				\
	value_item["seats"] = train.amount_seats;						\

extern "C" void handle_query_station(const char* request,char* feedback){
	_INIT_READER_AND_VALUE_ROOT;
	
	std::vector<Station> station_vector;
	if(int cout_station = query_station(request_root["staion"].asCString(),station_vector)){
		feedback_root["result"] = "pass";
		char msg_buf[64];
		sprintf(msg_buf,"%d station(s) found!",cout_station);
		feedback_root["message"] = msg_buf;
		Json::Value array_station;
		for ( int i = 0 ; i < station_vector.size() ; i++ ) {
			Station station =  station_vector[i];
			Json::Value station_item;
			station_item["city"] = station.city;
			station_item["name"] = station.name;
			array_station.append(station_item);
   		}
   		feedback_root["stations"] = array_station;
	} else {
		feedback_root["result"] = "fail";
		feedback_root["message"] = "no station found!";
	}
	
   	
   	strcpy(feedback,feedback_root.toStyledString().c_str());
}

extern "C" void handle_query_train(const char* request,char* feedback){
	_INIT_READER_AND_VALUE_ROOT;

	std::vector<Train> train_vector;
	if(int cout_train = query_train(request_root["start_station"].asCString(),
		request_root["arrival_station"].asCString(),train_vector)){

		feedback_root["result"] = "pass";
		char msg_buf[64];
		sprintf(msg_buf,"%d train(s) found!",cout_train);
		feedback_root["message"] = msg_buf;
		Json::Value array_train;
		for ( int i = 0 ; i < train_vector.size() ; i++ ) {
			Train train =  train_vector[i];
			Json::Value train_item;
			_INSERT_TRAIN_INTO_VALUE_ (train_item);
			array_train.append(train_item);
   		}
   		feedback_root["trains"] = array_train;
	} else {
		feedback_root["result"] = "fail";
		feedback_root["message"] = "no train found!";
	}
	
   	
   	strcpy(feedback,feedback_root.toStyledString().c_str());
}

extern "C" void handle_query_depart(const char* request,char* feedback){
	_INIT_READER_AND_VALUE_ROOT;

	std::vector<Depart> depart_vector;
	if(int cout_train = query_depart(request_root["start_station"].asCString(),
		request_root["arrival_station"].asCString(),
		request_root["date"].asCString(),depart_vector)){

		feedback_root["result"] = "pass";
		char msg_buf[64];
		sprintf(msg_buf,"%d depart(s) found!",cout_train);
		feedback_root["message"] = msg_buf;
		Json::Value array_train;
		for ( int i = 0 ; i < depart_vector.size() ; i++ ) {
			Depart depart = depart_vector[i]; 
			Train train =  depart.train;
			Json::Value depart_item;
			_INSERT_TRAIN_INTO_VALUE_ (depart_item);
			depart_item["date"] = depart.date;
			depart_item["remain_seats"] = depart.remain_seats;
			array_train.append(depart_item);
   		}
   		feedback_root["trains"] = array_train;
	} else {
		feedback_root["result"] = "fail";
		feedback_root["message"] = "no depart found!";
	}
	
   	
   	strcpy(feedback,feedback_root.toStyledString().c_str());
}


extern "C" void handle_order(const char* request,char* feedback){
	_INIT_READER_AND_VALUE_ROOT;
	printf("%s\n", request);
	Ticket ticket = order_ticket(request_root["train_number"].asCString(),
		request_root["date"].asCString());
	if (ticket.seat_number)
	{
		Train train =  ticket.depart.train;
		// _INSERT_TRAIN_INTO_VALUE_ (feedback_root);
		// feedback_root["date"] = ticket.depart.date;
		// feedback_root["seat"] = ticket.seat_number;
		feedback_root["result"] = "pass";
	} else {
		feedback_root["result"] = "fail";
		feedback_root["message"] = "no depart found!";
	}
	strcpy(feedback,feedback_root.toStyledString().c_str());

	printf("%s\n", feedback);

}
extern "C" void handle_change(const char* request,char* feedback){

}