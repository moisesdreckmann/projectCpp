#include <stdio.h>
#include <stdlib.h>
#include "loja.h"

int main() {

    int op, codigo, exclusao, codigoCompra, cadastro;
    char nomeDoProduto[50];
    float pagamento, total, pagamentoFinal, total2=0;
    LISTA lt, lt2;
    DADO d;
    CLIENTE cliente;

    criaLista(&lt);
    criaLista(&lt2);
    if(carregarEstoque(&lt, d) == CODIGO_INEXISTENTE) {
        d.codigo =1;
    } 

    do {
        printf("\n0. Acesso ao sistema - 1. Finalizar a compra\n");
        printf("\ninsira o codigo do produto: ");
        scanf("%d", &codigoCompra);
        incluirCompra(&lt, &lt2, codigoCompra);
        system("cls");
        total = exibe(&lt2);

        if(codigoCompra == 1) {
            if(lt2.n == 0 ) {
                system("cls");
                continue;
            } else { 
                printf("\nDeseja efetuar cadastro na loja? \n");
                printf("1. Com cadastro\n");
                printf("2. Efetuar cadastro\n");
                printf("3. Sem cadastro\n");
                scanf("%d", &cadastro);
                
                switch (cadastro) {
                case 1:
                    printf("digite o cpf: ");
	                scanf ("%d", &cliente.cpf);
                    if(verificarCliente(cliente) == CODIGO_INEXISTENTE) {
                        total2 = totalComDesconto(total);
                        printf("\ntotal da compra com desconto: %.2f\n", total2);
                        printf("\nvalor recebido: ");
                        scanf("%f", &pagamento);
                        if(pagamento < total2) {
                            printf("\npagamento nao realizado.Tente novamente\n");
                            continue;
                        } else {
                            pagamentoFinal = pagamento - total2;
                            printf("\ntroco: %.2f\n", pagamentoFinal);
                            liberarLista(&lt2);
                        }
                    } else {
                        printf("\ncliente nao encontrado\n");
                    }
                    break;
                case 2:
                    printf("digite o cpf: ");
	                scanf ("%d", &cliente.cpf);
                    printf("digite o nome: ");
                    scanf (" %s", cliente.nome);
                    if(verificarCliente(cliente) == CODIGO_INEXISTENTE) {
                        printf("\ncliente ja cadastrado no sistema\n");
                    } else {
                        cadastrarCliente(cliente);
                        printf("\ncliente inserido com sucesso\n");
                    }
                    total2 = totalComDesconto(total);
                    printf("\ntotal da compra com desconto: %.2f\n", total2);
                    printf("\nvalor recebido: ");
                    scanf("%f", &pagamento);
                    if(pagamento < total2) {
                        printf("\npagamento nao realizado.Tente novamente\n");
                        continue;
                    } else {
                        pagamentoFinal = pagamento - total2;
                        printf("\ntroco: %.2f\n", pagamentoFinal);
                        liberarLista(&lt2);
                    }
                    break;
                case 3:
                    printf("\nvalor recebido: ");
                    scanf("%f", &pagamento);
                    if(pagamento < total) {
                        continue;
                    } else {
                        pagamentoFinal = pagamento - total;
                        printf("\ntroco: %.2f\n", pagamentoFinal);
                        liberarLista(&lt2);
                    }
                    break;
                }
            }
        }

        if(codigoCompra == 0) { 
            do {
                printf("\n\n0. Fim\n");
                printf("\nLOJA: \n");
                printf("1. Inserir produto na lista da loja\n");
                printf("2. Exibir produtos da loja\n");
                printf("3. Excluir produto na lista da loja\n");
                printf("4. Imprimir nova etiqueta\n");
                printf("5. Alterar preco de produto da loja\n");
                printf("\nCOMPRA: \n");
                printf("6. Excluir produto da COMPRA\n");
                printf("7. Desconto/Preco errado na COMPRA\n\n");
                scanf("%d",  &op);
                switch (op)
                {
                case 0:
                    cadastrarProduto(&lt);
                    system("cls");
                    exibe(&lt2);
                    break;
                case 1:
                    d.codigo = lt.fim->info.codigo;
                    d.codigo++;
                    printf("digite o nome do produto: ");
                    scanf(" %s", d.nome);
                    printf("digite o valor do produto: ");
                    scanf("%f", &d.valor);
                    if(incluiNoFim(&lt, d) == FALTOU_MEMORIA) {
                        printf("\nfaltou memoria no sistema\n");
                    } else {
                        printf("\nproduto inserido com sucesso\n");
                    }
                    break;
                case 2:
                    system("cls");
                    exibe(&lt);
                    break;
                case 3:
                    printf("informe um codigo para a exclusao: ");
                    scanf("%d", &codigo);
                    exclusao = excluirNodo(&lt, &d, codigo);
                    if(exclusao == LISTA_VAZIA) {
                        printf("a lista esta vazia\n");
                    } else if(exclusao == CODIGO_INEXISTENTE){
                        printf("o produto e inexistente ou nao foi removido\n");
                    } else {
                        printf("O produto foi excluido com sucesso\n");
                    }
                    system("cls");
                    break;
                case 4:
                    printf("informe o modelo do produto: ");
                    scanf(" %s", nomeDoProduto);
                    imprimirEtiqueta(&lt, nomeDoProduto);
                    break;
                case 5:
                    printf("informe o codigo do produto: ");
                    scanf("%d", &codigo);
                    alterarValor(&lt, codigo);
                    break;
                case 6:
                    printf("informe um codigo para a exclusao: ");
                    scanf("%d", &codigo);
                    exclusao = excluirNodo(&lt2, &d, codigo);
                    if(exclusao == LISTA_VAZIA) {
                        printf("a lista esta vazia\n");
                    } else if(exclusao == CODIGO_INEXISTENTE){
                        printf("o produto e inexistente ou nao foi removido\n");
                    } else {
                        printf("O produto foi excluido com sucesso\n");
                    }
                    system("cls");
                    exibe(&lt2);
                    break;
                case 7:
                    printf("informe o codigo do produto: ");
                    scanf("%d", &codigo);
                    alterarValor(&lt2, codigo);
                    system("cls");
                    exibe(&lt2);
                    break;
                }
            } while(op != 0);
    }
    } while(codigoCompra >= 0);

    return 0;
}



