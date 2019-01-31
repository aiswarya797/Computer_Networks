#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include <netinet/in.h>

#define SERVER_PORT 3000
#define MAXLINE 4096
#define Max_Listen 5  /*Listen to a maximum of 5 clients*/

/*
STEPS IN SERVER SOCKET:
1. CREATE SOCKET
2. SOCKET DECLARATION
3. BIND THE SOCKET TO THE ADDRESS
4. LISTEN
5. LOOP FOR SERVING CLIENTS
6. ONCE YOU GET A CLIENT, ACCEPT
7. RECEIVE CLIENT'S REQUEST. IF SUCCESSFUL, SEND BACK AN ACKNOWLEDGEMENT
8. ONCE DONE CLOSE ALL THE SOCKETS
*/

int main(int argc, char* argv[])
{
	int serverfd;
	int acceptfd;
	struct sockaddr_in sevraddr, clientaddr;
	char buf[MAXLINE];
	int clienlen;
	int n;
	
	//create a socket 
	
	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	
	//socket declaration
	sevraddr.sin_family = AF_INET;
	sevraddr.sin_port = htons(SERVER_PORT);
	sevraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//Bind the server to the IP address
	
	bind(serverfd, (struct sockaddr* )(&sevraddr) , sizeof(sevraddr));
	
	//Listening
	
	listen(serverfd, Max_Listen);
	printf("%s\n","Server is up and running ... waiting for clients");
	
	for(; ;)
	{
		clienlen = sizeof(clientaddr);
		acceptfd = accept(serverfd, (struct sockaddr*)(&clientaddr), &clienlen); //Accept the client with client address = clentaddr.
		printf("%s\n","Received Response");
		
		while( (n=recv(acceptfd, buf, MAXLINE, 0)) >0)
		{
			printf("String received is: 	");
			puts(buf);
			send(acceptfd, buf, MAXLINE,0);
		}
		
		if(n<0)
		{
			perror("Error occurred during Read");
			exit(1);
		}
		
		close(acceptfd);	//close the client socket connection
	}
	close(serverfd);	//close the listening socket
}
	
	
	
	
	
