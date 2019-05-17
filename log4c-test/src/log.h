#ifndef __VCD_LOG_H__
#define __VCD_LOG_H__
#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>
#include <log4c.h>

void log_message(int priority ,
        const char *file, int line, const char *fun,
        const char *fmt , ...);
int test_log_fini(void);

#define LOG_FATAL(fmt,  args...) log_message(LOG4C_PRIORITY_FATAL, basename(__FILE__), __LINE__ , __FUNCTION__ , fmt, ##args)
#define LOG_ERROR(fmt,  args...) log_message(LOG4C_PRIORITY_ERROR, basename(__FILE__), __LINE__ , __FUNCTION__ , fmt, ##args)
#define LOG_WARN(fmt,   args...) log_message(LOG4C_PRIORITY_WARN,  basename(__FILE__), __LINE__ , __FUNCTION__ , fmt, ##args)
#define LOG_NOTICE(fmt, args...) log_message(LOG4C_PRIORITY_NOTICE,basename(__FILE__), __LINE__, __FUNCTION__ , fmt, ##args)
#define LOG_INFO(fmt,   args...) log_message(LOG4C_PRIORITY_INFO,  basename(__FILE__), __LINE__ , __FUNCTION__ , fmt, ##args)
#define LOG_DEBUG(fmt , args...) log_message(LOG4C_PRIORITY_DEBUG, basename(__FILE__), __LINE__ , __FUNCTION__ , fmt, ##args)
#define LOG_TRACE(fmt,  args...) log_message(LOG4C_PRIORITY_TRACE, basename(__FILE__), __LINE__ , __FUNCTION__ , fmt, ##args)

int test_log_init(void);

#endif