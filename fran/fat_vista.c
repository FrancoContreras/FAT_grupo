#include "fat_vista.h"

void mostrar_menu(){
    printf("\nMENU\n");
    printf("----------------------\n");
    printf("(1) Grabar archivo\n");
    printf("(2) Leer archivo\n");
    printf("(3) Eliminar archivo\n");
    printf("(5) Mostrar lista de archivos grabados\n");
    printf("(6) Mostrar todas las tablas\n");
    printf("(7) Mostrar tabla indice\n");
    printf("(8) Mostrar tabla de datos\n");
    printf("(9) Mostrar tabla de bits\n");
    printf("(0) Salir\n");
    printf("----------------------\n\n");
}

void iniciar(Fat *fat) {
    int opcion = -1;
    char nombre[12];
    char datos[52];
    char contenido[41] = "";

    while (opcion != 0) {
        mostrar_menu();
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        while (getchar() != '\n');

        switch (opcion) {
            case 1:
                printf("Ingresa nombre del archivo: ");
                fgets(nombre, 12, stdin);
                nombre[strcspn(nombre, "\n")] = '\0';
                if(max_size_nombre(nombre)){
                    printf("\nEl nombre ingresado supera los 10 caracteres\n"); 
                    break;
                }
                if(archivo_existe(nombre, fat)){
                    printf("\nEl archivo ya existe\n"); 
                }
                else{
                    printf("\nIngresa contenido: ");
                    fgets(datos, 52, stdin);
                    datos[strcspn(datos, "\n")] = '\0';
                    if(max_size_contenido(datos)){
                        printf("\nEl contenido del archivo supera los 40 caracteres\n"); 
                        break;
                    }
                    if(hay_espacio(datos, fat)){
                        grabar_archivo(nombre, datos, fat);
                        printf("\nArchivo grabado\n");
                    }
                    else{
                        printf("\nNo hay espacio suficiente para el archivo\n");  
                    }
                }
                break;
            case 2:
                printf("Ingresa nombre del archivo: ");
                fgets(nombre, 12, stdin);
                nombre[strcspn(nombre, "\n")] = '\0';
                if(max_size_nombre(nombre)){
                    printf("\nEl nombre ingresado supera los 10 caracteres\n"); 
                    break;
                }
                if(archivo_existe(nombre, fat)){
                    leer_archivo(nombre, fat, contenido);
                    printf("%s\n", contenido);
                }
                else{
                    printf("\nEl archivo no existe\n");  
                }
                break;
            case 3:
                printf("Ingresa nombre del archivo: ");
                fgets(nombre, 12, stdin);
                nombre[strcspn(nombre, "\n")] = '\0';
                if(max_size_nombre(nombre)){
                    printf("\nEl nombre ingresado supera los 10 caracteres\n"); 
                    break;
                }
                if(archivo_existe(nombre, fat)){
                    borrar_archivo(nombre, fat);
                    printf("\nArchivo eliminado\n");
                }
                else{
                    printf("\nEl archivo no existe\n");  
                }                
                break;
            case 5:
                mostrar_archivos_grabados(fat);
                break;
            case 6:
                mostrar_tabla_indice(fat);
                mostrar_tabla_datos(fat);
                mostrar_tabla_bit(fat);
                break;
            case 7:
                mostrar_tabla_indice(fat);
                break;
            case 8:
                mostrar_tabla_datos(fat);
                break;
            case 9:
                mostrar_tabla_bit(fat);
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no reconocida. Por favor, intente de nuevo.\n");
                break;
        }
    }
}

void mostrar_archivos_grabados(Fat *fat){
    bool flag = false;
    for(int i = 0; i< ARCHIVOS_MAXIMOS; i++){
        if(fat->tabla_indice.borrados[i] == 0 && strcmp(fat->tabla_indice.nombre[i], "Vacio") != 0){
            printf("Archivo [%d]: %s\n", i+1, fat->tabla_indice.nombre[i]);
            flag = true;
        }
    }
    if(flag == false){
        printf("No hay ningun archivo en el sistema\n");
    }
}

void mostrar_tabla_bit(Fat *fat) {
    printf("--- CONTENIDO DE LA TABLA DE INDICES ---\n");
    for (int i = 0; i < ARCHIVOS_MAXIMOS; i++) {
        printf("Indice [%d]: %d\n", i+1, fat->tabla_bit[i]);
    }
}

void mostrar_tabla_indice(Fat *fat) {
    printf("--- CONTENIDO DE LA TABLA DE INDICE ---\n");
    printf("%-8s %-10s %-10s %-10s %-10s\n", "Fila", "Nombre", "B_ini", "Qb", "Borr");
    
    for (int i = 0; i < ARCHIVOS_MAXIMOS; i++) {
        printf("[%d]      %-15s %-10d %-10d %-10d\n", 
               i+1, 
               fat->tabla_indice.nombre[i], 
               fat->tabla_indice.bloque_inicial[i], 
               fat->tabla_indice.cantidad_bloques[i], 
               fat->tabla_indice.borrados[i]);
    }
    printf("\n");
}

void mostrar_tabla_datos(Fat *fat) {
    printf("--- CONTENIDO DE LA TABLA DE DATOS ---\n");
    printf("%-8s %-40s %-10s\n", "Fila", "Datos", "B_sig");
    
    for (int i = 0; i < ARCHIVOS_MAXIMOS; i++) {
        printf("[%d]      %-42s %-10d\n", 
               i+1, 
               fat->tabla_datos.datos[i], 
               fat->tabla_datos.bloque_siguiente[i]);
    }
    printf("\n");
}