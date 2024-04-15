#include "../include/clientes.h"

#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Definição das estruturas

typedef enum menu_pedido{
    LAVAGEM = 1,         
    FINALIZAR_PEDIDO = 2,  
    SAIR = 3,               
    PASSADORIA = 4,
    COLETA_ENTREGA = 5
}Menu_Pedido;

typedef enum status_pedido {
    PENDENTE_COLETA,
    PENDENTE_PROCESSAMENTO,
    EM_PROCESSAMENTO,
    PRONTO_ENTREGA,
    CONCLUIDO
} Status_Pedido;

typedef struct itens{
    char nome[50];
    double valor;
}Itens;

typedef struct lista_itens{
    Menu_Pedido tipo;
    Itens* item;
    int quantidade;
    struct lista_itens* proxItem;
}Lista_Itens;

typedef struct pedido{
    int id;
    Lista_Itens* lista;
    Status_Pedido status;
    double total_pedido;
}Pedido;

/**
 * @brief Inicializa uma lista de itens.
 * 
 * @return Lista_Itens* Ponteiro para a lista de itens inicializada.
 */
Lista_Itens* inicializar_lista_itens(void);

/**
 * @brief Insere um item na lista de itens do pedido.
 * 
 * @param lista Lista de itens.
 * @param item Item a ser inserido.
 * @param quantidade Quantidade do item.
 * @param tipo Tipo do item conforme enumeração Menu_Pedido.
 * @return Lista_Itens* Ponteiro para a lista de itens atualizada.
 */
Lista_Itens* inserir_item(Lista_Itens* lista, Itens* item, int quantidade, Menu_Pedido tipo);

/**
 * @brief Remove um item da lista de itens do pedido.
 * 
 * @param lista Lista de itens.
 * @param item Item a ser removido.
 * @return Lista_Itens* Ponteiro para a lista de itens atualizada.
 */
Lista_Itens* remover_item(Lista_Itens* lista, Itens* item);

/**
 * @brief Verifica se um item já existe na lista de itens do pedido.
 * 
 * @param lista Lista de itens.
 * @param item Item a ser verificado.
 * @param tipo Tipo do item conforme enumeração Menu_Pedido.
 * @return Lista_Itens* Ponteiro para o item encontrado, se existir.
 */
Lista_Itens* verificar_existencia(Lista_Itens* lista, Itens* item, Menu_Pedido tipo);

/**
 * @brief Altera a quantidade de um item na lista de itens do pedido.
 * 
 * @param lista Lista de itens.
 * @param item Item cuja quantidade será alterada.
 * @param quantidade Nova quantidade do item.
 */
void alterar_quantidade(Lista_Itens* lista, Itens* item, int quantidade);

/**
 * @brief Modifica um item na lista de itens do pedido.
 * 
 * @param lista Lista de itens.
 * @param item Item a ser modificado.
 * @param itemAux Novo item que substituirá o anterior.
 */
void modificar_item(Lista_Itens* lista, Itens* item, Itens* itemAux);

/**
 * @brief Lê os itens de um arquivo e os armazena em um array.
 * 
 * @param arquivo Ponteiro para o arquivo de onde os itens serão lidos.
 * @return Itens* Ponteiro para o array de itens lidos.
 */
Itens* arrays_itens(FILE* arquivo);

/**
 * @brief Imprime os itens de um array.
 * 
 * @param itens_array Array de itens.
 * @param tamanho Tamanho do array.
 */
void imprimir_itens(Itens* itens_array, int tamanho);

/**
 * @brief Realoca a memória de um array de itens.
 * 
 * @param novo Ponteiro para o novo array.
 * @param tamanho Ponteiro para o tamanho atual do array.
 */
void realocar_memoria(Itens** novo, int* tamanho);

/**
 * @brief Preenche os detalhes de um novo pedido.
 * 
 * @param novo_pedido Ponteiro para o novo pedido.
 * @param lista Ponteiro para a lista de itens do pedido.
 * @return Pedido* Ponteiro para o pedido preenchido.
 */
Pedido* preencher_pedido(Pedido** novo_pedido, Lista_Itens** lista);

/**
 * @brief Exibe as opções do menu e obtém a escolha do usuário.
 * 
 * @return Menu_Pedido Opção escolhida pelo usuário.
 */
Menu_Pedido opcoes_menu(void);

/**
 * @brief Exibe o menu de opções de pedido.
 * 
 * @return Pedido* Ponteiro para o pedido escolhido pelo usuário.
 */
Pedido* menu_pedido(void);

/**
 * @brief Processa .
 * 
 * @param servico Item a ser processado.
 * @param novo_item Ponteiro para a lista de itens do pedido.
 * @param tipo Tipo do item conforme enumeração Menu_Pedido.
 * @param quantidade_itens Quantidade do item a ser processado.
 */
void processar_servico(Itens* servico, Lista_Itens** novo_item, Menu_Pedido tipo, int quantidade_itens);

/**
 * @brief Modifica o status de um pedido.
 * 
 * @param pedido Pedido cujo status será modificado.
 */
void modificar_status(Pedido* pedido);

/**
 * @brief Imprime a lista de itens do pedido.
 * 
 * @param lista Lista de itens.
 */
void imprimir_lista_itens(Lista_Itens* lista);

/**
 * @brief Imprime os detalhes de um pedido.
 * 
 * @param pedido Pedido a ser impresso.
 */
void imprimir_pedido(Pedido* pedido);

/**
 * @brief Imprime o status do pedido.
 * 
 * @param pedido Pedido cujo status será impresso.
 */
void imprimir_status_pedido(Pedido* pedido);

/**
 * @brief Escreve a lista de itens do pedido em um arquivo.
 * 
 * @param lista Lista de itens.
 * @param arquivo Ponteiro para o arquivo onde a lista será escrita.
 */
void escrever_lista_itens_arquivo(Lista_Itens* lista, FILE* arquivo);

/**
 * @brief Escreve o status do pedido em um arquivo.
 * 
 * @param arquivo Ponteiro para o arquivo onde o status será escrito.
 * @param pedido Pedido cujo status será escrito.
 */
void escrever_status_pedido(FILE* arquivo, Pedido* pedido);

#endif
