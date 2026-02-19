/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** myftp
*/

#ifndef INCLUDED_MYFTP_H
    #define INCLUDED_MYFTP_H

    #include <poll.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <sys/stat.h>

typedef struct client_s {
    int socket;
    int socket2;
    char commandbuffer[4096];
    char databuffer[4096];
    int login;
    char path[4096];
} client_t;

typedef struct server_s {
    char path[4096];
    int port;
    int nb_client;
    client_t client_list[1024];
    struct pollfd pollfds[1025];
    int socket;
    int isalive;
} server_t;

void start_server(int port, char *path);
int print_help(int argc, char *argv[]);
server_t server_init(int port, char *path);

#endif
