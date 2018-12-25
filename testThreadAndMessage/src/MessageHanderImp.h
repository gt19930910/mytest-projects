/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MessageHanderImp.h
 * Author: feng
 *
 * Created on 2017年3月19日, 下午1:21
 */

#ifndef MESSAGEHANDERIMP_H
#define MESSAGEHANDERIMP_H

#include "MessageHander.h"
#include "Message.h"

class MessageHanderImp : public MessageHander{
public:
    MessageHanderImp();
    MessageHanderImp(const MessageHanderImp& orig);
    virtual ~MessageHanderImp();
    
      virtual void OnMessage(Message* message);
    
private:

};

#endif /* MESSAGEHANDERIMP_H */

