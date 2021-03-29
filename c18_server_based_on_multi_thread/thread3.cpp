#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int sum=0;

void * thread_summation(void *arg){
    int start=((int*)arg)[0];
    int end=((int*)arg)[1];

    while(start<=end){
        sum+=start;
        printf("%d added!",start);
        start++;
        sleep(2);
    }
    return NULL;
}

int main()
{
    pthread_t id_t1,id_t2;
    int range1[]={1,10};
    int range2[]={11,13};

    pthread_create(&id_t1,NULL,thread_summation,range1);
    pthread_create(&id_t2,NULL,thread_summation,range2);
    
    pthread_join(id_t1,NULL);
    printf("t1 ended sum=%d\n",sum);
    pthread_join(id_t2,NULL);
    printf("sum=%d\n",sum);
    return 0;

}