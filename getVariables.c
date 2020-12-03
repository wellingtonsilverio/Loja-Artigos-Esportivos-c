#include <stdio.h>

int getInt(char* title){
    int aux;

    printf(title);

    scanf("%d", &aux);

    return aux;
}

float getFloat(char* title){
    float aux;

    printf(title);

    scanf("%f", &aux);

    return aux;
}

const char* getString(char* title){
    char* aux = (char*) malloc(sizeof(char) * 100);

    printf(title);

    setbuf(stdin, NULL);
    fgets(aux, 101, stdin);
    aux[strlen(aux) - 1] = '\0';

    return aux;
}
