ttss_server:communicate_server.o server_controller.o controller_user.o controller_ticket.o libjson.a
	g++ -o ttss_server communicate_server.o server_controller.o controller_user.o controller_ticket.o -L . -l json
communicate_server.o:communicate_server.cpp communicate_server.h
	g++ -c communicate_server.cpp
server_controller.o:server_controller.cpp server_controller.h communicate_server.h controller_user.h
	g++ -c server_controller.cpp
controller_user.o:controller_user.cpp controller_user.h
	g++ -c controller_user.cpp
controller_ticket.o:controller_ticket.cpp controller_ticket.h
	g++ -c controller_ticket.cpp
libjson.a:../jsoncpp-src-0.5.0.tar.gz
	tar -xzf ../jsoncpp-src-0.5.0.tar.gz
	scons -C jsoncpp-src-0.5.0 platform=linux-gcc
	cp jsoncpp-src-0.5.0/libs/linux-gcc-*/libjson_linux-gcc-*_libmt.a libjson.a
	rm -rf jsoncpp-src-0.5.0
clean:
	rm -f *.o *.a