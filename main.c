/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "include/myftp.h"

int main(int argc, char* argv[])
{
    struct stat filestat;


    if (argc == 2) {
        if (strcmp(argv[1],"--help") == 0) {
            printf("USAGE: ./myftp port path\n"
                        "port is the port number on which the server socket listens\n"
                        "path is the path to the home directory for the Anonymous user");
            return 0;
        } else {
            fprintf(stderr, "For help: --help");
            return 84;
        }
    } else if (argc == 3) {
        if (atoi(argv[1]) > 65535 || atoi(argv[1]) < 1) {
            fprintf(stderr, "Wrong port");
            return 84;
        } else if (stat(argv[2], &filestat) == -1 || !S_ISDIR(filestat.st_mode)) {
            fprintf(stderr, "Wrong Directory");
            return 84;
        } else {
            start_server(atoi(argv[1]), argv[2]);
        }

    } else {
        fprintf(stderr, "Usage: ./myftp port path\n");
        return 84;
    }
}