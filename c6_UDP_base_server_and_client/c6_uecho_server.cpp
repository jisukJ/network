#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define BUF_SIZE 1024

void error_handling(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char* argv[])
{
    int serv_sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t clnt_adr_sz;
    sockaddr_in serv_adr,clnt_adr;
    if(argc!=2){
        printf("Usage : %s <IP> <port>\n",argv[0]);
        exit(1);
    }
    serv_sock=socket(PF_INET,SOCK_DGRAM,0);
    if(serv_sock=-1){
        error_handling("UDP socket creation error");
    }
    memset(&serv_sock,0,sizeof(serv_sock));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_adr.sin_port=htons(atoi(argv[2]));

    if(bind(serv_sock,(sockaddr*)&serv_adr,sizeof(serv_adr))==-1){
        error_handling("bind() error!");
    }
    while(1){
        clnt_adr_sz=sizeof(clnt_adr);
        str_len=recvfrom(serv_sock,message,BUF_SIZE,0,(sockaddr*)&clnt_adr,&clnt_adr_sz);
        sendto(serv_sock,message,str_len,0,(sockaddr*)&clnt_adr,clnt_adr_sz);
    }
    close(serv_sock);
    return 0;
}