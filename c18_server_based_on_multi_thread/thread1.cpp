#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* thread_main(void *arg){
    int cnt=*((int*)arg);
    for(int i=0;i<cnt;++i){
        sleep(1);
        puts("running thread");
    }
    return NULL;
}

int main(int argc,char *argv[])
{
    pthread_t t_id;
    pthread_self();
    int thread_param=5;
    if(pthread_create(&t_id,NULL,thread_main,(void*)&thread_param)!=0){
         puts("pthread_create() error");
         return -1;
     }
     puts("end of main");
    return 0;
}