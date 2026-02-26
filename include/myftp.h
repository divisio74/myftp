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
    #include <unistd.h>
    #include <sys/stat.h>

    #define BUFSIZE 4096

typedef struct client_s {
    int socket;
    int socket2;
    char commandbuffer[BUFSIZE];
    int buf_start;
    int buf_len;
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
struct sockaddr_in init_sockaddr(int port);
void server_loop(server_t *server);
void accept_client(server_t *server);
void remove_client(server_t *server, int idx);
int handle_client(server_t *server, int idx);
void buf_push(client_t *client, char *data, int len);
int buf_pop_line(client_t *client, char *out, int max);
void extract_line(client_t *client, char *out, int max, int i);
void handle_all(server_t *server);
int check_client(server_t *server, int i);
int bind_server(server_t *server, int port);

#endif
