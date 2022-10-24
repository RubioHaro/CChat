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

showMenu()
{
    printBanner();
   
    int choice;
    printf("1. Create Standard Client\n");
    printf("2. Create Custom Client\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        create_standard_client();
        break;
    case 2:
        create_custom_client();
        break;
    case 3:
        exit(0);
    default:
        printf("Invalid option. Please try again.\n");
        showMenu();
        break;
    }
}

create_standard_client()
{
    int client_socket;
    char *server_ip = "127.0.0.1";
    int port = 8080;
    create_client(port, server_ip);
}

create_custom_client()
{
    int client_socket;
    char *server_ip;
    int port;
    printf("Enter server IP: ");
    scanf("%s", server_ip);
    printf("Enter port: ");
    scanf("%d", &port);

    create_client(port, server_ip);
}

create_client(int port, char *server_ip)
{
    // Create socket: Socket() call
    int client_socket;
    struct sockaddr_in server_address;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        printf("Error creating client socket\n");
        return -1;
    }
    else
    {
        printf("Client socket created\n");
    }

    // Connect to server: Connect() call
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        printf("Error connecting to server\n");
        return -1;
    }
    else
    {
        printf("Connected to server\n");
    }

    // Send and receive data on a while loop
    char server_response[BUFFER_SIZE];
    while (1)
    {
        // Receive data from the server
        recv(client_socket, &server_response, sizeof(server_response), 0);
        ServerMessageColor();
        if(strcmp(server_response, "exit") == 0)
        {
            printf("Server disconnected\n");
            break;
        }
        printf("Server: %s\n", server_response);
        
        // Send data to the server
        ClientMessageColor();
        printf("Client: ");
        scanf("%s", &server_response);
        send(client_socket, server_response, strlen(server_response), 0);
        ResetColor();
        if(strcmp(server_response, "exit") == 0)
        {
            printf("Client disconnected\n");
            break;
        } else if (strcmp(server_response, "clear") == 0)
        {
            system("clear");
        }
    }


    // char server_response[256];
    // recv(client_socket, &server_response, sizeof(server_response), 0);
    // printf("The server sent the data: %s\n", server_response);

    
    // char client_message[256];
    // printf("Enter message to send to server: ");
    // scanf("%s", client_message);
    // send(client_socket, client_message, sizeof(client_message), 0);


    // Close the socket
    close(client_socket);
    return 0;
}

