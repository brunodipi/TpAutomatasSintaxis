#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <funcionesPunto2.h>

int main(){
    char caracter[1];
    
    printf("Ingrese el caracter a validar \n");
    scanf("%s", caracter);

    int numero = caracterANumero(caracter[0]); //si se le pasan mas de 1 caracter solo toma el primero

    if(numero != -1)
        printf("El numero pasado a decimal es %d\n", numero);
    else
        printf("No es posible pasarlo a un numero\n");

    return 0;
}