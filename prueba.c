// Cuando sí existe y usando variables
#include <stdio.h>
#include <string.h>

int main(){
    char *pajar = "Hola mundo";
    char *aguja = "mundo";

    if(strstr(pajar, aguja) != NULL) {
        printf("Existe %s dentro de %s\n", aguja, pajar);
    }else{
        printf("No existe %s dentro de %s\n", aguja, pajar);
    }
    return 0;
}