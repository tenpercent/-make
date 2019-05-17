#include <pthread.h>
#include <stdatomic.h>

struct tmem {
    _Atomic int *counter;
    int tid;
};

static void* task(void *arg) {
    struct tmem* params = (struct tmem*) arg;
    int i = *params->counter;
    while (i > 0) {
        i = --(*params->counter);
    }
    return NULL;
}

int process_tasks(void) {
    const int nthr = 8;
    pthread_t threads[nthr];
    _Atomic int counter = 100000;
    for (int i = 0; i < nthr; ++i) {
	struct tmem arg = {.counter = &counter, .tid = i};    
        pthread_create(threads + i, 
		       NULL, /* default attributes */
		       &task,
		       &arg);
    }
    for (int i = 0; i < nthr; ++i) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}

