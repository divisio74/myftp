/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** server
*/

#include "../include/myftp.h"
#include <sys/socket.h>
#include <arpa/inet.h>

void start_server(int port, char *path)
{
    server_t server;
    struct sockaddr_in addr;
    int opt = 1;

    server = server_init(port, path);
    if (server.isalive == 0)
        return;
    if (setsockopt(server.socket, SOL_SOCKET,
            SO_REUSEADDR, &opt, sizeof(int)) == -1) {
        perror("Setsockopt failling for re-use");
        return;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server.socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("Issue with server binding");
        return;
    }
}

server_t server_init(int port, char *path)
{
    server_t server;
    int sfd;

    memset(&server, 0, sizeof(server_t));
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        server.isalive = 0;
        perror("error when server init");
        return server;
    }
    server.port = port;
    server.socket = sfd;
    strcpy(server.path, path);
    server.isalive = 1;
    return server;
}
