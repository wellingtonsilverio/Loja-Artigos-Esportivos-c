#include <stdio.h>
#include <stdlib.h>
#include "stock.h"

Stock *stocks;

void createStock(int code, char* name, float price, int amount) {
    Stock* child = (Stock*) malloc(sizeof(Stock));
    Stock* lastStock = getLastStock();

    if (lastStock->codigo == 0) {
        lastStock->nome = name;
        lastStock->codigo = code;
        lastStock->valor = price;
        lastStock->qtd = amount;
        lastStock->prox = NULL;

        return;
    }

    child->nome = name;
    child->codigo = code;
    child->valor = price;
    child->qtd = amount;
    child->prox = NULL;

    lastStock->prox = child;

    return;
}

Stock* getStock() {
    return stocks;
}

Stock* getFirstStock() {
    if (stocks == NULL) {
        stocks = (Stock*) malloc(sizeof(Stock));
        stocks->codigo = 0;
        stocks->prox = NULL;
    }

    return stocks;
}

Stock* getNextStock(Stock* stock){
    if (stock == NULL) {
        return stock;
    }

    return stock->prox;
}

Stock* getLastStock(){
    Stock* stock = getFirstStock();

    while (1) {
        if (getNextStock(stock) == NULL) {
            return stock;
        }
        stock = getNextStock(stock);
    }
}

Stock* getStockByCode(int code) {
    Stock* stock = getFirstStock();

    if (stock == NULL || stock->codigo == 0) {
        return;
    }

    while (stock != NULL && stock->codigo != code) {
        stock = getNextStock(stock);
    }

    return stock;
}
void updateStockByCode(int code, char* name, float price, int amount) {
    Stock* stock = getStockByCode(code);

    if (stock == NULL) {
        return;
    }

    stock->nome = name;
    stock->valor = price;
    stock->qtd = amount;
}

void deleteStockByCode(int code) {
    Stock* stock = getStockByCode(code);
    Stock* aux = (Stock*) malloc(sizeof(Stock));

    *aux = *stock;
    if (getNextStock(aux) != NULL) {
        *stock = *getNextStock(aux);
    } else {
       free(stock);
    }

    free(aux);
}

void printStock(){
    Stock* stock = getFirstStock();

    printf("\n\t--------------------------------------------------------------------\n");
    printf("\n\tCOD.PRODUTO       NOME       VALOR       QUANTIDADE");
    while (stock != NULL && stock->codigo != 0) {

        if (stock->valor >= 0) {
            printf("\n\t#%-10d    %s    %.2f    %d\n", stock->codigo, stock->nome, stock->valor, stock->qtd);
        } else {
            printf("\n\t#%-10d    %s    TROCA\n", stock->codigo, stock->nome);
        }

        stock = getNextCard(stock);
    }
    printf("\n\t--------------------------------------------------------------------\n");
}

void persistStock(){
    FILE *file;

    file = fopen("stock.bin", "w+b");

    if (file == NULL) {
        return;
    }

    Stock* stock = getFirstStock();

    while (stock != NULL) {
        fwrite(stock, sizeof(Stock), 1, file);
        stock = getNextStock(stock);
    }

    fclose(file);
}

void loadStock(){
    FILE *file;

    file = fopen("stock.bin", "rb");

    if (file == NULL) {
        return;
    }

    freeStock();

    while(1){
        Stock* stock = getFirstStock();
        Stock* read = (Stock*) malloc(sizeof(Stock));

        size_t r = fread(read, sizeof(Stock), 1, file);



        if (r < 1) {
            break;
        } else {
            if (stock->codigo == 0) {
                *stock = *read;
            } else {
                stock->prox = read;
            }

        }
    }

    fclose(file);
}

void freeStock(){
    free(stocks);
}

