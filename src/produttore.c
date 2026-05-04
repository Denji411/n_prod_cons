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

            if (buff -> buf[buff -> coda] == '\0') {
                break;
            }

            /*while (sem_vuoti > 0) {
                sleep(1);
            }*/

            pthread_mutex_lock(&mutex_file_in);
            for(int i = 0; i < NC; i++) {

                buff -> buf[buff -> testa] = '\0';
                sem_pieni++;
                sem_vuoti--;

                if (buff -> testa != 7) {
                    buff -> testa++;
                } else {
                    buff -> testa = 0;
                }

            }

            pthread_mutex_unlock(&mutex_file_out);
            break;

        }

        /*while (sem_vuoti > 0) {
            sleep(1);
        }*/

        pthread_mutex_lock(&mutex_file_in);

        buff -> buf[buff -> testa] = ch;
        sem_pieni++;
        sem_vuoti--;

        if (buff -> testa != 7) {
            buff -> testa++;
        } else {
            buff -> testa = 0;
        }

        pthread_mutex_unlock(&mutex_file_out);

    }

    pthread_exit(NULL);

}