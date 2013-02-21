bussiness_objects = user_info.o ticket_query.o communicate_client.o


ttss_client:client_controller.o $(bussiness_objects) libjson.a
	g++ -o ttss_client $(bussiness_objects) client_controller.o -L . -l json
$(bussiness_objects):communicate_client.h
client_controller.o:client_controller.cpp client_controller.h user_info.h
user_info.o:user_info.cpp user_info.h
ticket_query.o:ticket_query.cpp ticket_query.h 
communicate_client.o:communicate_client.cpp
libjson.a:../jsoncpp-src-0.5.0.tar.gz
	tar -xzf ../jsoncpp-src-0.5.0.tar.gz
	scons -C jsoncpp-src-0.5.0 platform=linux-gcc
	cp jsoncpp-src-0.5.0/libs/linux-gcc-*/libjson_linux-gcc-*_libmt.a libjson.a
	rm -rf jsoncpp-src-0.5.0
clean:
	rm -f *.o *.a