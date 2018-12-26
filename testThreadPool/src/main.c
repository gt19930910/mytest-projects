#include "threadpool.h"
#include <unistd.h>
#include <stdlib.h>

void *mytask(void *arg)
{
	printf("thread %d is working on task %d\n", (int)pthread_self(), *(int *)arg);
	//sleep(5);
	free(arg);
	return NULL;
}

int main(void)
{
	threadpool_t pool;
	threadpool_init(&pool, 1);
	int i;
	for (i = 1; i < 10; i++)
	{
		int *arg = malloc(sizeof(int));
		*arg = i;
		threadpool_add_task(&pool, mytask, arg);
		sleep(3);
	}
	
	puts("destroy threadpool");
	threadpool_destroy(&pool);
	return 0;
}
