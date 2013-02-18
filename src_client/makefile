ttss_client:communicate_client.o user_info.o
	g++ -o ttss_client communicate_client.o user_info.o -L . -l json
communicate_server.o:communicate_client.cpp communicate_client.h
	g++ -c communicate_client.cpp
user_info.o:user_info.cpp user_info.h communicate_client.h
	g++ -c user_info.cpp
clean:
	rm -f communicate_server.o user_info.o