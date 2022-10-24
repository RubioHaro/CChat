// add missing includes
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "cchat.h"

int main(int argc, char const *argv[])
{

    showMenu();
    return 0;
}

int create_server(int port, char *ip)
{
    // Create socket: Socket() call
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        printf("Error creating socket\n");
        return -1;
    }
    else
    {
        printf("Socket created\n");
    }

    // Bind socket to port: Bind() call
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(ip);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        printf("Error binding socket to port\n");
        return -1;
    }
    else
    {
        printf("Socket bound to %s:%d\n", ip, port);
    }

    while (1)
    {
        // Listen for connections: Listen() call
        if (listen(server_socket, 5) == -1)
        {
            printf("Error listening for connections\n");
            return -1;
        }
        else
        {
            printf("Listening for connections\n");
        }

        // Accept connection: Accept() call
        int client_socket;
        struct sockaddr_in client_address;
        socklen_t client_address_size = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_size);
        if (client_socket == -1)
        {
            printf("Error accepting connection\n");
            return -1;
        }
        else
        {
            printf("Connection accepted from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
        }

        // Send and receive data: Send() and Recv() calls (on a while loop)

        char server_response[BUFFER_SIZE] = "Hello from server";
        send(client_socket, server_response, sizeof(server_response), 0);
        int connection_status = 1;
        while (connection_status ==1)
        {
            // Receive data from the client
            recv(client_socket, &server_response, sizeof(server_response), 0);
            ServerMessageColor();
            printf("Client: %s\n", server_response);
            if (strcmp(server_response, "exit") == 0)
            {
                printf("Client disconnected\n");
                connection_status = 0;
                continue;
            }

            // Send data to the client
            ClientMessageColor();
            printf("Server: ");
            scanf("%s", &server_response);
            send(client_socket, &server_response, sizeof(server_response), 0);
            ResetColor();
            if (strcmp(server_response, "exit") == 0)
            {
                printf("Server disconnected\n");
                connection_status = 0;
                break;
            }
        }
    }

    // char server_message[256] = "You have reached the server";
    // send(client_socket, server_message, sizeof(server_message), 0);
    // char client_message[256];
    // recv(client_socket, &client_message, sizeof(client_message), 0);
    // printf("Client message: %s\n", client_message);

    // Close socket: Close() call
    close(server_socket);
    return 0;
}

void showMenu()
{
    printBanner();
    printf(" 0. Use as default server \n");
    printf(" 1. Use as custom server \n");
    printf(" 2. Exit \n");
    printf("Enter your choice: ");
    int option;
    scanf("%d", &option);
    switch (option)
    {
    case 0:
        // printf("Default server\n");
        defaultServer();
        break;
    case 1:
        // printf("Custom server\n");
        customServer();
        break;
    default:
        printf("Invalid option. Please try again.\n");
        showMenu();
        break;
    }
}

void defaultServer()
{
    printf("Default server\n");
    char *localhost = "127.0.0.1";
    if (create_server(8080, localhost) == -1)
    {
        printf("Error creating server\n");
        return -1;
    }
    else
    {
        printf("Server created\n");
    }
}

void customServer()
{
    printf("Custom server\n");
    char *localhost = "127.0.0.1";

    int port;
    printf("Enter port: ");
    scanf("%d", &port);

    char *ip;
    printf("Enter ip: ");
    scanf("%s", ip);

    if (validateServerSettings(port, ip))
    {
        if (create_server(port, ip) == -1)
        {
            printf("Error creating server\n");
            return -1;
        }
        else
        {
            printf("Server created\n");
        }
    }
    else
    {
        printf("Invalid server settings. Please try again.\n");
        customServer();
    }
}
