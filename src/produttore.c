#include "globals.h"
#include "produttore.h"

pthread_mutex_t mutex_file_in;

void* produttore(void* arg) {
    thread_args_t *args = (thread_args_t*)arg;
    buffer_t *buff = args -> buff;
    FILE *fp = args -> fp;

    char ch;
    while (1) {
        fscanf(fp, "%c", &ch);
        if (feof(ch)) {
            pthread_mutex_lock(&mutex_file_in);
            for(int i = 0; i < NC; i++) {
                if (sem_vuoti > 0) {
                    buff -> buf[buff -> testa] = '\0';
                    if (buff -> testa != 8) {
                        buff -> testa++;
                    } else {

                    }
                }
            }
            pthread_mutex_unlock(&mutex_file_in);
            break;
        }
    }

    pthread_exit(NULL);
}