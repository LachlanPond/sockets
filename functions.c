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

void setup_socket_connection(socket_t *socket, char *ip, int port) {
    soc_set_ip(socket, ip);
    soc_set_port(socket, port);
    soc_connect(socket);
}

void send_message(socket_t *socket, void *message, int32_t message_size) {
    // Send the size of the message to send so that the server knows how much data to expect
    int32_t *tmp_prep = malloc(4); // Allocate pointer to hold the message length value
    *tmp_prep = message_size;
    soc_send(socket, tmp_prep, sizeof(message_size));
    free(tmp_prep);

    // Wait for the server to send the acknowledgement signal
    int32_t *tmp_ack;
    soc_recv(socket, (void **)&tmp_ack, sizeof(*tmp_ack));
    if (*tmp_ack != ACK_NUMBER) {
        printf("Message send acknowledgement failed: %d\n", *tmp_ack);
    }

    // Send the message to the server
    soc_send(socket, message, message_size);
}

int32_t receive_message(socket_t *socket, void **response) {
    // Receive the size of the message
    int32_t *response_size;
    soc_recv(socket, (void **)&response_size, sizeof(*response_size));

    // Send the acknowledgement signal
    int32_t ack = ACK_NUMBER;
    soc_send(socket, &ack, sizeof(ack));

    // Receive the message
    void *tmp_response;
    soc_recv(socket, &tmp_response, *response_size);
    // printf("Test\n");
    // printf("response: %s", (char *)tmp_response);
    *response = tmp_response;
    return *response_size;
}

void send_file(socket_t *socket, char *filename) {
    char *file_buffer;
    int message_size = read_in_file(filename, &file_buffer);
    if (message_size < 0) {
        return;
    }
    send_message(socket, filename, strlen(filename)+1);
    send_message(socket, file_buffer, message_size);
    free(file_buffer);
    printf("File %s sent\n", filename);
}

void receive_file(socket_t *socket) {
    char *filename;
    receive_message(socket, (void **)&filename);
    char *file_buffer;
    int32_t file_buffer_size = receive_message(socket, (void **)&file_buffer);
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Unable to create/open file %s\n", filename);
        return;
    }
    fwrite(file_buffer, sizeof(*file_buffer), file_buffer_size, file);
    fclose(file);
    free(file_buffer);
}

int read_in_file(char *filename, char **result) {
    int size = 0;
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Unable to open file %s\n", filename);
        return -1;
    }
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    *result = malloc(size+1);
    if (size != fread(*result, sizeof(char), size, file)) {
        free(*result);
        printf("Unable to read file %s\n", filename);
        return -2;
    }
    fclose(file);
    (*result)[size] = 0;
    return size;
}