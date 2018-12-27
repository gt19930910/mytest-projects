#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*采用链表装载任务*/
typedef struct STask
{
	struct STask *pNext;
	int nValue;
}*TASK;

struct SThreadInfo 
{
	int bThreadRunning;
	int nThreadNum;
	int nTaskNum;
	TASK pTask;

	/*这个指针里面存储n个线程句柄(n为线程池大小)*/
	pthread_t *pThreadId;

	pthread_mutex_t hMutex;
	pthread_cond_t hCond;
};

struct SThreadInfo g_sThreadInfo;

/*初始化线程池*/
static void ThreadPoolInit(int nThreadNum);
/*线程池线程的执行函数*/
static void *ThreadPoolRoutine(void *ThreadParam);
/*线程池做链表中的某一个任务*/
static void ThreadPoolDoTask(TASK pTask);
/*取出链表中的头一个任务*/
static TASK ThreadPoolRetrieveTask();
/*销毁线程池*/
static void ThreadPoolDestroy();

static void ThreadPoolInit(int nThreadNum)
{
	/*线程池默认是个线程*/
	if (nThreadNum <= 0)
		nThreadNum = 10;

	pthread_mutex_init(&g_sThreadInfo.hMutex, NULL);
	pthread_cond_init(&g_sThreadInfo.hCond, NULL);

	g_sThreadInfo.nThreadNum = nThreadNum;
	g_sThreadInfo.bThreadRunning = 1;
	g_sThreadInfo.nTaskNum = 0;

	/*给每个handle分配空间*/
	g_sThreadInfo.pThreadId = (pthread_t*)malloc(sizeof(pthread_t*) * nThreadNum);

	/*创建n个线程*/
	for (int i = 0; i < nThreadNum; ++i)
		pthread_create(&g_sThreadInfo.pThreadId[i], NULL, ThreadPoolRoutine, NULL);
}

/*取任务，取链表头*/
static TASK ThreadPoolRetrieveTask()
{
	TASK pHead = g_sThreadInfo.pTask;
	if (pHead)
	{
		g_sThreadInfo.pTask = pHead->pNext;
		--g_sThreadInfo.nTaskNum;
		printf("retrieve a task, task value is [%d]\n", pHead->nValue);
		return pHead;
	}

	printf("no task\n");
	return NULL;
}

static void ThreadPoolDoTask(TASK pTask)
{
	if (!pTask)
		return;

	/*此时可以做任务,睡一秒模拟做任务*/
	sleep(1);

	printf("task value is [%d]\n", pTask->nValue);

	free(pTask);
}

static void ThreadPoolAddTask(TASK pTask)
{
	if (!pTask)
		return;

	pthread_mutex_lock(&g_sThreadInfo.hMutex);

	TASK pHead = g_sThreadInfo.pTask;

	if (!pHead)
	{
		g_sThreadInfo.pTask = pTask;
	} else
	{
		while (pHead->pNext != NULL)
		{
			pHead = pHead->pNext;
		}
		pHead->pNext = pTask;
	}

	++g_sThreadInfo.nTaskNum;

	/*关于先解锁还是先发信号，貌似先发信号的说法多一点，这里采用先发信号*/
	pthread_cond_signal(&g_sThreadInfo.hCond);
	pthread_mutex_unlock(&g_sThreadInfo.hMutex);
}

static void *ThreadPoolRoutine(void *ThreadParam)
{
	printf("thread NO.%d start\n", (int)pthread_self());

	while (g_sThreadInfo.bThreadRunning)
	{
		TASK pCurrentTask = NULL;

		pthread_mutex_lock(&g_sThreadInfo.hMutex);

		while (g_sThreadInfo.nTaskNum <= 0)
		{
			pthread_cond_wait(&g_sThreadInfo.hCond, &g_sThreadInfo.hMutex);

			/*收到signal信号之后，第一个能执行下去的也即抢到锁的，
			 *抢到锁之后其他线程会在此处卡死，本线程执行如果线程
			 *池收到结束信号，本线程会退出拿任务执行，并结束。第
			 *一个拿到锁的本线程nTaskNum肯定是大于0的。解锁之后，
			 *其他线程谁先抢到锁谁就退出，但是貌似会执行空任务。
			 */
			if (!g_sThreadInfo.bThreadRunning)
				break;
		}

		/*本线程第一个抢到锁，正常执行任务解锁，第二个抢到锁的线程
		 *发现nTaskNum是空的，那当然还是在while循环里面，继续wait，
		 *这边就能体现为啥一定要用while而不是if的真正原因了。
		 */
		if (g_sThreadInfo.nTaskNum > 0)
		{
			pCurrentTask = ThreadPoolRetrieveTask();

			pthread_mutex_unlock(&g_sThreadInfo.hMutex);

			ThreadPoolDoTask(pCurrentTask);
		} else
		{
			pthread_mutex_unlock(&g_sThreadInfo.hMutex);
		}
	}

	printf("thread NO.%d exit\n", (int)pthread_self());
}


static void ThreadPoolDestroy()
{
	g_sThreadInfo.bThreadRunning = 0;

	/*这个不需要加锁，因为这个一旦执行，所有的wait都不会等待了，
	 *即使执行的时候不在wait，之后继续wait也不会等待了
	 */
	pthread_cond_broadcast(&g_sThreadInfo.hCond);

	for (int i = 0; i < g_sThreadInfo.nThreadNum; ++i)
		pthread_join(g_sThreadInfo.pThreadId[i], NULL);

	free(g_sThreadInfo.pThreadId);

	pthread_mutex_destroy(&g_sThreadInfo.hMutex);
	pthread_cond_destroy(&g_sThreadInfo.hCond);
}

int main(int argc, char* argv[])
{
	/*初始化线程池*/
	ThreadPoolInit(10);
	
	/*添加任务*/
	TASK pTask = NULL;
	for (int i = 0; i < 100; ++i)
	{
		pTask = (TASK)malloc(sizeof(struct STask));
		pTask->nValue = i + 1;
		pTask->pNext = NULL;
		printf("add task, task value [%d]\n", pTask->nValue);
		ThreadPoolAddTask(pTask);
	}

	/*销毁线程池*/
	ThreadPoolDestroy();

	return 0;
}
