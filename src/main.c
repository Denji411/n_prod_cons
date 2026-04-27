#include <stdlib.h>
#include <unistd.h>

#include "globals.h"
#include "produttore.h"
#include "consumatore.h"

int main() {
    FILE *in_fp = fopen(INPUT_FILE, "r");
    if(in_fp == NULL) {
        perror("Errore di apertura file input");
        return EXIT_FAILURE;
    }

    FILE *out_fp = fopen(OUTPUT_FILE, "w");
    if(out_fp == NULL) {
        perror("Errore di apertura file output");
        return EXIT_FAILURE;
    }

    buffer_t *buff = malloc(sizeof(buffer_t));

    pthread_mutex_init(&mutex_file_in, NULL);
    pthread_mutex_init(&mutex_file_out, NULL);

    thread_args_t args_prod = { in_fp, buff };
    thread_args_t args_cons = { out_fp, buff };

    pthread_t prod[NP], cons[NC];

    for (int i = 0; i < NP; i ++) {
        if (pthread_create(&prod[i], NULL, produttore, &args_prod) != 0) {
            perror("Errore di crezione thread");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NC; i ++) {
        if (pthread_create(&cons[i], NULL, consumatore, &args_cons) != 0) {
            perror("Errore di crezione thread");
            return EXIT_FAILURE;
        }
    }
   
    for (int i = 0; i < NP; i ++) {
        pthread_join(prod[i], NULL);
    }

    for (int i = 0; i < NC; i ++) {
        pthread_join(cons[i], NULL);
    }

    fclose(in_fp);
    fclose(out_fp);

    pthread_mutex_destroy(&mutex_file_in);
    pthread_mutex_destroy(&mutex_file_out);

    free(buff);

    return EXIT_SUCCESS;
}