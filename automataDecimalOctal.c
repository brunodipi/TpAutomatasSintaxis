#include <stdio.h>
#include <ctype.h>

//Los enteros decimales, base 10. En este ejemplo tambien se tomarian como validos los octales porque se acepta el 0 como primer caracter como algo valido
//Estamos trabajando con alfabeto reducido

int columna (char c){
    switch (c)
    {
    case '+':
        return 1;
        break;

    case '-':
        return 2;
        break;
    
    default: //los numeros 0-9 se incluyen aca porque trabajamos con un alfabeto reducido
        return 0;
        break;
    }

}

int esPalabra (char* cadena) { //recibir asi la cadena es como recibir un puntero al primer caracter de la cadena
    //la tabla estatica se carga solo 1 vez en memoria, es como una "var global"
    static int tablaTransicion[4][3] = {
        {2, 1, 1},
        {2, 3, 3},
        {2, 3, 3},
        {3, 3, 3}

    };
    int estado = 0; //lo inicializas como en el estado inicial
    int i=0; //para ir avanzando la cadena, pasando por cada caracter
    int c = cadena[i]; // primer caracter a evaluar

    while (c != '\0' && estado != 3){ // '\0' o el caracter centila que corresponda
        estado = tablaTransicion[estado][columna (c)];
        i++;
        c = cadena[i];
    }
    
    if(estado == 2) //el estado de aceptacion, en este caso unico
        return 1;

    return 0;
}

int verifica(char* cadena){ //al ser alfabeto reducido tenemos que hacer esta verificacion
    int i=0; //para ir avanzando la cadena, pasando por cada caracter
    int c = cadena[i]; // primer caracter a evaluar
    

    while(c != '\0' && (c == '+' || c == '-' || isdigit(c))) {
        i++;
        c = cadena[i];
    }

    if (c == '\0')
        return 1;

    return 0;

}

int main () {
    char cadena[100];
    
    printf("Ingrese la cadena a validar \n");
    scanf("%s",cadena);

    if (verifica(cadena)){
        if(esPalabra(cadena)){
            printf("Es una palabra valida en Decimal u Octal \n");
        }
        else{
            printf("No es una palabra \n");
        }
    }

    else{
        printf("No verifica tener los caracteres validos para este lenguaje");
    }


    return 0;
}