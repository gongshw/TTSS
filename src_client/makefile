ttss_client:communicate_client.o
	g++ -o ttss_client communicate_client.o
communicate_server.o:communicate_client.cpp communicate_client.h
	g++ -c communicate_client.cpp
clean:
	rm -f communicate_server.o
