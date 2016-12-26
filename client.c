#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>//

int main(int argc,char* argv[]){
	int sockfd,port=5055;
	char buf[256];
	struct sockaddr_in servaddr;

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	//port=atoi(argv[2]);

	bzero((char*)&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(port);

	connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	while(1){
		printf("Client:");
		bzero(buf,sizeof(buf));
		fgets(buf,256,stdin);
		write(sockfd,buf,strlen(buf));
			if(buf[0]=='b' && buf[1]=='y' && buf[2]=='e'){
				close(sockfd);
				break;
			}

		bzero(buf,256);
		read(sockfd,buf,255);
		printf("\nserver:%s",buf);
			if(buf[0]=='b' && buf[1]=='y' && buf[2]=='e'){
				close(sockfd);
				break;
			}
	}
	close(sockfd);
	return 0;
}
