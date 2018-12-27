#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "condition.h"

typedef struct task
{
	void *(*run)(void *arg);
	void *arg;
	struct task *next;

}task_t;

typedef struct threadpool
{
	condition_t ready; //封装的锁和条件变量
	task_t *first;
	task_t *last;	
	int counter;	//当前线程
	int idle;		//最大空闲线程
	int max_threads;//最大允许开创的线程数
	int quit;
}threadpool_t;

void threadpool_init(threadpool_t *td, int threads);
void threadpool_destroy(threadpool_t *td);
void threadpool_add_task(threadpool_t *td, void *(*task)(void *arg), void *arg);
void *thread_routine(void *arg);

#endif
