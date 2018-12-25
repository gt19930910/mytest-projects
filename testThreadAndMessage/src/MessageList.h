/*
 * MessageList.h
 *
 *  Created on: 2016-4-14
 *      Author: wgt
 */

#ifndef MESSAGELIST_H_
#define MESSAGELIST_H_

#include <list>
#include <pthread.h>
#include <assert.h>
using namespace std;

template<typename DATA> class MessageList
{
	private:
		typedef DATA value_type;
		pthread_mutex_t mutex;

		pthread_cond_t cond;

	public:
		list<DATA> m_msglist;
		//构造函数
		MessageList()
		{
			pthread_mutex_init(&mutex, NULL);
			pthread_cond_init(&cond, NULL);
			m_msglist.clear();
		}
		//析构函数
		~MessageList()
		{
			pthread_mutex_destroy(&mutex);
			pthread_cond_destroy(&cond);
		}

		//封装线程互斥锁加锁
		void lock(void)
		{
			pthread_mutex_lock(&mutex);
		}
		//封装线程互斥锁解锁
		void unlock(void)
		{
			pthread_mutex_unlock(&mutex);
		}

		value_type &operator [](const int k)
		{

			lock();
			int size = m_msglist.size();
			unlock();

			assert(k < size && k > 0);

			int index = 0;
			for(typename list<value_type>::iterator type_tmp = m_msglist.begin(); type_tmp != m_msglist.end(); type_tmp++) {
				if(index == k) {
					return *type_tmp;
				}
				index++;
			}
			return *m_msglist.end();
		}

		//从链表末端插入数据
		bool push_back(value_type msg_data)
		{
			lock();
			m_msglist.push_back(msg_data);
			pthread_cond_signal(&cond);
			unlock();
			return true;
		}
		//从链表开始位置插入数据
		bool push_front(value_type msg_data)
		{
			lock();
			m_msglist.push_front(msg_data);
			pthread_cond_signal(&cond);
			unlock();
			return true;
		}

		//从链表开始位置删除数据
		bool pop_front(void)
		{
			if (m_msglist.empty())
			{
				return false;
			}
			lock();
			m_msglist.pop_front();
			unlock();
			return true;
		}
		//从链表末端删除数据
		bool pop_back(void)
		{
			if (m_msglist.empty())
			{
				return false;
			}
			lock();
			m_msglist.pop_back();
			unlock();
			return true;
		}

		value_type front(void)
		{
			lock();
			value_type tmp = m_msglist.front();
			unlock();
			return tmp;
		}

		value_type back(void)
		{
			lock();
			value_type tmp = m_msglist.back();
			unlock();
			return tmp;
		}

		//获取数据并pop第一个
		value_type front_pop(void)
		{
			lock();
			if (m_msglist.empty())
			{
				return NULL;
			}
			value_type tmp = m_msglist.front();
			m_msglist.pop_front();
			unlock();
			return tmp;
		}

		value_type wait()
		{
//			struct timespec times;
//			times.tv_sec = 0;
//			times.tv_nsec = 3000;
			lock();
			while (m_msglist.empty())
			{

//				pthread_cond_timedwait(&cond, &mutex, &times);
//				LOGE("wait ~~~~~~~~~~~~~~~1");
				pthread_cond_wait(&cond, &mutex);
			}
//			LOGE("wait ~~~~~~~~~~~~~~~2");
			value_type tmp = m_msglist.front();
			m_msglist.pop_front();
			unlock();
			return tmp;
		}

		void signal(value_type endSignal)
		{
			lock();
			m_msglist.push_front(endSignal);
			pthread_cond_signal(&cond);
			unlock();
		}

		//判断链表是否为空
		bool empty(void)
		{
			return m_msglist.empty();
		}
		//获取链表数据大小
		int size(void)
		{
			lock();
			int tmp = m_msglist.size();
			unlock();
			return tmp;
		}
		//清除链表数据
		bool clear(void)
		{
			lock();
			m_msglist.clear();
			unlock();
			return true;
		}

		void cleanAll()
		{
			lock();
			if (!m_msglist.empty())
			{
				typename list<DATA>::iterator i;
				for (i = m_msglist.begin(); i != m_msglist.end(); i++)
				{
					if (*i)
					{
						delete (*i);
					}
				}
			}
			m_msglist.clear();
			unlock();
		}
};

#endif /* MESSAGELIST_H_ */
