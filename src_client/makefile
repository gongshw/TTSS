ttss_client:communicate_client.o
	gcc -o ttss_client communicate_client.o
communicate_server.o:communicate_client.cpp communicate_client.h
	gcc -c communicate_client.cpp
clean:
	rm -f communicate_server.o
