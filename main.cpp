#include "ddbs.h"

#include <vector>
#include <string>
#include <cstring>

void clearScreen() {
    fprintf(stdout, "\033[2J\033[H");
    fflush(stdout);
}

// ddbs <actualHost> <actualDbName> <mainStoreHost> <mainStoreDbName>
int main(int argn, char* args[])
{    
    if(argn < 6) {
        fprintf(stderr, "Error: Faltan argumentos.\n");
        fprintf(stdout, "Uso: ddbs <actualHost> <actualDbName> <mainStoreHost> <mainStoreDbName>\n");
        return 1;
    }

    char query[1000];

    const char* actualHost     = args[1];
    const char* actualDatabase = args[2];

    const char* mainStoreHost = args[3];
    const char* mainStoreDB  = args[4];
     
    Client *c = new Client;
    c->client = new char*[4];
    c->addr = new char*[4];

    DBConfig actualStore;
    actualStore.host   = actualHost;
    actualStore.user   = mainUser;
    actualStore.passwd = mainPasswd;
    actualStore.db     = actualDatabase;
    MYSQL *conn        = initConnection(actualStore);

    while(1) {
        clearScreen();
        fprintf(stdout, "Bienvenido a la tienda %s\n\n", actualDatabase);

        fprintf(stdout, "Seleccione una opción: \n");
        fprintf(stdout, "1. Nuevo cliente\n");
        fprintf(stdout, "2. Actualizar datos del cliente\n");
        fprintf(stdout, "3. Buscar cliente\n");
        fprintf(stdout, "4. Nueva tabla distribuida\n");
        fprintf(stdout, "5. Nueva tienda\n");
        fprintf(stdout, "0. Salir\n");
        fprintf(stdout, ">>> ");
        fflush(stdout);

        int op;
        fscanf(stdin, "%d", &op);
        getchar();

        switch(op) {
            case 1:
                clearScreen();
                fprintf(stdout, "NUEVO CLIENTE\n\n");
                
                fprintf(stdout, "Introduzca el nombre del cliente ----------\n");
                fprintf(stdout, "Nombre: "); fflush(stdout);
                c->client[0] = new char[100];
                fgets(c->client[0], 100, stdin);
                c->client[0][strcspn(c->client[0], "\n")] = '\0';
                
                fprintf(stdout, "Apellido Paterno: "); fflush(stdout);
                c->client[1] = new char[50];
                fgets(c->client[1], 50, stdin);
                c->client[1][strcspn(c->client[1], "\n")] = '\0';
                
                fprintf(stdout, "Apellido Materno (si aplica): "); fflush(stdout);
                c->client[2] = new char[50];
                fgets(c->client[2], 50, stdin);
                c->client[2][strcspn(c->client[2], "\n")] = '\0';
                
                fprintf(stdout, "RFC: "); fflush(stdout);
                c->client[3] = new char[15];
                fgets(c->client[3], 15, stdin);
                c->client[3][strcspn(c->client[3], "\n")] = '\0';


                fprintf(stdout, "\nIntroduzca la dirección del cliente -------\n");
                fprintf(stdout, "Calle: "); fflush(stdout); 
                c->addr[0] = new char[200];
                fgets(c->addr[0], 200, stdin);
                c->addr[0][strcspn(c->addr[0], "\n")] = '\0';
                
                fprintf(stdout, "Número: "); fflush(stdout);
                c->addr[1] = new char[10];
                fgets(c->addr[1], 10, stdin);
                c->addr[1][strcspn(c->addr[1], "\n")] = '\0';
                
                fprintf(stdout, "Estado: "); fflush(stdout);
                c->addr[2] = new char[200];
                fgets(c->addr[2], 200, stdin);
                c->addr[2][strcspn(c->addr[2], "\n")] = '\0';
                
                fprintf(stdout, "Código Postal: "); fflush(stdout);
                c->addr[3] = new char[7];
                fgets(c->addr[3], 7, stdin);
                c->addr[3][strcspn(c->addr[3], "\n")] = '\0';
                
                newClient(c, conn);
                
                for(int i = 0; i < 4; i++) {
                    delete[] c->client[i];
                    delete[] c->addr[i];
                }
                delete[] c->client;
                delete[] c->addr;
                delete c;

                break;
            
            case 2:
                clearScreen();
                fprintf(stdout, "ACTUALIZANDO DATOS DEL CLIENTE\n\n");

                char rfc[15];
                fprintf(stdout, "Introduzca RFC: "); fflush(stdout);
                fgets(rfc, 15, stdin);
                rfc[strcspn(rfc, "\n")] = '\0';
                
                c = getClient(rfc, conn);

                if(c == NULL) break;

                fprintf(stdout, "\nDATOS ACTUALES DEL CLIENTE\n");
                fprintf(stdout, "\nNombre del cliente -------\n");
                fprintf(stdout, "Nombre: %s\nApellido Paterno: %s\nApellido Materno: %s\nRFC: %s", c->client[1], c->client[2], c->client[3], c->client[4]);
                fprintf(stdout, "\n\nDirección del cliente -------\n");
                fprintf(stdout, "Calle: %s\nNúmero: %s\nEstado: %s\nCódigo Postal: %s", c->addr[1], c->addr[2], c->addr[3], c->addr[4]);
                
                fprintf(stdout, "\n\nINTRODUCE LOS DATOS ACTUALIZADOS\n"); 
                fprintf(stdout, "\nIntroduzca el nombre del cliente -------\n");
                fprintf(stdout, "Nombre: "); fflush(stdout);
                c->client[1] = new char[100];
                fgets(c->client[1], 100, stdin);
                c->client[1][strcspn(c->client[1], "\n")] = '\0';
                
                fprintf(stdout, "Apellido Paterno: "); fflush(stdout);
                c->client[2] = new char[50];
                fgets(c->client[2], 50, stdin);
                c->client[2][strcspn(c->client[2], "\n")] = '\0';
                
                fprintf(stdout, "Apellido Materno (si aplica): "); fflush(stdout);
                c->client[3] = new char[50];
                fgets(c->client[3], 50, stdin);
                c->client[3][strcspn(c->client[3], "\n")] = '\0';


                fprintf(stdout, "\nIntroduzca la dirección del cliente -------\n");
                fprintf(stdout, "Calle: "); fflush(stdout);
                c->addr[1] = new char[200];
                fgets(c->addr[1], 200, stdin);
                c->addr[1][strcspn(c->addr[1], "\n")] = '\0';
                
                fprintf(stdout, "Número: "); fflush(stdout);
                c->addr[2] = new char[10];
                fgets(c->addr[2], 10, stdin);
                c->addr[2][strcspn(c->addr[2], "\n")] = '\0';
                
                fprintf(stdout, "Estado: "); fflush(stdout);
                c->addr[3] = new char[200];
                fgets(c->addr[3], 200, stdin);
                c->addr[3][strcspn(c->addr[3], "\n")] = '\0';
                
                fprintf(stdout, "Código Postal: "); fflush(stdout);
                c->addr[4] = new char[5];
                fgets(c->addr[4], 5, stdin);
                c->addr[4][strcspn(c->addr[4], "\n")] = '\0';

                updateClient(c, conn);
                
				for(int i = 0; i < 4; i++) {
                    delete[] c->client[i];
                    delete[] c->addr[i];
                }
                delete[] c->client;
                delete[] c->addr;
                delete c;
 
                break;
            
            case 3:
                clearScreen(); 
                fprintf(stdout, "BUSCAR CLIENTES\n\n");
               
                char yn;
                fprintf(stdout, "Mostrar todos los clientes y/n: ");
                fscanf(stdin, "%c", &yn); getchar();

                if(yn == 'y' || yn == '\n') {
                    showAllClients(conn);
                } else if(yn == 'n') {
                    searchClient(conn);
                } 
                    
                break;
            
            case 4:
                clearScreen();
                fprintf(stdout, "CREANDO NUEVA TABLA DISTRIBUIDA\n\n");
                
                fprintf(stdout, "Introduzca solo el nombre de la tabla, sus atributos y el tipo de atributos en formato comando SQL\n");
                do {
                    strcpy(query, "CREATE TABLE ");
                    char temp[900];

                    fprintf(stdout, "$ ");
                    fgets(temp, sizeof(temp), stdin); 
                    temp[strcspn(temp, "\n")] = '\0';

                    strcat(query, temp);
                     
                } while(newTable(query, conn));
                
                fprintf(stdout, "\nNueva tabla creada correctamente\n");
                fprintf(stdout, "Presiona enter para volver...");
                
                int ch; while ((ch = getchar()) != '\n' && ch != EOF);
                getchar();
                
                break;
             
            case 5:
                clearScreen();
                fprintf(stdout, "AGREGANDO NUEVA TIENDA A LA RED\n\n");
                
                char host[15];
                char db[100];
                
                fprintf(stdout, "IP de conexión a la base de datos: "); fflush(stdout);
                fgets(host, 15, stdin);
                host[strcspn(host, "\n")] = '\0';
                
                fprintf(stdout, "Nombre de la base de datos (sin espacios): "); fflush(stdout);
                fgets(db, 100, stdin);
                db[strcspn(db, "\n")] = '\0';

                newStore(host, db, mainStoreHost, mainStoreDB, conn);
                
                break;

            case 0:
                fprintf(stdout, "Bye :D\n");
                return 0;
            
            default:
                clearScreen();
                fprintf(stdout, "Error");
                getchar();
                
                break;
        }
    }
    

    mysql_close(conn);

    return 0;
}
