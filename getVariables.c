#include <stdio.h>

//getInt: recebe uma string do titulo do item a ser inserido no sistema e usa scanf para o mesmo. 
int getInt(char* title){
    int aux;

    printf(title);
    scanf("%d", &aux);
    return aux;
}

//getFloat: recebe uma string do titulo do item a ser inserido no sistema e usa scanf para o mesmo. 
float getFloat(char* title){
    float aux;

    printf(title);
    scanf("%f", &aux);
    return aux;
}

//getString: recebe uma string do titulo do item a ser inserido no sistema e usa fgets para o mesmo. 
const char* getString(char* title){
    char* aux = (char*) malloc(sizeof(char) * 100);

    printf(title);
    setbuf(stdin, NULL);
    fgets(aux, 101, stdin);
    aux[strlen(aux) - 1] = '\0';
    return aux;
}
