#ifndef SALES_H
#define SALES_H

//structs(todas possuem base em "listas ligadas" - possuem um ponteiro para o prox item da lista).
typedef struct sale{
  int codProduto;
  int codVenda;
  float valor;
  int qtd;
  struct sale *prox;
} Sale;

typedef struct cart{
  int codVenda;
  int CPF;
  int pagamento;
  Sale *sales;
  struct cart *prox;
} Card;

void createSale(int, int, float, int);
Sale* getFirstSale();
Sale* getNextSale(Sale*);
Sale* getLastSale();
Sale* getSaleByCode(int);
Sale* getFirstSaleByCardCode(int);
Sale* getSpecificSaleByCode(Sale*, int);
void updateSaleByCode(int, float, int);
void deleteSaleByCode(int);
void printSale(Sale*);
void persistSale();
void loadSale();
void freeSale();

void createCard(int, int, int, Sale*);
Card* getFirstCard();
Card* getNextCard(Card*);
Card* getLastCard();
Card* getCardByCode(int);
void updateCardByCode(int, int, int);
void deleteCardByCode(int);
void printCards();
void persistCard();
void loadCard();
void freeCard();


#endif
