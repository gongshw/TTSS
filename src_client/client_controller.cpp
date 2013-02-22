#include "client_controller.h"

#include <cstring>
#include <cstdio>

#include <QtGui/QApplication>
#include "ClientUI/logDialog.h"
#include "ClientUI/clientmainwindow.h"

#include "user_info.h"
#include "ticket_query.h"

int main(int argc, char *argv[])
{
	// std::vector<Depart> train_vector;
	// query_depart("南京","扬州","2013-02-20",train_vector);

	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

	QApplication a(argc, argv);


    
	ClientMainWindow w;
    logDialog ld(&w);
    ld.show();

	//w.show();

    return a.exec();



	//printf("%s\n", user_msg);


	//Ticket t;
	// order_ticket("K1123","2013-02-20",t);
}