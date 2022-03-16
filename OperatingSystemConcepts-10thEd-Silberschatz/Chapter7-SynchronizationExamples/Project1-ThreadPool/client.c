#include "threadpool.h"

typedef struct data
{
    int a;
    int b;
    int c;
}args;

void add(void *param)
{
    int Time2Sleep = (rand() %5) + 1;
    struct data *temp;
    temp = (struct data*)param;
    
    printf(YEL "[#] task[%d] Sleep for %d seconds\n",temp->c, Time2Sleep);
    sleep(Time2Sleep);

    printf(MAG "[#] task[%d] add two values %d and %d result = %d\n",temp->c,temp->a, temp->b, temp->a + temp->b);
}

int main(void)
{
    srand(time(NULL));

    int numTask = 20;
    args *work;
    
    pool_init();

    work = (args*) malloc (sizeof(args)*numTask);
    for(int i=0;i<numTask;i++)
    {
        work[i].a = rand() %50;
        work[i].b = rand() %50;
        work[i].c = i+1;
        pool_submit(&add,&work[i]);
        sleep(1);
    }

    sleep(numTask);

    pool_shutdown();

    free(work);

    return 0;
}
