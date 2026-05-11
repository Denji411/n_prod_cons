#include "globals.h"

pthread_mutex_t mutex_file_in;
pthread_mutex_t mutex_file_out;
pthread_mutex_t mutex_sentinel;
int sentinel_inviati = 0;

sem_t sem_vuoti;
sem_t sem_pieni;
pthread_mutex_t mutex_buf;
