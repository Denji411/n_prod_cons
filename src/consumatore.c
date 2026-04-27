#include "globals.h"
#include "consumatore.h"

pthread_mutex_t mutex_file_out;

void* consumatore(void* arg) {
    thread_args_t *args = (thread_args_t*)arg;
    buffer_t *buff = args -> buff;
    FILE *fp = args -> fp;

    pthread_exit(NULL);
}