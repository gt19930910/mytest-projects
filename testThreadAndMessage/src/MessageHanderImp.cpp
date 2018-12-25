/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MessageHanderImp.cpp
 * Author: feng
 * 
 * Created on 2017年3月19日, 下午1:21
 */

#include "MessageHanderImp.h"
#include "stdio.h"

MessageHanderImp::MessageHanderImp() {
}

MessageHanderImp::MessageHanderImp(const MessageHanderImp& orig) {
}

MessageHanderImp::~MessageHanderImp() {
}

void MessageHanderImp::OnMessage(Message* message){
    
    
    printf("MessageHanderImp::OnMessage\n");
    
 }