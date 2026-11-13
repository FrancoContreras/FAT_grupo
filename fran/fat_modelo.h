#ifndef FAT_MODELO_H
#define FAT_MODELO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ARCHIVOS_MAXIMOS 10
#define CONTENIDO_MAXIMO 41
#define NOMBRE_MAXIMO 11

typedef struct {
    char nombre[ARCHIVOS_MAXIMOS][11];
    int bloque_inicial[ARCHIVOS_MAXIMOS];
    int cantidad_bloques[ARCHIVOS_MAXIMOS];
    int borrados[ARCHIVOS_MAXIMOS];
} TablaIndice;

typedef struct {
    char datos[ARCHIVOS_MAXIMOS][11];
    int bloque_siguiente[ARCHIVOS_MAXIMOS];
} TablaDatos;

typedef struct {
    TablaIndice tabla_indice;
    TablaDatos tabla_datos;
    int tabla_bit[ARCHIVOS_MAXIMOS];
} Fat;

void grabar_archivo(char *nombre_archivo, char *archivo, Fat *fat);
void leer_archivo(char *nombre_archivo, Fat *fat, char *contenido);
void borrar_archivo(char *nombre_archivo, Fat *fat);
void crear_tabla_indice(Fat *fat);
void crear_tabla_datos(Fat *fat);
void crear_tabla_bit(Fat *fat);
bool max_size_contenido(char *archivo);
bool max_size_nombre(char *nombre);
bool hay_espacio(char *archivo, Fat *fat);
bool archivo_existe(char *nombre_archivo, Fat *fat);

#endif