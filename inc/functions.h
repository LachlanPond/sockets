#ifndef HEADER
#define HEADER
#include "header.h"
#endif

void print_help();
void setup_socket_connection(socket_t *client_socket, char *ip, int port);
void send_message(socket_t *client_socket, void *message, int32_t message_size);
void receive_message(socket_t *client_socket, void **response);