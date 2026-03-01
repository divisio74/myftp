/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** pasv.c
*/

#include "../../include/myftp.h"

int cmd_pasv_socket(client_t *client)
{
    int fd;
    struct sockaddr_in addr;

    if (client->socket2 != -1) {
        close(client->socket2);
        client->socket2 = -1;
    }
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        dprintf(client->socket, "425 Can't open data connection.\r\n");
        return -1;
    }
    addr = init_sockaddr(0);
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1
        || listen(fd, 1) == -1) {
        close(fd);
        dprintf(client->socket, "425 Can't open data connection.\r\n");
        return -1;
    }
    return fd;
}

void send_pasv_response(client_t *client, int data_fd)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    unsigned short port;
    unsigned char *ip;

    getsockname(data_fd, (struct sockaddr *)&addr, &len);
    port = ntohs(addr.sin_port);
    getsockname(client->socket, (struct sockaddr *)&addr, &len);
    ip = (unsigned char *)&addr.sin_addr.s_addr;
    dprintf(client->socket, "227 Entering Passive Mode "
        "(%d,%d,%d,%d,%d,%d).\r\n",
        ip[0], ip[1], ip[2], ip[3], port >> 8, port & 0xFF);
}

int cmd_pasv(server_t *server, int idx, char *arg)
{
    client_t *client = &server->client_list[idx];
    int fd;

    (void)arg;
    fd = cmd_pasv_socket(client);
    if (fd == -1)
        return 0;
    client->socket2 = fd;
    client->pasv_mode = 1;
    send_pasv_response(client, fd);
    return 0;
}
