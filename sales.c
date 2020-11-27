#include <stdio.h>
#include <stdlib.h>
#include "sales.h"

//cadastrarCarrinho: recebe a lista de carrinho de compras e adiciona um novo carrinho.
int cadastrarCarrinho(carrinho **listaCart){
  carrinho *novo = (carrinho *)malloc(sizeof(carrinho));

  if (novo == 0){
    printf("\tErro de alocacao!!!\n");
  }else{
    printf("\tCPF: ");
    scanf("%d", &novo->CPF);
    printf("\tCodigo de venda: ");
    scanf("%d", &novo->codVenda);
    novo->prox = NULL;
    if ((*listaCart)->codVenda == 0){
      criaListaVendas(&(*listaCart)->lista);
      (*listaCart)->codVenda = novo->codVenda;
      (*listaCart)->CPF = novo->CPF;
    }else{
      criaListaVendas(&novo->lista);
      pegarUltimoCarrinho(listaCart)->prox = novo;
    }
  }
  printf("\tCARRINHO DE COMPRAS CRIADO COM SUCESSO!\n\n");
  return novo->codVenda;
}

//excluirCarrinho: recebe o carrinho de compras a ser removido e remove da lista.
void excluirCarrinho(carrinho **item){
  carrinho *morta;

  morta = *item;
  *item = morta->prox;
  free(morta);
}

//formaPagamento: recebe o carrinho desejado e a forma de pagamento(0-1) e adiciona ao carrinho.
void formaPagamento(carrinho **item, int payment){
  carrinho *p = *item;

  p->pagamento = payment;
}

//pegarUltimoCarrinho: recebe a lista de carrinhos e retorna o ultimo.
carrinho *pegarUltimoCarrinho(carrinho **lista){
  carrinho *p = (*lista);

  while (p->prox != NULL){
    p = p->prox;
  }

  return p;
}
//pegarUltimoCarrinho2: recebe a lista de carrinhos e retorna o ultimo.
carrinho *pegarUltimoCarrinho2(carrinho **lista, int codVenda){
  carrinho *p = (*lista);

  while (p != NULL){
  	if (p->codVenda == codVenda) {
  		return p;
	}
    p = p->prox;
  }

  return p;
}

//pegarUltimaVenda: recebe a lista de carrinhos e retorna o ultimo.
vendas *pegarUltimaVenda(vendas **lista){
  vendas *p = (*lista);

  while (p->prox != NULL){
    p = p->prox;
  }
  return p;
}

//procuraCarrinho: verifica se o carrinho existe ou nao no estoque. retorna 1 se positivo e 0 caso negativo.
int procuraCarrinho(carrinho **lista, int cpf, int codSale){
  carrinho *p = (*lista);
  int find = 0;

  while (p != NULL){
    if (p->CPF == cpf && p->codVenda == codSale){
      find = 1;
    }
    p = p->prox;
  }
  return find;
}

//criaListaVendas: ao adicionar um novo carrinho, o mesmo usa seu ponteiro para criar uma lista de compras do mesmo.
void criaListaVendas(vendas **iniVendas){
  *iniVendas = (vendas *)malloc(sizeof(vendas));

  (*iniVendas)->codProduto = 0;
  (*iniVendas)->prox = NULL;
}
