#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/tcp.h>

void error_handling(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char* argv[])
{
    int sock;
    int opt_val;
    int state;
    socklen_t opt_len;

    sock=socket(PF_INET,SOCK_STREAM,0);
    opt_len=sizeof(opt_val);
    state=getsockopt(sock,IPPROTO_TCP,TCP_NODELAY,&opt_val,&opt_len);
    if(state){
        error_handling("getsockopt() error!");
    }
    printf("Quick ack : %d \n",opt_val);
    opt_val=1;
    state=setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,&opt_val,sizeof(opt_val));
    if(state){
        error_handling("setsockopt() error!");
    }
    opt_val=0;
    opt_len=sizeof(opt_val);
    state=getsockopt(sock,IPPROTO_TCP,TCP_NODELAY,&opt_val,&opt_len);
    if(state){
        error_handling("getsockopt() error!");
    }
    printf("Quick ack : %d \n",opt_val);
    return 0;
}