#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024

void error_handling(const char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char* argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    sockaddr_in serv_adr;
    FILE *readfp,*writefp;
    if(argc!=3){
        printf("Usage : %s <IP> <port>\n",argv[0]);
        exit(1);
    }
    sock=socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_adr.sin_port=htons(atoi(argv[2]));

    if(connect(sock,(sockaddr*)&serv_adr,sizeof(serv_adr))==-1){
        error_handling("connect() error!");
    }
    puts("Connected..........");
    readfp=fdopen(sock,"r");
    writefp=fdopen(sock,"w");
    while(1){
        fputs("Input message(Q to quit): ",stdout);
        fgets(message,BUF_SIZE,stdin);
        if(!strcmp(message,"q\n")||!strcmp(message,"Q\n")){
            break;
        }
        fputs(message,writefp);
        fflush(writefp);
        fgets(message,BUF_SIZE,readfp);
        printf("Message from server : %s",message);
    }
    fclose(writefp);
    fclose(readfp);
    return 0;
}