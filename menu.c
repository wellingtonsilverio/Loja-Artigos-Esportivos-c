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
	int loopVendas = 1, pagamento, opcao, codVenda, qtdVenda;
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

	switch (menuOpcao){
	case 1:
		printf("\n\tCADASTRAR PRODUTO:\n");
		printf("\n\tDigite o codigo do produto: ");
		scanf("%d", &codigoProduto);
		if (getStockByCode(codigoProduto) != NULL) {
			printf("\n\tERRO! - codigo ja cadastrado!\n");
		} else {
			createStock(codigoProduto, getString("\tNome: "), getFloat("\tPreco: "), getInt("\tQuantidade: "));
		}
		break;
	case 2:
		printf("\n\tCADASTRAR CLIENTE:\n");
		printf("\n\tDigite o CPF do novo cliente: ");
		scanf("%d", &cpf);
		if (getClientByCPF(cpf) != NULL) {
			printf("\n\tERRO! - CPF ja cadastrado!\n");
		} else {
			createClient(getString("\tNome: "), cpf, getInt("\tTelefone: "), getString("\tE-mail: "));
		}
		break;
	case 3:
		printf("\n\tCADASTRAR VENDA:\n\n");
		cpf = getInt("\tCPF: ");
		Client* client = getClientByCPF(cpf);
		if (client != NULL && client->CPF == cpf) {
			codVenda = getInt("\tCodigo de venda: ");
			if (getCardByCode(codVenda) == NULL) {
				loopVendas = 1;
				qtdVenda = 0;
				do {
				    printf("\tInforme o codigo do produto: ");
				    scanf("%d", &codigoProduto);
				    printf("\tInforme a quantidade: ");
				    scanf("%d", &quantidade);
				    Stock* product = getStockByCode(codigoProduto);
				    if (product != NULL && product->active == 1 && product->qtd >= quantidade) {
					createSale(codigoProduto, codVenda, product->valor * quantidade, quantidade);
					qtdVenda++;
					loopVendas = getInt("\tDeseja adicionar um novo item?(0-NAO / 1-SIM): ");
				    } else {
					printf("\n\tProduto nao existe, nao tem a quantidade ou esta fora de estoque!\n");
					loopVendas = getInt("\tDeseja continuar comprando?(0-NAO / 1-SIM): ");
					if (loopVendas == 0) {
					    break;
					}
				    }
				} while (loopVendas == 1);

				if (qtdVenda > 0) {
					createCard(codVenda, cpf, getInt("\tForma de pagamento(0-CREDITO / 1-DEBITO): "), getFirstSaleByCardCode(codVenda));
		   			printf("\n\tVENDA REGISTRADA COM SUCESSO!\n");
				} else {
					printf("\tVenda finalizada!\n");
				}
		    	}
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
		if (card != NULL){
			refound(codigoVenda, codigoProduto);
			printf("\n\tTROCA EFETUADA COM SUCESSO!\n");
		}else{
			printf("\n\tERRO! - Venda nao encontrada!\n");
		}
		break;
	case 5:
		printf("\n\t1.Alterar dados do cliente\n");
		printf("\t2.Alterar dados do produto\n");
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
			if (getClientByCPF(cpf) != NULL){
                printf("\n\tCLIENTE ENCONTRADO! - INSIRA OS NOVOS DADOS:\n");
				updateClientByCPF(cpf, getString("\tNome: "), getInt("\tTelefone: "), getString("\n\tE-mail: "));
			}else{
				printf("\n\tERRO! - CPF nao encontrado!\n");
			}
			break;
		case 2:
			printf("\n\tALTERAR PRODUTO:\n");
			printf("\n\tDigite o codigo do produto: ");
			scanf("%d", &codigoProduto);

			if (getStockByCode(codigoProduto) != NULL) {
                printf("\n\tPRODUTO ENCONTRADO! - INSIRA OS NOVOS DADOS:\n");
                updateStockByCode(codigoProduto, getString("\tNome: "), getFloat("\tValor(R$): "), getInt("\n\tQuantidade: "));
			} else {
                printf("\n\tERRO - Estoque nao encontrado!!!\n");
			}
			break;
		case 3:
			printf("\n\tEXCLUIR CLIENTE:\n");
			printf("\n\tDigite o CPF do cliente: ");
			scanf("%d", &cpf);
			if (getClientByCPF(cpf) != NULL){
                printf("\n\tCLIENTE ENCONTRADO!\n");
				printf("\tVoce tem certeza?(1-SIM / 0-NAO): ");
				scanf("%d", &opcao);
				if (opcao == 1){
					deleteClientByCPF(cpf);
					printf("\n\tCLIENTE EXCLUIDO COM SUCESSO!\n");
				}
			}else{
				printf("\n\tERRO! - CPF nao encontrado!\n");
			}
			break;
		case 4:
			printf("\n\tEXCLUIR PRODUTO:\n");
			printf("\n\tDigite o codigo do produto: ");
			scanf("%d", &codigoProduto);
			if (getStockByCode(codigoProduto) != NULL){
                printf("\n\tPRODUTO ENCONTRADO!\n");
				printf("\tVoce tem certeza?(1-SIM / 0-NAO): ");
				scanf("%d", &opcao);
				if (opcao == 1)
				{
					deleteStockByCode(codigoProduto);
					printf("\n\tITEM EXCLUIDO COM SUCESSO !\n");
				}
			}
			else
			{
				printf("\n\tERRO! - Codigo nao encontrado!\n");
			}
			break;
		default:
			printf("\n\tERRO! - opcao invalida\n");
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
        printf("\n\tOS DADOS FORAM SALVOS COM SUCESSO !\n\n");
		break;
	case 9:
		loadAll();
		printf("\n\tOS DADOS FORAM CARREGADOS COM SUCESSO !\n\n");
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
    printf("\n\tPressione 0 para voltar ao menu: ");
    scanf("%d", &botao);
  }
  system("cls");
}
