#include <stdio.h>
#include <stdlib.h>
#include "sales.h"
#include "stock.h"

Sale *sales;
Card *cards;

//createSale: recebe os dados da venda nova, e a adiciona a lista de vendas.
void createSale(int code, int cardCode, float price, int amount) {
    Sale* lastSale = getLastSale();

    if (lastSale->codProduto == 0) {
        lastSale->codProduto = code;
        lastSale->codVenda = cardCode;
        lastSale->valor = price;
        lastSale->qtd = amount;
        lastSale->prox = NULL;

        return;
    }

    Sale* child = (Sale*) malloc(sizeof(Sale));

    child->codProduto = code;
    child->codVenda = cardCode;
    child->valor = price;
    child->qtd = amount;
    child->prox = NULL;

    lastSale->prox = child;

    return;
}

//getFirstSale: retorna o primeiro item da lista.
Sale* getFirstSale() {
    if (sales == NULL) {
        sales = (Sale*) malloc(sizeof(Sale));
        sales->codProduto = 0;
        sales->prox = NULL;
    }

    return sales;
}

//getNextSale: retorna o proximo item da lista.
Sale* getNextSale(Sale* sale){
    if (sale == NULL) {
        return sale;
    }

    return sale->prox;
}

//getLastSale: retorna o ultimo item da lista.
Sale* getLastSale(){
    Sale* sale = getFirstSale();
    while (1) {
        if (getNextSale(sale) == NULL) {
            return sale;
        }
        sale = getNextSale(sale);
    }
}

//getSaleByCode: recebe o codigo da venda desejada, procura e retorna o mesmo.
Sale* getSaleByCode(int code){
    Sale* sale = getFirstSale();

    if (sale == NULL || sale->codProduto == 0) {
        return;
    }

    while (sale != NULL && sale->codProduto != code) {
        sale = getNextSale(sale);
    }

    return sale;
}

//getFirstSaleByCardCode: recebe o codigo da estoque desejada, procura e retorna o primeiro.
Sale* getFirstSaleByCardCode(int cardCode) {
    Sale* sale = getFirstSale();

    if (sale == NULL || sale->codProduto == 0) {
        return;
    }

    while (sale != NULL && sale->codVenda != cardCode) {
        sale = getNextSale(sale);
    }

    return sale;
}

//getSpecificSaleByCode: recebe a venda e o codigo, procura e retorna o item desejado.
Sale* getSpecificSaleByCode(Sale* sale, int code){
    if (sale == NULL || sale->codProduto == 0) {
        return;
    }

    while (sale->codProduto != code) {
        sale = sale->prox;
    }

    return sale;
}

//updateSaleByCode: recebe os dados da venda a ser atualizada, e modifica o mesmo na lista.
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

//deleteSaleByCode: recebe o codigo do item a ser excluido, o procura e remove da lista.
void deleteSaleByCode(int code){
    Sale* sale = getSaleByCode(code);
    Sale* aux = (Sale*) malloc(sizeof(Sale));

    *aux = *sale;
    if (getNextSale(aux) != NULL) {
        *sale = *getNextSale(aux);
    }

    free(aux);
}

//printSale: imprime a lista de vendas.
void printSale(Sale* sale) {
    if (sale == NULL) {
        return;
    }

    int codeCard = sale->codVenda;

    printf("\n\tCOD.Produto       VALOR       QUANTIDADE");
    while (sale != NULL && sale->codVenda == codeCard) {
        if (sale->valor > 0) {
            printf("\n\t#%-13d    %.2f    %8d\n", sale->codProduto, sale->valor, sale->qtd);
        } else {
            printf("\n\t#%-10d    TROCA    %d\n", sale->codProduto, sale->qtd);
        }
        sale = getNextSale(sale);
    }
}

//persistSale: salva os dados registrados no sistema em um arquivo.
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

//loadSale: carrega os dados existentes no arquivo.
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
                sale = getNextSale(sale);
            }
        }
    }

    fclose(file);
}

//freeSale: libera a memoria de vendas
void freeSale(){
    free(sales);
}

//createCard: recebe as informacoes para cadastro de uma venda e adiciona uma novo carrinho a lista de carrinhos.
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
    } else {
        child->codVenda = code;
        child->CPF = CPF;
        child->pagamento = paymentType;
        child->sales = sales;
        child->prox = NULL;

        lastCard->prox = child;
    }

    while (sales != NULL) {
        stock = getStockByCode(sales->codProduto);
        stock->qtd -= sales->qtd;

        sales = sales->prox;
    }

    return;
}

//getFirstCard: retorna o primeiro item da lista de vendas.
Card* getFirstCard() {
    if (cards == NULL) {
        cards = (Card*) malloc(sizeof(Card));
        cards->codVenda = 0;
        cards->prox = NULL;
    }

    return cards;
}

//getNextCard: retorna o proximo carrinho na lista.
Card* getNextCard(Card* card){
    if (card == NULL) {
        card = (Card*) malloc(sizeof(Card));

        return card;
    }

    return card->prox;
}

//getLastCard: retorna o ultimo carrinho.
Card* getLastCard(){
    Card* card = getFirstCard();
    while (1) {
        if (getNextCard(card) == NULL) {
            return card;
        }
        card = getNextCard(card);
    }
}

//getCardByCode: recebe o codigo do carrinho a ser procurado e retorna o mesmo. 
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

//updateCardByCode: recebe os dados para a atualizacao do carrinho, e o modifica.
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

//deleteCardByCode: recebe o codigo do carrinho a ser excluido, o encontra e exclui o mesmo.
void deleteCardByCode(int code){
    Card* card = getCardByCode(code);
    Card* aux = (Card*) malloc(sizeof(Card));

    *aux = *card;
    if (getNextCard(aux) != NULL) {
        *card = *getNextCard(aux);
    }

    free(aux);
}

//printCards: imprime a lista de carrinhos.
void printCards(){
    Card* card = getFirstCard();

    while (card != NULL) {
        printf("\n\t--------------------------------------------------------------------");
        printf("\n\tCOD.VENDA       CPF");
        printf("\n\t#%-10d      %d\n", card->codVenda, card->CPF);
        printSale(card->sales);
        printf("\n\tForma de Pagamento: ");
        if (card->pagamento == 1){
      		printf("DEBITO\n");
     	}else{
      		printf("CREDITO\n");
     	}
        printf("\t--------------------------------------------------------------------\n");
        card = getNextCard(card);
    }
}

//persistCard: salva os dados do sistema em um arquivo.
void persistCard(){
    FILE *file;

    file = fopen("card.bin", "w+b");

    if (file == NULL) {
        return;
    }

    Card* card = getFirstCard();

    while (card != NULL) {
        card->sales = NULL;
        fwrite(card, sizeof(Card), 1, file);
        card = getNextCard(card);
    }

    fclose(file);
}

//loadCard: carrega os dados do arquivo no sistema.
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
                card = getNextCard(card);
            }

            card->sales = getFirstSaleByCardCode(card->codVenda);

        }
    }

    fclose(file);
}

//freeCard: libera a memoria.
void freeCard(){
    free(cards);
}
