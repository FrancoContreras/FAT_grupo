#include "fat_modelo.h"

void borrar_archivo(char *nombre_archivo, Fat *fat){
    int i;
    int bloque_actual = 0;
    for(i = 0; i < ARCHIVOS_MAXIMOS; i++){
        if(strcmp(fat->tabla_indice.nombre[i], nombre_archivo) == 0){
            bloque_actual = fat->tabla_indice.bloque_inicial[i] -1;
            break;
        }
    }
    strcpy(fat->tabla_datos.datos[bloque_actual], "Vacio");
    fat->tabla_bit[bloque_actual] = 0;
    fat->tabla_indice.borrados[i] = 1;
    fat->tabla_indice.cantidad_bloques[i] = 0;
    fat->tabla_indice.bloque_inicial[i] = 0;
    int siguiente = fat->tabla_datos.bloque_siguiente[bloque_actual];
    fat->tabla_datos.bloque_siguiente[bloque_actual] = 0;

    while(siguiente != 0){
        bloque_actual = siguiente - 1;
        strcpy(fat->tabla_datos.datos[bloque_actual], "Vacio");
        fat->tabla_bit[bloque_actual] = 0;
        siguiente = fat->tabla_datos.bloque_siguiente[bloque_actual];
        fat->tabla_datos.bloque_siguiente[bloque_actual] = 0;
    }
}

void leer_archivo(char *nombre_archivo, Fat *fat, char *destino){
    int i;
    int bloque_actual = 0;
    for(i = 0; i < ARCHIVOS_MAXIMOS; i++){
        if(strcmp(fat->tabla_indice.nombre[i], nombre_archivo) == 0){
            bloque_actual = fat->tabla_indice.bloque_inicial[i] -1;
            break;
        }
    }
   strncat(destino, fat->tabla_datos.datos[bloque_actual], 10);
    int siguiente = fat->tabla_datos.bloque_siguiente[bloque_actual];

    while(siguiente != 0){
        bloque_actual = siguiente - 1;
        strncat(destino, fat->tabla_datos.datos[bloque_actual], 10);
        siguiente = fat->tabla_datos.bloque_siguiente[bloque_actual];
    }
}

bool hay_espacio(char *archivo, Fat *fat){
    float cantidad_bloques = strlen(archivo) / 10.0;
    bool flag = true;
    
    for(int i = 0; i < ARCHIVOS_MAXIMOS; i++){
        if(fat->tabla_bit[i] == 0){
            cantidad_bloques--;
        }
    }

    if(cantidad_bloques > 0){
        flag = false;
    }
    
    return flag;
}

void grabar_archivo(char *nombre_archivo, char *archivo, Fat *fat){
    int i;
    int j = 0;
    float cantidad_bloques = strlen(archivo) / 10.0;
    int pedazos = 0;
    int contador_bloques = 0;
    bool es_bloque_inicial = true;

    for(i = 0; i < ARCHIVOS_MAXIMOS; i++){
            if(strcmp(fat->tabla_indice.nombre[i], "Vacio") == 0 || fat->tabla_indice.borrados[i] == 1){
                strcpy(fat->tabla_indice.nombre[i], nombre_archivo);
                fat->tabla_indice.borrados[i] = 0;
                break;
            }
        }

    while(cantidad_bloques > 0){
        if(fat->tabla_bit[j] == 0){
            memcpy(fat->tabla_datos.datos[j], archivo + pedazos, 10);
            fat->tabla_datos.datos[j][10] = '\0';
            contador_bloques++;

            if(es_bloque_inicial == true){
                fat->tabla_indice.bloque_inicial[i] = j+1;
                es_bloque_inicial = false;
            }
            fat->tabla_bit[j] = 1;
            pedazos += 10;

            if(cantidad_bloques > 1){
                for(int k = j+1; k < ARCHIVOS_MAXIMOS+1; k++){
                    if(fat->tabla_bit[k] == 0){
                        fat->tabla_datos.bloque_siguiente[j] = k+1;
                        break;
                    }
                }
            }
            cantidad_bloques--;
        }
        j++;
    }
    fat->tabla_indice.cantidad_bloques[i] = contador_bloques;
    
}

void crear_tabla_indice(Fat *fat) {
    memset(&(fat->tabla_indice.bloque_inicial), 0,  sizeof(fat->tabla_indice.bloque_inicial));
    memset(&(fat->tabla_indice.cantidad_bloques), 0,  sizeof(fat->tabla_indice.cantidad_bloques));
    memset(&(fat->tabla_indice.borrados), 0,  sizeof(fat->tabla_indice.borrados));
    for (int i = 0; i < ARCHIVOS_MAXIMOS; i++) {
        strcpy(fat->tabla_indice.nombre[i], "Vacio");
    }    
}

void crear_tabla_datos(Fat *fat) {
    memset(&(fat->tabla_datos.bloque_siguiente), 0,  sizeof(fat->tabla_datos.bloque_siguiente));
    for (int i = 0; i < ARCHIVOS_MAXIMOS; i++) {
        strcpy(fat->tabla_datos.datos[i], "Vacio");
    }
}

void crear_tabla_bit(Fat *fat){
    memset(&(fat->tabla_bit), 0, sizeof(fat->tabla_bit));
}

bool archivo_existe(char *nombre_archivo, Fat *fat){
    bool flag = false;
    for(int i = 0; i < ARCHIVOS_MAXIMOS; i++){
        if(strcmp(fat->tabla_indice.nombre[i], nombre_archivo) == 0 && fat->tabla_indice.borrados[i] == 0){
            flag = true;
        }
    }
    return flag;
}

bool max_size_contenido(char *archivo){
    int i = 0;
    
    for (i = 0; archivo[i] != '\0'; i++) {}
    
    return (i >= CONTENIDO_MAXIMO);
}

bool max_size_nombre(char *nombre) {
    int i = 0;

    for (i = 0; nombre[i] != '\0'; i++) {}
    
    return (i >= NOMBRE_MAXIMO);
}