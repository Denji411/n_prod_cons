#include "globals.h"
#include "consumatore.h"

pthread_mutex_t mutex_file_out;

void* consumatore(void* arg) {
    thread_args_t *args = (thread_args_t*)arg;
    buffer_t *buff = args -> buff;
    FILE *fp = args -> fp;

    char ch;
    while (1) {
        if (buff -> buf[buff -> coda] == '\0') {   
            break;
        }

        /*while (sem_pieni > 0) {
            sleep(1);
        }*/

        pthread_mutex_lock(&mutex_file_out);

        ch = buff -> buf[buff -> coda];
        fprintf(fp, "%c", ch);
        sem_pieni--;
        sem_vuoti++;

        if (buff -> coda != 7) {
            buff -> coda++;
        } else {
            buff -> coda = 0;
        }

        pthread_mutex_unlock(&mutex_file_in);

    }

    pthread_exit(NULL);

}