#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Estrutura enumerada para atualização de status do pedido.*/
typedef enum status_pedido Status_Pedido;

/*Estrutura enumerada para ajudar na organização do menu pedidos.*/
typedef enum menu_pedido Menu_Pedido;

/*Estrutura usada para preencher a lista de pedidos.*/
typedef struct itens Itens;

/*Lista encadeada que armazena os itens do serviços a serem feitos.*/
typedef struct lista_itens Lista_Itens;

/*Estrutura que contém a lista de itens e demais informações do pedido.*/
typedef struct pedido Pedido;

/*Função que inicializa a lista de itens.*/
Lista_Itens* criar_lista(void);

/*Função para inserir itens na lista do pedido.*/
Lista_Itens* inserir_item(Lista_Itens* lista, Itens* item, int quantidade, int tipo);

/*Função para retirar um item da lista.*/
Lista_Itens* retirar_item(Lista_Itens* lista, Itens* item);

/*Função para verificar se um item já está presente na lista, afim de evitar itens duplicados.*/
Lista_Itens* verificar(Lista_Itens* lista, Itens* servico);

/*Função para alterar a quantidade de um item já adicionado a lista.*/
void alterar_quantidade(Lista_Itens* lista, Itens* item, int quantidade);

/*Função para modificar um item da lista.*/
void modificar_item(Lista_Itens* lista, Itens* item, Itens* itemAux);

/*Função para imprimir os itens da lista.*/
void imprimir_lista(Lista_Itens* lista);

/*Função para realocar memória de acordo com a quantidade de itens do menu serviços.*/
void realocar_memoria(Itens** novo, int* tamanho);

/*Função para ler um arquivo texto com a pré-definição de itens e preços e armazenar em um vetor.*/
Itens* arrays_itens(FILE* arquivo);

/*Função para imprimir os itens de cada menu serviço.*/
void imprimir_itens(Itens* itens_array, int tamanho);

/*Função para imprimir as opções do menu principal.*/
Menu_Pedido opcoes_menu();

/*Função para preencher pedido com informações além da lista de itens.*/
Pedido** preencher_pedido(Pedido** novo_pedido, Lista_Itens** lista);

/*Função para editar status de um pedido existente.*/
Pedido* editar_status(Pedido* pedido, int op);

/*Função para manipular adequadamente cada função do menu principal.*/
void menu_pedido();