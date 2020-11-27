#include <stdio.h>
#include "client.h"

//cadastrarCliente: recebe a lista de clientes, cadastra um cliente novo e adiciona a lista.
void cadastrarCliente(cliente **lista, int cpf){
  cliente *novo = (cliente *)malloc(sizeof(cliente));

  if (novo == 0){
    printf("\tErro de alocacao!!!\n");
  }else{
    setbuf(stdin, NULL);
    printf("\tNome: ");
    fgets(novo->nome, 101, stdin);
    novo->nome[strlen(novo->nome) - 1] = '\0';
    novo->CPF = cpf;
    printf("\tTelefone: ");
    scanf("%d", &novo->fone);
    printf("\tE-mail: ");
    setbuf(stdin, NULL);
    fgets(novo->email, 101, stdin);
    novo->email[strlen(novo->email) - 1] = '\0';
    novo->prox = NULL;
    if ((*lista)->CPF == 0){
      strcpy((*lista)->nome, novo->nome);
      (*lista)->CPF = novo->CPF;
      (*lista)->fone = novo->fone;
      strcpy((*lista)->email, novo->email);
    }else{
      pegarUltimoCliente(lista)->prox = novo;
    }
    printf("\n\tCLIENTE CADASTRADO COM SUCESSO!\n\n");
  }
}
//modificarCliente: recebe a lista de clientes e altera seu cadastro.
void modificarCliente(cliente **lista, int cpf){
  cliente *p = (*lista);
  int find = 0;

  while (p != NULL){
    if (p->CPF == cpf){
      find = 1;
      printf("\tCLIENTE ENCONTRADO! - Alterar cadastro\n");
      setbuf(stdin, NULL);
      printf("\tNome: ");
      fgets(p->nome, 101, stdin);
      p->nome[strlen(p->nome) - 1] = '\0';
      printf("\tCPF: ");
      scanf("%d", &p->CPF);
      printf("\tTelefone: ");
      scanf("%d", &p->fone);
      printf("\tE-mail: ");
      setbuf(stdin, NULL);
      fgets(p->email, 101, stdin);
      p->email[strlen(p->email) - 1] = '\0';

      printf("\n\tCliente - alteracao\n");
      printf("\t");
      puts(p->nome);
      printf("\tCpf - %d\n", p->CPF);
      printf("\tFone - %d\n", p->fone);
      printf("\tEmail - ");
      puts(p->email);
      printf("-------------------------------------------------\n");
    }
    p = p->prox;
  }
  if (find == 0){
    printf("\tERRO - Cliente nao encontrado!!!\n");
  }
}

//excluirCliente: recebe o cliente a ser removido e remove da lista.
void excluirCliente(cliente *item){
  cliente *morta = (cliente*) malloc(sizeof(cliente));

  morta = item;
  item = morta->prox;
  free(morta);
}

//pegarUltimoCliente: recebe a lista de clientes e retorna o ultimo.
cliente *pegarUltimoCliente(cliente **lista){
  cliente *p = (*lista);

  while (p->prox != NULL){
    p = p->prox;
  }
  return p;
}

//procuraCliente: verifica se o cliente existe ou n�o, recebe a lista e retorna 1 caso positivo e 0 caso negativo.
int procuraCliente(cliente **lista, int cpf){
  cliente *p = (*lista);
  int find = 0;

  while (p != NULL){
    if (p->CPF == cpf){
      find = 1;
    }
    p = p->prox;
  }
  return find;
}

//pegarCliente: recebe a lista de cliente e o cpf e retorna o cliente desejado.
cliente *pegarCliente(cliente **lista, int cpf){
  cliente *p = (*lista);

  while (p != NULL){
    if (p->CPF == cpf){
      return p;
    }
    p = p->prox;
  }
}

//imprimeListaCLientes: recebe a lista de clientes e imprime.
void imprimeListaClientes(cliente **lista){
  cliente *p = (*lista);

  while (p != NULL){
    printf("\tCliente - \n");
    puts(p->nome);
    printf("\tCpf - %d\n", p->CPF);
    printf("\tFone-%d\n", p->fone);
    printf("\tEmail - ");
    puts(p->email);
    printf("-------------------------------------------------\n");
    p = p->prox;
  }
}

