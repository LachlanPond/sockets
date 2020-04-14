#ifndef HEADER
#define HEADER
#include "header.h"
#endif
#include "socketfunc.h"

int main() {
    // Create a socket
    socket_t client_socket;

    // Specify an address for the socket
    soc_set_ip(&client_socket, "0.0.0.0");
    soc_set_port(&client_socket, 9002);
    soc_set_msg(&client_socket, "Yyu arw a simp!\n");

    soc_connect(&client_socket);
    char *response;
    soc_recv(&client_socket, &response);
    printf("%s", response);

    soc_set_msg(&client_socket, response);
    soc_close(&client_socket);
    free(response);
    free(client_socket.msg);

    // // Connect to the server
    // int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    
    // // Check for error with the connection
    // if (connection_status == -1) {
    //     printf("There was an error making a connection to the remote socket\n");
    // }

    // // Receive data from the server
    // char server_response[256];
    // recv(network_socket, &server_response, sizeof(server_response), 0);

    // // Print out the data from the server
    // printf("%s", server_response);

    // // Close the socket
    // close(network_socket);

    return 0;
}