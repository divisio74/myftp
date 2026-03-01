/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** retr.c
*/

#include "../../include/myftp.h"

int retr_checkers(server_t *server, client_t *client, char *newpath)
{
    struct stat st;

    if (strlen(newpath) >= BUFSIZE) {
        dprintf(client->socket, "550 Path too long.\r\n");
        return 0;
    }
    if (stat(newpath, &st) != 0 || !S_ISREG(st.st_mode)) {
        dprintf(client->socket, "550 No such file or directory.\r\n");
        return 0;
    }
    if (!is_within_root(server->path, newpath)) {
        dprintf(client->socket, "550 Permission denied.\r\n");
        return 0;
    }
    return 1;
}

int open_data_connection(client_t *client)
{
    int fd;
    struct sockaddr_in addr;

    if (client->pasv_mode) {
        fd = accept(client->socket2, NULL, NULL);
        close(client->socket2);
        client->socket2 = -1;
        return fd;
    }
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
        return -1;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = client->data_ip;
    addr.sin_port = client->data_port;
    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        close(fd);
        return -1;
    }
    return fd;
}int open_data_connection(client_t *client)
{
    int fd;
    struct sockaddr_in addr;

    if (client->pasv_mode) {
        fd = accept(client->socket2, NULL, NULL);
        close(client->socket2);
        client->socket2 = -1;
        return fd;
    }
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
        return -1;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = client->data_ip;
    addr.sin_port = client->data_port;
    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        close(fd);
        return -1;
    }
    return fd;
}

int open_retr_file(server_t *server, client_t *client, char *arg,
    char *newpath)
{
    if (arg[0] == '/')
        snprintf(newpath, BUFSIZE * 2, "%s%s", server->path, arg);
    else
        snprintf(newpath, BUFSIZE * 2, "%s/%s", client->path, arg);
    if (retr_checkers(server, client, newpath) != 1)
        return -1;
    return open(newpath, O_RDONLY);
}

void transfer_file(int file_fd, int data_fd, client_t *client)
{
    char buffer[BUFSIZE];
    int bytes;

    bytes = read(file_fd, buffer, BUFSIZE);
    while (bytes > 0) {
        write(data_fd, buffer, bytes);
        bytes = read(file_fd, buffer, BUFSIZE);
    }
    close(file_fd);
    close(data_fd);
    dprintf(client->socket, "226 Transfer complete.\r\n");
}

int cmd_retr(server_t *server, int idx, char *arg)
{
    client_t *client = &server->client_list[idx];
    char newpath[BUFSIZE * 2];
    int file_fd;
    int data_fd;

    if (verif_arg(arg, client) == 1)
        return 0;
    file_fd = open_retr_file(server, client, arg, newpath);
    if (file_fd == -1)
        return 0;
    dprintf(client->socket, "150 Opening data connection.\r\n");
    data_fd = open_data_connection(client);
    if (data_fd == -1) {
        close(file_fd);
        dprintf(client->socket, "425 Can't open data connection.\r\n");
        return 0;
    }
    transfer_file(file_fd, data_fd, client);
    return 0;
}
