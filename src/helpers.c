/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** helpers
*/

#include "../include/myftp.h"

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
