#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    char server_message[256] = "You are a simp!\n";

    // Create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    while(1) {
        int number_of_allowed_connections = 5;
        listen(server_socket, number_of_allowed_connections);
    
        int client_socket;
        client_socket = accept(server_socket, NULL, NULL);

        // Send the message to the client
        send(client_socket, server_message, 256, 0);
    }

    // Close the socket
    close(server_socket);

    return 0;
}