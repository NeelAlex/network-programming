#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>
#include<semaphore.h>
void error(const char *msg)
{
   perror(msg);
   exit(1);
 }
 
 int sockfd;
 int client_count;
 sem_t mutex;
 
 void *handle_connection(void *newsockfda)
 {
     int newsockfd1;
     newsockfd1=(int)newsockfda;
     char buffer[256];
     int n,cli_num;
     sem_wait(&mutex);
     client_count++;
     printf("Client count:%d\n",client_count);
     cli_num=client_count-1;
     sem_post(&mutex);
     while(1)
     {
       bzero(buffer,256);
       n=read(newsockfd1,buffer,255);
       if(n<0)
			error("Error reading from socket");
		printf("Client %d:%s\n",cli_num,buffer);
		if(buffer[0]=='b'&&buffer[1]=='y'&&buffer[2]=='e')
		{
			close(newsockfd1);
			return 0;
		}
		bzero(buffer,256);
		printf("server:");
		fgets(buffer,255,stdin);
		n=write(newsockfd1,buffer,18);
		if(n<0)
			error("Error writing to socket");
		if(buffer[0]=='b'&&buffer[1]=='y'&&buffer[2]=='e')
		{
		close(sockfd);
		 //  exit(0);
		}
	}
	//close(newsockfd1);
	//close(sockfd);
	exit(0);
}

int main(int argc,char *argv[])
{
	int sockfd,portno=12345,newsockfd;
	socklen_t clilen;
	sem_init(&mutex,0,1);
	pthread_t thread;
	//char buffer[256];
	struct sockaddr_in serv_addr,cli_addr;
	int n;
	if(argc<2)
	{
		fprintf(stderr,"Error! No port provided\n");
		exit(1);
	}
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
		error("Error opening socket..\n");
	bzero((char *)&serv_addr,sizeof(serv_addr));
	portno=atoi(argv[1]);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(portno);
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
		error("Error on binding\n");
	listen(sockfd,5);
	clilen=sizeof(cli_addr);
	while(1)
	{
	newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
	if(newsockfd<0)
		error("Error on accept\n");
   pthread_create(&thread,NULL,handle_connection,(void *)newsockfd);
	}
		return 0;
		}
