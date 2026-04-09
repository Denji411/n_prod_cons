#ifndef CONSUMATORE_H
#define CONSUMATORE_H

#include <pthread.h>

#define NC 3
#define OUTPUT_FILE "output/output.txt"

extern pthread_mutex_t mutex_file_out;

void* consumatore(void*);

#endif