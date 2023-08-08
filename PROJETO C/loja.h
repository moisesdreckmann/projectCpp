#ifndef listade_H
#define listade_H

#define SUCESSO 0
#define LISTA_VAZIA 1
#define FALTOU_MEMORIA 2
#define CODIGO_INEXISTENTE 3

typedef struct {
        int codigo;
        char nome[50];
        float valor;
} DADO;
        
typedef struct nodo Nodo;

struct nodo {
       DADO info;
       Nodo *ant;
       Nodo *prox;
};

typedef struct {
        Nodo *inicio;
        Nodo *fim;
        int n;
} LISTA;

typedef struct {
        int cpf;
        char nome[50]; 
} CLIENTE;

void criaLista(LISTA *lt);
int incluiNoFim(LISTA *lt, DADO d);
float exibe(LISTA *lt);
int excluirNodo(LISTA *lt, DADO *dadoExcluido, int codigo);
void imprimirEtiqueta(LISTA *lt, char* nomeDoProduto);
void incluirCompra(LISTA *lt, LISTA *lt2, int codigo);
void alterarValor(LISTA *lt2, int codigo);
void liberarLista(LISTA *lt);
int carregarEstoque(LISTA *lt, DADO d);
void cadastrarProduto(LISTA *lt);
void cadastrarCliente(CLIENTE cliente);
int verificarCliente(CLIENTE cliente);
float totalComDesconto(float total);


#endif



