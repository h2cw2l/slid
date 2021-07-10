#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t mtx;
pthread_cond_t cond;
volatile unsigned long flag = 0;
char ca[6] = "abcde";

void * thread_func(void * arg){   
    int i = 0;
    for(i = 0; i < 5; i++){
       pthread_mutex_lock(&mtx);
       if(1 == flag){
           pthread_cond_wait(&cond, &mtx);
       }
       printf("%c", ca[i]);
       flag = 1;
       pthread_cond_signal(&cond);
       pthread_mutex_unlock(&mtx);
    }
}

void * thread_func1(void * arg){
   
    int i = 0;
    for(i = 0; i < 5; i++){

        pthread_mutex_lock(&mtx);
        if(0 == flag){
            pthread_cond_wait(&cond, &mtx);
        }
        printf("%d", i + 1);

        flag = 0;
        // if signal before wait, not effect 
        // wait must before signal
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);
    }
}

int main(){

    int initrt = pthread_mutex_init(&mtx, NULL);
    if(initrt != 0){
        printf("\r\n  lock init failed  \r\n");
        
        return -1;
    }
    
    if(pthread_cond_init(&cond, NULL) < 0){
         printf("\r\n init cond failed  \r\n");
         return -1;
    }

    pthread_t pt1;
    int time0 = 1;
    int pt1c = pthread_create(&pt1, NULL, thread_func, (void *)time0);
    if(pt1c < 0){
        printf("\r\n create pt1c failed, pt1c = %d  \r\n", pt1c);
        return pt1c;
    }
    
    pthread_t pt2;
    int time = 2;
    int pt2c = pthread_create(&pt2, NULL, thread_func1, (void *)time);
    if(pt2c < 0){
        printf("\r\n create pt1c failed, pt2c = %d  \r\n", pt2c);
        return pt2c;
    }
    void * pt1ret;
    pthread_join(pt1, &pt1ret);
    void * pt2ret;
    pthread_join(pt2, &pt2ret);
    // sleep(5);
    printf("\r\n");
    return 0;
}
