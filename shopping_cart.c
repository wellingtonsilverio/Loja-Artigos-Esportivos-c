#include <stdio.h>
#include "sales.h"
#include "stock.h"

void createShoppingCard(int saleCode, int amount){

}

void refound(int cardCode, int saleCode){
    Card* card = getCardByCode(cardCode);
    Sale* sale = getSpecificSaleByCode(card->sales, saleCode);
    Stock* stock = getStockByCode(sale->codProduto);

    if (sale != NULL) {
        sale->valor = -1;
        stock->qtd += sale->qtd;
    }
}
