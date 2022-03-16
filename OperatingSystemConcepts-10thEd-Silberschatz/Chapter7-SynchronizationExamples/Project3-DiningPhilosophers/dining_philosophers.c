#include <pthread.h>
#include <unistd.h>
#include "color.h"

// the number of philosophers
#define NUMBER      5
// the maximum time (in seconds) to sleep
#define MAX_SLEEP_TIME  3

pthread_mutex_t chopstick_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t chopstick_available = PTHREAD_COND_INITIALIZER;
int chopsticks[NUMBER];

int getWaitTime()
{
    return (rand() % MAX_SLEEP_TIME) + 1;
}
void think(int pnum)
{
    int thinkTime = getWaitTime();
    MyPrint(BYEL, "Philosopher %d is thinking for %d seconds\n", pnum, thinkTime);
    sleep(thinkTime);
}

void pickup_forks(int pnum)
{
    pthread_mutex_lock(&chopstick_mutex);
    while (chopsticks[pnum] == 1 || chopsticks[(pnum + 1) % 5] == 1)
    {
        pthread_cond_wait(&chopstick_available, &chopstick_mutex);
    }
    
    chopsticks[pnum] = 1;
    chopsticks[(pnum + 1) % 5] = 1;
    pthread_mutex_unlock(&chopstick_mutex);
}

void return_forks(int pnum)
{
    chopsticks[pnum] = 0;
    chopsticks[(pnum + 1) % 5] = 0;
    pthread_cond_signal(&chopstick_available);
}

void eat(int pnum)
{
    int eatTime = getWaitTime(); // The amount of time to eat
    MyPrint(BRED, "Philosopher %d is hungry\n", pnum);
    
    pickup_forks(pnum);
    
    // Eat
    MyPrint(BCYN, "Philosopher %d is eating for %d seconds\n", pnum, eatTime);
    sleep(eatTime);
    
    return_forks(pnum);
}

void *dine(void *pnum_ptr)
{
    int pnum = *(int*)pnum_ptr;
    MyPrint(BGRN, "Created philosopher thread %d\n", pnum);
    
    while(1)
    {
        think(pnum);
        eat(pnum);
    }
}

int main(int argc, char* argv[])
{
    int i, rc;
    pthread_t philosophers[NUMBER];
    
    srand(time(NULL));
    
    for (i = 0; i < NUMBER; ++i)
        chopsticks[i] = 0;

    for (i = 0; i < NUMBER; ++i)
    {
        if ((rc = pthread_create(&philosophers[i], NULL, &dine, &i)))
            MyPrint(BRED, "Thread creation failed: %d\n", rc);
        sleep(1);
    }
    
    for (i = 0; i < NUMBER; ++i)
        pthread_join(philosophers[i], NULL);

    exit(0);
}


