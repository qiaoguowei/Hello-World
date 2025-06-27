#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <functional>
#include <memory>

class Worker
{
public:
    Worker();
    ~Worker();

    void process();

private:
    std::shared_mutex _mutex;
#define ARRAY_SIZE 100000
    int array_S[ARRAY_SIZE];
};

Worker::Worker()
{
    memset(array_S, 0, sizeof(array_S));
    srand(time(nullptr));
    for (int i = 0; i < ARRAY_SIZE; ++i)
        array_S[i] = rand() % 1000;
}

Worker::~Worker()
{
}

void Worker::process()
{
    for (int tmp_num = 0; tmp_num < 10000; ++tmp_num)
    {
        int i = rand() % (ARRAY_SIZE - 1);
        int j = rand() % (ARRAY_SIZE - 1); //[0, 99999]
        int i_1 = i + 1;
        int i_2 = i + 2;

        if (i_1 >= ARRAY_SIZE)
            i_1 = i_1 % ARRAY_SIZE;

        if (i_2 >= ARRAY_SIZE)
            i_2 = i_2 % ARRAY_SIZE;

        int num_i = 0;  //取值 S[i]
        int num_i1 = 0; //取值 S[i+1]
        int num_i2 = 0; //取值 S[i+2]

        {
            std::shared_lock<std::shared_mutex> m_lock(_mutex); //读锁
            num_i = array_S[i];
            num_i1 = array_S[i_1];
            num_i2 = array_S[i_2];
        } //出了生存的范围读锁自动解锁释放

        {
            std::unique_lock<std::shared_mutex> m_lock(_mutex); //写锁
            array_S[j] = num_i + num_i1 + num_i2;
            std::cout << "array_S[" << j << "] = " << array_S[j] << std::endl;
        }
    }
}

int main(int argc, char *argv[])
{
    Worker m_worker;
    std::vector<std::shared_ptr<std::thread>> threads_vec;

    int M = 3;

    for (int i = 0; i < M; ++i)
    {
        std::shared_ptr<std::thread> t(new std::thread(std::bind(&Worker::process, &m_worker)));
        threads_vec.push_back(t);
    }

    for (int i = 0; i < threads_vec.size(); ++i)
    {
        threads_vec[i]->join();
    }
}











