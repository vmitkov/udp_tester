// Server side implementation of UDP client-server model 
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
#endif //_WIN32

#define PORT	0x4322 
#define MAXLINE 1024 

// Driver code 
int main() {
	int sockfd;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;

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
	memset(&cliaddr, 0, sizeof(cliaddr));

	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	// Bind the socket with the server address 
	if (bind(sockfd, (const struct sockaddr*) & servaddr,
		sizeof(servaddr)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	int len, n;

	len = sizeof(cliaddr); //len is value/resuslt 
	
	while (1)
	{
		n = recvfrom(sockfd, (char*)buffer, MAXLINE,
			0, (struct sockaddr*) & cliaddr,
			&len);
		if (n < MAXLINE)
		{
			buffer[n] = '\0';
		}
		else
		{
			buffer[MAXLINE - 1] = '\0';
		}
		printf("%s\n", buffer);
	}
	
#ifdef _WIN32
//---------------------------------------------
// Clean up and quit.
	WSACleanup();
#endif //_WIN32

	return 0;
}
