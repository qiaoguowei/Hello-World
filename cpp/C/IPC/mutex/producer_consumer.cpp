#include <iostream>
#include <pthread.h>
#include <string.h>
#include <algorithm>
#include <unistd.h>

#define NITEMS      1024
#define NTHREADS    100

int nitems;
struct
{
    pthread_mutex_t mutex;
    int buff[NITEMS];
    int nput;
    int nval;
} shared = {
    PTHREAD_MUTEX_INITIALIZER
};

void *produce(void *);
void *consume(void *);

int main(int argc, char *argv[])
{
    int nthreads;
    int count[NTHREADS];

    pthread_t tid_produce[NTHREADS];
    pthread_t tid_consume;

    if (argc != 3)
    {
        std::cout << "usage: a.out <#items> <#threads>" << std::endl;
        return -1;
    }

    nitems = std::min(atoi(argv[1]), NITEMS);
    nthreads = std::min(atoi(argv[2]), NTHREADS);

    //pthread_setconcurrency(nthreads);
    for (int i = 0; i < nthreads; ++i)
    {
        count[i] = 0;
        int t_errno;
        if ( (t_errno = pthread_create(&tid_produce[i], NULL, produce, &count[i])))
        {
            std::cout << "pthread_create() failed. error: " << strerror(t_errno) <<std::endl;
            return -1;
        }
    }

    for (int i = 0; i < nthreads; ++i)
    {
        pthread_join(tid_produce[i], NULL);
        std::cout << "count[" << i << "] = " << count[i] << std::endl;
    }

    int t_errno;
    if ( (t_errno = pthread_create(&tid_consume, NULL, consume, NULL)))
    {
        std::cout << "pthread_create() failed. error: " << strerror(t_errno) << std::endl;
        return -1;
    }
    pthread_join(tid_consume, NULL);

    return 0;
}

void *produce(void *arg)
{
    for ( ; ; )
    {
        pthread_mutex_lock(&shared.mutex);
        if (shared.nput >= nitems)
        {
            pthread_mutex_unlock(&shared.mutex);
            return NULL;
        }
        shared.buff[shared.nput] = shared.nval;
        shared.nput++;
        shared.nval++;
        pthread_mutex_unlock(&shared.mutex);
        *((int *)arg) += 1;
    }
}

void *consume(void *arg)
{
    for (int i = 0; i < nitems; ++i)
    {
        if (shared.buff[i] != i)
            std::cout << "buff[" << i << "] = " << shared.buff[i] << std::endl;
    }
    return NULL;
}













