typedef enum {
    DECIMAL,
    OCTAL,
    HEXADECIMAL,
    ERROR
} Lenguaje;

int columnaDec (char c);
int columnaOct (char c);
int columnaHexa (char c);
int verifica(char* cadena);
int esPalabraOct (char* cadena);
int esPalabraDec (char* cadena);
int esPalabraHexa (char* cadena);
void evaluar(char* cadena);
