#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NP 3
#define NC 3

#define SENTINEL '\0'
#define BUFFER_SIZE 8

typedef struct {
    char buf[BUFFER_SIZE];
    int testa;
    int coda;
    int count;
} buffer_t;

typedef struct {
    buffer_t *buff;
    FILE *fp;
} thread_args_t;

extern pthread_mutex_t mutex_file_in;
extern pthread_mutex_t mutex_file_out;
extern pthread_mutex_t mutex_sentinel;
extern int sentinel_inviati;

extern sem_t sem_vuoti;
extern sem_t sem_pieni;
extern pthread_mutex_t mutex_buf;

#endif
