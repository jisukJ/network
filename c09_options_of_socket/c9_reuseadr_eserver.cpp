#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error_handling(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    char message[30];
    int option,str_len;
    socklen_t optlen, clnt_adr_sz;
    sockaddr_in serv_adr,clnt_adr;
    if(argc!=2){
        printf("Usage: %s <port>",argv[0]);
        exit(1);
    }
    serv_sock=socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock==-1){
        error_handling("socket() error!");
    }
    optlen=sizeof(option);
    option=true;
    setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,&option,optlen);
    memset(&serv_sock,0,sizeof(serv_sock));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_adr.sin_port=htons(atoi(argv[2]));

    if(bind(serv_sock,(sockaddr*)&serv_adr,sizeof(serv_adr))==-1){
        error_handling("bind() error!");
    }
    if(listen(serv_sock,5)==-1){
        error_handling("listen() error!");
    }
    clnt_adr_sz=sizeof(clnt_adr);
    clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr,&clnt_adr_sz);
    while((str_len=read(clnt_sock,message,sizeof(message)))!=0){
        write(clnt_sock,message,str_len);
        write(1,message,str_len);
    }
    close(clnt_sock);
    close(serv_sock);
    return 0;
}