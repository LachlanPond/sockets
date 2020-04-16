#ifndef HEADER
#define HEADER
#include "header.h"
#endif

void print_help();
void setup_socket_connection(socket_t *client_socket, char *ip, int port);
void send_message(socket_t *client_socket, void *message, int32_t message_size);
int32_t receive_message(socket_t *client_socket, void **response);
void send_file(socket_t *socket, char *filename);
void receive_file(socket_t *socket);
int read_in_file(char *filename, char **result);