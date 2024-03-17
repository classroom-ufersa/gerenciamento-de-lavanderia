#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include <string.h>
#include <ctype.h>


typedef struct Cliente{
    char nome[50];
    char numero[15];
    clientes *prox;
}clientes;


clientes* lista_cria(void){
    return NULL;
}


void limpabuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int verificar_nome(char nome[50]) {
    int tamanho_da_string = strlen(nome);
    for (int i = 0; i < tamanho_da_string; i++) {
         if (!isalpha(nome[i])  && nome[i] != ' '){
            limpabuffer();
            printf("Nome invalido, digite novamente.\n");
            return 1;
        }
    }
    return 0;
}


int verificar_numero(char numero[15]) {
    int tamanho_da_string = strlen(numero);
    for (int i = 0; i < tamanho_da_string; i++) {
        if (!isdigit(numero[i]) && numero[i] != ' '){
            limpabuffer();
            printf("Numero invalido, digite novamente.\n");
            return 1;
        }
    }
    return 0;
}


clientes* add_clientes(clientes *l, FILE * arquivo_cliente){
    clientes *novo = (clientes*)malloc(sizeof(clientes));
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", novo->nome);
    while(verificar_nome(novo->nome) == 1){
        printf("Digite o nome do cliente: ");
        scanf(" %[^\n]", novo->nome);
    }

    printf("Digite o numero do cliente: ");
    scanf(" %[^\n]", novo->numero);
    while(verificar_numero(novo->numero) == 1){
        printf("Digite o numero do cliente: ");
        scanf(" %[^\n]", novo->numero);
    }

    
    fprintf(arquivo_cliente, "Nome: %s\n", novo->nome);
    fprintf(arquivo_cliente, "Numero de Telefone: %s\n", novo->numero);
    fprintf(arquivo_cliente, "\n");
    novo->prox = l;
    return novo;
}

void lista_imprime(clientes *l){
    clientes *p;
    for(p = l; p != NULL; p = p->prox){
        printf("Nome: %s\n", p->nome);
        printf("Numero: %s\n", p->numero);
    }
}



clientes* retirar_cliente(clientes *pessoa, FILE *arquivo_cliente){
    char nome[50];

    fclose(arquivo_cliente);
    arquivo_cliente = fopen("arquivo_dados_dos_clientes.txt", "w");

    printf("Digite o nome do cliente que deseja retirar: ");
    scanf(" %[^\n]", nome);

    clientes *cliente_anterior = NULL;
    clientes *cliente_atual = pessoa;

    while(cliente_atual != NULL && strcmp(cliente_atual->nome, nome) != 0){
        cliente_anterior = cliente_atual;
        cliente_atual = cliente_atual->prox;
    }

    if(cliente_atual == NULL){
        printf("Cliente não encontrado na lista.\n");
        return pessoa;
    }

    if(cliente_anterior == NULL){
        pessoa = cliente_atual->prox;
    } else {
        cliente_anterior->prox = cliente_atual->prox;
    }

    clientes *cliente_temp;

     for(cliente_temp = pessoa; cliente_temp != NULL; cliente_temp = cliente_temp->prox){
        fprintf(arquivo_cliente, "Nome: %s\n", cliente_temp->nome);
        fprintf(arquivo_cliente, "Numero de Telefone: %s\n", cliente_temp->numero);
        fprintf(arquivo_cliente, "\n");
    }
    
    fclose(arquivo_cliente);
    free(cliente_atual);
    printf("Cliente %s retirado da lista e arquivo atualizado.\n", nome);
    return pessoa;
}
