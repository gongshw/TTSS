#include "business_ticket.h"

#include <cstring>
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
	std::string sql__check_exist_string = sql_buf;
	MYSQL_RES* result = dao.executeSQL(sql__check_exist_string);
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
	std::string sql__check_exist_string = sql_buf;
	MYSQL_RES* result = dao.executeSQL(sql__check_exist_string);
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
		"AND ARRIVAL_STATION_NAME LIKE \"%%%s%%\""
		"AND DATE = \"%s\"",
		start_station,arrival_station,date);
	std::string sql__check_exist_string = sql_buf;
	MYSQL_RES* result = dao.executeSQL(sql__check_exist_string);
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