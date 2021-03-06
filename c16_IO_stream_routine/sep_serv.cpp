#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main(int argc,char *argv[])
{
    int serv_sock,clnt_sock;
    FILE *readfp,*writefp;

    sockaddr_in serv_addr,clnt_addr;
    socklen_t clnt_adr_sz;
    char buf[BUF_SIZE]={0,};
    serv_sock=socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    bind(serv_sock,(sockaddr*)&serv_addr,sizeof(serv_addr));
    listen(serv_sock,5);
    clnt_adr_sz=sizeof(clnt_addr);
    clnt_sock=accept(serv_sock,(sockaddr*)&clnt_addr,&clnt_adr_sz);

    readfp=fdopen(clnt_sock,"r");
    writefp=fdopen(clnt_sock,"w");

    fputs("FROM SERVER: Hi~ client?\n",writefp);
    fputs("I love all of the world!\n",writefp);
    fputs("You are awesome!\n",writefp);
    fflush(writefp);
    fclose(writefp);
    fgets(buf,sizeof(buf),readfp);
    fputs(buf,stdout);    
    fclose(readfp);
    return 0;
}