/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** parsing.c
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
    if (!arg) {
        dprintf(client->socket, "501 Syntax error in arguments.\r\n");
        return 0;
    }
}