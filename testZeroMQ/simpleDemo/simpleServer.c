/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//编译方式:gcc server.c -l zmq 

#include <stdio.h>
#include <zmq.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#define MAX_BUFFER_LEN 1024

int main(int arg0, char** arg1)
{
    void *context = zmq_ctx_new();
    void *responder = zmq_socket(context, ZMQ_REP);
    int rc = zmq_bind(responder, "tcp://*:8888");
    assert(rc == 0);

    while (1)
    {
   	   	char buffer[MAX_BUFFER_LEN] = {0};
   		zmq_recv(responder, buffer, 20, 0);
   		printf("%s.\n", buffer);
   		sleep(1);
   		zmq_send(responder, "hello", 5, 0);
   		printf("send hello to client.\n");
    }

    return 0;
}
