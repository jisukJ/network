#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(const char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char* argv[])
{
    int send_sock;
    sockaddr_in broad_ard;
    FILE *fp;
    char buf[BUF_SIZE];
    int so_brd=1;
    if(argc!=3){
        printf("Usage : %s <Broadcast IP> <port>\n",argv[0]);
        exit(1);
    }

    send_sock=socket(PF_INET,SOCK_DGRAM,0);
    memset(&broad_ard,0,sizeof(broad_ard));
    broad_ard.sin_family=AF_INET;
    broad_ard.sin_addr.s_addr=inet_addr(argv[1]);
    broad_ard.sin_port=htons(atoi(argv[2]));
    
    setsockopt(send_sock,SOL_SOCKET,SO_BROADCAST,&so_brd,sizeof(so_brd));
    if((fp=fopen("news.txt","r"))==NULL){
        error_handling("fopen() error!");
    }
    while(fgets(buf,BUF_SIZE,fp)!=NULL){
        sendto(send_sock,buf,strlen(buf),0,(sockaddr*)&broad_ard,sizeof(broad_ard));
        sleep(2);
    }
    close(send_sock);
    return 0;
}