#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>

#define NUMBER_OF_THREADS 3
#define QUEUE_SIZE 9

// function prototypes
int pool_init(void);
int pool_submit(void (*somefunction)(void *p), void *p);
void pool_shutdown(void);

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
