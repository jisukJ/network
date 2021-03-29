#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char* argv[])
{
    FILE* fp;
    int fd=open("data.txt",O_WRONLY|O_TRUNC|O_CREAT);
    if(fd==-1){
        fputs("file open error",stderr);
        return -1;
    }

    printf("First file descriptor: %d\n",fd);
    fp=fdopen(fd,"w");
    fputs("TCP/IP SOCKET PROGRAMMING\n",fp);
    printf("Second file descriptor: %d\n",fileno(fp));
    fclose(fp);
    return 0;
}