
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>

#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>


#define SERVER_PORT 8888

bool setSocketNonblock(int fd){
    int opts;
    opts=fcntl(fd,F_GETFL);

    if(opts<0){
        return false;
    }
    opts = opts|O_NONBLOCK;
    if(fcntl(fd,F_SETFL,opts)<0){
        return false;
    }
    return true;
}

struct User {
    /* The clients socket. */
    int fd;

    /* The bufferedevent for this client. */
    struct bufferevent *buf_ev;
};

void buffered_on_error(struct bufferevent *bev, short what, void *ctx){
    struct User *this_client = (struct User *)ctx;
    fprintf(stderr,"buffered_on_error fd:%d",this_client->fd);
}

void buffered_on_read(struct bufferevent *bev, void *arg)
{
    struct User *this_client = (struct User *)arg;
    uint8_t data[8192];
    size_t n;

    /* Read 8k at a time and send it to all connected clients. */
    for (;;) {
        n = bufferevent_read(bev, data, sizeof(data));
        if (n <= 0) {
            /* Done. */
            break;
        }

        fprintf(stderr,"buffered_on_read recv %d size from fd:%d\n",n,this_client->fd);
        /* send data back */
        bufferevent_write(this_client->buf_ev, data,  n);
    }

}
void on_accept(int fd, short ev, void *arg)
{
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    struct User *client;

    client_fd = accept(fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        fprintf(stderr, "accept failed");
        return;
    }
    fprintf(stderr, "on_accept new clent connecting... fd:%d\n",client_fd);

    /* Set the client socket to non-blocking mode. */
    setSocketNonblock(client_fd);

    /* create a client object. */
    client = new User;
    if (client == NULL)
        fprintf(stderr, "malloc failed");

    client->fd = client_fd;
    client->buf_ev = bufferevent_socket_new((struct event_base *)arg, client_fd, 0);

    bufferevent_setcb(client->buf_ev, buffered_on_read, NULL,buffered_on_error, client);

    /* We have to enable it before our callbacks will be called. */
    bufferevent_enable(client->buf_ev, EV_READ);

    fprintf(stderr, "Accepted connection from %s\n",inet_ntoa(client_addr.sin_addr));
}


int tcp_server_demo(int argc, char **argv)
{
    fprintf(stderr, "tcp_server_demo begin\n");

    int listen_fd;
    struct sockaddr_in listen_addr;
    struct event ev_accept;

    /* Initialize libevent. */
    struct event_base * evbase = event_base_new();

    /* Create our listening socket. */
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0)
        fprintf(stderr, "listen failed");

    memset(&listen_addr, 0, sizeof(listen_addr));
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_addr.s_addr = INADDR_ANY;
    listen_addr.sin_port = htons(SERVER_PORT);

    /* bind */
    if (bind(listen_fd, (struct sockaddr *)&listen_addr,sizeof(listen_addr)) < 0)
        fprintf(stderr, "bind failed\n");

    /* listen */
    if (listen(listen_fd, 5) < 0)
         fprintf(stderr, "listen failed\n");

    /* set the socket reuse*/
    int reuseaddr_on = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_on,sizeof(reuseaddr_on));

    /* Set the socket to non-blocking */
    if (!setSocketNonblock(listen_fd))
         fprintf(stderr, "failed to set server socket to non-blocking");

    /* create a read event to be notified when a client connects. */
    event_assign(&ev_accept, evbase, listen_fd, EV_READ|EV_PERSIST,on_accept, evbase);

    event_add(&ev_accept, NULL);

    fprintf(stderr, "tcp server started ,connect to the port:%d\n",SERVER_PORT);
    /* Start the event loop. */
    event_base_dispatch(evbase);

    fprintf(stderr, "tcp_server_demo end\n");

    return 0;
}
