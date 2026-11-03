#include <vector>

#include "ddbs.h"

int main(int argn, char* args[])
{
    newStore(
        "127.0.0.1",
        "morelia_store"
    );

    newStore(
        "127.0.0.1",
        "patzcuaro_store"
    );

    newStore(
        "127.0.0.1",
        "uruapan_store"
    );
    
    newStore(
        "127.0.0.1",
        "napa_store"
    );

    return 0;
}