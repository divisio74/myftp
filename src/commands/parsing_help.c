/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** parsing_help.c
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

int get_log_cmd_idx(char *cmd)
{
    int i = 0;
    const char *log_cmds[] = {
        "PWD", "CWD", "CDUP", "PASV", "PORT",
        "LIST", "RETR", "STOR", "NOOP", "DELE", NULL
    };

    while (log_cmds[i] != NULL) {
        if (strcmp(cmd, log_cmds[i]) == 0)
            return i;
        i++;
    }
    return -1;
}
