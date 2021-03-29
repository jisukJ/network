#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
    if(sig==SIGALRM){
        puts("Time out!");
    }
    alarm(2);
}
void escape(int sig)
{
    if(sig==SIGINT){
        puts("Ctrl+C Pressed");
    }
}


int main(int argc,char* argv[])
{
    struct sigaction act;
    struct sigaction act2;
    act.sa_handler=timeout;
    act2.sa_handler=escape;
    sigemptyset(&act.sa_mask);
    sigemptyset(&act2.sa_mask);
    act.sa_flags=0;
    act2.sa_flags=0;
    sigaction(SIGALRM,&act,0);
    sigaction(SIGINT,&act2,0);
    alarm(2);
    for(int i=0;i<3;++i){
        puts("wait...");
        sleep(100);
    }
    return 0;
}