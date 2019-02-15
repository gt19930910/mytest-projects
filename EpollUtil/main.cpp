/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>


#include "epoll_socket.h"


class TcpSocketWatcher: public EpollSocketWatcher{
public:
    int on_accept(EpollContext &epoll_context) {
        printf("TcpSocketWatcher on_accept\n" );
    }

    int on_readable(EpollContext &epoll_context, char *read_buffer, int buffer_size, int read_size){
        printf("TcpSocketWatcher on_readable\n" );
    }

    /**
     * return :
     * if return value == 1, we will close the connection
     * if return value == 2, we will continue to write
     */
    int on_writeable(EpollContext &epoll_context){
        printf("TcpSocketWatcher on_writeable\n" );
    }

    int on_close(EpollContext &epoll_context){
        printf("TcpSocketWatcher on_close\n" );
    }
};

// call by epoll thread
void ScheduleHandler(){
    //printf("ScheduleHandler\n");
}

int main(int arg0,char** arg1){
   
   // socket watcher
   TcpSocketWatcher tcpWatcher;


   EpollSocket* epoll = new EpollSocket();

   // set a func to epollsocket
   // will call this func in main thread
   // stop when exit epollsocket
   epoll->set_schedule(ScheduleHandler);

   // set port and watcher to epollsocket 
   // start server
   epoll->start_epoll(8888,tcpWatcher,1000,100000);

   return 0;
}
