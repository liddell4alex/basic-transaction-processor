#include "ddbs.h"
#include <iostream>
#include <cstring>

char **copyRow(MYSQL_ROW row, int fields) {
    char **copy = new char*[fields];

    for(int i = 0; i < fields; i++) {
        copy[i] = new char[strlen(row[i] + 1)];
        strcpy(copy[i], row[i]);
    }

    return copy;
}

void newStore(const char *host, const char *db, const char* mainStoreHost, const char* mainStoreDB, MYSQL *connAct) {
    char query[1000];
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    // Checando si ya se inicializó la base de datos en la tienda actual
    snprintf(query, sizeof(query), "SELECT SCHEMA_NAME FROM information_schema.SCHEMATA WHERE SCHEMA_NAME = '%s'", db);

    if(mysql_query(connAct, query) != 0) {
        finish_with_error(connAct);
        return;
    } else {
        result = mysql_store_result(connAct);
    }
    
    if(mysql_num_rows(result) == 0) { 
        fprintf(stdout, "No existe la base de datos de la tienda %s\n", db); getchar();
        mysql_close(connAct);
        mysql_free_result(result);
        return;
    }
 
    // Conect main store
    DBConfig main_store;
    main_store.host   = mainStoreHost;
    main_store.user   = mainUser;
    main_store.passwd = mainPasswd;
    main_store.db     = mainStoreDB;
    MYSQL *connAux = initConnection(main_store);

    // Si ya existe la sucursal retorna
    snprintf(query, sizeof(query), "SELECT * FROM store WHERE db_name = '%s'", db);

    if(mysql_query(connAux, query) != 0) {
        finish_with_error(connAux);
        return;
    } else {
        result = mysql_store_result(connAux);
    }
    
    if(mysql_num_rows(result) > 0) {
        mysql_close(connAux);
        mysql_free_result(result);
        
        fprintf(stdout, "\nYa existe la tienda %s\n", db); 
        fprintf(stdout, "Presiona enter para volver...");
        
        int ch; while ((ch = getchar()) != '\n' && ch != EOF);
        getchar();
        return;
    }


    // Add new store to main store
    snprintf(query, sizeof(query), "INSERT INTO store(host, db_name)    \
                                    VALUES ('%s','%s')", host, db);
     
    if(mysql_query(connAux, query) != 0) {
        finish_with_error(connAux);
        return;
    }
   

    // Recolecting conection configs from the main store
    if(mysql_query(connAux, "SELECT * FROM store;") != 0) {
        finish_with_error(connAux);
        return;
    } else {
        result = mysql_store_result(connAux);
        mysql_close(connAux);
    }



    // Conectandome y agregando la sucursal actual
    int numStores = mysql_num_rows(result);
    for(int i = 0; i < numStores; i++) {
        // Store actual
        mysql_data_seek(result, i);
        row = mysql_fetch_row(result);

        DBConfig store;
        store.host   = row[1];
        store.user   = mainUser;
        store.passwd = mainPasswd;
        store.db     = row[2];
        connAux = initConnection(store);

        if(connAux == NULL) {
            continue;
        }

        // Itero sobre cada tienda agregando todas las demas existentes
        mysql_data_seek(result, 0);
        while((row = mysql_fetch_row(result))) {
            snprintf(query, sizeof(query), "INSERT IGNORE INTO store(host, db_name) \
                                    VALUES ('%s','%s')", row[1], row[2]);
    
            if(mysql_query(connAux, query) != 0) {
                continue;
            }

        }

        mysql_close(connAux);
    }
 
    mysql_free_result(result);

    fprintf(stdout, "\nNueva tienda %s creada correctamente\n", db);
    fprintf(stdout, "Presiona enter para volver...");
    
    int ch; while ((ch = getchar()) != '\n' && ch != EOF);
    getchar();
}

void newClient(Client *c, MYSQL *conn) {
    char query[1000]; 

    snprintf(query, sizeof(query), "INSERT INTO client(name, flname, mlname, rfc) \
                                    VALUES ('%s','%s','%s','%s')",
            c->client[0], c->client[1], c->client[2], c->client[3]);
   
    if(mysql_query(conn, query) != 0) {
        finish_with_error(conn);
        return;
    }
    
    snprintf(query, sizeof(query), "INSERT INTO address(street, house_num, state, postal_code, client) \
                                    VALUES ('%s','%s','%s','%s','%s')",
            c->addr[0], c->addr[1], c->addr[2], c->addr[3], c->client[3]);
    
    if(mysql_query(conn, query) != 0) {
        finish_with_error(conn);
        return;
    }
  
    fprintf(stdout, "\nCliente %s %s %s agregado correctamente\n", c->client[0], c->client[1], c->client[2]);
    fprintf(stdout, "Presiona enter para volver...");
    
    int ch; while ((ch = getchar()) != '\n' && ch != EOF);
    getchar();
}

