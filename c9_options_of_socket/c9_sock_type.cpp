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
    int tcp_sock,udp_sock;
    int sock_type;
    socklen_t optlen;
    int state;

    optlen=sizeof(sock_type);
    tcp_sock=socket(PF_INET,SOCK_STREAM,0);
    udp_sock=socket(PF_INET,SOCK_DGRAM,0);
    printf("SOCK_STREAM: %d\n",SOCK_STREAM);
    printf("SOCK_DGRAM: %d\n",SOCK_DGRAM);

    state=getsockopt(tcp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);
    if(state){
        error_handling("getsockopt() error!");
    }
    printf("Socket type two: %d\n",sock_type);
    return 0;
}