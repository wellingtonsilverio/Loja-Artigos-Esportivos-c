#include <stdio.h>

int getInt(char* title){
    int aux;

    printf(title);

    scanf("%d", &aux);

    return aux;
}

char* getString(char* title){
    char aux[100];

    printf(title);

    setbuf(stdin, NULL);
    fgets(aux, 101, stdin);
    aux[strlen(aux) - 1] = '\0';

    return aux;
}
