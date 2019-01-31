#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include <netinet/in.h>
#include<stdlib.h>

#define MAXLINE 4096
#define SERVER_PORT 3000

/*
STEPS FOR CLIENT:
1. SOCKET CREATE
2. SOCKET DECLARATION
3. CONNECT
4. LOOP TILL YOU GET INPUT
5. SEND REQUEST SERVER, IF SUCCESSFUL YOU RECEIVE AN ACKNOWLEDGEMENT FROM SERVER
*/

int main(int argc, char* argv[])
{
	int sockfd;	//Socket of the client
	struct sockaddr_in servaddr;	//Server address is stored in servaddr
	char sendline, recvline;
	
	if(argc != 2)
	{
		perror("Insert HostName and Port Number");
		exit(1);
	}
	
	//Create socket for client:
	
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	if(sockfd < 0)
	{
		perror("error in creating a socket for client");
		exit(2);
	}
	
	//Socket Declaration:
	
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);	//Convert to Big Endian
	servaddr.sin_addr.s_addr =  inet_addr(argv[1]);
	
	//Connect the client to server:
	
	if(connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) <0)
	{
		perror("Connection to server failed");
		exit(3);
	}
	
	//get input : loop 
	
	while(fgets(sendline, MAXLINE, stdin) != NULL)
	{
		send(sockfd, sendline, strlen(sendline), 0);
		
		if(recv(sockfd, recvline, strlen(recvline), 0) == 0)
		{
			perror("Server terminated");
			exit(4);
		}
		
		printf("%s", "String received from server :");
		fputs(recvline, stdout);
		
	}
	exit(0);
}
	
