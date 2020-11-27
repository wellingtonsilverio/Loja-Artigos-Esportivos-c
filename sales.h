#ifndef SALES_H
#define SALES_H

//structs(todas possuem base em "listas ligadas" - possuem um ponteiro para o prox item da lista).
typedef struct sale{
  int codProduto;
  float valor;
  int qtd;
  struct sale *prox;
} venda;

typedef struct cart{
  venda *lista;
  int codVenda;
  int CPF;
  int pagamento;
  struct cart *prox;
} carrinho;

venda *pegarUltimaVenda(venda **);

void excluirCarrinho(carrinho **);
void formaPagamento(carrinho **, int);
carrinho *pegarUltimoCarrinho(carrinho **);
carrinho *pegarUltimoCarrinho2(carrinho **, int codVenda);
int cadastrarCarrinho(carrinho **);
int procuraCarrinho(carrinho **, int, int);


#endif
