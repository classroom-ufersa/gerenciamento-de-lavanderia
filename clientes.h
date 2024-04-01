#ifndef CLIENTES_H
#define CLIENTES_H

struct pedido;

#include "pedidos.c"

typedef struct lista_pedidos {
    Pedido* pedido;
    struct lista_pedidos* prox;
} Lista_Pedidos;

typedef struct clientes {
    char nome[50];
    char contato[15];
    Lista_Pedidos* lista;
    struct clientes* prox;
} Clientes;

Clientes* inicializar_lista_clientes(void);

Clientes* inserir_cliente(Clientes* lista, char nome[50], char contato[15]);

Clientes* adicionar_clientes(Clientes* lista);

Clientes* remover_cliente(Clientes* lista);

Clientes* buscar_cliente(Clientes* lista);

Lista_Pedidos* inicializar_lista_pedidos(void);

void adicionar_pedidos(Clientes* cliente, Pedido* pedido);

Lista_Pedidos* remover_pedido(Clientes* cliente, struct pedido* pedido);

void limpabuffer(void);

int validar_nome(const char nome[50]);

void formatar_nome(char *nome);

int validar_contato(const char *numero);

void formatar_contato(char *numero);

void imprimir_lista_pedidos(Clientes* cliente);

struct pedido* buscar_pedido(Clientes* cliente, int id);

void modificar_status(Pedido* pedido);

void escrever_arquivo(Clientes* lista, FILE* arquivo);

void imprimir_clientes_pedidos(Clientes* lista);

#endif

