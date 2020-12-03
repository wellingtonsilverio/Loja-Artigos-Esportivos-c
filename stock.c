#include <stdio.h>
#include <stdlib.h>
#include "stock.h"

Stock *stocks;

//createStock: recebe os dados do novo produto em estoque e o adiciona a lista(stocks).
void createStock(int code, char* name, float price, int amount) {
    Stock* child = (Stock*) malloc(sizeof(Stock));
    Stock* lastStock = getLastStock();

    if (lastStock->codigo == 0) {
        strcpy(lastStock->nome, name);
        lastStock->codigo = code;
        lastStock->valor = price;
        lastStock->qtd = amount;
        lastStock->prox = NULL;

        return;
    }

    strcpy(child->nome, name);
    child->codigo = code;
    child->valor = price;
    child->qtd = amount;
    child->active = 1;
    child->prox = NULL;

    lastStock->prox = child;

    return;
}

//getStock: retorna o estoque.
Stock* getStock() {
    return stocks;
}

//getFirstStock: retorna o primeiro item em estoque.
Stock* getFirstStock() {
    if (stocks == NULL) {
        stocks = (Stock*) malloc(sizeof(Stock));
        stocks->codigo = 0;
        stocks->prox = NULL;
    }

    return stocks;
}

//getNextStock: retorna o proximo item do estoque
Stock* getNextStock(Stock* stock){
    if (stock == NULL) {
        return stock;
    }

    return stock->prox;
}

//getLastStock: retorna o ultimo item da lista em estoque.
Stock* getLastStock(){
    Stock* stock = getFirstStock();

    while (1) {
        if (getNextStock(stock) == NULL) {
            return stock;
        }
        stock = getNextStock(stock);
    }
}

//getStockByCode: recebe o codigo do produto e retorna o produto desejado.
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

//updateStockByCode:recebe os dados para atualizacao do produto, procura e modifica os dados do produto desejado.
void updateStockByCode(int code, char* name, float price, int amount) {
    Stock* stock = getStockByCode(code);

    if (stock == NULL) {
        return;
    }

    strcpy(stock->nome, name);
    stock->valor = price;
    stock->qtd = amount;
}

//deleteStockByCode: recebe o codigo do produto e exclui o mesmo da lista.
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

//printStock: imprime os dados da lista em estoque.
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

//persistStock: salva toda lista de estoque em um arquivo binario.
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

//loadStock: carrega os dados da lista de estoque que estão no arquivo para a memoria do sistema.
void loadStock(){
    FILE *file;

    file = fopen("stock.bin", "rb");

    if (file == NULL) {
        return;
    }

    freeStock();
    Stock* stock = getFirstStock();

    while(1){
        Stock* read = (Stock*) malloc(sizeof(Stock));

        size_t r = fread(read, sizeof(Stock), 1, file);

        if (r < 1) {
            break;
        } else {
            if (stock == NULL) {
                stock = (Stock*) malloc(sizeof(Stock));
                stock->codigo = 0;
                stock->prox = NULL;
            }
            if (stock->codigo == 0) {
                read->prox = NULL;
                *stock = *read;
            } else {
                read->prox = NULL;
                stock->prox = read;
            }

            stock = getNextStock(stock);

        }
    }

    fclose(file);
}

//freeStock: libera a memoria da lista em estoque.
void freeStock(){
    free(stocks);
}

