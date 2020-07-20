#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include<sys/un.h>
#include<unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

	

int main(int argc, char* argv[])
{
	if (argc !=2)
	{
		printf("Error: missing port\n");
		exit(0);
	}	
	int  port = atoi(argv[1]);
	char msg[100];

	struct sockaddr_in servAddr;

	//creating a stream oriented socket
	int serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if(serverfd < 0)
	{
		printf("Error: Failed creating socket\n");
		exit(0);
	}

	//bind the socket to its local address
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);
	int bindstatus = bind(serverfd, (struct sockaddr*)&servAddr, sizeof(servAddr));
	if(bindstatus < 0)
	{
		printf("Error: Failed to bind socket to address\n");
		exit(0);
	}
	printf("____________________________________\n");
	printf("Please wait while we connect....!!!!\n");
	printf("____________________________________\n");
	
	printf("bind succesful\n");
	//listen for 5 request at a time
	listen(serverfd, 5);

	//need a new address to connect to client
	struct sockaddr_in newservAddr;
	//socklen_t newsockAddrsize = sizeof(newsockAddr);
	int new_len = sizeof(newservAddr);

	//receive a request from client using accept
	//accept, create a new socket descriptor
	//Handle new connection with client
	int newsd = accept(serverfd, (struct sockaddr*)&newservAddr, &new_len);
	if(newsd < 0)
	{
		printf("Error in accepting client request\n");
	}

	printf("Connection Succedded....!!!!\n");
	while(1){
		//Receive a message from the client
		printf("Awaiting client response\n");

		memset(&msg, 0, sizeof(msg));

		read(newsd, msg, sizeof(msg));
		if(strcmp(msg, "exit") == 0)
		{
			printf("Client has quit the session\n");
			exit(0);
		}
		printf("Client : %s\n",msg);
		printf("Server : ");
		char obuff[100],ch;
		scanf("%[^\n]s",obuff);
		ch = getchar();


		//send the message to client
		memset(&msg, 0, sizeof(msg));

		write(newsd, obuff, sizeof(obuff));
		}
	close(newsd);
	close(serverfd);

	printf("Connection closed");

	return 0;
}
