/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** parsing.c
*/

#include "../../include/myftp.h"

void parse_cmd(char *line, char *cmd, char **arg)
{
    int i = 0;

    while (line[i] != '\0' && line[i] != ' ') {
        cmd[i] = toupper(line[i]);
        i++;
    }
    cmd[i] = '\0';
    if (line[i] == ' ' && line[i + 1] != '\0')
        *arg = line + i + 1;
}

int is_login(client_t *client)
{
    if (!client->login) {
        dprintf(client->socket, "530 Not logged in.\r\n");
        return 0;
    }
    return 1;
}

int unlog_command(server_t *server, int idx, char *cmd, char *arg)
{
    if (strcmp(cmd, "USER") == 0)
        return cmd_user(server, idx, arg);
    if (strcmp(cmd, "PASS") == 0)
        return cmd_pass(server, idx, arg);
    if (strcmp(cmd, "QUIT") == 0)
        return cmd_quit(server, idx, arg);
    if (strcmp(cmd, "HELP") == 0)
        return cmd_help(server, idx, arg);
    return -1;
}

int log_command(server_t *server, int idx, char *cmd, char *arg)
{
    client_t *client = &server->client_list[idx];

    if (strcmp(cmd, "PWD") == 0) {
        if (is_login(client) == 0)
            return 0;
        return cmd_pwd(server, idx, arg);
    }
    if (strcmp(cmd, "CWD") == 0) {
        if (is_login(client) == 0)
            return 0;
        return cmd_cwd(server, idx, arg);
    }
    if (strcmp(cmd, "PASV") == 0) {
        if (is_login(client) == 0)
            return 0;
        return cmd_pasv(server, idx, arg);
    }
    if (strcmp(cmd, "STOR") == 0) {
        if (is_login(client) == 0)
            return 0;
        return cmd_stor(server, idx, arg);
    }
    if (strcmp(cmd, "RETR") == 0) {
        if (is_login(client) == 0)
            return 0;
        return cmd_retr(server, idx, arg);
    }
    if (strcmp(cmd, "PORT") == 0) {
        if (is_login(client) == 0)
            return 0;
        return cmd_port(server, idx, arg);
    }
    if (strcmp(cmd, "NOOP") == 0) {
        if (is_login(client) == 0)
            return 0;
        return cmd_noop(server, idx, arg);
    }
    if (strcmp(cmd, "DELE") == 0) {
        if (is_login(client) == 0)
            return 0;
        return cmd_dele(server, idx, arg);
    }
    if (strcmp(cmd, "LIST") == 0) {
        if (is_login(client) == 0)
            return 0;
        return cmd_list(server, idx, arg);
    }
    if (strcmp(cmd, "CDUP") == 0) {
        if (is_login(client) == 0)
            return 0;
        return cmd_cdup(server, idx, arg);
    }
    return -1;
}

int dispatch_command(server_t *server, int idx, char *line)
{
    client_t *client = &server->client_list[idx];
    char cmd[BUFSIZE] = {0};
    char *arg = NULL;
    int result_unlog = 0;
    int result_log = 0;

    parse_cmd(line, cmd, &arg);
    result_unlog = unlog_command(server, idx, cmd, arg);
    if (result_unlog != -1)
        return result_unlog;
    result_log = log_command(server, idx, cmd, arg);
    if (result_log != -1)
        return result_log;
    dprintf(client->socket, "500 Unknown command.\r\n");
    return 0;
}
