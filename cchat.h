// add missing includes
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

# define BUFFER_SIZE 1024


void printBanner()
{
    printf("\033[33m.........................\n");
    printf("...................___...\n");
    printf("..../  `/  `|__| /\\ |....\n");
    printf("....\\__,\\__,|  |/~~\\|....\n");
    printf(".........................\n");
    printf(".........................\n");
}

int validateServerSettings(int port, char *ip)
{
    if (port < 0 || port > 65535)
    {
        printf("Invalid port. Please try again.\n");
        return -1;
    }
    else
    {
        printf("Valid Port: %d\n", port);
    }

    if (inet_addr(ip) == -1)
    {
        printf("Invalid ip. Please try again.\n");
        return -1;
    }
    else
    {
        printf("Valid ip\n");
    }
}

int checkPortAvailability(int port)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        return -1;
    }
    else
    {
        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(port);
        if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        {
            return -1;
        }
        else
        {
            if (listen(server_fd, 5) < 0)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }
    }

    // closing the socket
    closeSocket(server_fd);
}

void closeSocket(int socket_fd)
{
    int tru = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &tru, sizeof(int));
}

void ServerMessageColor(){
    printf("\033[0;32m");
}

void ClientMessageColor(){
    printf("\033[0;34m");
}

void ResetColor(){
    printf("\033[0m");
}