void updateClient(Client *c, MYSQL *conn) {
    char query[1000];

    snprintf(query, sizeof(query), "UPDATE client       \
                                    SET name = '%s',    \
                                        flname = '%s',  \
                                        mlname = '%s'   \
                                    WHERE rfc = '%s'",  \
            c->client[1], c->client[2], c->client[3], c->client[4]);
    
    if(mysql_query(conn, query) != 0) {
        finish_with_error(conn);
        return;
    }    
    
    snprintf(query, sizeof(query), "UPDATE address          \
                                    SET street = '%s',      \
                                        house_num = '%s',   \
                                        state = '%s',       \
                                        postal_code = '%s'  \
                                    WHERE client = '%s'",   \
            c->addr[1], c->addr[2], c->addr[3], c->addr[4], c->client[4]);
    
    if(mysql_query(conn, query) != 0) {
        finish_with_error(conn);
        return;
    }    
    
    fprintf(stdout, "\nCliente %s %s %s actualizado correctamente\n", c->client[1], c->client[2], c->client[3]);
    fprintf(stdout, "Presiona enter para volver...");
    
    int ch; while ((ch = getchar()) != '\n' && ch != EOF);
    getchar();
}

Client *getClient(char *rfc, MYSQL *conn) {
    char query[1000];

    MYSQL_RES *resultClient;
    MYSQL_ROW rowClient;
    MYSQL_RES *resultAddr;
    MYSQL_ROW rowAddr;

    Client *c = new Client;

    snprintf(query, sizeof(query), "SELECT * FROM client WHERE rfc = '%s'", rfc);
     
    if(mysql_query(conn, query) != 0) {
        finish_with_error(conn);
        return NULL;
    } 
    resultClient = mysql_store_result(conn);
    
    snprintf(query, sizeof(query), "SELECT * FROM address WHERE client = '%s'", rfc);
    
    if(mysql_query(conn, query) != 0) {
        finish_with_error(conn);
        return NULL;
    } 
    resultAddr = mysql_store_result(conn);
    
    if(mysql_num_rows(resultClient) > 0 && mysql_num_rows(resultAddr) > 0) {
        rowClient = mysql_fetch_row(resultClient);
        rowAddr = mysql_fetch_row(resultAddr); 
    } else {
        fprintf(stdout, "\nEl cliente no existe...\n");
        fprintf(stdout, "Presiona enter para volver...");
    
        int ch; while ((ch = getchar()) != '\n' && ch != EOF);
        getchar();
        return NULL;
    }

    c->client = copyRow(rowClient, 5);
    c->addr = copyRow(rowAddr, 6);

    mysql_free_result(resultClient);
    mysql_free_result(resultAddr);

    return c;
}

int newTable(char *q, MYSQL *conn) {
    char query[1000];
    MYSQL_RES *result;
    MYSQL_ROW row;
    DBConfig store;
    
    snprintf(query, sizeof(query), "SELECT * FROM store");
    
    if(mysql_query(conn, query) != 0) {
        finish_with_error(conn);
        return 1;
    }
    
    result = mysql_store_result(conn);

    while((row = mysql_fetch_row(result))) {
        store.host   = row[1];
        store.user   = mainUser;
        store.passwd = mainPasswd;
        store.db     = row[2];
        conn = initConnection(store);
        
        if(mysql_query(conn, q) != 0) {
            fprintf(stderr, "Error: %s\n", mysql_error(conn));
            mysql_free_result(result);
            mysql_close(conn);

            return 1;
        } 

        mysql_close(conn);
    }

    return 0;
}

