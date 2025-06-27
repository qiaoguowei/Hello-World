#include <iostream>
#include <string>
#include <pthread.h>

using namespace std;

void *thread_cb(void *arg)
{
    std::pair<int, string> *mPair = (std::pair<int, string> *)arg;
    cout << mPair->first << ", " << mPair->second << endl;
    return NULL;
}

int main()
{
    pthread_t tid;
    std::pair<int, string> mPair;
    mPair = make_pair(11, "aaa");
    if (pthread_create(&tid, NULL, thread_cb, (void *)&mPair) != 0)
    {
        perror("pthread_create()");
        return -1;
    }

    pthread_join(tid, NULL);

    return 0;
}
