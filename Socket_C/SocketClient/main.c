#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<string.h>

int main(){

	int socketFD = socket(AF_INET, SOCK_STREAM, 0);
	
	/*
   	 This code initializes a socket address structure (`sockaddr_in`)
   	 for an IPv4 connection. It sets the IP address to "127.0.0.1" (localhost),
  	 assigns port 2000 (converted to network byte order), and converts the
  	 IP address from string format to binary using `inet_pton()`.
       */
	char* ip = "142.250.31.100";
	struct sockaddr_in address;
	address.sin_family = AF_INET; //IPv4 family
     	address.sin_port = htons(80); //usually there are around 65000 port but 0-1023 are reserved for system
        inet_pton(AF_INET, ip, &address.sin_addr);
	
	int result = connect(socketFD, &address, sizeof address);
	
	if(result == 0)
		printf("Connection was successfull\n");
	
        // Prepare HTTP GET request
        const char *message = "GET / HTTP/1.1\r\n"
                               "Host: google.com\r\n"
                               "Connection: close\r\n"
                               "\r\n";

	send(socketFD, message, strlen(message), 0);

	char buffer[1024];
	recv(socketFD, buffer, 1024, 0);

	printf("Response was %s\n", buffer);
	return 0;
}
