/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** parsing.c
*/

#include "../../include/myftp.h"

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

int exec_log_cmd_advanced(server_t *server, int idx, char *arg, int cmd_idx)
{
    if (cmd_idx == 3)
        return cmd_pasv(server, idx, arg);
    if (cmd_idx == 4)
        return cmd_port(server, idx, arg);
    if (cmd_idx == 6)
        return cmd_retr(server, idx, arg);
    if (cmd_idx == 7)
        return cmd_stor(server, idx, arg);
    if (cmd_idx == 9)
        return cmd_dele(server, idx, arg);
    return -1;
}

int exec_log_cmd(server_t *server, int idx, char *arg, int cmd_idx)
{
    int advanced_cmd;

    if (cmd_idx == 0)
        return cmd_pwd(server, idx, arg);
    if (cmd_idx == 1)
        return cmd_cwd(server, idx, arg);
    if (cmd_idx == 2)
        return cmd_cdup(server, idx, arg);
    if (cmd_idx == 5)
        return cmd_list(server, idx, arg);
    if (cmd_idx == 8)
        return cmd_noop(server, idx, arg);
    advanced_cmd = exec_log_cmd_advanced(server, idx, arg, cmd_idx);
    if (advanced_cmd != -1)
        return advanced_cmd;
    return -1;
}

int log_command(server_t *server, int idx, char *cmd, char *arg)
{
    client_t *client = &server->client_list[idx];
    int cmd_idx = get_log_cmd_idx(cmd);

    if (cmd_idx == -1)
        return -1;
    if (is_login(client) == 0)
        return 0;
    return exec_log_cmd(server, idx, arg, cmd_idx);
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
