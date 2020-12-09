#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "client.h"
#include "stock.h"
#include "sales.h"
#include "shopping_cart.h"
#include "getVariables.h"

//menu: menu interativo com o usuario.
void menu() {

	// Variaveis
	int cpf, cliente, estoque;
	int codigoProduto, quantidade, codigoVenda;
	int loopVendas = 1, pagamento, opcao, codVenda;
	int menuOpcao, submenu;

	printf("\n\tLoja de Artigos Esportivos\n\n");

	printf("\t1. Cadastrar produtos\n");
	printf("\t2. Cadastrar cliente\n");
	printf("\t3. Registrar venda\n");
	printf("\t4. Trocas\n");
	printf("\t5. Modificar registros\n");
	printf("\t6. Vendas\n");
	printf("\t7. Estoque\n");
	printf("\t8. Salvar dados\n");
	printf("\t9. Carregar dados\n");
	printf("\t0. Sair\n");
	printf("\n\tSelecione a opcao desejada: ");
	scanf("%d", &menuOpcao);

	switch (menuOpcao)
	{
	case 1:
		printf("\n\tCADASTRAR PRODUTO:\n");
		printf("\n\tDigite o codigo do produto: ");
		scanf("%d", &codigoProduto);
		if (getStockByCode(codigoProduto) != NULL) {
			printf("\tERRO! - codigo ja cadastrado!\n");
		} else {
			createStock(codigoProduto, getString("\tNome: "), getFloat("\tPreco: "), getInt("\tQuantidade: "));
		}
		break;
	case 2:
		printf("\n\tCADASTRAR CLIENTE:\n");
		printf("\n\tDigite o CPF do novo cliente: ");
		scanf("%d", &cpf);
		if (getClientByCPF(cpf) != NULL) {
			printf("\tERRO! - CPF ja cadastrado!\n");
		} else {
			createClient(getString("\tNome: "), cpf, getInt("\tTelefone: "), getString("\tE-mail: "));
		}
		break;
	case 3:
		printf("\n\tCADASTRAR VENDA:\n");
		cpf = getInt("\tCPF: ");
		if (getClientByCPF(cpf) != NULL) {
                codVenda = getInt("\tCodigo de venda: ");
            	if (getCardByCode(codVenda) == NULL) {
                loopVendas = 1;

                do {
                    printf("\tInforme o codigo do produto: ");
                    scanf("%d", &codigoProduto);
                    printf("\tInforme a quantidade: ");
                    scanf("%d", &quantidade);
                    Stock* product = getStockByCode(codigoProduto);
                    if (product != NULL && product->qtd >= quantidade) {
                        createSale(codigoProduto, codVenda, product->valor * quantidade, quantidade);

                        loopVendas = getInt("\tDeseja adicionar um novo item?(1-sim, 0-nao): ");
                    } else {
                        printf("\n\tProduto nao existe ou esta fora de estoque!\n");
                    }
                } while (loopVendas == 1);

                createCard(codVenda, cpf, getInt("\tForma de pagamento(0-credito, 1-debito): "), getFirstSaleByCardCode(codVenda));
            }
            printf("\tPAGAMENTO EFETUADO COM SUCESSO!\n");
		} else {
		    printf("\tCPF nao cadastrado!\n");
		}



		break;
	case 4:
		printf("\n\tTROCAR PRODUTO:\n");
		printf("\n\tInforme o codigo da venda: ");
		scanf("%d", &codigoVenda);
		printf("\tInforme o codigo do produto: ");
		scanf("%d", &codigoProduto);
		Card* card = getCardByCode(codigoVenda);
		if (card != NULL)
		{
			refound(codigoVenda, codigoProduto);
			printf("\tProduto trocado com sucesso!!\n");
		}
		else
		{
			printf("\tERRO! - carrinho nao encontrado!\n");
		}
		break;
	case 5:
		printf("\n\t1.Alterar dados cliente\n");
		printf("\t2.Alterar dados produto\n");
		printf("\t3.Excluir cliente\n");
		printf("\t4.Excluir produto\n");
		printf("\n\tSeleciona a opcao desejada: ");
		scanf("%d", &submenu);
		switch (submenu)
		{
		case 1:
			printf("\n\tALTERAR CLIENTE:\n");
			printf("\n\tDigite o CPF do cliente: ");
			scanf("%d", &cpf);
			if (getClientByCPF(cpf) != NULL)
			{
				updateClientByCPF(cpf, getString("\tNome: "), getInt("\tTelefone: "), getString("\tE-mail: "));
			}
			else
			{
				printf("\tERRO! - CPF nao encontrado!\n");
			}
			break;
		case 2:
			printf("\n\tALTERAR PRODUTO:\n");
			printf("\n\tDigite o codigo do produto: ");
			scanf("%d", &codigoProduto);

			if (getStockByCode(codigoProduto) != NULL) {
                printf("\tPRODUTO ENCONTRADO! - Alterar cadastro\n");

                updateStockByCode(codigoProduto, getString("\tNome: "), getFloat("\tValor(R$): "), getInt("\tQuantidade: "));

                printf("\tEstoque - alteracao\n");
			} else {
                printf("\tERRO - Estoque nao encontrado!!!\n");
			}
			break;
		case 3:
			printf("\n\tEXCLUIR CLIENTE:\n");
			printf("\n\tDigite o CPF do cliente: ");
			scanf("%d", &cpf);
			if (getClientByCPF(cpf) != NULL){
				printf("\tVoce tem certeza?(1-Sim, 0-Nao): ");
				scanf("%d", &opcao);
				if (opcao == 1){
					deleteClientByCPF(cpf);
					printf("\tCLIENTE EXCLUIDO COM SUCESSO!!!\n");
				}
			}else{
				printf("\tERRO! - nao foi possivel encontrar o CPF!\n");
			}
			break;
		case 4:
			printf("\n\tEXCLUIR PRODUTO:\n");
			printf("\n\tDigite o codigo do produto: ");
			scanf("%d", &codigoProduto);
			if (getStockByCode(codigoProduto) != NULL)
			{
				printf("\tVoce tem certeza?(1-Sim, 0-Nao): ");
				scanf("%d", &opcao);
				if (opcao == 1)
				{
					deleteStockByCode(codigoProduto);
					printf("\tITEM EXCLUIDO COM SUCESSO !\n");
				}
			}
			else
			{
				printf("\tERRO! - nao foi possivel encontrar o Codigo do produto!\n");
			}
			break;
		default:
			printf("\tERRO! - opcao invalida\n");
		}
		break;
	case 6:
		printCards();
		break;
	case 7:
		printStock();
		break;
	case 8:
		saveAll();
		/* AQUI ACHO QUE CABE UM IF (DEU CERTO) IMPRIME MENSAGEM DE CONFIRMAÇÃO, ELSE MENSAGEM DE ERRO DEIXEI A ESTRUTURA
		MAS N SEI O QUE COLOCAR NA VERIFICAÇÃO
        /* if(){
		printf("\n\tOS DADOS FORAM SALVOS COM SUCESSO !\n\n");
        }else{
            printf("\n\tErro - OS DADOS NAO FORAM SALVOS!\n\n");
        } */
		break;
	case 9:
		loadAll();
		 /* AQUI TBM if(){
		printf("\n\tOS DADOS FORAM CARREGADOS COM SUCESSO !\n\n");
        }else{
            printf("\n\tErro - OS DADOS NAO FORAM CARREGADOS!\n\n");
        }
        */
		break;
	case 0:
		printf("\n\tObrigado por usar o Sistema - Loja de Artigos Esportivos\n");
		break;
	default:
		printf("\n\tERRO! - Opcao invalida\n");
		}

	if (menuOpcao != 0)
	{
		pressioneZero();
		menu();

		return;
	}

	freeSale();
	freeCard();
	freeStock();
	freeClient();
}

void pressioneZero(){
  int botao = 1;

  while (botao != 0){
    printf("\tPressione 0 para voltar ao menu: ");
    scanf("%d", &botao);
  }
  system("cls");
}
