#ifndef HEADER
#define HEADER
#include "header.h"
#endif

int main() {
    socket_t server_socket;
    int port = 9002;

    soc_set_ip(&server_socket, "0.0.0.0");
    soc_set_port(&server_socket, port);

    // Create the server socket
    server_socket.id = socket(AF_INET, SOCK_STREAM, 0);

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_socket.port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to our specified IP and port
    bind(server_socket.id, (struct sockaddr *) &server_address, sizeof(server_address));

    while(1) {
        int number_of_allowed_connections = 5;
        listen(server_socket.id, number_of_allowed_connections);
    
        socket_t client_socket;
        client_socket.id = accept(server_socket.id, NULL, NULL);

        receive_file(&client_socket);
        // printf("allow\n");
    }

    // Close the socket
    soc_close(&server_socket);

    return 0;
}