#include "globals.h"
#include "produttore.h"

void* produttore(void* arg) {
    thread_args_t *args = (thread_args_t*)arg;
    buffer_t *buff = args->buff;
    FILE     *fp   = args->fp;

    char ch;
    while (1) {
        pthread_mutex_lock(&mutex_file_in);
        int ret = fscanf(fp, "%c", &ch);
        pthread_mutex_unlock(&mutex_file_in);

        if (ret == EOF) {
            pthread_mutex_lock(&mutex_sentinel);
            if (!sentinel_inviati) {
                sentinel_inviati = 1;
                pthread_mutex_unlock(&mutex_sentinel);

                for (int i = 0; i < NC; i++) {
                    sem_wait(&sem_vuoti);
                    pthread_mutex_lock(&mutex_buf);
                    buff->buf[buff->testa] = SENTINEL;
                    buff->testa = (buff->testa + 1) % BUFFER_SIZE;
                    buff->count++;
                    pthread_mutex_unlock(&mutex_buf);
                    sem_post(&sem_pieni);
                }
            } else {
                pthread_mutex_unlock(&mutex_sentinel);
            }
            break;
        }

        sem_wait(&sem_vuoti);
        pthread_mutex_lock(&mutex_buf);

        buff->buf[buff->testa] = ch;
        buff->testa = (buff->testa + 1) % BUFFER_SIZE;
        buff->count++;

        pthread_mutex_unlock(&mutex_buf);
        sem_post(&sem_pieni);
    }

    pthread_exit(NULL);
}
