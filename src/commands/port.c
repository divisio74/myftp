/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** transfert
*/

#include "../../include/myftp.h"

int cmd_port_parsing(client_t *client, char *arg)
{
    int h1;
    int h2;
    int h3;
    int h4;
    int p1;
    int p2;

    if (sscanf(arg, "%d,%d,%d,%d,%d,%d", &h1, &h2, &h3, &h4, &p1, &p2) != 6) {
        dprintf(client->socket, "501 Syntax error in arguments.\r\n");
        return 1;
    }
    client->data_ip = htonl((h1 << 24) | (h2 << 16) | (h3 << 8) | h4);
    client->data_port = htons((p1 << 8) | p2);
    return 0;
}

int cmd_port(server_t *server, int idx, char *arg)
{
    client_t *client = &server->client_list[idx];

    if (verif_arg(arg, client) == 1)
        return 0;
    if (cmd_port_parsing(client, arg) == 1)
        return 0;
    client->pasv_mode = 0;
    dprintf(client->socket, "200 PORT command successful.\r\n");
    return 0;
}
