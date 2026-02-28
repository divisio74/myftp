/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** stor.c
*/

#include "../../include/myftp.h"

int stor_checkers(server_t *server, client_t *client, char *newpath)
{
    if (strlen(newpath) >= BUFSIZE) {
        dprintf(client->socket, "550 Path too long.\r\n");
        return 0;
    }
    if (!is_within_root(server->path, newpath)) {
        dprintf(client->socket, "550 Permission denied.\r\n");
        return 0;
    }
    return 1;
}

int open_stor_file(server_t *server, client_t *client, char *arg,
    char *newpath)
{
    if (arg[0] == '/')
        snprintf(newpath, BUFSIZE * 2, "%s%s", server->path, arg);
    else
        snprintf(newpath, BUFSIZE * 2, "%s/%s", client->path, arg);
    if (stor_checkers(server, client, newpath) != 1)
        return -1;
    return open(newpath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void transfer_file_stor(int file_fd, int data_fd, client_t *client)
{
    char buffer[BUFSIZE];
    int bytes;

    bytes = read(data_fd, buffer, BUFSIZE);
    while (bytes > 0) {
        write(file_fd, buffer, bytes);
        bytes = read(data_fd, buffer, BUFSIZE);
    }
    close(file_fd);
    close(data_fd);
    dprintf(client->socket, "226 Transfer complete.\r\n");
}

int cmd_stor(server_t *server, int idx, char *arg)
{
    client_t *client = &server->client_list[idx];
    char newpath[BUFSIZE * 2];
    int file_fd;
    int data_fd;

    if (verif_arg(arg, client) == 1)
        return 0;
    file_fd = open_stor_file(server, client, arg, newpath);
    if (file_fd == -1)
        return 0;
    dprintf(client->socket, "150 Opening data connection.\r\n");
    data_fd = open_data_connection(client);
    if (data_fd == -1) {
        close(file_fd);
        dprintf(client->socket, "425 Can't open data connection.\r\n");
        return 0;
    }
    transfer_file_stor(file_fd, data_fd, client);
    return 0;
}
