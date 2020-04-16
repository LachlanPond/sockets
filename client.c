#ifndef HEADER
#define HEADER
#include "header.h"
#endif

int main(int argc, char *argv[]) {
    // Create a socket
    socket_t client_socket;
    int port = 9002;

    // Handle program input
    if (argc == 1) {
        print_help();
        return 0;
    }
    else if (argc == 2) {
        if (!strcmp(argv[1], "h") || !strcmp(argv[1], "help")) {
            print_help();
            return 0;
        }
        else {
            setup_socket_connection(&client_socket, argv[1], port);
        }
    }

    send_file(&client_socket, "client");

    soc_close(&client_socket);

    return 0;
}