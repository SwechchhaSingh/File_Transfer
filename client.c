#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

void recieve(int *sockid,char *data,int len)
{
	int st,rec=0;
	int len1=len;
	while(rec!=len1)
	{
		st=recv(sockid,data,len,0);
		rec+=st;			
		printf("%d bytes recieved \n",st);
		data=&data[st];
		len=len-st;
	}
	printf("Total Recieved : %d",rec);
}


int main()
{
	int port;
	printf("Enter port:");
	scanf("%d",&port);
int sockid;
struct sockaddr_in addrport;
sockid = socket(PF_INET, SOCK_STREAM, 0);

struct sockaddr_in serverport;
sockid = socket(PF_INET, SOCK_STREAM, 0);
serverport.sin_family = AF_INET;
serverport.sin_port = htons(port);
serverport.sin_addr.s_addr = inet_addr("0.0.0.0");

printf("\n Connecting .... \n");
int connect_status=connect(sockid,(struct sockaddr *) &serverport,sizeof(serverport));
if(connect_status<0)
write(2,"Connection Error",16);
else
printf("\nConnected\n");


int size;
char ch[5]="ok";

start:recv(sockid,&size,sizeof(int),0);
printf("\nReady to recieve %d bytes \n",size);
char msg[size];
send(sockid,ch,5,0);
recieve(sockid,msg,size);

printf("\n*********************************************\n" );
printf("%s\n",msg );
printf("*********************************************\n" );

goto start;
close(sockid);

}

