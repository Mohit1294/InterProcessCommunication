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
#include<errno.h>


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Error: missing IP Address\n");
		exit(0);
	}

	char *servIP = argv[1];
	int port = atoi(argv[2]);

	char msg[100];

	struct hostent* host = gethostbyname(servIP);
	struct sockaddr_in sendsockAddr;
	bzero((char*)&sendsockAddr, sizeof(sendsockAddr));
	sendsockAddr.sin_family = AF_INET;
	sendsockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
	sendsockAddr.sin_port = htons(port);

	int clientsd = socket(AF_INET, SOCK_STREAM, 0);

	//try to connect
	int status = connect(clientsd, (struct sockaddr*)&sendsockAddr, sizeof(sendsockAddr));
	if (status < 0)
	{
		printf("Error connecting to server...!!!!\n");
		perror("Error: ");
		exit(0);
	}

	printf("Connection to server is succedded...!!\n");

	while(1)
	{
		printf("Client: ");
		char sbuff[100],ch;
		scanf("%[^\n]s",sbuff);
		ch = getchar();
		if (strcmp(sbuff,"exit") == 0)
		{
			write(clientsd, sbuff, sizeof(sbuff));
			printf("Exit Successful ....!!!!\n");
			exit(0);
		}
		int byteswritten = write(clientsd, sbuff, sizeof(sbuff));

		if(byteswritten < 0)
		{
			printf("message not sent \n");
		}
		memset(&msg, 0, sizeof(msg));
		read(clientsd,msg, sizeof(msg));
		printf("Server: %s\n",msg);
	}
	close(clientsd);


}
