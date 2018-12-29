#include "src/threadpool.h"
#include <unistd.h>
#include <stdlib.h>

void *Task(void *arg)
{
	printf("thread %d is working on task %d\n", (unsigned int)pthread_self(), *(int *)arg);
	free(arg);
	return NULL;
}

int main(void)
{
	/*
	 * 线程池完整版，在同级目录下有一个extra threadpool demo use c
	 * 文件夹里面用c语言实现的线程池，里面有详细注释和这个版本类似
	 * 稍微简洁一点
	 */

	/*初始化线程池，10个线程*/
	threadpool_t pool;
	threadpool_init(&pool, 10);
	int i;
	/*给线程池添加十个任务，以函数指针的形式传入*/
	for (i = 1; i < 10; i++)
	{
		int *arg = malloc(sizeof(int));
		*arg = i;
		threadpool_add_task(&pool, Task, arg);
	}
	
	/*销毁线程池*/
	threadpool_destroy(&pool);
	return 0;
}
