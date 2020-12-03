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
        return sale;
    }

    return sale->prox;
}

Sale* getLastSale(){
    Sale* sale = getFirstSale();
    while (1) {
        if (getNextSale(sale) == NULL) {
            return sale;
        }
        sale = getNextSale(sale);
    }
}

Sale* getSaleByCode(int code){
    Sale* sale = getFirstSale();

    if (sale == NULL || sale->codProduto == 0) {
        return;
    }

    while (sale != NULL && sale->codProduto != code) {
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
    if (getNextSale(aux) != NULL) {
        *sale = *getNextSale(aux);
    }

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

void persistSale(){
    FILE *file;

    file = fopen("sale.bin", "w+b");

    if (file == NULL) {
        return;
    }

    Sale* sale = getFirstSale();

    while (sale != NULL) {
        fwrite(sale, sizeof(Sale), 1, file);
        sale = getNextSale(sale);
    }

    fclose(file);
}

void loadSale(){
    FILE *file;

    file = fopen("sale.bin", "rb");

    if (file == NULL) {
        return;
    }

    freeSale();
    Sale* sale = getFirstSale();

    while(1){
        Sale* read = (Sale*) malloc(sizeof(Sale));

        size_t r = fread(read, sizeof(Sale), 1, file);

        if (r < 1) {
            break;
        } else {
            if (sale == NULL) {
                sale = (Sale*) malloc(sizeof(Sale));
                sale->codProduto = 0;
                sale->prox = NULL;
            }
            if (sale->codProduto == 0) {
                read->prox = NULL;
                *sale = *read;
            } else {
                read->prox = NULL;
                sale->prox = read;
            }

            sale = getNextSale(sale);
        }
    }

    fclose(file);
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
        if (getNextCard(card) == NULL) {
            return card;
        }
        card = getNextCard(card);
    }
}

Card* getCardByCode(int code){
    Card* card = getFirstCard();

    if (card == NULL || card->codVenda == 0) {
        return;
    }

    while (card != NULL && card->codVenda != code) {
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
    if (getNextCard(aux) != NULL) {
        *card = *getNextCard(aux);
    }

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

void persistCard(){
    FILE *file;

    file = fopen("card.bin", "w+b");

    if (file == NULL) {
        return;
    }

    Card* card = getFirstCard();

    while (card != NULL) {
        fwrite(card, sizeof(Card), 1, file);
        card = getNextCard(card);
    }

    fclose(file);
}

void loadCard(){
    FILE *file;

    file = fopen("card.bin", "rb");

    if (file == NULL) {
        return;
    }

    freeCard();
    Card* card = getFirstCard();

    while(1){
        Card* read = (Card*) malloc(sizeof(Card));

        size_t r = fread(read, sizeof(Card), 1, file);

        if (r < 1) {
            break;
        } else {
            if (card == NULL) {
                card = (Card*) malloc(sizeof(Card));
                card->codVenda = 0;
                card->prox = NULL;
            }
            if (card->codVenda == 0) {
                read->prox = NULL;
                *card = *read;
            } else {
                read->prox = NULL;
                card->prox = read;
            }

            card = getNextCard(card);

        }
    }

    fclose(file);
}

void freeCard(){
    free(cards);
}
