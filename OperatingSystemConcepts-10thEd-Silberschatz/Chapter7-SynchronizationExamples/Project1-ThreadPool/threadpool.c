#include "threadpool.h"

pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;
sem_t full;         
sem_t empty; 

typedef struct works
{
    void (*function)(void *p);
    void *data;
    struct works* next;
} task;

typedef struct Mythreadpool {
	int qsize;			//number in the queue
	pthread_t *threads;	//pointer to threads
	task* qhead;		//queue head pointer
	task* qtail;		//queue tail pointer
	int shutdown;
} threadpool;
threadpool pool;

int enqueue(task* cur) 
{
    pthread_mutex_lock(&qlock);
    sem_wait(&full);
    if(pool.qsize == 0) {
		pool.qhead = cur; 
		pool.qtail = cur;
	} else {
		pool.qtail->next = cur;
		pool.qtail = cur;			
	}
    sem_post(&empty);
	pool.qsize++;
	pthread_mutex_unlock(&qlock); 
    return 0;
}

task* dequeue(int tnum) 
{
    task* cur;
    pthread_mutex_lock(&qlock);
    while( pool.qsize == 0) {
        pthread_mutex_unlock(&qlock);
        sem_wait(&empty);
        pthread_mutex_lock(&qlock);
        if(pool.shutdown) {
            printf(RESET "[!] thread %d Shutdown!!\n", tnum);
			pthread_mutex_unlock(&qlock);
			pthread_exit(NULL);
		}
    }
    cur = pool.qhead;	//set the cur variable.  
	pool.qsize--;		//decriment the size.  

    if(pool.qsize == 0) {
        pool.qhead = NULL;
        pool.qtail = NULL;
    }
    else {
        pool.qhead = cur->next;
    }

    sem_post(&full);
    pthread_mutex_unlock(&qlock);
    
    return cur;
}

int pool_submit(void (*somefunction)(void *p), void *arg)
{
    task * cur;

	cur = (task*) malloc(sizeof(task));
	if(cur == NULL) {
		fprintf(stderr, "Out of memory creating a work struct!\n");
		return 1;	
	}
    cur->function = somefunction;
    cur->data = arg;

    enqueue(cur);
    printf(CYN "[*] added new task\n");

    return 0;
}

void Myexecute(void (*somefunction)(void *), void *p)
{
    (*somefunction)(p);
}

void *worker(void *param)
{
    task* cur;
    int tnum = *(int*)param + 1;
    printf(GRN "[!] Created thread %d\n", tnum);

	while(1) {

        printf(WHT "[!] thread %d looking for job\n", tnum);
        cur = dequeue(tnum);
		printf(RED "[!] thread %d got new job\n", tnum);

        //(cur->function) (cur->data); 
        Myexecute(cur->function, cur->data);
		free(cur);
	}
}


int pool_init(void)
{
    pool.threads = (pthread_t*) malloc (sizeof(pthread_t) * NUMBER_OF_THREADS);
    if(!pool.threads) {
        fprintf(stderr, "Out of memory creating a new threadpool!\n");
        return 1;	
    }

    pool.qsize = 0;
    pool.qhead = NULL;
    pool.qtail = NULL;
    pool.shutdown = 0;

    sem_init(&full, 0, QUEUE_SIZE);   
    sem_init(&empty, 0, 0);   

    for (int i = 0;i < NUMBER_OF_THREADS;i++) {
        if(pthread_create(&(pool.threads[i]),NULL,&worker,&i)) {
            fprintf(stderr, "Thread initiation error!\n");	
            return 1;		
        }
        sleep(1);
    }
    return 0;
}

void pool_shutdown(void)
{
    pool.shutdown = 1;

    for (int i = 0;i < NUMBER_OF_THREADS;i++)
        sem_post(&empty);

    for (int i = 0;i < NUMBER_OF_THREADS;i++)
        pthread_join(pool.threads[i],NULL);
    
    free(pool.threads);

    sem_destroy(&full);
    sem_destroy(&empty);
}
