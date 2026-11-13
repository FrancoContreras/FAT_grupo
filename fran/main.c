#include "fat_vista.h"
#include "fat_modelo.h"

int main(){
    Fat fat;
    crear_tabla_bit(&fat);
    crear_tabla_datos(&fat);
    crear_tabla_indice(&fat);
    iniciar(&fat);

    return 0;
}