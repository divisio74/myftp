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

int cmd_noop(server_t *server, int idx, char *arg)
{
    client_t *client = &server->client_list[idx];

    (void)arg;
    dprintf(client->socket, "200 OK.\r\n");
    return 0;
}

int cmd_dele(server_t *server, int idx, char *arg)
{
    client_t *client = &server->client_list[idx];
    char newpath[BUFSIZE * 2];

    if (verif_arg(arg, client) == 1)
        return 0;
    if (arg[0] == '/')
        snprintf(newpath, BUFSIZE * 2, "%s%s", server->path, arg);
    else
        snprintf(newpath, BUFSIZE * 2, "%s/%s", client->path, arg);
    if (!is_within_root(server->path, newpath)) {
        dprintf(client->socket, "550 Permission denied.\r\n");
        return 0;
    }
    if (unlink(newpath) == -1) {
        dprintf(client->socket, "550 Delete operation failed.\r\n");
        return 0;
    }
    dprintf(client->socket, "250 File deleted.\r\n");
    return 0;
}
