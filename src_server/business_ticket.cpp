#include "business_ticket.h"

#include <cstring>
#include <cstdlib>
#include <string>

#include "database.h"

#define _INIT_TRAIN_ 															\
	set_colunm_into(row,result,"NUMBER",train.number);							\
	set_colunm_into(row,result,"START_STATION_CITY",							\
		train.start_station.city);												\
	set_colunm_into(row,result,"START_STATION_NAME",train.start_station.name);	\
	set_colunm_into(row,result,"START_TIME",train.start_tinme);					\
	set_colunm_into(row,result,"ARRIVAL_STATION_CITY",							\
		train.start_station.city);												\
	set_colunm_into(row,result,"ARRIVAL_STATION_NAME",							\
		train.arrival_station.name);											\
	set_colunm_into(row,result,"ARRIVAL_TIME",train.arrival_tinme);				\
	set_colunm_into(row,result,"PRICE",train.price);							\
	set_colunm_into(row,result,"SEATS",train.amount_seats);						\

void update_depart_seats(const char* depart_id,const int remain_seats_int);
void insert_ticket(const char* depart_id,const int ticket_number,const char* username);

void set_colunm_into(MYSQL_ROW row, MYSQL_RES* result, 
	const char* field_name, char* buf){

	std::string column_str;
	dao.get_column(row,result,field_name,column_str);
	strcpy(buf,column_str.c_str());

}

/* 查询车站 */
int query_station(const char* city_name, std::vector<Station> & result_vector){
	char sql_buf[512];
	sprintf(sql_buf,"SELECT * FROM STATION WHERE CITY = \"%s\"",
		city_name);
	std::string sql_string = sql_buf;
	MYSQL_RES* result = dao.executeSQL(sql_string);
	int result_count = 0;

	MYSQL_ROW row;
	
	while (row = mysql_fetch_row(result))
	{
		result_count++;
		Station station;
		set_colunm_into(row,result,"CITY",station.city);
		set_colunm_into(row,result,"NAME",station.name);
		result_vector.push_back(station);
	} 

	mysql_free_result(result);
	return result_count;
}

int query_train(const char* start_station,const char* arrival_station,
	std::vector<Train>&result_vector){

	char sql_buf[512];
	sprintf(sql_buf,"SELECT * FROM TRAIN_VIEW WHERE "
		"START_STATION_NAME LIKE \"%%%s%%\" "
		"AND ARRIVAL_STATION_NAME LIKE \"%%%s%%\"",
		start_station,arrival_station);
	std::string sql_string = sql_buf;
	MYSQL_RES* result = dao.executeSQL(sql_string);
	int result_count = 0;

	MYSQL_ROW row;
	
	while (row = mysql_fetch_row(result))
	{
		result_count++;
		Train train;
		_INIT_TRAIN_;
		result_vector.push_back(train);
	} 

	mysql_free_result(result);
	return result_count;
}

int query_depart(const char* start_station,const char* arrival_station,
	const Date date,std::vector<Depart> & result_vector){

	char sql_buf[512];
	sprintf(sql_buf,"SELECT * FROM DEPART_VIEW WHERE "
		"START_STATION_NAME LIKE \"%%%s%%\" "
		"AND ARRIVAL_STATION_NAME LIKE \"%%%s%%\" "
		"AND DATE = \"%s\"",
		start_station,arrival_station,date);
	std::string sql_string = sql_buf;
	MYSQL_RES* result = dao.executeSQL(sql_string);
	int result_count = 0;

	MYSQL_ROW row;
	
	while (row = mysql_fetch_row(result))
	{
		result_count++;
		Train train;
		Depart depart;
		_INIT_TRAIN_;
		depart.train = train;
		set_colunm_into(row,result,"DATE",depart.date);
		set_colunm_into(row,result,"REMAIN_SEATS",depart.remain_seats);
		result_vector.push_back(depart);
	} 
	mysql_free_result(result);
	return result_count;
}


//train_number 车次
//date 发车日期
bool order_ticket(const char* train_number, const char* date,
	const char* username,  Ticket & ticket){

	char sql_buf[512];
	sprintf(sql_buf,"SELECT * FROM DEPART_VIEW WHERE "
		"NUMBER = \"%s\" AND "
		"DATE = \"%s\"",train_number, date);
	MYSQL_RES* result = dao.executeSQL(std::string(sql_buf));
	std::string depart_id,remain_seats,amount_seats;
	MYSQL_ROW row;
	if(row = mysql_fetch_row(result)){
		dao.get_column(row,result,"did",depart_id);
		dao.get_column(row,result,"remain_seats",remain_seats);
		dao.get_column(row,result,"seats",amount_seats);
		int remain_seats_int = atoi(remain_seats.c_str());
		if (remain_seats_int>0)
		{
			int ticket_number = atoi(amount_seats.c_str())-remain_seats_int+1;
			sprintf(ticket.seat_number,"%d",ticket_number);
			Train train;
			Depart depart;
			_INIT_TRAIN_;
			depart.train = train;
			set_colunm_into(row,result,"DATE",depart.date);
			sprintf(depart.remain_seats,"%d",--remain_seats_int);
			ticket.depart = depart;
			mysql_free_result(result);
			update_depart_seats(depart_id.c_str(),remain_seats_int);
			insert_ticket(depart_id.c_str(),ticket_number,username);
			return true;
		}
	}
	mysql_free_result(result);
	return false;
}

void update_depart_seats(const char* depart_id,const int remain_seats_int){
	char sql_buf[512];
	sprintf(sql_buf,"UPDATE DEPART SET REMAIN_SEATS =  %d WHERE "
		"DID = %s",remain_seats_int, depart_id);

	mysql_free_result(dao.executeSQL(std::string(sql_buf)));
}

void insert_ticket(const char* depart_id,const int ticket_number, 
	const char * consumer){

	char sql_buf[512];
	sprintf(sql_buf,"INSERT INTO TICKET(NUMBER,DID,CONSUMER) "
		"VALUES(%d,%s,\"%s\")",ticket_number,depart_id,consumer);
	mysql_free_result(dao.executeSQL(std::string(sql_buf)));
}

int query_ticket(const char * username,std::vector<Ticket> & result_vector){
	char sql_buf[512];
	sprintf(sql_buf,"SELECT * FROM TICKET_VIEW WHERE "
		"CONSUMER LIKE \"%%%s%%\" ",
		username);
	std::string sql_string = sql_buf;
	MYSQL_RES* result = dao.executeSQL(sql_string);
	int result_count = 0;

	MYSQL_ROW row;
	
	while (row = mysql_fetch_row(result))
	{
		result_count++;
		Train train;
		Depart depart;
		_INIT_TRAIN_;
		depart.train = train;
		set_colunm_into(row,result,"DATE",depart.date);
		set_colunm_into(row,result,"REMAIN_SEATS",depart.remain_seats);
		Ticket ticket;
		set_colunm_into(row,result,"TICKET_NUMBER",ticket.seat_number);
		ticket.depart = depart;
		result_vector.push_back(ticket);
	} 

	mysql_free_result(result);
	return result_count;

}
