#include "threadPool.h"

void threadpool_init(threadpool_t *td, int threads)
{
	condition_init(&td->ready);
	td->first = NULL;
	td->last  = NULL;
	td->counter = 0;
	td->idle = 0;
	td->max_threads = threads;
	td->quit = 0;
}

void threadpool_destroy(threadpool_t *td)
{
	if (td->quit)
		return;
	condition_lock(&td->ready);
	td->quit = 1;
	if (td->counter > 0)
	{
		if (td->idle > 0)
		{
			condition_broadcast(&td->ready);
		}
		while(td->counter)
		{
			condition_wait(&td->ready);
		}
	}
	condition_unlock(&td->ready);
	condition_destroy(&td->ready);
}

void *thread_routine(void *arg)
{
	struct timespec abstime;
	int timeout;
	printf("thread %d is starting\n", (int)pthread_self());
	threadpool_t *td = (threadpool_t *)arg;
	while(1)
	{
		timeout = 0;
		condition_lock(&td->ready);
		td->idle++;
		while(td->first == NULL && !td->quit)
		{
			printf("thread %d is waiting\n", (int)pthread_self());
			clock_gettime(CLOCK_REALTIME, &abstime);
			abstime.tv_sec += 2;
			int status;
			status = condition_timedwait(&td->ready, &abstime);
			if (status == ETIMEDOUT)
			{
				/*如果等待超过两秒没任务就结束这个线程*/
				timeout = 1;
				break;
			}
		}

		/*此时可用线程减一*/
		td->idle--;
		/*处理任务*/
		if (td->first != NULL)
		{
			task_t *t = td->first;
			td->first = td->first->next;
			condition_unlock(&td->ready);
			t->run(t->arg);
			free(t);
			condition_lock(&td->ready);
		}

		/*如果提示退出并且队列里面没任务，就让所有等待的线程直接退出*/
		if (td->quit && td->first == NULL)
		{
			td->counter--;
			if (td->counter == 0)
				condition_signal(&td->ready);
			condition_unlock(&td->ready);
			break;
		}

		/*如果超时了，就当前线程数减1*/
		if (timeout == 1)
		{
			td->counter--;
			condition_unlock(&td->ready);
			break;
		}
		condition_unlock(&td->ready);
	}

	printf("thread %d is exiting\n", (int)pthread_self());
	return NULL;
}

void threadpool_add_task(threadpool_t *td, void *(*task)(void *arg), void *arg)
{
	task_t *newtask	= (task_t *)malloc(sizeof(task_t));
	newtask->run = task;
	newtask->arg = arg;
	newtask->next = NULL;

	condition_lock(&td->ready);
	/*任务加载*/
	if (td->first == NULL)
	{
		td->first = newtask;
	}else
	{
		td->last->next = newtask; 
	}
	td->last = newtask;
	
	if (td->idle > 0){
		/*如果有空闲就让工作*/
		condition_signal(&td->ready);
	}
	else if (td->counter < td->max_threads)
	{
		/*如果没空闲就创建线程*/
		pthread_t tid;
		pthread_create(&tid, NULL, thread_routine, td);
		td->counter++;
	}
	condition_unlock(&td->ready);
}


















