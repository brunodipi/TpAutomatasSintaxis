#include <funcionesPunto1.h>

int main () {
    char cadenaCompleta[100];
    
    printf("Ingrese la cadena a validar \n");
    scanf("%s",cadenaCompleta);

    //char* cadena = strtok(cadenaCompleta, "#");
    char cadena[100];
    int i = 0;
    int j = 0;

    while(1) {
        char c = cadenaCompleta[i];

        if(c == '#') {
            cadena[j] = '\0'; // para cerrar la palabra a analizar
            printf("Cadena evaluada: %s \n", cadena);
            evaluar(cadena); // Evalua todos los lenguajes
            j = 0; // reinicia para proxima palabra
        }
        else if(c == '\0') {
            cadena[j] = '\0'; // para cerrar la palabra a analizar
            printf("Cadena evaluada: %s \n", cadena);
            evaluar(cadena); // Evalua todos los lenguajes
            break; // es la ultima cadena a evaluar, corto el while
        }
        else {
            cadena[j++] = c; // carga caracteres
        }
        i++;
    }

    return 0;
}