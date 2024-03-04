#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

#define NBUFF 10
#define SEM_MUTEX "/sem_mutex"
#define SEM_NEMPTY "/sem_nempty"
#define SEM_NSTORED "/sem_nstored"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int nitems;

struct
{
    int buff[NBUFF];
    sem_t *mutex;
    sem_t *nempty;
    sem_t *nstored;
} shared;

void *produce(void *);
void *consume(void *);

int main(int argc, char *argv[])
{
    pthread_t tid_produce, tid_consume;

    if (argc != 2)
    {
        std::cout << "usage: prodcons1 <#items>" << std::endl;
        return -1;
    }
    nitems = atoi(argv[1]);

    shared.mutex = sem_open(SEM_MUTEX, O_CREAT, FILE_MODE, 1);
    if (shared.mutex == SEM_FAILED)
    {
        std::cout << "sem_open() failed. Error message: " << strerror(errno) << std::endl;
        return -1;
    }
    shared.nempty = sem_open(SEM_NEMPTY, O_CREAT, FILE_MODE, NBUFF);
    if (shared.nempty == SEM_FAILED)
    {
        std::cout << "sem_open() failed. Error message: " << strerror(errno) << std::endl;
        return -1;
    }
    shared.nstored = sem_open(SEM_NSTORED, O_CREAT, FILE_MODE, 0);
    if (shared.nstored == SEM_FAILED)
    {
        std::cout << "sem_open() failed. Error message: " << strerror(errno) << std::endl;
        return -1;
    }

    int produce_errno = pthread_create(&tid_produce, NULL, produce, NULL);
    if (produce_errno)
    {
        std::cout << "pthread_create() failed. Error message: " << strerror(produce_errno) << std::endl;
        return -1;
    }

    int consume_errno = pthread_create(&tid_consume, NULL, consume, NULL);
    if (consume_errno)
    {
        std::cout << "pthread_create() failed. Error message: " << strerror(consume_errno) << std::endl;
        pthread_cancel(tid_produce);
        pthread_join(tid_produce, NULL);
        return -1;
    }

    pthread_join(tid_produce, NULL);
    pthread_join(tid_consume, NULL);

    sem_close(shared.mutex);
    sem_close(shared.nempty);
    sem_close(shared.nstored);

    sem_unlink(SEM_MUTEX);
    sem_unlink(SEM_NEMPTY);
    sem_unlink(SEM_NSTORED);

    return 0;
}

void *produce(void *arg)
{
    for (int i = 0; i < nitems; ++i)
    {
        sem_wait(shared.nempty);
        sem_wait(shared.mutex);
        shared.buff[i % NBUFF] = i;
        sem_post(shared.mutex);
        sem_post(shared.nstored);
    }
    return NULL;
}

void *consume(void *arg)
{
    for (int i = 0; i < nitems; ++i)
    {
        sem_wait(shared.nstored);
        sem_wait(shared.mutex);
        //if (shared.buff[i % NBUFF] != i)
            std::cout << "buff[" << i % NBUFF << "] = " << shared.buff[i % NBUFF] << std::endl;
        sem_post(shared.mutex);
        sem_post(shared.nempty);
    }
    return NULL;
}
