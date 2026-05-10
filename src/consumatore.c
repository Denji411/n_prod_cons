#include "globals.h"
#include "consumatore.h"

void* consumatore(void* arg) {
    thread_args_t *args = (thread_args_t*)arg;
    buffer_t *buff = args->buff;
    FILE     *fp   = args->fp;

    char ch;
    while (1) {
        sem_wait(&sem_pieni);
        pthread_mutex_lock(&mutex_buf);

        ch = buff->buf[buff->coda];
        buff->coda = (buff->coda + 1) % BUFFER_SIZE;
        buff->count--;

        pthread_mutex_unlock(&mutex_buf);
        sem_post(&sem_vuoti);

        if (ch == SENTINEL) break;

        pthread_mutex_lock(&mutex_file_out);
        fprintf(fp, "%c", ch);
        pthread_mutex_unlock(&mutex_file_out);
    }

    pthread_exit(NULL);
}
