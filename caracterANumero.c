#include <stdio.h>
#include <ctype.h>
#include <string.h>

//PUNTO 2

int caracterANumero(char caracter) {
    if (caracter >= '0' && caracter <= '9') {
        return caracter - '0'; //el ascii de 0 es 48, el de 1 es 49, 2->50 y asi
                                //entonces, al restarle esos 48 asociados al 0 obtenes el numero decimal
    }
    return -1;
}

int main(){
    char caracter[1];
    
    printf("Ingrese el caracter a pasar a numero \n");
    scanf("%s", caracter);

    int numero = caracterANumero(caracter[0]); //si se le pasan mas de 1 caracter solo toma el primero

    if(numero != -1)
        printf("El numero pasado a decimal es %d\n", numero);
    else
        printf("No es posible pasarlo a un numero\n");

    return 0;
}