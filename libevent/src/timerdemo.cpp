
#include <stdio.h>


#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/util.h>


static void timeout_cb(evutil_socket_t fd, short event, void *arg)
{
    fprintf(stderr,"timeout_cb callback per 2 seconed");
}

int timer_demo(int argc,char** argv){

    fprintf(stderr,"begin test timer demo");

    /* libevent base */
    struct event_base *base;

    /* event */
    struct event timeout;
    struct timeval tv;

    /* Initalize the event library */
    base = event_base_new();

    // EV_PERSIST : always callback
    // EV_ET      : only callback once
    int flags = EV_PERSIST;

    /* Initalize one event */
    event_assign(&timeout, base, -1, flags, timeout_cb, (void*) &timeout);

    evutil_timerclear(&tv);
    tv.tv_sec = 2;
    event_add(&timeout, &tv);

    /* begin event loop */
    event_base_dispatch(base);

    fprintf(stderr,"end test timer demo");

    return 0;
}
