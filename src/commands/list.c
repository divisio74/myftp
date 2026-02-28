/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** list.c
*/

#include "../../include/myftp.h"

DIR *cmd_list_dir(client_t *client)
{
    DIR *dir;

    dir = opendir(client->path);
    if (!dir) {
        dprintf(client->socket, "550 Failed to open directory.\r\n");
        return NULL;
    }
    return dir;
}

int cmd_list_datafd(client_t *client, DIR *dir)
{
    int data_fd;

    if (dir == NULL)
        return -1;
    dprintf(client->socket, "150 Opening data connection.\r\n");
    data_fd = open_data_connection(client);
    if (data_fd == -1) {
        closedir(dir);
        dprintf(client->socket, "425 Can't open data connection.\r\n");
        return -1;
    }
    return data_fd;
}

int cmd_list(server_t *server, int idx, char *arg)
{
    client_t *client = &server->client_list[idx];
    int data_fd;
    DIR *dir;
    struct dirent *entry;

    (void)arg;
    dir = cmd_list_dir(client);
    data_fd = cmd_list_datafd(client, dir);
    if (data_fd == -1)
        return 0;
    entry = readdir(dir);
    while (entry != NULL) {
        dprintf(data_fd, "%s\r\n", entry->d_name);
        entry = readdir(dir);
    }
    closedir(dir);
    close(data_fd);
    dprintf(client->socket, "226 Transfer complete.\r\n");
    return 0;
}
