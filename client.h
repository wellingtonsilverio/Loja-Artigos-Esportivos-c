#ifndef CLIENT_H
#define CLIENT_H

//structs(todas possuem base em "listas ligadas" - possuem um ponteiro para o prox item da lista).
typedef struct client{
  char nome[100];
  int CPF;
  int fone;
  char email[100];
  struct client *prox;
} cliente;

void cadastrarCliente(cliente **, int);
void modificarCliente(cliente **, int);
void excluirCliente(cliente *);
cliente *pegarUltimoCliente(cliente **);
int procuraCliente(cliente **, int);
cliente *pegarCliente(cliente **, int);
void imprimeListaClientes(cliente **);

#endif
