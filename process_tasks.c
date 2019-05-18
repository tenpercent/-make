#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>

struct tmem {
    _Atomic int *counter;
    int tid;
    const char** commands;
};

static void* task(void *arg) {
    struct tmem* params = (struct tmem*) arg;
    int i = *params->counter;
    while (i > 0) {
        i = (*params->counter)--;
	if (i < 0) break;
	system(params->commands[i]);
	printf("i = %d\n", i);
    }
    return NULL;
}

int process_tasks(void) {
    const int nthr = 8;
    const int ntasks = 1000;
    pthread_t threads[nthr];
    _Atomic int counter = ntasks;
    const char* arr[ntasks];
    const char* cmd = "date";
    for (int i = 0; i < ntasks; ++i) {
        arr[i] = cmd;
    }
    for (int i = 0; i < nthr; ++i) {
	struct tmem arg = {.counter = &counter, .tid = i, .commands = arr};    
        pthread_create(threads + i, 
			NULL,
		    &task,
		    &arg);
    }
    for (int i = 0; i < nthr; ++i) {
        pthread_join(threads[i], NULL);
    }
    // check
    for (int i = 0; i < ntasks; ++i) {
       // printf("%d\n", arr[i]);	    
       if (arr[i] == 0) {
	   printf("AAA!");    
           return -1;
       }
    }
    return 0;
}

