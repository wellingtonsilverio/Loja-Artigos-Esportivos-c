#ifndef STOCK_H
#define STOCK_H

//structs(todas possuem base em "listas ligadas" - possuem um ponteiro para o prox item da lista).
typedef struct stock{
  char nome[100];
  int codigo;
  float valor;
  int qtd;
  int active;
  struct stock *prox;
} Stock;

void createStock(int, char*, float, int);
Stock* getStock();
Stock* getFirstStock();
Stock* getNextStock(Stock*);
Stock* getLastStock();
Stock* getStockByCode(int);
void updateStockByCode(int, char*, float, int);
void deleteStockByCode(int);
void printStock();
void persistStock();
void loadStock();
void freeStock();

#endif
