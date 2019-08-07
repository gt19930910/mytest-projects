/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <unistd.h>
#include <malloc.h>


extern "C"{
#include "ijkthreadpool.h"

}


#define LOGD(...) printf(__VA_ARGS__); printf("\n")

struct TaskCtx{
    int id;
};

void run_func(void *arg1, void *arg2){

    TaskCtx *ctx = (TaskCtx*)arg1;

    int n = 5;
    while(n-->0){
        LOGD("run_func:%d,n:%d,thread-id:%lld",ctx->id,n,pthread_self());
        sleep(1);
    }

}


int main(int arg0,char** arg1){
   
    LOGD("main begin");

    // 1. create thread pool
    IjkThreadPoolContext* ctx = ijk_threadpool_create(5,50,0);

    // 2. add task
    int num = 10;
    while(num-->0){

        TaskCtx *tx = (TaskCtx*)calloc(1,sizeof(TaskCtx));
        tx->id = num;
        ijk_threadpool_add(ctx,run_func,(void*)tx,0,0);
    }

    while(1){
        usleep(10000);
    }
    LOGD("main end");

   return 0;
}
