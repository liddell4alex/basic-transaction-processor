#include "ddbs.h"
#include <iostream>

void newStore(const char* host, const char* db) {
    std::string query;
    MYSQL_RES *result;
    MYSQL_ROW row;
 
    // Conect main store (morelia_store)
    DBConfig morelia_store;
    morelia_store.host   = "localhost";
    morelia_store.user   = mainUser;
    morelia_store.passwd = mainPasswd;
    morelia_store.db     = "morelia_store";
    MYSQL *conn = initConnection(morelia_store);

    // Si no existe la base de datos para la nueva sucursal retorna
    query =  "SELECT SCHEMA_NAME ";
    query += "FROM information_schema.SCHEMATA ";
    query += "WHERE SCHEMA_NAME = '";
    query += db;
    query += "';";

    if(mysql_query(conn, query.c_str())) {
        finish_with_error(conn);
    } else {
        result = mysql_store_result(conn);
    }

    if(mysql_num_rows(result) == 0) {
        fprintf(stdout, "No existe la base de datos de la tienda %s\n", db);
        mysql_close(conn);
        mysql_free_result(result);
        return;
    }



    // Si ya existe la sucursal retorna
    query = "SELECT * FROM store ";
    query += "WHERE db_name = '";
    query += db;
    query += "';";

    if(mysql_query(conn, query.c_str())) {
        finish_with_error(conn);
    } else {
        result = mysql_store_result(conn);
    }
    
    if(mysql_num_rows(result) > 0) {
        fprintf(stdout, "Ya existe la tienda %s\n", db);
        mysql_close(conn);
        mysql_free_result(result);
        return;
    }


    // Add new store to main store
    query = "INSERT INTO store(host, db_name) VALUES ('"; 
    query += host;
    query += "', '";
    query += db;
    query += "');";
    
    if(mysql_query(conn, query.c_str())) {
        finish_with_error(conn);
    }
   
    


    // Recolecting conection configs from the main store
    if(mysql_query(conn, "SELECT * FROM store;")) {
        finish_with_error(conn);
    } else {
        result = mysql_store_result(conn);
        mysql_close(conn);
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
        conn = initConnection(store);

        if(conn == NULL) {
            continue;
        }

        // Itero sobre cada tienda agregando todas las demas existentes
        mysql_data_seek(result, 0);
        while((row = mysql_fetch_row(result))) {
            query = "INSERT IGNORE INTO store(host, db_name) VALUES ('"; 
            query += row[1];
            query += "', '";
            query += row[2];
            query += "');";
    
            if(mysql_query(conn, query.c_str())) {
                if(finish_with_error(conn)) continue;
            }

        }

        mysql_close(conn);
    }


    fprintf(stdout, "Nueva tienda %s creada correctamente\n", db);
    
    mysql_free_result(result);
}