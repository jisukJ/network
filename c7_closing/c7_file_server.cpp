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
    
    int serv_sock,clnt_sock;
    FILE* fp;
    char buf[BUF_SIZE];
    int read_cnt;

    sockaddr_in serv_adr,clnt_adr;
    socklen_t adr_sz;

    if(argc!=2){
        printf("Usage : %s <port>",argv[0]);
    }

    fp=fopen("c7_file_server.cpp","rb");
    serv_sock=socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));

    bind(serv_sock,(sockaddr*)&serv_adr,sizeof(serv_adr));
    listen(serv_sock,5);
    adr_sz=sizeof(clnt_adr);
    clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr,&adr_sz);
    
    while(1){
        read_cnt=fread(buf,1,BUF_SIZE,fp);
        if(read_cnt<BUF_SIZE){
            write(clnt_sock,buf,read_cnt);
            break;
        }
        write(clnt_sock,buf,BUF_SIZE);
    }
    shutdown(clnt_sock,SHUT_WR);
    read(clnt_sock,buf,BUF_SIZE);
    printf("Message from client: %s\n",buf);

    fclose(fp);
    close(clnt_sock);
    close(serv_sock);
    return 0;
}