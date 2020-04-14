#ifndef HEADER
#define HEADER
#include "header.h"
#endif
#include "socketfunc.h"

int main(int argc, char *argv[]) {
    // Create a socket
    socket_t client_socket;

    // Handle program input
    if (argc == 1) {
        print_help();
        return 0;
    }
    else if (argc == 2) {
        if (strcmp(argv[1], "h") || strcmp(argv[1], "help")) {
            print_help();
            return 0;
        }
        else {
            soc_set_ip(&client_socket, argv[1]);
        }
    }

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

    return 0;
}