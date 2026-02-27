/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** client
*/

#include "../include/myftp.h"
#include <sys/socket.h>

void buf_push(client_t *client, char *data, int len)
{
    int pos;
    int i = 0;

    for (i = 0; i < len && client->buf_len < BUFSIZE; i++) {
        pos = (client->buf_start + client->buf_len) % BUFSIZE;
        client->commandbuffer[pos] = data[i];
        client->buf_len++;
    }
}

int buf_pop_line(client_t *client, char *out, int max)
{
    int pos = 0;
    int next = 0;
    int i = 0;

    for (i = 0; i < client->buf_len - 1; i++) {
        pos = (client->buf_start + i) % BUFSIZE;
        next = (client->buf_start + i + 1) % BUFSIZE;
        if (client->commandbuffer[pos] == '\r'
                && client->commandbuffer[next] == '\n') {
            extract_line(client, out, max, i);
            return 1;
        }
    }
    return 0;
}

void accept_client(server_t *server)
{
    int fd;

    if (server->nb_client >= 1024)
        return;
    fd = accept(server->socket, NULL, NULL);
    if (fd == -1)
        return;
    memset(&server->client_list[server->nb_client], 0, sizeof(client_t));
    server->client_list[server->nb_client].socket = fd;
    strcpy(server->client_list[server->nb_client].path, server->path);
    server->nb_client++;
    server->pollfds[server->nb_client].fd = fd;
    server->pollfds[server->nb_client].events = POLLIN;
    dprintf(fd, "220 Service ready.\r\n");
}

void remove_client(server_t *server, int idx)
{
    close(server->client_list[idx].socket);
    server->nb_client--;
    server->client_list[idx] = server->client_list[server->nb_client];
    server->pollfds[idx + 1] = server->pollfds[server->nb_client + 1];
}

int handle_client(server_t *server, int idx)
{
    client_t *client = &server->client_list[idx];
    char tmpbuffer[BUFSIZE];
    char line[BUFSIZE];
    int bytes;

    bytes = read(client->socket, tmpbuffer, BUFSIZE - 1);
    if (bytes <= 0) {
        remove_client(server, idx);
        return 1;
    }
    buf_push(client, tmpbuffer, bytes);
    while (buf_pop_line(client, line, BUFSIZE)) {
        if (dispatch_command(server, idx, line) == 1)
            return 1;
    }
    return 0;
}
