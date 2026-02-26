/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** server
*/

#include "../include/myftp.h"
#include <sys/socket.h>
#include <arpa/inet.h>

int check_client(server_t *server, int i)
{
    if (server->pollfds[i + 1].revents & POLLIN)
        return handle_client(server, i);
    return 0;
}

int bind_server(server_t *server, int port)
{
    struct sockaddr_in addr;
    int opt = 1;

    if (setsockopt(server->socket, SOL_SOCKET,
            SO_REUSEADDR, &opt, sizeof(int)) == -1) {
        perror("Setsockopt failling for re-use");
        return 0;
    }
    addr = init_sockaddr(port);
    if (bind(server->socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("Issue with server binding");
        return 0;
    }
    if (listen(server->socket, 1024) == -1) {
        perror("Issue with server listening");
        return 0;
    }
    return 1;
}
