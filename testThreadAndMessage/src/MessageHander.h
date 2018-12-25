/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MessageHander.h
 * Author: feng
 *
 * Created on 2017年3月19日, 下午12:39
 */

#ifndef MESSAGEHANDER_H
#define MESSAGEHANDER_H


#include "Message.h"
class MessageHander {
public:
    MessageHander();
    MessageHander(const MessageHander& orig);
    virtual ~MessageHander();
    
    virtual void OnMessage(Message* message)=0;
    
public:
    MessageHander* pHander;
    Message *pMessage;
private:
    
};

#endif /* MESSAGEHANDER_H */

