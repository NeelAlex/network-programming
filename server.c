#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>//

int main(int argc, char* argv[]){
	int sockfd,newsockfd,port=5055,len;
	char buf[256];
	struct sockaddr_in servaddr,cliaddr;

	//port=atoi(argv[1]);//
	sockfd=socket(AF_INET,SOCK_STREAM,0);//

	bzero((char*)&servaddr,sizeof(servaddr));//
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port=htons(port);

	bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	listen(sockfd,5);
	len=sizeof(cliaddr);
	newsockfd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);

	while(1){
		bzero(buf,256);
		read(newsockfd,buf,255);
		printf("Client:%s",buf);
			if(buf[0]=='b' && buf[1]=='y' && buf[2]=='e'){
				close(sockfd);
				break;
			}

		//bzero(buf,256);
		//fgets(buf,255,stdin);
		write(newsockfd,buf,strlen(buf));
		printf("Server:%s",buf);

		if(buf[0]=='b' && buf[1]=='y' && buf[2]=='e'){
				close(sockfd);
				break;
			}

	}
	close(sockfd);
	close(newsockfd);
	return 0; 
}
