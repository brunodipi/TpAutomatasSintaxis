#include <stdio.h>
#include <ctype.h>

//Este automata reconoce unicamente Hexadecimales

int columna (char c){
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

int esPalabra (char* cadena) { //recibir asi la cadena es como recibir un puntero al primer caracter de la cadena
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
        estado = tablaTransicion[estado][columna (c)];
        i++;
        c = cadena[i];
    }
    
    if(estado == 3) //el estado de aceptacion, en este caso unico
        return 1;

    return 0;
}

int verifica(char* cadena){ //al ser alfabeto reducido tenemos que hacer esta verificacion
    int i=0; //para ir avanzando la cadena, pasando por cada caracter
    int c = cadena[i]; // primer caracter a evaluar
    
    while(c != '\0' && (c == 'x' ||  isxdigit(c))) {
        i++;
        c = cadena[i];
    }

    if (c == '\0')
        return 1;

    return 0;

}

int main () {
    char cadena[100]; //cadena a validar
    printf("Ingrese la cadena a validar \n");
    scanf("%s",cadena);

    if (verifica(cadena)){
        if(esPalabra(cadena)){
            printf("Es una palabra valida en Hexa \n");
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