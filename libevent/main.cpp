/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>


/***
 *     how to use libevent
 *
 *   1. download libevent 'http://libevent.org/'
 *   2. ./autogen.sh
 *   3. mkdir install-dir
 *   4. ./configure --prefix=/usr/path/install-dir
 *   5. make && make install
 *   6. cp -r include /usr/your/project
 *   7. cp -d libs/*  /usr/your/project
 *
 *   event_base_new();
 *   event_assign();
 *   event_add();
 *   event_base_dispatch();
 ***/


extern int timer_demo(int argc,char** argv);
extern int tcp_server_demo(int argc, char **argv);

int main(int arg0,char** arg1){

    int demo = 2;

    switch(demo){
    case 1:
        timer_demo(arg0,arg1);
        break;
    case 2:
        tcp_server_demo(arg0,arg1);
        break;
    }

    printf("end!!\n");

   return 0;
}
