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


// Declaração das funções relacionadas aos itens (Itens, Lista_Itens)
Lista_Itens* inicializar_lista_itens(void);
Lista_Itens* inserir_item(Lista_Itens* lista, Itens* item, int quantidade, Menu_Pedido tipo);
Lista_Itens* remover_item(Lista_Itens* lista, Itens* item);
Lista_Itens* verificar_existencia(Lista_Itens* lista, Itens* item, Menu_Pedido tipo);
void alterar_quantidade(Lista_Itens* lista, Itens* item, int quantidade);
void modificar_item(Lista_Itens* lista, Itens* item, Itens* itemAux);
void imprimir_lista_itens(Lista_Itens* lista);
Itens* arrays_itens(FILE* arquivo);
void realocar_memoria(Itens** novo, int* tamanho);
void imprimir_itens(Itens* itens_array, int tamanho);

// Declaração das funções relacionadas aos pedidos (Pedido)
Pedido* preencher_pedido(Pedido** novo_pedido, Lista_Itens** lista);
void imprimir_pedido(Pedido* pedido);
Pedido* menu_pedido(void);
void escrever_lista_itens_arquivo(Lista_Itens* lista, FILE* arquivo);
void escrever_status_pedido(FILE* arquivo, Pedido* pedido);
void imprimir_status_pedido(Pedido* pedido);

// Funções auxiliares ou de utilidade geral
Menu_Pedido opcoes_menu(void);
void processar_servico(Itens* servico, Lista_Itens** novo_item, Menu_Pedido tipo, int quantidade_itens);
void modificar_status(Pedido* pedido);

#endif
