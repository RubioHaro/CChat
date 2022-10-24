# CChat
Is a system for chatting between two users. It is written in C and uses the sockets for communication.

The system is very simple and is intended for educational purposes.
Created by: (RubioHaro)[http://rubioharo.tech]

## How to use
1. Compile the server and the client
2. Run the server
3. Run the client
4. Type the message and press enter

## How to compile
1. `gcc -o server server.c`
2. `gcc -o client client.c`
 
## How to run
1. `./server`
2. `./client`

## About the system process
### Server 
The server is waiting for a connection from the client. When the client connects, the server sends a message to the client and waits for a message from the client. When the client sends a message, the server sends a message to the client and waits for a message from the client. This process continues until the client sends the message "exit".

The process for the server is: 
1. Create a socket
2. Bind the socket to an address
3. Listen for connections on a socket
4. Accept a connection on a socket
5. Send and receive data
6. Close the socket

### Client
The client connects to the server. When the client connects, the server sends a message to the client and waits for a message from the client. When the client sends a message, the server sends a message to the client and waits for a message from the client. This process continues until the client sends the message "exit".

The process for the client is:
1. Create a socket
2. Connect the socket to the address of the server
3. Send and receive data
4. Close the socket
