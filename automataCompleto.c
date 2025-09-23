#include <stdio.h>
#include <ctype.h>
#include <string.h>

/***************************************
 * ERRORES:
 * No acepta decimales sin signo
 * Los octales tienen que ser sin signo
****************************************/

//Los enteros decimales, base 10. En este ejemplo tambien se tomarian como validos los octales porque se acepta el 0 como primer caracter como algo valido
//Estamos trabajando con alfabeto reducido
typedef enum {
    DECIMAL_OCTAL,
    HEXADECIMAL,
    ERROR
} Lenguaje;

int columnaDecOct (char c){
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
    
    while(c != '\0' && (c == 'x' ||  isxdigit(c))) {
        i++;
        c = cadena[i];
    }

    if (c == '\0')
        return HEXADECIMAL;
    else {
        i=0; //para ir avanzando la cadena, pasando por cada caracter
        c = cadena[i]; // primer caracter a evaluar
        
        while(c != '\0' && (c == '+' || c == '-' || isdigit(c))) {
            i++;
            c = cadena[i];
        }

        if (c == '\0')
            return DECIMAL_OCTAL;
    }

    return ERROR;
}

int esPalabraDecOct (char* cadena) { //recibir asi la cadena es como recibir un puntero al primer caracter de la cadena
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
        estado = tablaTransicion[estado][columnaDecOct (c)];
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

int main () {
    char cadenaCompleta[100];
    
    printf("Ingrese la cadena a validar \n");
    scanf("%s",cadenaCompleta);

    char* cadena = strtok(cadenaCompleta, "#");
    while(cadena != NULL) {
        printf("Cadena evaluada: %s \n", cadena);
        

        Lenguaje lenguaje = verifica(cadena);
        switch(lenguaje){
            case DECIMAL_OCTAL:
                if(esPalabraDecOct(cadena)){
                    printf("Es una palabra valida en Decimal u Octal \n");
                }
                else
                printf("No es una palabra valida en Decimal u Octal y no cumple caracteres para Hexadecimal\n");
                break;
            case HEXADECIMAL:
                if(esPalabraHexa(cadena)){
                    printf("Es una palabra valida en Hexadecimal \n");
                }
                else
                    printf("No es una palabra valida en Hexadecimal y no cumple caracteres para Decimal u Octal\n");
                break;
            case ERROR:
                printf("No verifica tener los caracteres validos para ningun lenguaje");
                break;      
        }

        cadena = strtok(NULL, "#"); // Arranca de donde dejo antes

    }

    return 0;
}