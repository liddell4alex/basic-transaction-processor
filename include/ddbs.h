#ifndef DDBS_H
#define DDBS_H

#include <mysql.h>
#include <cstdio>
#include <cstdlib>

inline const char* mainUser = "ddbs";
inline const char* mainPasswd = "";

typedef struct DBConfig {
    const char* host;
    const char* user;
    const char* passwd;
    const char* db;
} DBConfig;

typedef struct Client {
    char **client;
    char **addr; 
} Client;

void finish_with_error(MYSQL *conn);

MYSQL *initConnection(const DBConfig &dbconfig);

void newStore(const char *host, const char *db, const char* mainStoreHost, const char* mainStoreDB, MYSQL *connAct);

void newClient(Client *c, MYSQL *conn);

void updateClient(Client *c, MYSQL *conn);

Client *getClient(char *rfc, MYSQL *conn);

int newTable(char *q, MYSQL *conn);

void showAllClients(MYSQL *conn);

void searchClient(MYSQL *conn);

#endif /* DDBS_H */