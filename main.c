/*
  Matheus Eduardo da Silva  RA:230719
  Caio Pereira Masseu       RA:256341
  Wellington A. A. Silverio RA:178667
*/

#include <stdlib.h>
#include "main.h"
#include "menu.h"

Client *clients;
estoque *stocks;
carrinho *carts;
venda *sales;

int main()
{
	criarListas();

	menu(&clients, &stocks, &carts);

	return 0;
}

//criaListas: cria as listas existente no software usando os ponteiros de ponteiros recebidos na entrada(CPF, codigo e cod de venda comecam com 0).
void criarListas(){
  clients = (Client *)malloc(sizeof(Client));
  stocks = (estoque *)malloc(sizeof(estoque));
  carts = (carrinho *)malloc(sizeof(carrinho));
  sales = (venda *)malloc(sizeof(venda));

  (clients)->CPF = 0;
  (clients)->prox = NULL;
  (stocks)->codigo = 0;
  (stocks)->prox = NULL;
  (carts)->codVenda = 0;
  (carts)->prox = NULL;
  (sales)->codProduto = 0;
  (sales)->prox = NULL;
}
