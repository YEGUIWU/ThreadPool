#include "thread_pool.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
/* 线程池中的线程，模拟处理业务 */
void* process(void* arg)
{
    printf("thread 0x%x working on task %d\n ", (unsigned int)pthread_self(), *(int*)arg);
    sleep(1);
    printf("task %d is end\n", *(int*)arg);

    return (void*)0;
}
int main(void)
{
    /*thread_pool_t *thread_pool_create(int min_thr_num, int max_thr_num, int queue_max_size);*/
    thread_pool_t* thp = thread_pool_create(3, 100, 100);/*创建线程池，池里最小3个线程，最大100，队列最大100*/
    printf("pool inited");
    int num[20], i;
    for (i = 0; i < 20; i++) 
    {
        num[i] = i;
        printf("add task %d\n", i);
        thread_pool_add(thp, process, (void*)&num[i]);     /* 向线程池中添加任务 */
    }
    sleep(5);                                          /* 等子线程完成任务 */
    thread_pool_destroy(thp);
    
    return 0;
}