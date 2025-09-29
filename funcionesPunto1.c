#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "funcionesPunto1.h"
//Los enteros decimales, base 10. En este ejemplo tambien se tomarian como validos los octales porque se acepta el 0 como primer caracter como algo valido
//Estamos trabajando con alfabeto reducido


int columnaDec (char c){
    switch (c)
    {
    case '0':
        return 1;
        break;

    case '+':
        return 2;
        break;

    case '-':
        return 3;
        break;
    
    default: //los numeros 0-9 se incluyen aca porque trabajamos con un alfabeto reducido
        return 0;
        break;
    }

}

int columnaOct (char c){
    switch (c)
    {
    case '0':
        return 1;
        break;
    
    default: //los numeros 0-7 se incluyen aca porque trabajamos con un alfabeto reducido
        return 0;
        break;
    }

}

int columnaHexa (char c){
    switch (c)
    {
        case '0':
            return 0;
            break;

        case 'x':
            return 1;
            break;
        
        default: //los numeros 1-9 y A-F se incluyen aca porque trabajamos con un alfabeto reducido
            return 2;
            break;
    }

}

int verifica(char* cadena){ //al ser alfabeto reducido tenemos que hacer esta verificacion
    int i=0; //para ir avanzando la cadena, pasando por cada caracter
    int c = cadena[i]; // primer caracter a evaluar
    if(c == '0'){
        c = 'P'; //P de Pifiaste, es hexa/octal, no hace falta analizar si es decimal porque no lo es
    }
    while(c != '\0' && (c == '+' || c == '-' || isdigit(c))) { 
        i++;
        c = cadena[i];
    }

    if (c == '\0')
        return DECIMAL;

    else {
        int i=0; //para ir avanzando la cadena, pasando por cada caracter
        int c = cadena[i]; // primer caracter a evaluar
        while(c != '\0' && (c>='0' && c<='7')) {
            i++;
            c = cadena[i];
        }

        if (c == '\0')
            return OCTAL;
        
        else{
            i=0; //para ir avanzando la cadena, pasando por cada caracter
            c = cadena[i]; // primer caracter a evaluar
            
            while(c != '\0' && (c == 'x' ||  isxdigit(c))) {
                i++;
                c = cadena[i];
            }

            if (c == '\0')
                return HEXADECIMAL;
        }
    }

    return ERROR;
}

int esPalabraOct (char* cadena) { //recibir asi la cadena es como recibir un puntero al primer caracter de la cadena
    //la tabla estatica se carga solo 1 vez en memoria, es como una "var global"
    static int tablaTransicion[4][2] = {
        {3, 1},
        {2, 2},
        {2, 2},
        {3, 3}

    };

    int estado = 0; //lo inicializas como en el estado inicial
    int i=0; //para ir avanzando la cadena, pasando por cada caracter
    int c = cadena[i]; // primer caracter a evaluar

    while (c != '\0' && estado != 3){ // '\0' o el caracter centila que corresponda
        estado = tablaTransicion[estado][columnaOct(c)];
        i++;
        c = cadena[i];
    }
    
    if(estado == 2) //el estado de aceptacion, en este caso unico
        return 1;

    return 0;
}


int esPalabraDec (char* cadena) { //recibir asi la cadena es como recibir un puntero al primer caracter de la cadena
    //la tabla estatica se carga solo 1 vez en memoria, es como una "var global"
    static int tablaTransicion[4][4] = {
        {2, 3, 1, 1},
        {2, 3, 3, 3},
        {2, 2, 3, 3},
        {3, 3, 3, 3}

    };

    int estado = 0; //lo inicializas como en el estado inicial
    int i=0; //para ir avanzando la cadena, pasando por cada caracter
    int c = cadena[i]; // primer caracter a evaluar

    while (c != '\0' && estado != 3){ // '\0' o el caracter centila que corresponda
        estado = tablaTransicion[estado][columnaDec(c)];
        i++;
        c = cadena[i];
    }
    
    if(estado == 2) //el estado de aceptacion, en este caso unico
        return 1;

    return 0;
}


int esPalabraHexa (char* cadena) { //recibir asi la cadena es como recibir un puntero al primer caracter de la cadena
    //la tabla estatica se carga solo 1 vez en memoria, es como una "var global"
    static int tablaTransicion[5][3] = {
        {1, 4, 4},
        {4, 2, 4},
        {3, 4, 3},
        {3, 4, 3},
        {4, 4, 4} //se agrega un estado 4 como estado de rechazo
    };
    int estado = 0; //lo inicializas como en el estado inicial
    int i=0; //para ir avanzando la cadena, pasando por cada caracter
    int c = cadena[i]; // primer caracter a evaluar

    while (c != '\0' && estado != 4){ // '\0' o el caracter centila que corresponda
        estado = tablaTransicion[estado][columnaHexa (c)];
        i++;
        c = cadena[i];
    }
    
    if(estado == 3) //el estado de aceptacion, en este caso unico
        return 1;

    return 0;
}

void evaluar(char* cadena){
    int lenguaje = verifica(cadena);
    switch(lenguaje){
        case DECIMAL:
            if(esPalabraDec(cadena)){
                printf("Es una palabra valida en Decimal \n");
            }
            else
                printf("No es una palabra valida en Decimal y no cumple caracteres para Hexadecimal ni Octal\n");
            break;

        case OCTAL:
            if(esPalabraOct(cadena)){
                printf("Es una palabra valida en Octal \n");
            }
            else
                printf("No es una palabra valida en Octal y no cumple caracteres para Hexadecimal ni Decimal\n");
            break;

        case HEXADECIMAL:
            if(esPalabraHexa(cadena)){
                printf("Es una palabra valida en Hexadecimal \n");
            }
            else
                printf("No es una palabra valida en Hexadecimal y no cumple caracteres para Decimal ni Octal\n");
            break;
        case ERROR:
            printf("No verifica tener los caracteres validos para ningun lenguaje");
            break;      
    }

}
