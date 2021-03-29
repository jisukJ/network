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
    int serv_sock,clnt_sock;
    char message[BUF_SIZE];
    int str_len;

    sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;
    FILE *readfp,*writefp;
    if(argc!=2){
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }

    serv_sock=socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock,(sockaddr*)&serv_adr,sizeof(serv_adr))==-1){
        error_handling("bind() error!");
    }
    if(listen(serv_sock,5)==-1){
        error_handling("listen() error!");
    }
    clnt_adr_sz=sizeof(clnt_adr);
    for(int i=0;i<5;++i){
        if((clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr,&clnt_adr_sz))==-1){
            error_handling("accept() error!");
        }
        printf("Connected client %d\n",clnt_sock);
        readfp=fdopen(clnt_sock,"r");
        writefp=fdopen(clnt_sock,"w");
        while(!feof(readfp)){
            fgets(message,BUF_SIZE,readfp);
            fputs(message,writefp);
            fflush(writefp);
        }
        fclose(readfp);
        fclose(writefp);
    }
    close(serv_sock);
    return 0;
}