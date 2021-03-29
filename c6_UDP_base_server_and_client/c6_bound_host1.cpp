#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30

void error_handling(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char* argv[])
{
    int sock;
    char message[BUF_SIZE];
    sockaddr_in my_adr,your_adr;
    socklen_t adr_sz;
    int str_len;

    if(argc!=2){
        exit(1);
    }
    
    sock=socket(PF_INET,SOCK_DGRAM,0);
    if(sock==-1){
        error_handling("");
    }
    memset(&my_adr,0,sizeof(my_adr));
    my_adr.sin_family=AF_INET;
    my_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    my_adr.sin_port=htons(atoi(argv[2]));

    if(bind(sock,(sockaddr*)&my_adr,sizeof(my_adr))==-1){
        error_handling("");
    }
    for(int i=0;i<3;++i){
        sleep(5);
        adr_sz=sizeof(your_adr);
        str_len=recvfrom(sock,message,sizeof(message),0,(sockaddr*)&your_adr,&adr_sz);
        printf("Message %d: %s \n",i+1,message);
    }
    close(sock);
    return 0;
}