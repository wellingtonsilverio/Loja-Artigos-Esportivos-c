#include <stdio.h>
#include "sales.h"
#include "stock.h"

//cadastrarVendas: recebe a lista de vendas e adiciona uma nova venda a mesma.
void cadastrarVendas(venda **lista, estoque **listaStock, int codProduto, int quantidade){
  venda *novo = (venda *)malloc(sizeof(venda));
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

//trocaItem: recebe as listas de carrinho e estoque, junto com o codigo do carrinho e do produto a ser ressarcido, atualiza o estoque e modifica a venda para "troca"(-1).
void trocaItem(carrinho **lista, estoque **listaStock, int codSale, int codProduto){
  carrinho *p = (*lista);
  estoque *q = (*listaStock);
  venda *r = (p->lista);

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

//imprimeVendas: recebe a lista de vendas e imprime ela.
void imprimeVendas(venda **lista, estoque **iniStock){
  venda *p = (*lista);
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
