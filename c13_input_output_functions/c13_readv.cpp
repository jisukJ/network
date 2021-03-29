#include <stdio.h>
#include <sys/uio.h>

#define BUF_SIZE 100

int main(int argc,char* argv[])
{
    iovec vec[2];
    char buf1[BUF_SIZE]={0,};
    char buf2[BUF_SIZE]={0,};

    vec[0].iov_base=buf1;
    vec[0].iov_len=5;
    vec[1].iov_base=buf2;
    vec[1].iov_len=BUF_SIZE;

    int str_len=readv(0,vec,2);
    printf("Read bytes: %d\n",str_len);
    printf("First message: %s\n",buf1);
    printf("Second message: %s\n",buf2);
    printf("END!");
    return 0;
}