/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignalThread.h
 * Author: feng
 *
 * Created on 2017年3月19日, 下午12:38
 */

#ifndef SIGNALTHREAD_H
#define SIGNALTHREAD_H

#include <queue>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "Message.h"
#include "MessageHander.h"
#include "MessageList.h"


using namespace std;

struct MessageData{
    MessageHander* pHander;
    Message*pMessage;
};


class SignalThread {
public:
    SignalThread(){
        pthread_cond_init(&cond, NULL);
        pthread_mutex_init(&mutex, NULL);
    }
    virtual ~SignalThread(){
        pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
    }
    
    void start(){
        pthread_t t;
        
        pthread_mutex_lock(&mutex);
        pthread_create(&t,NULL,run,this);
        
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);
    }
    int postMessage(MessageHander* hander,Message* message = NULL){
        
        MessageData * pessageData = new MessageData();
        pessageData->pHander = hander;
        pessageData->pMessage = message;
        
        m_queue.push_back(pessageData);
    }
    
private:
         void* _start(void * arg){

            while(1){
                
                pthread_mutex_lock(&mutex);
                pthread_cond_signal(&cond);
                pthread_mutex_unlock(&mutex);
                
                //要改成阻塞式的队列
                MessageData* hander = m_queue.wait();;
                if(hander){
                    printf("_start SignalThread OnMessage\n");
                    hander->pHander->OnMessage(hander->pMessage);
                }
            }
            return NULL;
    }
        
        static void *run(void* pths){
            SignalThread* THIS = (SignalThread*)pths;
            return THIS->_start(pths);
        }
        
private:
//    FIFOQueue<MessageData*> m_queue;
    
    MessageList<MessageData*> m_queue;
    
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    
};

#endif /* SIGNALTHREAD_H */

