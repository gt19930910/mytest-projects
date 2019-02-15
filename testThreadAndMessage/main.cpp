/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test.cpp
 * Author: feng
 *
 * Created on 2017年3月19日, 下午12:39
 */

#include <cstdlib>



#include "Message.h"
#include "MessageHanderImp.h"
#include "SignalThread.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    printf("----start\n");
    SignalThread signalThread;
    signalThread.start();
    
    printf("----post\n");
    signalThread.postMessage(new MessageHanderImp(),new Message());
    printf("----post end\n");
    
    getchar();
    return 0;
}

