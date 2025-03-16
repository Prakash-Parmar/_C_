#include<socket_utils.h>
#include <stdbool.h>
#include <unistd.h>

int main(){

	int socketFD = createTCPIpv4Socket();
	printf("the client socket fd is: %d\n", socketFD);
	struct sockaddr_in *address = createIpv4Address("127.0.0.1", 2000);

	int result = connect(socketFD, (struct sockaddr *)address, sizeof(*address));
	
	if(result == 0)
		printf("Connection was successfull\n");

	char *line = NULL;
	size_t lineSize = 0;
	printf("Type and we will send(type exit)...\n");

	while(true){
		ssize_t charCount =  getline(&line, &lineSize, stdin);
		
		if(charCount > 0){
			if(strcmp(line,"exit\n") == 0)
				break;

			size_t amountWasSent = send(socketFD, line, charCount, 0);
		}
	}


	//char buffer[1024];
	//recv(socketFD, buffer, 1024, 0);

	//printf("Response was %s\n", buffer);


	free(address);
	close(socketFD);
	return 0;
}

