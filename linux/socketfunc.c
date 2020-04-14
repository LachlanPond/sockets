#include "socketfunc.h"

void soc_set_ip(socket_t *client_socket, char *ip) {
    strcpy(client_socket->ip, ip);
}

void soc_set_port(socket_t *client_socket, int port) {
    client_socket->port = port;
}

void soc_set_msg(socket_t *client_socket, char *msg) {
    client_socket->msg = malloc(strlen(msg) + 1);
    strcpy(client_socket->msg, msg);
}

void soc_connect(socket_t *client_socket) {
    // Create a socket
    client_socket->id = socket(AF_INET, SOCK_STREAM, 0);

    // Specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(client_socket->port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Connect to the server
    int connection_status = connect(client_socket->id, (struct sockaddr *) &server_address, sizeof(server_address));
    
    // Check for error with the connection
    if (connection_status == -1) {
        printf("There was an error making a connection to the remote socket\n");
    }
}

void soc_recv(socket_t *client_socket, char **response) {
    char *tmp = malloc(strlen(client_socket->msg) + 1);
    recv(client_socket->id, tmp, strlen(client_socket->msg) + 1, 0);
    *response = tmp;
}

void soc_close(socket_t *client_socket) {
    close(client_socket->id);
}