#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>

struct tmem {
    _Atomic int *counter;
    int tid;
    int *arr;
};

static void* task(void *arg) {
    struct tmem* params = (struct tmem*) arg;
    int i = *params->counter;
    while (i > 0) {
        i = --(*params->counter);
	params->arr[i] = 1 + params->tid;
    }
    return NULL;
}

int process_tasks(void) {
    const int nthr = 8;
    pthread_t threads[nthr];
    _Atomic int counter = 100000;
    int arr[100000] = {0};
    for (int i = 0; i < nthr; ++i) {
	struct tmem arg = {.counter = &counter, .tid = i, .arr = arr};    
        pthread_create(threads + i, 
		       NULL, /* default attributes */
		       &task,
		       &arg);
    }
    for (int i = 0; i < nthr; ++i) {
        pthread_join(threads[i], NULL);
    }
    // check
    for (int i = 0; i < 100000; ++i) {
       // printf("%d\n", arr[i]);	    
       if (arr[i] == 0) {
	   printf("AAA!");    
           return -1;
       }
    }
    return 0;
}

