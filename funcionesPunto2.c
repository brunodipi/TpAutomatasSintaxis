#include "funcionesPunto2.h"

int caracterANumero(char caracter) {
    if (caracter >= '0' && caracter <= '9') {
        return caracter - '0'; //el ascii de 0 es 48, el de 1 es 49, 2->50 y asi
                                //entonces, al restarle esos 48 asociados al 0 obtenes el numero decimal
    }
    return -1;
}