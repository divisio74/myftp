/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** simple
*/

#include "../../include/myftp.h"

int cmd_quit(server_t *server, int idx, char *arg)
{
    client_t *client = &server->client_list[idx];

    (void)arg;
    dprintf(client->socket, "221 Service closing control connection.\r\n");
    remove_client(server, idx);
    return 1;
}

int cmd_help(server_t *server, int idx, char *arg)
{
    client_t *client = &server->client_list[idx];

    (void)arg;
    dprintf(client->socket, "214 USER PASS QUIT HELP NOOP PWD CWD CDUP "
        "PASV PORT LIST RETR STOR DELE\r\n");
    return 0;
}
