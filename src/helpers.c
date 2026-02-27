/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** helpers
*/

#include "../include/myftp.h"

int verif_arg(char *arg, client_t *client)
{
    if (!arg) {
        dprintf(client->socket, "501 Syntax error in arguments.\r\n");
        return 1;
    }
    return 0;
}

int print_help(int argc, char *argv[])
{
    if (argc == 2) {
        if (strcmp(argv[1], "--help") == 0) {
            printf("USAGE: ./myftp port path\n"
        "port is the port number on which the server socket listens\n"
        "path is the path to the home directory for the Anonymous user");
            return 1;
        }
    }
    return 0;
}

void extract_line(client_t *client, char *out, int max, int i)
{
    int line_len = i < max - 1 ? i : max - 1;
    int j = 0;

    for (j = 0; j < line_len; j++)
        out[j] = client->commandbuffer[(client->buf_start + j) % BUFSIZE];
    out[line_len] = '\0';
    client->buf_start = (client->buf_start + i + 2) % BUFSIZE;
    client->buf_len -= i + 2;
}

int is_within_root(const char *root, const char *path)
{
    size_t len = strlen(root);

    if (strncmp(path, root, len) != 0)
        return 0;
    if (path[len] == '\0')
        return 1;
    if (path[len] == '/')
        return 1;
    return 0;
}
