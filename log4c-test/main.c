/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include "src/log.h"

int main(int arg0, char** arg1) {
   
	test_log_init();

	LOG_FATAL("LOG_FATAL");
 	LOG_ERROR("LOG_ERROR");
 	LOG_WARN("LOG_WARN"); 
 	LOG_NOTICE("LOG_NOTICE");
 	LOG_INFO("LOG_INFO"); 
 	LOG_DEBUG("LOG_DEBUG"); 
 	LOG_TRACE("LOG_TRACE");
    
    return 0;
}
