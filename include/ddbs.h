#ifndef DDBS_H
#define DDBS_H

#include <mysql.h>
#include <cstdio>
#include <cstdlib>

inline const char* mainUser = "xain";
inline const char* mainPasswd = "";

typedef struct DBConfig {
    const char* host;
    const char* user;
    const char* passwd;
    const char* db;
} DBConfig;

int finish_with_error(MYSQL *conn);

MYSQL *initConnection(const DBConfig &dbconfig);

void newStore(const char* host, const char* db);

#endif /* DDBS_H */