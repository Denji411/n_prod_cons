#include "globals.h"
#include "produttore.h"

pthread_mutex_t mutex_file_in;

void* produttore(void* arg) {
    thread_args_t *args = (thread_args_t*) arg;
    buffer_t *buff = args->buff;
    FILE *fp   = args->fp;

    while ()

    pthread_exit(NULL);
}