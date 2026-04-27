#ifndef PRODUTTORE_H
#define PRODUTTORE_H

#include <pthread.h>

#define INPUT_FILE "input/input.txt"

extern pthread_mutex_t mutex_file_in;

void* produttore(void*);

#endif