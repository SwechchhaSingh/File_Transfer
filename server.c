#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <string.h>



#define max_request 4



void transmit(int *sockid,char *data,int len)
{
	int st=0,sen=0;
	int len1=len;
	while(sen!=len1)
	{
		st=send(sockid,data,len,0);
		sen+=st;		
		printf("%d bytes transmitted \n",st);
		data=&data[st];
		len=len-st;
	}
	printf("\nTotal %d Bytes sent\n",sen);

}

int main()
{
	int port;
	printf("Enter port:");
	scanf("%d",&port);
	struct sockaddr_in addrport;
	addrport.sin_family = AF_INET;
	addrport.sin_port = htons(port);
	addrport.sin_addr.s_addr = htonl(INADDR_ANY);

        int sockid = socket(PF_INET, SOCK_STREAM, 0);
	
	if(bind(sockid, (struct sockaddr *) &addrport, sizeof(addrport))!= -1) 
	{
		printf("\nPort Bind Success\n");
	}
	else
	{
		printf("\nBinding Failed\n");
		return(0);
	}


	int listen_status=listen(sockid,max_request);
	if(listen_status==-1)
	printf("\nListening Error\n");
	else
	printf("\nListening...\n");
	
	struct sockaddr_in clientaddr;
	int addlen=sizeof(struct sockaddr_in);
	int new_client_socket=accept(sockid,(struct sockaddr_in *)&clientaddr,&addlen);
	printf("\n Connection Accepted \n");

	int length;
	char msg[50];
	char reception[5];
start:	scanf("%s",msg);
	

	FILE * f = fopen (msg, "r");

	if (f)
	{
  		fseek (f, 0, SEEK_END);
  		length = ftell (f);
  		fseek (f, 0, SEEK_SET);
  		char data[length];
	        fread (data, 1, length, f);
	        fclose (f);
		
	
	
	
	send(new_client_socket,&length,sizeof(length),0);
	recv(new_client_socket,reception,5,0);
	
	if(!strcmp(reception,"ok"))
	transmit(new_client_socket,data,length);
	
	}
	
	goto start;
	
	close(new_client_socket);
	close(sockid);
}

