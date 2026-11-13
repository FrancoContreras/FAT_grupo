#ifndef FAT_VISTA_H
#define FAT_VISTA_H

#include <stdio.h>
#include "fat_modelo.h"

void mostrar_menu();
void iniciar(Fat *fat);
void mostrar_archivos_grabados(Fat *fat);
void mostrar_tabla_indice(Fat *fat);
void mostrar_tabla_datos(Fat *fat);
void mostrar_tabla_bit(Fat *fat);

#endif