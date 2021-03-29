#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char* argv[])
{
    int sock;
    FILE *fp;

    char buf[BUF_SIZE];
    int read_cnt;
    sockaddr_in serv_adr;
    if(argc!=3){
        error_handling("");
    }
    fp=fopen("receive.dat","wb");
    sock=socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_adr.sin_port=htons(atoi(argv[2]));

    connect(sock,(sockaddr*)&serv_adr,sizeof(serv_adr));
    while((read_cnt=read(sock,buf,BUF_SIZE))!=0){
       fwrite(buf,1,read_cnt,fp); 
    }
    puts("Received file data");
    write(sock,"Thank you",10);
    fclose(fp);
    close(sock);
    return 0;
}