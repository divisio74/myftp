/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
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
            
        }

    } else {
        fprintf(stderr, "Usage: ./myftp port path\n");
        return 84;
    }
}