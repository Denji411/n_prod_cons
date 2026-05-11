#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "globals.h"
#include "produttore.h"
#include "consumatore.h"

int main() {
    FILE *in_fp = fopen(INPUT_FILE, "r");
    if (in_fp == NULL) {
        perror("Errore di apertura file input");
        return EXIT_FAILURE;
    }

    FILE *out_fp = fopen(OUTPUT_FILE, "w");
    if (out_fp == NULL) {
        perror("Errore di apertura file output");
        fclose(in_fp);
        return EXIT_FAILURE;
    }

    buffer_t *buff = malloc(sizeof(buffer_t));
    if (buff == NULL) {
        perror("Errore di allocazione buffer");
        fclose(in_fp); fclose(out_fp);
        return EXIT_FAILURE;
    }
    
    memset(buff->buf, 0, sizeof(buff->buf));
    buff->testa = 0;
    buff->coda  = 0;
    buff->count = 0;

    pthread_mutex_init(&mutex_file_in,  NULL);
    pthread_mutex_init(&mutex_file_out, NULL);
    pthread_mutex_init(&mutex_buf,      NULL);
    pthread_mutex_init(&mutex_sentinel, NULL);
    sem_init(&sem_vuoti, 0, BUFFER_SIZE);
    sem_init(&sem_pieni, 0, 0);

    thread_args_t args_prod = { buff, in_fp  };
    thread_args_t args_cons = { buff, out_fp };

    pthread_t prod[NP], cons[NC];

    for (int i = 0; i < NP; i++) {
        if (pthread_create(&prod[i], NULL, produttore, &args_prod) != 0) {
            perror("Errore di creazione thread produttore");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NC; i++) {
        if (pthread_create(&cons[i], NULL, consumatore, &args_cons) != 0) {
            perror("Errore di creazione thread consumatore");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NP; i++) pthread_join(prod[i], NULL);
    for (int i = 0; i < NC; i++) pthread_join(cons[i], NULL);

    fclose(in_fp);
    fclose(out_fp);

    pthread_mutex_destroy(&mutex_file_in);
    pthread_mutex_destroy(&mutex_file_out);
    pthread_mutex_destroy(&mutex_buf);
    sem_destroy(&sem_vuoti);
    sem_destroy(&sem_pieni);

    free(buff);
    return EXIT_SUCCESS;
}
