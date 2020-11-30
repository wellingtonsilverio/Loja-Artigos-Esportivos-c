#include <stdio.h>
#include <stdlib.h>
#include "sales.h"
#include "stock.h"

Sale *sales;
Card *cards;

void createSale(int code, int cardCode, float price, int amount) {
    Sale* child = (Sale*) malloc(sizeof(Sale));
    Sale* lastSale = getLastSale();

    if (lastSale->codProduto == 0) {
        lastSale->codProduto = code;
        lastSale->codVenda = cardCode;
        lastSale->valor = price;
        lastSale->qtd = amount;
        lastSale->prox = NULL;

        return;
    }

    child->codProduto = code;
    child->codVenda = cardCode;
    child->valor = price;
    child->qtd = amount;
    child->prox = NULL;

    lastSale->prox = child;

    return;
}

Sale* getFirstSale() {
    if (sales == NULL) {
        sales = (Sale*) malloc(sizeof(Sale));
        sales->codProduto = 0;
        sales->prox = NULL;
    }

    return sales;
}

Sale* getNextSale(Sale* sale){
    if (sale == NULL) {
        sale = (Sale*) malloc(sizeof(Sale));

        return sale;
    }

    return sale->prox;
}

Sale* getLastSale(){
    Sale* sale = getFirstSale();
    while (1) {
        if (sale->prox == NULL) {
            return sale;
        }
        sale = sale->prox;
    }
}

Sale* getSaleByCode(int code){
    Sale* sale = getFirstSale();

    if (sale == NULL || sale->codProduto == 0) {
        return;
    }

    while (sale->codProduto != code) {
        sale = sale->prox;
    }

    return sale;
}

Sale* getSpecificSaleByCode(Sale* sale, int code){
    if (sale == NULL || sale->codProduto == 0) {
        return;
    }

    while (sale->codProduto != code) {
        sale = sale->prox;
    }

    return sale;
}

void updateSaleByCode(int code, float price, int amount){
    Sale* sale = getSaleByCode(code);

    if (sale == NULL) {
        return;
    }

    sale->codProduto = code;
    sale->valor = price;
    sale->qtd = amount;

    return;
}

void deleteSaleByCode(int code){
    Sale* sale = getSaleByCode(code);
    Sale* aux = (Sale*) malloc(sizeof(Sale));

    *aux = *sale;
    *sale = *getNextSale(aux);

    free(aux);
}

void printSale(Sale* sale) {
    if (sale == NULL) {
        return;
    }

    int codeCard = sale->codVenda;

    printf("\n\t\tCOD.Produto       VALOR       QUANTIDADE");
    while (sale != NULL && sale->codVenda == codeCard) {
        printf("\n\t\t#%-10d    %.2f    %d\n", sale->codProduto, sale->valor, sale->qtd);
        sale = getNextSale(sale);
    }
}

void freeSale(){
    free(sales);
}


void createCard(int code, int CPF, int paymentType, Sale* sales) {
    Card* child = (Card*) malloc(sizeof(Card));
    Card* lastCard = getLastCard();
    Stock* stock;

    if (lastCard->codVenda == 0) {
        lastCard->codVenda = code;
        lastCard->CPF = CPF;
        lastCard->pagamento = paymentType;
        lastCard->sales = sales;
        lastCard->prox = NULL;

        return;
    }

    child->codVenda = code;
    child->CPF = CPF;
    child->pagamento = paymentType;
    child->sales = sales;
    child->prox = NULL;

    lastCard->prox = child;

    while (sales != NULL) {
        stock = getStockByCode(sales->codProduto);
        stock->qtd -= sales->qtd;

        sales = sales->prox;
    }

    return;
}

Card* getFirstCard() {
    if (cards == NULL) {
        cards = (Card*) malloc(sizeof(Card));
        cards->codVenda = 0;
        cards->prox = NULL;
    }

    return cards;
}

Card* getNextCard(Card* card){
    if (card == NULL) {
        card = (Card*) malloc(sizeof(Card));

        return card;
    }

    return card->prox;
}

Card* getLastCard(){
    Card* card = getFirstCard();
    while (1) {
        if (card->prox == NULL) {
            return card;
        }
        card = card->prox;
    }
}

Card* getCardByCode(int code){
    Card* card = getFirstCard();

    if (card == NULL || card->codVenda == 0) {
        return;
    }

    while (card->codVenda != code) {
        card = card->prox;
    }

    return card;
}

void updateCardByCode(int code, int CPF, int paymentType){
    Card* card = getCardByCode(code);

    if (card == NULL) {
        return;
    }

    card->codVenda = code;
    card->CPF = CPF;
    card->pagamento = paymentType;

    return;
}

void deleteCardByCode(int code){
    Card* card = getCardByCode(code);
    Card* aux = (Card*) malloc(sizeof(Card));

    *aux = *card;
    *card = *getNextCard(aux);

    free(aux);
}

void printCards(){
    Card* card = getFirstCard();

    while (card != NULL) {
        printf("\n\t--------------------------------------------------------------------\n");
        printf("\n\tCOD.VENDA       CPF");
        printf("\n\t#%-10d    %d\n", card->codVenda, card->CPF);
        printSale(card->sales);
        printf("\tPagamento: ");
        if (card->pagamento == 1){
      		printf("DEBITO\n");
     	}else{
      		printf("CREDITO\n");
     	}
        printf("\n\t--------------------------------------------------------------------\n");
        card = getNextCard(card);
    }
}

void freeCard(){
    free(cards);
}
