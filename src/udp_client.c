// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#ifdef _WIN32
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
#include <sys/socket.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#endif

#define PORT	0x4322 
#define MAXLINE 1024 

// Driver code 
int main() {
	int sockfd;
	const char* hello = "Hello from client";
	struct sockaddr_in	 servaddr;

#ifdef _WIN32
	int iResult;
	WSADATA wsaData;
	// ----------------------
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup failed with error: %d\n", iResult);
		return 1;
	}
#endif //_WIN32

	// Creating socket file descriptor 
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Filling server information 
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
#ifdef _WIN32
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
#else
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.200");
#endif //_WIN32

	while (1)
	{
		sendto(sockfd, (const char*)hello, strlen(hello),
			0, (const struct sockaddr*) & servaddr,
			sizeof(servaddr));
		printf("Hello message sent.\n");
#ifdef _WIN32
		Sleep(1000);
#else
		sleep(1);
#endif //_WIN32

	}

#ifdef _WIN32
	//---------------------------------------------
	// Clean up and quit.
	closesocket(sockfd);
	WSACleanup();
#else
	close(sockfd);
#endif //_WIN32
	return 0;
}
