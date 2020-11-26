#ifndef REGISTRO_H
#define REGISTRO_H

//structs(todas possuem base em "listas ligadas" - possuem um ponteiro para o prox item da lista).
typedef struct client{
  char nome[100];
  int CPF;
  int fone;
  char email[100];
  struct client *prox;
} cliente;

typedef struct stock{
  char nome[100];
  int codigo;
  float valor;
  int qtd;
  struct stock *prox;
} estoque;

typedef struct sales{
  int codProduto;
  float valor;
  int qtd;
  struct sales *prox;
} vendas;

typedef struct cart{
  vendas *lista;
  int codVenda;
  int CPF;
  int pagamento;
  struct cart *prox;
} carrinho;

//prototipos de funcoes
//criar itens:
void criarListas(cliente **, estoque **, carrinho **);
void cadastrarCliente(cliente **, int);
void cadastrarEstoque(estoque **, int);
void cadastrarVendas(vendas **, estoque **, int, int);
int cadastrarCarrinho(carrinho **);

//modificar/vendas:
void modificarCliente(cliente **, int);
void modificarEstoque(estoque **, int);
void excluirCliente(cliente *);
void excluirEstoque(estoque *);
void excluirCarrinho(carrinho **);
void formaPagamento(carrinho **, int);
int checkEstoque(estoque **, int, int);
float recebeValor(estoque **, int);
void trocaItem(carrinho **, estoque **, int, int);

//busca e afins:
cliente *pegarUltimoCliente(cliente **);
estoque *pegarUltimoEstoque(estoque **);
vendas *pegarUltimaVenda(vendas **);
carrinho *pegarUltimoCarrinho(carrinho **);
carrinho *pegarUltimoCarrinho2(carrinho **, int codVenda);
int procuraCliente(cliente **, int);
int procuraEstoque(estoque **, int);
int procuraCarrinho(carrinho **, int, int);
cliente *pegarCliente(cliente **, int);
estoque *pegarEstoque(estoque **, int);

//imprimir itens:
void imprimeListaClientes(cliente **);
void imprimeEstoque(estoque **);
void imprimeVendas(vendas **, estoque **);
void imprimeCarrinhos(carrinho **, estoque **);

//loops/menus:
void pressioneZero();

#endif
