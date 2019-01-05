/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <zmq.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUFFER_LEN 1024

int main(int arg0, char** arg1)
{
    void *context = zmq_ctx_new();
    void *requester = zmq_socket(context, ZMQ_REQ);
    if (0 != zmq_connect(requester, "tcp://localhost:8888"))
    {
    	perror("cannot connect to server.");
	}
  	
  	char buffer[MAX_BUFFER_LEN] = {0};
  	printf("send hello to server.\n");
  	zmq_send(requester, "hello", 5, 0);
  	zmq_recv(requester, buffer, 20, 0);
  	printf("received %s.\n", buffer);

  	zmq_close(requester);
  	zmq_ctx_destroy(context);

   return 0;
}
