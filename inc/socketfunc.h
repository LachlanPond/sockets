#ifndef HEADER
#define HEADER
#include "header.h"
#endif

typedef struct {
    int id;
    char ip[30];
    int port;
} socket_t;

void soc_set_ip(socket_t *client_socket, char *ip);
void soc_set_port(socket_t *client_socket, int port);
void soc_set_msg(socket_t *client_socket, char *msg);
void soc_connect(socket_t *client_socket);
void soc_send(socket_t *client_socket, void *message, int message_length);
void soc_recv(socket_t *client_socket, void **response, int response_size);
void soc_close(socket_t *client_socket);