#ifndef CLIENTES_H
#define CLIENTES_H

#include "../include/pedidos.h"

//typedef struct pedidos Pedido;
typedef struct lista_pedidos {
    Pedido* pedido;
    struct lista_pedidos* prox;
}Lista_Pedidos;

//typedef struct clientes Clientes;
typedef struct clientes {
    char nome[50];
    char contato[16];
    char Cpf[15];
    Lista_Pedidos* lista;
    struct clientes* prox;
} Clientes;

/*
 * @brief Inicializa a lista de clientes
 *
 * @param void
 * @param void
 *
 * @return void
 *  */
Clientes* inicializar_lista_clientes(void);

/*
 * @brief Insere um cliente na lista de clientes
 *
 * @param Clientes *lista Lista encadeada de clientes
 * @param char nome[50] Nome do cliente
 *
 * @return Clientes* Retorna a lista de clientes atualizada
 * */
Clientes* inserir_cliente(Clientes* lista, char nome[50], char contato[15], char cpf[15]);

/*
 * @brief Adiciona um cliente na lista de clientes
 *
 * @param Clientes *lista Lista encadeada de clientes
 *
 * @return Clientes* Retorna a lista de clientes atualizada
 *  */
Clientes* adicionar_clientes(Clientes* lista);

/*
 * @brief Remove um cliente da lista de clientes
 *
 * @param Clientes *lista Lista encadeada de clientes
 *
 * @return Clientes* Retorna a lista de clientes atualizada
 *  */
Clientes* remover_cliente(Clientes* lista, Clientes* cliente);

/*
 * @brief Busca um cliente na lista de clientes
 *
 * @param Clientes *lista Lista encadeada de clientes
 *
 * @return Clientes* Retorna o cliente encontrado
 *  */
Clientes* buscar_cliente(Clientes* lista);

/*
 * @brief Inicializa a lista de pedidos
 *
 * @param void
 * @param void
 *
 * @return Lista_Pedidos* Retorna a lista de pedidos inicializada
 *  */
Lista_Pedidos* inicializar_lista_pedidos(void);

/*
 * @brief Adiciona um pedido na lista de pedidos
 *
 * @param Clientes *cliente Cliente que fez o pedido
 * @param Pedido *pedido Pedido feito pelo cliente
 *
 * @return void
 *  */
void adicionar_pedidos(Clientes* lista_principal, Clientes* cliente, Pedido* pedido);

/*
 * @brief Remove um pedido da lista de pedidos
 *
 * @param Clientes *cliente Cliente que fez o pedido
 * @param Pedido *pedido Pedido feito pelo cliente
 *
 * @return Lista_Pedidos* Retorna a lista de pedidos atualizada
 *  */
Lista_Pedidos* remover_pedido(Clientes* lista_principal, Clientes* cliente, Pedido* pedido);


/*
 * @brief Imprime a lista de clientes
 *
 * @param Clientes *lista Lista encadeada de clientes
 *
 * @return void
 *  */
void imprimir_lista_pedidos(Clientes* cliente);

/*
 * @brief Busca um pedido na lista de pedidos
 *
 * @param Clientes *cliente Cliente que fez o pedido
 * @param int id Identificador do pedido
 *
 * @return Pedido* Retorna o pedido encontrado
 *  */
Pedido* buscar_pedido(Clientes* cliente, int id);

/*
 * @brief Modifica o status do pedido
 *
 * @param Pedido* pedido Pedido a ser modificado
 *
 * @return void
 *  */
void modificar_status(Pedido* pedido);

/*
 * @brief Escreve a lista de clientes em um arquivo
 *
 * @param Clientes *lista Lista encadeada de clientes
 *
 * @return void
 *  */
void escrever_arquivo(Clientes* lista);

/*
 * @brief imprimir lista de clientes e seus pedidos
 *
 * @param clientes *lista Lista encadeada de clientes
 *
 * @return void
 * */
void imprimir_clientes_pedidos(Clientes* lista);

/*
 * @brief Libera a mem�ria alocada para a lista de clientes
 *
 * @param Clientes *inicio In�cio da lista encadeada de clientes
 *
 * @return void
 *  */
void liberar_memoria_clientes(Clientes* inicio) ;

/*
 * @brief ler arquivo de teste para preencher a lista de clientes
 *
 * @param FILE* arquivo Arquivo com os dados dos clientes
 * @param Clientes** lista Lista encadeada de clientes
 *
 * @return void
 *  */
void ler_arquivo_teste(FILE* arquivo, Clientes** lista);

/*
* @brief Busca um cliente na lista de clientes
* @param Clientes* lista Lista encadeada de clientes
* @param const char* cpf CPF do cliente a ser buscado

* @return Clientes* Retorna o cliente encontrado
*/
Clientes* buscar_cliente_por_cpf(Clientes* lista, const char* cpf);

#endif

