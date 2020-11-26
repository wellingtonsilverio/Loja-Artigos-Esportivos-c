/*
  Matheus Eduardo da Silva  RA:230719
  Caio Pereira Masseu       RA:256341
  Wellington A. A. Silverio RA:178667
*/

//bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"

//funcoes
//CRIAR/CADASTRAR  ITENS:
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

//criaListaVendas: ao adicionar um novo carrinho, o mesmo usa seu ponteiro para criar uma lista de compras do mesmo.
void criaListaVendas(vendas **iniVendas){
  *iniVendas = (vendas *)malloc(sizeof(vendas));

  (*iniVendas)->codProduto = 0;
  (*iniVendas)->prox = NULL;
}

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

//cadastrarEstoque: recebe a lista do estoque e cadastra um novo produto.
void cadastrarEstoque(estoque **lista, int codigoProduto){
  estoque *novo = (estoque *)malloc(sizeof(estoque));

  if (novo == 0){
    printf("Erro de alocacao!!!\n");
  }else{
    setbuf(stdin, NULL);
    printf("\tNome: ");
    fgets(novo->nome, 101, stdin);
    novo->nome[strlen(novo->nome) - 1] = '\0';
    novo->codigo = codigoProduto;
    printf("\tValor(R$): ");
    scanf("%f", &novo->valor);
    printf("\tQuantidade: ");
    scanf("%d", &novo->qtd);
    novo->prox = NULL;
    if ((*lista)->codigo == 0){
      strcpy((*lista)->nome, novo->nome);
      (*lista)->codigo = novo->codigo;
      (*lista)->valor = novo->valor;
      (*lista)->qtd = novo->qtd;
    }else{
      pegarUltimoEstoque(lista)->prox = novo;
    }
    printf("\n\tPRODUTO CADASTRADO COM SUCESSO NO ESTOQUE!\n\n");
  }
}

//cadastrarVendas: recebe a lista de vendas e adiciona uma nova venda a mesma.
void cadastrarVendas(vendas **lista, estoque **listaStock, int codProduto, int quantidade){
  vendas *novo = (vendas *)malloc(sizeof(vendas));
  estoque *p = (*listaStock);

  if (novo == 0){
    printf("\tErro de alocacao!!!\n");
  }else{
    novo->codProduto = codProduto;
    novo->valor = recebeValor(&p, codProduto);
    novo->qtd = quantidade;
    novo->prox = NULL;
    if ((*lista)->codProduto == 0){
      (*lista)->codProduto = novo->codProduto;
      (*lista)->valor = novo->valor;
      (*lista)->qtd = novo->qtd;
      free(novo);
    }else{
      pegarUltimaVenda(lista)->prox = novo;
    }
  }
  printf("\tVENDA ADICIONADA COM SUCESSO!\n\n");
}

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

//MODIFICAR/VENDAS:
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

//modificarEstoque: recebe a lista de estoque e altera seu cadastro.
void modificarEstoque(estoque **lista, int codigo){
  estoque *p = (*lista);
  int find = 0;

  while (p != NULL){
    if (p->codigo == codigo){
      find = 1;
      printf("\tPRODUTO ENCONTRADO! - Alterar cadastro\n");
      setbuf(stdin, NULL);
      printf("\tNome: ");
      fgets(p->nome, 101, stdin);
      p->nome[strlen(p->nome) - 1] = '\0';
      printf("\tCodigo: ");
      scanf("%d", &p->codigo);
      printf("\tValor(R$): ");
      scanf("%f", &p->valor);
      printf("\tQuantidade: ");
      scanf("%d", &p->qtd);

      printf("\tEstoque - alteracao\n");
      printf("\t");
      puts(p->nome);
      printf("\tCodigo - %d\n", p->codigo);
      printf("\tValor(R$) - %.2f\n", p->valor);
      printf("\tQuantidade - %d\n", p->qtd);
      printf("-------------------------------------------------\n");
    }
    p = p->prox;
  }
  if (find == 0){
    printf("\tERRO - Estoque nao encontrado!!!\n");
  }
}

//excluirCliente: recebe o cliente a ser removido e remove da lista.
void excluirCliente(cliente *item){
  cliente *morta = (cliente*) malloc(sizeof(cliente));

  morta = item;
  item = morta->prox;
  free(morta);
}

