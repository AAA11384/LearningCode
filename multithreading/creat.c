#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_THREAD 5

int counter = 0;
sem_t sem;

static void *my_thread(void *data){
    int need_add = 10000;

    while(need_add != 0){
        sem_wait(&sem);
        need_add--;
        counter++;
        //printf("thread %d plus 1 to counter \n",*(int*)data);
        sem_post(&sem);
    }
    
    return NULL;   
}

static void *no_sem_thread(void *data){
    int need_add = 10000;

    while(need_add != 0){
        need_add--;
        counter++;
    }
    
    return NULL;
}

int main(int argc, char **argv){
    pthread_t threads[NUM_THREAD];
    int threads_id[NUM_THREAD];

    sem_init(&sem, 0, 1);

    for(int i = 0; i < NUM_THREAD; i++){
        threads_id[i] = i+1;
        pthread_create(&threads[i], NULL, my_thread, &(threads_id[i]));
        //pthread_create(&threads[i], NULL, no_sem_thread, NULL);
    }


    for(int i =0; i < NUM_THREAD; i++){
        pthread_join(threads[i], NULL);
    }

    printf("cunter is %d\n", counter);
}
