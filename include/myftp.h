/*
** EPITECH PROJECT, 2026
** FTP
** File description:
** myftp
*/

#ifndef INCLUDED_MYFTP_H
    #define INCLUDED_MYFTP_H

#include <stdio.h>

typedef struct client_s {

} client_t;

typedef struct server_s {
    client_t client_list[1024];
} server_t;

void start_server(int port, char* path);




#endif
