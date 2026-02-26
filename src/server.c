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
    server_t server = server_init(port, path);

    if (server.isalive == 0 || bind_server(&server, port) == 0)
        return;
    server_loop(&server);
}

void handle_all(server_t *server)
{
    for (int i = 0; i < server->nb_client; i++) {
        if (check_client(server, i) == 1)
            i--;
    }
}

void server_loop(server_t *server)
{
    server->pollfds[0].fd = server->socket;
    server->pollfds[0].events = POLLIN;
    while (server->isalive) {
        if (poll(server->pollfds, server->nb_client + 1, -1) == -1)
            break;
        if (server->pollfds[0].revents & POLLIN)
            accept_client(server);
        handle_all(server);
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

struct sockaddr_in init_sockaddr(int port)
{
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    return addr;
}
