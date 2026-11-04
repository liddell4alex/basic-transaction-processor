#include "ddbs.h"

#include <vector>

void clearScreen() {
    fprintf(stdout, "\033[2J\033[H");
    fflush(stdout);
}

int main(int argn, char* args[])
{
    const char* actualDatabase = "morelia_store";
    const char* actualHost     = "127.0.0.1";

    DBConfig actualStore;
    actualStore.host   = actualHost;
    actualStore.user   = mainUser;
    actualStore.passwd = mainPasswd;
    actualStore.db     = actualDatabase;
    (void)actualStore;

    while(1) {
        clearScreen();

        fprintf(stdout, "Seleccione una opción: \n");
        fprintf(stdout, "1. Nuevo cliente\n");
        fprintf(stdout, "2. Actualizar datos del cliente\n");
        fprintf(stdout, "3. Buscar cliente\n");
        fprintf(stdout, "4. Nueva tabla distribuida\n");
        fprintf(stdout, "5. Nueva tienda\n");
        fprintf(stdout, ">>> ");
        fflush(stdout);

        int op;
        fscanf(stdin, "%d", &op);
        getchar();

        switch(op) {
            case 1:
                clearScreen();
                fprintf(stdout, "En desarrollo");
                getchar();

                break;
            
            case 2:
                clearScreen();
                fprintf(stdout, "En desarrollo");
                getchar();
                
                break;
            
            case 3:
                clearScreen();
                fprintf(stdout, "En desarrollo");
                getchar();
                
                break;
            
            case 4:
                clearScreen();
                fprintf(stdout, "En desarrollo");
                getchar();
                
                break;
            
            case 5:
                clearScreen();
                char db[100];
                char host[100];
                
                fprintf(stdout, "Nombre de la base de datos (sin espacios): "); fflush(stdout);
                fscanf(stdin, "%99s", db); getchar(); 
                fprintf(stdout, "Host de la base de datos: "); fflush(stdout);
                fscanf(stdin, "%99s", host); getchar();

                newStore(host, db);
                
                getchar();
                
                break;
            
            default:
                clearScreen();
                fprintf(stdout, "Error");
                getchar();
                
                break;
        }
    }

    return 0;
}