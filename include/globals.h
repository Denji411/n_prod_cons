#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>

#define SENTINEL -1
#define BUFFER_SIZE 8

typedef struct {
    buffer_t *buff;
    FILE *fp;
} thread_args_t;

typedef struct {
    char buf[BUFFER_SIZE];
    int testa;
    int coda;
    int count;
} buffer_t;

extern int sem_vuoti;
extern int sem_pieni;
extern int mutex_buf;

#endif