//excluirEstoque: recebe o produto a ser removido e remove da lista.
void excluirEstoque(estoque *item){
  estoque *morta = (estoque*)malloc(sizeof(estoque));

  morta = item;
  item = morta->prox;
  free(morta);
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

//recebeValor: usado para fazer a recepcao/devolucao do valor.
float recebeValor(estoque **lista, int codProduto){
  estoque *p = (*lista);
  float valor;

  while (p != NULL){
    if (p->codigo == codProduto){
      valor = p->valor;
    }
    p = p->prox;
  }
  return valor;
}

//trocaItem: recebe as listas de carrinho e estoque, junto com o codigo do carrinho e do produto a ser ressarcido, atualiza o estoque e modifica a venda para "troca"(-1).
void trocaItem(carrinho **lista, estoque **listaStock, int codSale, int codProduto){
  carrinho *p = (*lista);
  estoque *q = (*listaStock);
  vendas *r = (p->lista);
  
  int qtdRessarcida;
  int find = 0;

  while (p != NULL){
    if (p->codVenda == codSale){
      while (r!= NULL){
        if (r->codProduto == codProduto){
          r->valor = -1;
          qtdRessarcida = r->qtd;
          find = 1;
        }
        r = r->prox;
      }
    }
    p = p->prox;
  }

  while (q != NULL){
    if (q->codigo == codProduto){
      q->qtd += qtdRessarcida;
    }
    q = q->prox;
  }

  if (find == 0){
    printf("\tERRO - Nao foi possivel realizar a troca\n");
  }
}

//checkEstoque: recebe o codigo do produto e a quantidade desejada, caso seja possivel, atualiza o estoque e retorna 1, e retorna 0 caso contrario.
int checkEstoque(estoque **lista, int codProduto, int quantidade){
  estoque *p = (*lista);
  int check = 0;

  while (p != NULL){
    if (p->codigo == codProduto && p->qtd >= quantidade){
      check = 1;
      p->qtd -= quantidade;
    }
    p = p->prox;
  }
  return check;
}

//BUSCA E AFINS:
//pegarUltimoCliente: recebe a lista de clientes e retorna o ultimo.
cliente *pegarUltimoCliente(cliente **lista){
  cliente *p = (*lista);

  while (p->prox != NULL){
    p = p->prox;
  }
  return p;
}

//pegarUltimoEstoque: recebe a lista de estoque e retorna o ultimo.
estoque *pegarUltimoEstoque(estoque **lista){
  estoque *p = (*lista);

  while (p->prox != NULL){
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

//procuraEstoque: verifica se o produto existe ou nao no estoque. retorna 1 se positivo e 0 caso negativo.
int procuraEstoque(estoque **lista, int codigo){
  estoque *p = (*lista);
  int find = 0;

  while (p != NULL){
    if (p->codigo == codigo){
      find = 1;
    }
    p = p->prox;
  }
  return find;
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

//pegarEstoque: recebe a lista de estoque e o codigo e retorna o cliente desejado.
estoque *pegarEstoque(estoque **lista, int codigo){
  estoque *p = (*lista);

  while (p != NULL){
    if (p->codigo == codigo){
      return p;
    }
    p = p->prox;
  }
}

//IMPRIMIR ITENS:
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

//imprimeEstoque: recebe a lista de estoque e imprime(JEITO DE ARRUMAR A ULTIMA IMPRESSAO SEM GAMBIARRA).
void imprimeEstoque(estoque **lista){
  estoque *p = (*lista);

  printf("\n\tESTOQUE\n");
  printf("\n\tCOD.PRODUTO     NOME       QTD      VALOR");
  printf("\n\t-------------------------------------------------");
  while (p != NULL){
    printf("\n\t#%-10d     %-6s     %3d      R$%.2f", p->codigo, p->nome, p->qtd, p->valor);
    p = p->prox;
  }
  printf("\n\t-------------------------------------------------\n");
}

//imprimeVendas: recebe a lista de vendas e imprime ela.
void imprimeVendas(vendas **lista, estoque **iniStock){
  vendas *p = (*lista);
  estoque *q = (*iniStock);

  while (p->prox != NULL){
    printf("\n\n\tCOD. PRODUTO      QTD     VALOR");
    printf("\n\t%d", p->codProduto);
    if (p->valor == -1){
      printf("\t%d\t Troca\n", p->qtd);
    }else{
      printf("\t\t%d\t  R$ %.2f\n", p->qtd, p->valor);
    }
    printf("\t--------------------------------------------------------------------\n");
    p = p->prox;
  }
    printf("\n\n\tCOD. PRODUTO      QTD     VALOR");
    printf("\n\t%d", p->codProduto);
    if (p->valor == -1){
      printf("\t%d\t Troca\n", p->qtd);
    }else{
      printf("\t\t%d \t  R$ %.2f\n", p->qtd, p->valor);
    }
    printf("\t--------------------------------------------------------------------\n");
    p = p->prox;
}

//imprimeCarrinhos: recebe a lista de carrinhos de compras e imprime ela.
void imprimeCarrinhos(carrinho **lista, estoque **iniStock){
  carrinho *p = (*lista);
  estoque *q = (*iniStock);

  printf("\n\tVENDAS\n");
  if(p->codVenda !=0){
  	 while (p->prox!= NULL){
     	printf("\n\t--------------------------------------------------------------------");
     	printf("\n\tCOD.VENDA       CPF");
     	printf("\n\t#%-10d    %d", p->codVenda, p->CPF);
     	imprimeVendas(&p->lista, &q);
     	printf("\tPagamento: ");
     	if (p->pagamento == 1){
      		printf("DEBITO\n");
     	}else{
      		printf("CREDITO\n");
     	}
     	p = p->prox;
     }
	 printf("\n\t--------------------------------------------------------------------");
     printf("\n\tCOD.VENDA       CPF");
     printf("\n\t#%-10d    %d", p->codVenda, p->CPF);
     imprimeVendas(&p->lista, &q);
     printf("\tPagamento: ");
     if (p->pagamento == 1){
       printf("DEBITO\n");
     }else{
       printf("CREDITO\n");
     } 
  }
 
}

//LOOPS/MENUS:
//pressioneZero: recebe como entrada um int, caso 0, ele limpa a tela.
void pressioneZero(){
  int botao = 1;

  while (botao != 0){
    printf("\tPressione 0 para voltar ao menu: ");
    scanf("%d", &botao);
  }
  system("cls");
}


