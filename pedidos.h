#include "clientes.h"

#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Definição das estruturas

typedef enum status_pedido {
    PENDENTE_COLETA,
    PENDENTE_PROCESSAMENTO,
    EM_PROCESSAMENTO,
    PRONTO_ENTREGA,
    CONCLUIDO
} Status_Pedido;

typedef struct itens{
    int id;
    char nome[50];
    double valor;
}Itens;

typedef struct lista_itens{
    int tipo;
    Itens* item;
    int quantidade;
    struct lista_itens* proxItem;
}Lista_Itens;

struct pedido{
    int id;
    Lista_Itens* lista;
    Status_Pedido status;
    double total_pedido;
};

typedef struct pedido Pedido;

typedef enum menu_pedido{
    LAVAGEM = 1,           
    PASSADORIA = 2,         
    COLETA_ENTREGA = 3,      
    FINALIZAR_PEDIDO = 4,  
    SAIR = 5               
}Menu_Pedido;

// Declaração das funções relacionadas aos itens (Itens, Lista_Itens)
Lista_Itens* inicializar_lista_itens(void);
Lista_Itens* inserir_item(Lista_Itens* lista, Itens* item, int quantidade, int tipo);
Lista_Itens* remover_item(Lista_Itens* lista, Itens* item, int tipo);
Lista_Itens* verificar_existencia(Lista_Itens* lista, Itens* item, int tipo);
void alterar_quantidade(Lista_Itens* lista, Itens* item, int quantidade, int tipo);
void modificar_item(Lista_Itens* lista, Itens* item, Itens* itemAux, int tipo);
void imprimir_lista_itens(Lista_Itens* lista);
Itens* arrays_itens(FILE* arquivo);
void realocar_memoria(Itens** novo, int* tamanho);
void imprimir_itens(Itens* itens_array, int tamanho);

// Declaração das funções relacionadas aos pedidos (Pedido)
void imprimir_pedido(Pedido* pedido);
Pedido* preencher_pedido(Pedido** novo_pedido, Lista_Itens** lista);
Pedido* menu_pedido(void);
void escrever_lista_itens_arquivo(Lista_Itens* lista, FILE* arquivo);
void escrever_status_pedido(FILE* arquivo, Pedido* pedido);
void imprimir_status_pedido(Pedido* pedido);

// Funções auxiliares ou de utilidade geral
int validar_entrada(const char* print, int min, int max);
Menu_Pedido opcoes_menu(void);
void processar_servico(Itens* servico, Lista_Itens** novo_item, int tipo, int quantidade_itens);

#endif
