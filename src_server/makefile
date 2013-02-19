#
#文件:makefile
#作者:龚世伟
#日期:2013.02.18
#描述:编译服务器主程序和库
#

server_objects =  communicate_server.o server_controller.o
business_objects = controller_user.o controller_ticket.o database.o


ttss_server: $(server_objects) libjson.a lib_handle.so
	g++ -o ttss_server $(server_objects) -L . -l json -l dl
lib_handle.so: $(business_objects) libjson.a
	g++ -o lib_handle.so -shared $(business_objects) -L . -l json $$(mysql_config --libs)

server_objects: communicate_server.h
business_objects: database.h
communicate_server.o:communicate_server.cpp
	g++ -c communicate_server.cpp
server_controller.o:server_controller.cpp server_controller.h
controller_user.o:controller_user.cpp
	g++ -c controller_user.cpp $$(mysql_config --cflags)
controller_ticket.o:controller_ticket.cpp
database.o:database.cpp database.h
	g++ -c database.cpp $$(mysql_config --cflags)

libjson.a:../jsoncpp-src-0.5.0.tar.gz
	tar -xzf ../jsoncpp-src-0.5.0.tar.gz
	scons -C jsoncpp-src-0.5.0 platform=linux-gcc
	cp jsoncpp-src-0.5.0/libs/linux-gcc-*/libjson_linux-gcc-*_libmt.a libjson.a
	rm -rf jsoncpp-src-0.5.0
clean:
	rm -f *.o *.a *.so