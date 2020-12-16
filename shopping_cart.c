#include <stdio.h>
#include "sales.h"
#include "stock.h"

//refund: recebe os dados do carrinho e realiza a troca(ressarcimento) do produto.
void refound(int cardCode, int saleCode){
    Card* card = getCardByCode(cardCode);
    Sale* sale = getSpecificSaleByCode(card->sales, saleCode);
    Stock* stock = getStockByCode(sale->codProduto);

    if (sale != NULL) {
        sale->valor = -1;
        stock->qtd += sale->qtd;
    }
}
