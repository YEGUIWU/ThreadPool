#ifndef __THREAD_POOL_H_
#define __THREAD_POOL_H_

typedef struct thread_pool_t thread_pool_t;

/**
 ** @function thread_pool_create
 ** @describe create a thread_pool_t object
 ** @param_1 min_th_num
 ** @param_2 max_th_num
 ** @param_3 queue_max_size
 ** @return thread_pool_t*
 **/
thread_pool_t* thread_pool_create(int min_th_num, int max_th_num, int queue_max_size);

/**
 ** @function threadpool_add
 ** @desc add a new task in the queue of a thread pool
 ** @param pool     Thread pool to which add the task.
 ** @param function Pointer to the function that will perform the task.
 ** @param argument Argument to be passed to the function.
 ** @return 0 if all goes well,else -1
 **/
int thread_pool_add(thread_pool_t* pool, void* (*func)(void* arg), void* arg);

/**
 ** @function threadpool_destroy
 ** @desc Stops and destroys a thread pool.
 ** @param pool  Thread pool to destroy.
 ** @return 0 if destory success else -1
 *      */
int thread_pool_destroy(thread_pool_t* pool);

/**
 ** @desc get the thread num
 ** @pool pool threadpool
 ** @return # of the thread
 **/
int thread_pool_all_threadnum(thread_pool_t* pool);

/**
 ** desc get the busy thread num
 ** @param pool threadpool
 ** return # of the busy thread
 **/
int thread_pool_busy_threadnum(thread_pool_t* pool);

#endif// __THREAD_POOL_H_
