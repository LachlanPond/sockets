#ifndef HEADER
#define HEADER
#include "header.h"
#endif

void soc_set_ip(socket_t *client_socket, char *ip) {
    strcpy(client_socket->ip, ip);
}

void soc_set_port(socket_t *client_socket, int port) {
    client_socket->port = port;
}

void soc_connect(socket_t *client_socket) {
    // Initialise Winsock
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
    }
    
    // Create a socket
    if ((client_socket->id = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    // Specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(client_socket->port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Connect to the server
    if (connect(client_socket->id, (struct sockaddr *) &server_address, sizeof(server_address)) > 0) {
        puts("connection error");
    }
}

void soc_send(socket_t *client_socket, void *message, int message_length) {
    if (send(client_socket->id, message, message_length, 0) < 0) {
        printf("Failed to send message\n");
    }
}

void soc_recv(socket_t *client_socket, void **response, int response_size) {
    void *tmp = malloc(response_size);
    recv(client_socket->id, tmp, response_size, 0);
    *response = tmp;
}

void soc_close(socket_t *client_socket) {
    closesocket(client_socket->id);
}