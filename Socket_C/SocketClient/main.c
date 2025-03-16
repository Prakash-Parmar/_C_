#include<socket_utils.h>
#include <stdbool.h>
#include <unistd.h>

void startListeningAndPrintMessage(int socketFD);
void startListeningAndPrintMessageOnNewThread(int socketFD);

int main(){

	int socketFD = createTCPIpv4Socket();
	printf("the client socket fd is: %d\n", socketFD);
	struct sockaddr_in *address = createIpv4Address("127.0.0.1", 2000);

	int result = connect(socketFD, (struct sockaddr *)address, sizeof(*address));
	
	if(result == 0)
		printf("Connection was successfull\n");

	char* username = NULL;
        size_t nameSize = 0;
        printf("Please enter your username first: \n");
        ssize_t nameCount = getline(&username, &nameSize, stdin);
	username[nameCount-1] = 0;


	char *line = NULL;
	size_t lineSize = 0;
	printf("Type and we will send(type exit)...\n");



	startListeningAndPrintMessageOnNewThread(socketFD);


	char buffer[1024];

	while(true){

		ssize_t charCount =  getline(&line, &lineSize, stdin);
		line[charCount - 1] = 0;
		
		sprintf(buffer, "%s: %s", username, line);
		if(charCount > 0){
			if(strcmp(line,"exit") == 0)
				break;

			size_t amountWasSent = send(socketFD, buffer, strlen(buffer), 0);
		}
	}


	//char buffer[1024];
	//recv(socketFD, buffer, 1024, 0);

	//printf("Response was %s\n", buffer);


	free(address);
	close(socketFD);
	return 0;
}

void startListeningAndPrintMessageOnNewThread(int socketFD){
	pthread_t id;
	pthread_create(&id, NULL, startListeningAndPrintMessage, socketFD );
}

void startListeningAndPrintMessage(int socketFD){
        char buffer[1024];
        while(true){

                ssize_t amountReceived = recv(socketFD, buffer, 1024, 0);

                if(amountReceived > 0){
                        buffer[amountReceived] = 0;
                        printf(" %s\n", buffer);

  
                }
                if(amountReceived == 0)
                        break;
        }
        close(socketFD);
}


