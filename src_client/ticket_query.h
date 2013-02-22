/*
文件:ticket_query.h
作者:龚世伟
日期:2013.02.21
描述:查票购票和改签的业务逻辑
*/


#ifndef TTSS_CLIENT_BUSINESS_TICKET_H_
#define TTSS_CLIENT_BUSINESS_TICKET_H_

#include <vector>

//日期数据类型
typedef char Date[32];
typedef char Time[32];

//班次数据结构
struct Train
{
	char number[32];		//车次
	char start_station[32];	//始发站
	Time start_tinme;//发车时间
	char arrival_station[32];	//终点站
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

/* 查询车次 */
int query_train(const char* start,const char* arrival,std::vector<Train>&);

/* 查询发车 */
int query_depart(const char* start,const char* arrival,
	const char* date,std::vector<Depart> &);

/* 订票 */
bool order_ticket(const char* train_number,const char* date,Ticket&);

/* 改签 */
Ticket change_ticket(Ticket,Date);

/* 查询我的车票 */
int query_ticket(std::vector<Ticket>&);

#endif //TTSS_CLIENT_BUSINESS_TICKET_H_