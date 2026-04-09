#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "globals.h"
#include "produttore.h"
#include "consumatore.h"

int main() {
    pthread_t prod[NP], cons[NC];

    for (int i = 0; i < NP; i ++) {
        if (pthread_create(&prod[i], NULL, produttore, NULL) != 0) {
            perror("Errore di crezione thread");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NC; i ++) {
        if (pthread_create(&cons[i], NULL, consumatore, NULL) != 0) {
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

    return EXIT_SUCCESS;
}