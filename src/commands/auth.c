/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** auth.c
*/

#include "../../include/myftp.h"

int cmd_user(server_t *server, int idx, char *arg)
{
    client_t *client = &server->client_list[idx];

    if (!arg) {
        dprintf(client->socket, "501 Syntax error in arguments.\r\n");
        return 0;
    }
    strncpy(client->username, arg, 255);
    client->username[255] = '\0';
    client->login = 0;
    dprintf(client->socket, "331 User name okay, need password.\r\n");
    return 0;
}

int cmd_pass(server_t *server, int idx, char *arg)
{
    client_t *client = &server->client_list[idx];

    (void)arg;
    if (client->username[0] == '\0') {
        dprintf(client->socket, "503 Bad sequence of commands.\r\n");
        return 0;
    }
    if (strcmp(client->username, "anonymous") == 0) {
        dprintf(client->socket, "230 User logged in, proceed.\r\n");
        client->login = 1;
        return 0;
    } else {
        dprintf(client->socket, "530 Not logged in.\r\n");
        return 0;
    }
}
