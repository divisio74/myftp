/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** myftp.h
*/

#ifndef INCLUDED_MYFTP_H
    #define INCLUDED_MYFTP_H

    #include <poll.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <ctype.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <dirent.h>
    #include <fcntl.h>

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
    char username[256];
    int pasv_mode;
    unsigned int data_ip;
    unsigned short data_port;
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
int verif_arg(char *arg, client_t *client);
void server_init(server_t *server, int port, char *path);
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
int is_within_root(const char *root, const char *path);
int dispatch_command(server_t *server, int idx, char *line);
int log_command(server_t *server, int idx, char *cmd, char *arg);
int unlog_command(server_t *server, int idx, char *cmd, char *arg);
void parse_cmd(char *line, char *cmd, char **arg);
int is_login(client_t *client);
int cmd_user(server_t *server, int idx, char *arg);
int cmd_pass(server_t *server, int idx, char *arg);
int cmd_cwd(server_t *server, int idx, char *arg);
int cmd_cdup(server_t *server, int idx, char *arg);
int cwd_checkers(server_t *server, client_t *client, char *newpath);
int cmd_pwd(server_t *server, int idx, char *arg);
int cmd_quit(server_t *server, int idx, char *arg);
int cmd_help(server_t *server, int idx, char *arg);
int cmd_pasv(server_t *server, int idx, char *arg);
int cmd_pasv_socket(client_t *client);
void send_pasv_response(client_t *client, int data_fd);
int cmd_port_parsing(client_t *client, char *arg);
int cmd_port(server_t *server, int idx, char *arg);
int retr_checkers(server_t *server, client_t *client, char *newpath);
int open_data_connection(client_t *client);
int open_retr_file(server_t *server, client_t *client, char *arg,
    char *newpath);
void transfer_file(int file_fd, int data_fd, client_t *client);
int cmd_retr(server_t *server, int idx, char *arg);
int stor_checkers(server_t *server, client_t *client, char *newpath);
int open_stor_file(server_t *server, client_t *client, char *arg,
    char *newpath);
void transfer_file_stor(int file_fd, int data_fd, client_t *client);
int cmd_stor(server_t *server, int idx, char *arg);
DIR *cmd_list_dir(client_t *client);
int cmd_list_datafd(client_t *client, DIR *dir);
int cmd_list(server_t *server, int idx, char *arg);
int cmd_dele(server_t *server, int idx, char *arg);
int cmd_noop(server_t *server, int idx, char *arg);
int get_log_cmd_idx(char *cmd);
int exec_log_cmd(server_t *server, int idx, char *arg, int cmd_idx);
int exec_log_cmd_advanced(server_t *server, int idx, char *arg, int cmd_idx);

#endif
