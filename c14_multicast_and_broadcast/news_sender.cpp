#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TTL 64
#define BUF_SIZE 30

void error_handling(const char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char* argv[])
{
    int send_sock;
    sockaddr_in mul_adr;
    int time_live=TTL;
    FILE* fp;
    char buf[BUF_SIZE];
    if(argc!=3){
        printf("Usage : %s <GroupIP> <port>\n",argv[0]);
        exit(1);
    }

    send_sock=socket(PF_INET,SOCK_DGRAM,0);
    memset(&mul_adr,0,sizeof(mul_adr));
    mul_adr.sin_family=AF_INET;
    mul_adr.sin_addr.s_addr=inet_addr(argv[1]);
    mul_adr.sin_port=htons(atoi(argv[2]));

    setsockopt(send_sock,IPPROTO_IP,IP_MULTICAST_TTL,&time_live,sizeof(time_live));
    if((fp=fopen("news.txt","r"))==NULL){
        error_handling("fopen() error!");
    }
    while(fgets(buf,BUF_SIZE,fp)!=NULL){
        sendto(send_sock,buf,strlen(buf),0,(sockaddr*)&mul_adr,sizeof(mul_adr));
    }
    fclose(fp);
    close(send_sock);
    return 0;
}