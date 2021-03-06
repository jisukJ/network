#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024

void error_handling(const char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
}
int main(int argc,char* argv[])
{
    int sock;
    char message[BUF_SIZE];
    sockaddr_in serv_addr,from_addr;
    int str_len;
    socklen_t adr_sz;

    if(argc!=3){
        printf("Usage : %s <IP> <port>",argv[0]);
    }
    sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock==-1){
        error_handling("socket() error!");
    }
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));

    while(1){
        fputs("Insert message(q to quit): ",stdout);
        fgets(message,sizeof(message),stdin);
        if(!strcmp(message,"q\n")||!strcmp(message,"Q\n")){
            break;
        }
        sendto(sock,message,strlen(message),0,(sockaddr*)&serv_addr,sizeof(serv_addr));
        adr_sz=sizeof(from_addr);
        str_len=recvfrom(sock,message,BUF_SIZE,0,(sockaddr*)&from_addr,&adr_sz);
        message[str_len]=0;
        printf("Message from server: %s",message);
    }
    close(sock);
    return 0;
}