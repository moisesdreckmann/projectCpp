#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loja.h"


void criaLista(LISTA *lt) {
	lt->inicio = NULL;
	lt->fim = NULL;
	lt->n = 0;
} 

int incluiNoFim(LISTA *lt, DADO d) {
	Nodo *pNodo;
	pNodo = (Nodo *) malloc(sizeof(Nodo));
	if(pNodo == NULL) {
		return FALTOU_MEMORIA;
	} else {
		pNodo->info = d;
		pNodo->prox = NULL;
		pNodo->ant = lt->fim;
		if(lt->n == 0) {
			lt->inicio = pNodo;	
		} else {
			lt->fim->prox = pNodo;
		}
		lt->fim = pNodo;
		lt->n++;
		return SUCESSO;
	}
}

float exibe(LISTA *lt) {
	float acumulador=0;
	if(lt->n == 0) {
		printf("a lista esta vazia\n");
	} else {
		Nodo *pAux = lt->inicio;
		printf("\nProdutos:\n");
		while(pAux != NULL) {
			printf("cod: %d     nome: %s     valor: %.2f\n", pAux->info.codigo, pAux->info.nome, pAux->info.valor);
			acumulador += pAux->info.valor;
			pAux = pAux->prox;
		}
		printf("\ntotal da compra: %.2f\n", acumulador);
	}
	return acumulador;
}

int excluirNodo(LISTA *lt, DADO *dadoExcluido, int codigo) {
	if(lt->n == 0) {
		return LISTA_VAZIA;
	} else {
		Nodo *pAux = lt->inicio;
		char operador = 'n';
		while(pAux != NULL) {
			if(codigo == pAux->info.codigo) {
				*dadoExcluido = pAux->info;
				do {
					printf("tem certeza que deseja excluir %d %s (y.yes n.no)?", pAux->info.codigo, pAux->info.nome);
					scanf(" %c", &operador);
				} while(operador != 'n' && operador != 'y' && operador != 'Y' && operador != 'N');
				if(operador == 'n' || operador == 'N') {
					break;
				} else {
					if(lt->n == 1) {
					lt->inicio = NULL;
					lt->fim = NULL;
					} else if(pAux == lt->inicio) {
						pAux->prox->ant = NULL;
						lt->inicio = pAux->prox;
					} else if(pAux == lt->fim) {
						pAux->ant->prox = NULL;
						lt->fim = pAux->ant;
					} else {
						pAux->ant->prox = pAux->prox;
						pAux->prox->ant = pAux->ant;
					}
					lt->n--;
					free(pAux);
					return SUCESSO;
				}
			}
			pAux = pAux->prox;
			
		}
		return CODIGO_INEXISTENTE;
	}
}

void imprimirEtiqueta(LISTA *lt, char* nomeDoProduto) {
	Nodo *pAux = lt->inicio;
	while(pAux != NULL) {
		if(strstr(pAux->info.nome, nomeDoProduto) != NULL) { //compara as strings
			printf("codigo: %d produto: %s\n", pAux->info.codigo, pAux->info.nome);
		}
		pAux = pAux->prox;
	}
}

void incluirCompra(LISTA *lt, LISTA *lt2, int codigo) {
    Nodo *pAux = lt->inicio;
    while (pAux != NULL) {
        if (pAux->info.codigo == codigo) {
            DADO novoProduto = pAux->info;  // Cria uma c?pia do produto
            incluiNoFim(lt2, novoProduto);  // Insere a c?pia na lista lt2
            break;
        }
        pAux = pAux->prox;
    }
}

void alterarValor(LISTA *lt2, int codigo) {
	if(lt2->n == 0) {
		printf("a lista esta vazia\n");
	} else {
		Nodo *pAux = lt2->inicio;
		while(pAux != NULL) {
			if(codigo == pAux->info.codigo) {
				printf("digite o novo valor do produto: ");
				scanf("%f", &pAux->info.valor);
			}
			pAux = pAux->prox;
		}
	}
}

void liberarLista(LISTA *lt) {
    Nodo *pAux = lt->inicio;
    Nodo *pProx;

    while (pAux != NULL) {
        pProx = pAux->prox;
        free(pAux);
        pAux = pProx;
    }

    lt->inicio = NULL;
    lt->fim = NULL;
    lt->n = 0;
}

int carregarEstoque(LISTA *lt, DADO d) {
	FILE *arq;
	if((arq = fopen("dados.txt","r")) == NULL) {
        return CODIGO_INEXISTENTE;
	} else {
		
		while(fscanf(arq, "%d %s %f\n", &d.codigo, d.nome, &d.valor) != EOF) {
			if (incluiNoFim(lt, d) == FALTOU_MEMORIA) {
	            printf("Operacao NAO realizada: Faltou Memoria!\n");
			} else {
				continue;
			} 
		}
		fclose(arq);
		return SUCESSO;
    }
}

void cadastrarProduto(LISTA *lt) {
	FILE *arq;
	if((arq = fopen("dados.txt","w")) == NULL) {
		printf("Erro ao fazer o backup");
	} else {
		Nodo *aux = lt->inicio;
		while(aux != NULL) {
			fprintf(arq, "%d %s %.2f\n", aux->info.codigo, aux->info.nome, aux->info.valor);
			aux = aux->prox;
		}
		fclose(arq);
		printf ("Gravacao Realizada com Sucesso! \n\n");
	}
}

void cadastrarCliente(CLIENTE cliente) {
    FILE *arquivo;
    arquivo = fopen("clientes.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para gravacao.\n");
        return;
    }

    fprintf(arquivo, "%d %s\n", cliente.cpf, cliente.nome);
    fclose(arquivo);
}

int verificarCliente(CLIENTE cliente) {
	FILE *arquivo;
	int cpf;
    char nome[50];
	arquivo = fopen("clientes.txt", "r");
	while (fscanf(arquivo, "%d %s", &cpf, nome) != EOF) {
		if(cliente.cpf == cpf) {
			fclose(arquivo);
			return CODIGO_INEXISTENTE;
		} 
	}
	return SUCESSO;
}

float totalComDesconto(float total) {
	float total2;
	total2 = total -(total * 0.10);
	return total2;
}
