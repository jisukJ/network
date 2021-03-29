#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
using namespace std;

#define NUM_THREAD 100

void * thread_inc(void *arg);
void * thread_des(void *arg);
long long num=0;



int main(int argc,char *argv[])
{
    pthread_t thread_id;
    vector<pthread_t>box;
    printf("sizeof long long: %ld \n",sizeof(long long));
    for(int i=0;i<NUM_THREAD;++i){
        if(i%2){
            pthread_create(&thread_id,NULL,thread_inc,NULL);
            box.push_back(thread_id);
        }else{
            pthread_create(&thread_id,NULL,thread_des,NULL);
            box.push_back(thread_id);
        }
    }
    for(int i=0;i<box.size();++i){
        pthread_join(box[i],NULL);
    }
    printf("results: %lld\n",num);
    return 0;
    
}

void * thread_inc(void * arg){
    for(int i=0;i<50000000;++i){
        num+=1;
    }
    printf("calc done!\n");
    return NULL;
}
void * thread_des(void * arg){
    for(int i=0;i<50000000;++i){
        num-=1;
    }
    printf("calc done!\n");
    return NULL;
}