#ifndef PORTNO
#define PORTNO 9999
#endif

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <unistd.h>

int main()
{
    char content[1024] = "";
    char server_message[2048] = "";
    snprintf(content, 1024, "%s", "<!DOCTYPE html><html><head><title>Document</title></head><body>Hello</body></html>");
    snprintf(server_message, 2048, "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/html\r\n\r\n%s\n", content);

    printf("Creating a server socket\n");
    int server_socket = 0;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1)
    {
        printf("Failed to create a socket\n");
        return -1;
    }
    printf("Created a server socket with id %d\n", server_socket);
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORTNO);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("Binding socket\n");
    int connection_status = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if(connection_status != 0)
    {
        printf("Failed to bind socket\n");
        return -1;
    }
    printf("Listening for connections.\n\n");
    listen(server_socket, 10);

    int client_socket = 0;
    while(1)
    {
	    client_socket = accept(server_socket, NULL, NULL);
        printf("We got one!\n");
	    send(client_socket, server_message, sizeof(server_message), 0);
	    close(client_socket);
        printf("Served\n\n");
    }
    close(server_socket);

    return 0;
}