#include "ddbs.h"

void finish_with_error(MYSQL *conn) {
    fprintf(stdout, "\n");
    fprintf(stderr, "Error: %s\n", mysql_error(conn));
    mysql_close(conn);
    
    fprintf(stdout, "Presiona enter para volver...");
    int ch; while ((ch = getchar()) != '\n' && ch != EOF);
    getchar();
}

MYSQL *initConnection(const DBConfig &dbconfig) {
    // Instance and Init connection
    MYSQL *conn;
    
    if(!(conn = mysql_init(0))) {
        finish_with_error(conn);
        return NULL;
    }

    // Connect to database
    if(!mysql_real_connect(
        conn,               // Connection
        dbconfig.host,      // Host
        dbconfig.user,      // User
        dbconfig.passwd,    // Password
        dbconfig.db,        // Database
        3306,               // Port
        NULL,               // Path to socket file
        0                   // Additional options
    )) {
        finish_with_error(conn);
        return NULL;
    }

    return conn;
}