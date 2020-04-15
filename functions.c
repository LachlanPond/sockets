#ifndef HEADER
#define HEADER
#include "header.h"
#endif

void print_help() {
    char *infoString = "Simple socket experimentation project\n"
                        "github.com/LachlanPond/sockets\n\n"
                        "Usage: client ip";
    puts(infoString);
}

void setup_socket_connection(socket_t *client_socket, char *ip, int port) {
    soc_set_ip(client_socket, ip);
    soc_set_port(client_socket, port);
    soc_connect(client_socket);
}

void send_message(socket_t *client_socket, void *message, int32_t message_size) {
    // Send the size of the message to send so that the server knows how much data to expect
    int32_t *tmp_prep = malloc(4); // Allocate pointer to hold the message length value
    *tmp_prep = message_size;
    soc_send(client_socket, tmp_prep, sizeof(message_size));
    free(tmp_prep);

    // Wait for the server to send the acknowledgement signal
    int32_t *tmp_ack;
    soc_recv(client_socket, (void **)&tmp_ack, sizeof(*tmp_ack));
    if (*tmp_ack != ACK_NUMBER) {
        printf("Message send acknowledgement failed: %d\n", *tmp_ack);
    }

    // Send the message to the server
    soc_send(client_socket, message, message_size);
}

void receive_message(socket_t *client_socket, void **response) {
    // Receive the size of the message
    int32_t *response_size;
    soc_recv(client_socket, (void **)&response_size, sizeof(*response_size));

    // Send the acknowledgement signal
    int32_t ack = ACK_NUMBER;
    soc_send(client_socket, &ack, sizeof(ack));

    // Receive the message
    void *tmp_response;
    soc_recv(client_socket, &tmp_response, *response_size);
    // printf("Test\n");
    // printf("response: %s", (char *)tmp_response);
    *response = tmp_response;
}