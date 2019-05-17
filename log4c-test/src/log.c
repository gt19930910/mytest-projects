#include <libgen.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

static log4c_category_t *log_category = NULL;

/*******************************************************************************/
static const char* dated_format(
        const log4c_layout_t *a_layout,
        const log4c_logging_event_t *a_event)
{
    static char buffer[1024];

#ifndef _WIN32
//#ifndef __HP_cc
//#warning gmtime() routine should be defined in sd_xplatform
//#endif
    struct tm tm;
    gmtime_r(&a_event->evt_timestamp.tv_sec, &tm);
    snprintf(buffer, sizeof(buffer), "%04d%02d%02d %02d:%02d:%02d.%06ld %-5s %s\n",
             tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
             (tm.tm_hour + 8) % 24, tm.tm_min, tm.tm_sec,
             a_event->evt_timestamp.tv_usec,
             log4c_priority_to_string(a_event->evt_priority),
             a_event->evt_msg);
#else
    SYSTEMTIME stime;

    if (FileTimeToSystemTime(&a_event->evt_timestamp, &stime)) {
        snprintf(buffer, sizeof(buffer), "%04d%02d%02d %02d:%02d:%02d.%03ld %-6s %s\n",
                 stime.wYear, stime.wMonth , stime.wDay,
                 (stime.wHour + 8) % 24, stime.wMinute, 
                 stime.wSecond, stime.wMilliseconds,
                 log4c_priority_to_string(a_event->evt_priority),
                 a_event->evt_msg);
    }
#endif
    return buffer;
}

/*******************************************************************************/
const log4c_layout_type_t log4c_layout_type_spice = {
    "dated_format",
    dated_format,
};

static int init_dated_format(void)
{
    log4c_layout_type_set(&log4c_layout_type_spice);//自定义格式类型函数指针
    return 0;
}

// ===  FUNCTION  ======================================================================
//  Name:  log_message
//  Description:  记录日志信息
//  @param priority [in]: 日志类别
//  @param file [in]: 文件
//  @param line [in]: 行
//  @param fun [in]: 函数
//  @param fmt [in]: 格式化参数
// =====================================================================================
void log_message(int priority, const char *file, int line, const char *fun, const char *fmt, ...)
{
    const int len_buf = 2048;
    char new_fmt[len_buf];
    va_list ap;
    int n;
    if (log_category == NULL) {
        return;
    }

    n = snprintf(new_fmt, len_buf, "[%s %d %s] ", file, line, fun);
    if (n <= 0) {
        return;
    }

    n += snprintf(new_fmt + n, len_buf - n, "%s", fmt);

    va_start(ap, fmt);
    log4c_category_vlog(log_category, priority, new_fmt, ap);
    va_end(ap);
}

// ===  FUNCTION  ======================================================================
//  Name:  log_fini
//  Description:  清理所有申请的内存，关闭它们打开的文件
// =====================================================================================
int test_log_fini(void)
{
    return log4c_fini();
}

static void set_log4c_envirment(void)
{
    setenv("LOG4C_RCPATH", ".", 0);
}

int test_log_init(void)
{
    set_log4c_envirment();
    init_dated_format();
    if (log4c_init() == 1) {
        return -1;
    }

    log_category = log4c_category_get("file");
    return 0;
}