void showAllClients(MYSQL *conn) {
    char query[1000];
    Client *c; 
    MYSQL_RES *resultStores;
    MYSQL_ROW rowStores;
    MYSQL_RES *resultClient;
    MYSQL_ROW rowClient;
    DBConfig store;
 
    snprintf(query, sizeof(query), "SELECT * FROM store");
    
    if(mysql_query(conn, query) != 0) {
        finish_with_error(conn);
        return;
    }
    
    resultStores = mysql_store_result(conn);
    
    while((rowStores = mysql_fetch_row(resultStores))) {
        store.host   = rowStores[1];
        store.user   = mainUser;
        store.passwd = mainPasswd;
        store.db     = rowStores[2];
        conn = initConnection(store);
    
        snprintf(query, sizeof(query), "SELECT * FROM client");
    
        if(mysql_query(conn, query) != 0) {
            finish_with_error(conn);
            mysql_free_result(resultStores);
            return;
        }
        
        resultClient = mysql_store_result(conn);
             
        fprintf(stdout, "\n---- TIENDA: %s ----\n", rowStores[2]);
        while((rowClient = mysql_fetch_row(resultClient))) {

            c = getClient(rowClient[4], conn);
            
            fprintf(stdout, "----------------------------\n"); 
            fprintf(stdout, "INFO: %s, %s, %s, %s\n", c->client[1], c->client[2], c->client[3], c->client[4]); 
            fprintf(stdout, "DIR.: %s, %s, %s, %s\n", c->addr[1], c->addr[2], c->addr[3], c->addr[4]); 
            fprintf(stdout, "----------------------------\n\n"); 
    
            for(int i = 0; i < 5; i++) { 
                delete[] c->client[i];
            }
            for(int i = 0; i < 6; i++) { 
                delete[] c->addr[i];
            }
            delete[] c->client;
            delete[] c->addr; 
            delete c;
        } 
    
        mysql_free_result(resultClient);
        mysql_close(conn);
    }

    mysql_free_result(resultStores);
            
    fprintf(stdout, "\nPresiona enter para volver..."); 
    int ch; while ((ch = getchar()) != '\n' && ch != EOF);
    getchar();
}

void searchClient(MYSQL *conn) {
    char query[1000];
    char name[200] = "";
    char rfc[13] = "";

    Client *c;
    
    MYSQL_RES *resultStores;
    MYSQL_ROW rowStores;
    MYSQL_RES *resultClient;
    MYSQL_ROW rowClient;

    DBConfig store;
    
    snprintf(query, sizeof(query), "SELECT * FROM store");
    
    if(mysql_query(conn, query) != 0) {
        finish_with_error(conn);
        return;
    }
    
    resultStores = mysql_store_result(conn);
    
    fprintf(stdout, "Buscar por nombre: "); fflush(stdout);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    
    fprintf(stdout, "Buscar por RFC: "); fflush(stdout);
    fgets(rfc, sizeof(rfc), stdin);
    rfc[strcspn(rfc, "\n")] = '\0';

    while((rowStores = mysql_fetch_row(resultStores))) {
        store.host   = rowStores[1];
        store.user   = mainUser;
        store.passwd = mainPasswd;
        store.db     = rowStores[2];
        conn = initConnection(store);
        
        snprintf(query, sizeof(query), "SELECT * FROM client        \
                                        WHERE name LIKE '%%%s%%'    \
                                        AND rfc LIKE '%%%s%%'",
        name, rfc);
    
        if(mysql_query(conn, query) != 0) {
            finish_with_error(conn);
            mysql_free_result(resultStores);
            mysql_free_result(resultClient);
            return;
        }

        resultClient = mysql_store_result(conn);

        fprintf(stdout, "---- TIENDA: %s ----\n", rowStores[2]);
        while((rowClient = mysql_fetch_row(resultClient))) {
            c = getClient(rowClient[4], conn);
            
            fprintf(stdout, "----------------------------\n"); 
            fprintf(stdout, "INFO: %s, %s, %s, %s\n", c->client[1], c->client[2], c->client[3], c->client[4]); 
            fprintf(stdout, "DIR.: %s, %s, %s, %s\n", c->addr[1], c->addr[2], c->addr[3], c->addr[4]); 
            fprintf(stdout, "----------------------------\n\n"); 
    
            for(int i = 0; i < 5; i++) { 
                delete[] c->client[i];
            }
            for(int i = 0; i < 6; i++) { 
                delete[] c->addr[i];
            }
            delete[] c->client;
            delete[] c->addr; 
            delete c;
        } 

        mysql_free_result(resultClient);
        mysql_close(conn);
    }

    mysql_free_result(resultStores);
            
    fprintf(stdout, "\nPresiona enter para volver..."); 
    int ch; while ((ch = getchar()) != '\n' && ch != EOF);
    getchar();
}
