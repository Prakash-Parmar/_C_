#include "socket_utils.h"

int createTCPIpv4Socket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

struct sockaddr_in* createIpv4Address(const char* ip, int port) {
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    if (address == NULL) {
        perror("Failed to allocate memory for address");
        exit(EXIT_FAILURE);
    }
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    
    if(strlen(ip) == 0){
    	address->sin_addr.s_addr = INADDR_ANY;
    }else{
    	inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    }

    return address;
}

