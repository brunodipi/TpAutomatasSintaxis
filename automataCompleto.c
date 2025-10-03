//--------PUNTO1--------
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    DECIMAL,
    OCTAL,
    HEXADECIMAL,
    ERROR
} Lenguaje;

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

void evaluar(char* cadena, int* cantDec, int* cantOct, int* cantHexa){
    int lenguaje = verifica(cadena);
    switch(lenguaje){
        case DECIMAL:
            if(esPalabraDec(cadena)){
                printf("Es una palabra valida en Decimal \n");
                (*cantDec)++;
            }
            else
                printf("No es una palabra valida en Decimal y no cumple caracteres para Hexadecimal ni Octal\n");
            break;

        case OCTAL:
            if(esPalabraOct(cadena)){
                printf("Es una palabra valida en Octal \n");
                (*cantOct)++;
            }
            else
                printf("No es una palabra valida en Octal y no cumple caracteres para Hexadecimal ni Decimal\n");
            break;

        case HEXADECIMAL:
            if(esPalabraHexa(cadena)){
                printf("Es una palabra valida en Hexadecimal \n");
                (*cantHexa)++;
            }
            else
                printf("No es una palabra valida en Hexadecimal y no cumple caracteres para Decimal ni Octal\n");
            break;
        case ERROR:
            printf("No verifica tener los caracteres validos para ningun lenguaje\n");
            break;      
    }

}

void ingresarCadena(char cadenaCompleta[]){
    int opcion;
    while(1){

        printf("Como quiere ingresar la cadena?\n");
        printf(" 1. Por terminal \n");
        printf(" 2. Por archivo \n");
        
        if (scanf("%d", &opcion) != 1) { // si scanf no pudo leer un número
            printf("Entrada invalida. Intente de nuevo.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF); // limpiar buffer
            continue; 
        }
        if(opcion == 1){
            printf("Ingrese la cadena a validar \n");
            scanf("%s",cadenaCompleta);
            break;
        }
        else if(opcion == 2){
            while(1){
                printf("Ingrese el nombre del archivo \n");
                char archivo[100];
                scanf("%s",archivo);
                FILE* archivoCadena = fopen(archivo, "r");
                if(archivoCadena != NULL){
                    fgets(cadenaCompleta, 100, archivoCadena);
                    fclose(archivoCadena);
                    return;
                } else {
                    printf("Archivo invalido: No se pudo abrir\n");
                }
            }
        }
        else {
            printf("Opcion ingresada incorrecta (Opciones: 1 o 2)\n");
            opcion == -1;
        }
    }
}

int main () {
    char cadenaCompleta[100];
    ingresarCadena(cadenaCompleta);

    int cantidadDecimal = 0;
    int cantidadOctal = 0;
    int cantidadHexa = 0;

    char cadena[100];
    int i = 0;
    int j = 0;

    while(1) {
        char c = cadenaCompleta[i];

        if(c == '#') {
            cadena[j] = '\0'; // para cerrar la palabra a analizar
            printf("Cadena evaluada: %s \n", cadena);
            evaluar(cadena, &cantidadDecimal, &cantidadOctal, &cantidadHexa); // Evalua todos los lenguajes
            j = 0; // reinicia para proxima palabra
        }
        else if(c == '\0') {
            cadena[j] = '\0'; // para cerrar la palabra a analizar
            printf("Cadena evaluada: %s \n", cadena);
            evaluar(cadena, &cantidadDecimal, &cantidadOctal, &cantidadHexa); // Evalua todos los lenguajes
            break; // es la ultima cadena a evaluar, corto el while
        }
        else {
            cadena[j++] = c; // carga caracteres
        }
        i++;
    }
    printf("Cantidad de candenas evaluadas exitosamente:\n");
    printf("Cantidad decimal: %d\n", cantidadDecimal);
    printf("Cantidad octal: %d\n", cantidadOctal);
    printf("Cantidad hexadecimal: %d\n", cantidadHexa);

    return 0;
}