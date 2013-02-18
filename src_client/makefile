ttss_client:communicate_client.o user_info.o libjson.a
	g++ -o ttss_client communicate_client.o user_info.o -L . -l json
communicate_server.o:communicate_client.cpp communicate_client.h
	g++ -c communicate_client.cpp
user_info.o:user_info.cpp user_info.h communicate_client.h
	g++ -c user_info.cpp
libjson.a:../jsoncpp-src-0.5.0.tar.gz
	tar -xzf ../jsoncpp-src-0.5.0.tar.gz
	scons -C jsoncpp-src-0.5.0 platform=linux-gcc
	cp jsoncpp-src-0.5.0/libs/linux-gcc-*/libjson_linux-gcc-4.2.1_libmt.a libjson.a
	rm -rf jsoncpp-src-0.5.0
clean:
	rm -f *.o *.a