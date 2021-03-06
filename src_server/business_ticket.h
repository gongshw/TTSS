/*
文件:business_ticket.h
作者:龚世伟
日期:2013.02.21
描述:查票购票和改签的业务逻辑
*/


#ifndef TTSS_SERVER_BUSINESS_TICKET_H_
#define TTSS_SERVER_BUSINESS_TICKET_H_

#include <vector>

//日期数据类型
typedef char Date[32];
typedef char Time[32];

//车站数据结构
struct Station
{
	//车站所在城市
	char city[32];

	//车站名称
	char name[32];
};


//班次数据结构
struct Train
{
	char number[32];		//车次
	Station start_station;	//始发站
	Time start_tinme;//发车时间
	Station arrival_station;	//终点站
	Time arrival_tinme;//到达时间
	char price[32];			//票价
	char amount_seats[32];		//总座位数
};

//每天的发车信息
struct Depart
{
	Train train;	//车次信息
	Date date;		//发车日期
	char remain_seats[32];	//剩余座位数
};

//车票
struct Ticket
{
	Depart depart;		//发车信息
	char seat_number[32];	//座位号
};

/* 查询车站 */
int query_station(const char* city_name,std::vector<Station>&);

/* 查询车次 */
int query_train(const char* start,const char* arrival,std::vector<Train>&);

/* 查询发车 */
int query_depart(const char* start,const char* arrival,
	const Date,std::vector<Depart> &);

/* 订票 */
bool order_ticket(const char* , const char* , const char*, Ticket&);

/* 改签 */
Ticket change_ticket(Ticket,Date);

//查询购买的车票
int query_ticket(const char * username,std::vector<Ticket> & result_vector);


#endif //TTSS_SERVER_BUSINESS_TICKET_H_