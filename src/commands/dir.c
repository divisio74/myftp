/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** dir.c
*/

#include "../../include/myftp.h"

int cwd_checkers(server_t *server, client_t *client, char *newpath)
{
    struct stat st;

    if (strlen(newpath) >= BUFSIZE) {
        dprintf(client->socket, "550 Path too long.\r\n");
        return 0;
    }
    if (stat(newpath, &st) != 0 || !S_ISDIR(st.st_mode)) {
        dprintf(client->socket, "550 No such file or directory.\r\n");
        return 0;
    }
    if (!is_within_root(server->path, newpath)) {
        dprintf(client->socket, "550 Permission denied.\r\n");
        return 0;
    }
    return 1;
}

int cmd_pwd(server_t *server, int idx, char *arg)
{
    client_t *client = &server->client_list[idx];
    char *virtual_path = client->path + strlen(server->path);

    (void)arg;
    if (virtual_path[0] == '\0')
        virtual_path = "/";
    dprintf(client->socket, "257 \"%s\" is current directory.\r\n",
        virtual_path);
    return 0;
}

int cmd_cwd(server_t *server, int idx, char *arg)
{
    client_t *client = &server->client_list[idx];
    int len_np = BUFSIZE * 2;
    char newpath[len_np];
    char resolved[BUFSIZE];

    if (verif_arg(arg, client) == 1)
        return 0;
    if (arg[0] == '/')
        snprintf(newpath, len_np, "%s%s", server->path, arg);
    else
        snprintf(newpath, len_np, "%s/%s", client->path, arg);
    if (cwd_checkers(server, client, newpath) != 1)
        return 0;
    if (realpath(newpath, resolved) == NULL)
        return 0;
    strcpy(client->path, resolved);
    dprintf(client->socket, "250 Directory successfully changed.\r\n");
    return 0;
}

int cmd_cdup(server_t *server, int idx, char *arg)
{
    client_t *client = &server->client_list[idx];
    int len_np = BUFSIZE * 2;
    char newpath[len_np];
    char resolved[BUFSIZE];

    (void)arg;
    snprintf(newpath, len_np, "%s/..", client->path);
    if (cwd_checkers(server, client, newpath) != 1)
        return 0;
    if (realpath(newpath, resolved) == NULL)
        return 0;
    strcpy(client->path, resolved);
    dprintf(client->socket, "200 Directory successfully changed.\r\n");
    return 0;
}
