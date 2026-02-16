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
