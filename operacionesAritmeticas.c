#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "funcionesPunto1.h" // Para usar las funciones del punto 1
#include "funcionesPunto2.h" // Para usar las funciones del punto 2

int hacerCuenta(int resultadoAnterior, char operador, int numero){
    switch(operador){
        case '+': return resultadoAnterior + numero;
        case '-': return resultadoAnterior - numero;
        case '*': return resultadoAnterior * numero;
        case '/': return resultadoAnterior / numero;
    }
    return resultadoAnterior; 
}


int stringANumero(char* cadena) {
    int resultado = 0;
    int i = 0;

    while (cadena[i] != '\0') { // recorre hasta fin de cadena
        resultado = resultado * 10 + caracterANumero(cadena[i]);
        i++;
    }

    return resultado;
}

int resolverTermino(char* cadenaCompleta){
    char cadena[100];
    int i = 0;
    int j = 0;

    int resultado = 0;
    char operador = '+'; // primero es un + porque hay que sumar lo primero
    
    while(1){
        char c = cadenaCompleta[i];
        if(c == '*' || c == '/' || c == '\0'){
            cadena[j] = '\0';
            int lenguaje = verifica(cadena); // ver que sea decimal
            if(lenguaje != DECIMAL){
                printf("Hay caracteres invalidos para el lenguaje decimal");
                return -1;
            }
            int numero = stringANumero(cadena); // pasarlo a numero
            resultado = hacerCuenta(resultado, operador, numero); 
            operador = c;
            j = 0;

            if(c == '\0'){
                return resultado;
            }
        }
        else {
            cadena[j++] = c; // carga caracteres
        }
        i++;
        
    }

    return resultado;
}

int main(){
    char cadenaCompleta[100];
    
    printf("Ingrese la cadena a validar \n");
    scanf("%s",cadenaCompleta);

    //char* cadena = strtok(cadenaCompleta, "#");
    char cadena[100];
    int i = 0;
    int j = 0;

    int resultado = 0;
    char operador = '+';

    while(1) {
        char c = cadenaCompleta[i];

        if(c == '+' || c == '-') {
            cadena[j] = '\0'; // para cerrar la palabra a analizar
            printf("Cadena evaluada: %s \n", cadena);
            int valor = resolverTermino(cadena);
            resultado = hacerCuenta(resultado, operador, valor);
            
            operador = c; // guardo el nuevo signo
            j = 0; // reinicia para proxima palabra
        }
        else if(c == '\0') {
            cadena[j] = '\0'; // para cerrar la palabra a analizar
            printf("Cadena evaluada: %s \n", cadena);
            int valor = resolverTermino(cadena);
            resultado = hacerCuenta(resultado, operador, valor);
            
            break; // es la ultima cadena a evaluar, corto el while
        }
        else {
            cadena[j++] = c; // carga caracteres
        }
        i++;
    }

    printf("Resultado = %d\n", resultado);
    return 0;
}