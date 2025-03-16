#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

// Function to create a TCP IPv4 socket
int createTCPIpv4Socket();

// Function to create an IPv4 address structure
struct sockaddr_in* createIpv4Address(const char* ip, int port);

#endif // SOCKET_UTILS_H

