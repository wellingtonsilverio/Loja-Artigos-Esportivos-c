/*
  Matheus Eduardo da Silva  RA:230719
  Caio Pereira Masseu       RA:256341
  Wellington A. A. Silverio RA:178667
*/

#include <stdlib.h>
#include "main.h"
#include "menu.h"

cliente *iniCliente;
estoque *iniEstoque;
carrinho *iniCarrinho;

int main()
{
	criarListas(&iniCliente, &iniEstoque, &iniCarrinho);

	menu(&iniCliente, &iniEstoque, &iniCarrinho);

	return 0;
}

//criaListas: cria as listas existente no software usando os ponteiros de ponteiros recebidos na entrada(CPF, codigo e cod de venda comecam com 0).
void criarListas(cliente **iniCliente, estoque **iniEstoque, carrinho **iniCarrinho){
  *iniCliente = (cliente *)malloc(sizeof(cliente));
  *iniEstoque = (estoque *)malloc(sizeof(estoque));
  *iniCarrinho = (carrinho *)malloc(sizeof(carrinho));

  (*iniCliente)->CPF = 0;
  (*iniCliente)->prox = NULL;
  (*iniEstoque)->codigo = 0;
  (*iniEstoque)->prox = NULL;
  (*iniCarrinho)->codVenda = 0;
  (*iniCarrinho)->prox = NULL;
}
