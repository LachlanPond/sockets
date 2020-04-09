#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

// #pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server_address;

    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    printf("Done\n");

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
    }
    printf("Socket created\n");

    // Specify an address for the socket
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = inet_addr("13.211.3.157");

    // Connect to the remote server
    if (connect(s, (struct sockaddr *) &server_address, sizeof(server_address)) > 0) {
        puts("connection error");
        return 1;
    }

    puts("Connected to server");

    // Receive data from the server
    char server_response[256];
    recv(s, server_response, sizeof(server_response), 0);

    // Print out the data from the server
    printf("%s\n", server_response);

    return 0;
}