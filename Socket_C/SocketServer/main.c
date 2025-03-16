
#include<socket_utils.h>
#include <unistd.h> 
#include <stdbool.h>
#include <pthread.h>

struct AcceptedSocket{
	int acceptedSocketFD;
	struct sockaddr_in address;
	int error;
	bool acceptedSuccessfully;
};



struct AcceptedSocket * acceptedIncomingConnection(int serverSocketFD);
void startAcceptingIncomingConnections(int serverSocketFD);
void receiveAndPrintIncomingDataOnSeparateThread(struct AcceptedSocket *pSocket);
void receiveAndPrintIncomingData(int socketFD);
void sendReceivedMessageToOtherClients(int socketFD,char *buffer);

struct AcceptedSocket acceptedSockets[10];
int acceptedSocketsCount = 0;

int main(){

	int serverSocketFD = createTCPIpv4Socket();
	struct sockaddr_in *serverAddress = createIpv4Address("", 2000);

	int result = bind(serverSocketFD, serverAddress, sizeof(*serverAddress));
	if(result == 0)
		printf("Socket was bound successfully\n");

	int listenResult = listen(serverSocketFD, 10);
	 


	startAcceptingIncomingConnections(serverSocketFD);


	shutdown(serverSocketFD, SHUT_RDWR);
	return 0;
}

void startAcceptingIncomingConnections(int serverSocketFD){
	
	while(true){
                struct AcceptedSocket* clientSocket = acceptedIncomingConnection(serverSocketFD);
		acceptedSockets[acceptedSocketsCount++] = *clientSocket;  
                receiveAndPrintIncomingDataOnSeparateThread(clientSocket);
	}
}


void receiveAndPrintIncomingDataOnSeparateThread(struct AcceptedSocket *pSocket){
	pthread_t id;
	pthread_create(&id, NULL, receiveAndPrintIncomingData, pSocket->acceptedSocketFD );
}
  
void receiveAndPrintIncomingData(int socketFD){
	char buffer[1024];
	while(true){
                ssize_t amountReceived = recv(socketFD, buffer, 1024, 0);

                if(amountReceived > 0){
                        buffer[amountReceived] = 0;
                        printf("%s\n", buffer);

			sendReceivedMessageToOtherClients(socketFD, buffer );

                }
                if(amountReceived == 0)
                        break;
        }
	close(socketFD);
}

void sendReceivedMessageToOtherClients(int socketFD,char *buffer ){
	for(int i=0; i<acceptedSocketsCount; i++){
		if(acceptedSockets[i].acceptedSocketFD != socketFD){
			send(acceptedSockets[i].acceptedSocketFD, buffer, strlen(buffer), 0);
		}
	}
}

struct AcceptedSocket * acceptedIncomingConnection(int serverSocketFD){
	struct sockaddr_in clientAddress;
        int clientAddressSize = sizeof (struct sockaddr_in);
        int clientSocketFD = accept(serverSocketFD, &clientAddress, &clientAddressSize);

	struct AcceptedSocket * acceptedSocket = malloc(sizeof(struct AcceptedSocket));
	acceptedSocket->address = clientAddress;
	acceptedSocket->acceptedSocketFD = clientSocketFD;
	acceptedSocket->acceptedSuccessfully = clientSocketFD>0;

	if(! acceptedSocket->acceptedSuccessfully)
		acceptedSocket->error = clientSocketFD;

	return acceptedSocket;
}

