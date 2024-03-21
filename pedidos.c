#include <string.h>
#include <stdbool.h>
#include "pedidos.h"

enum status_pedido{
    PENDENTE_COLETA,
    PENDENTE_PROCESSAMENTO,
    EM_PROCESSAMENTO,
    PRONTO_ENTREGA,
    CONCLUIDO
};

enum menu_pedido{
    LAVAGEM = 0,
    PASSADORIA = 1,
    COLETA_ENTREGA = 2,
    FINALIZAR_PEDIDO = 3,
    SAIR = 4
};

struct itens{
    int id;
    char nome[50];
    double valor;
};

struct lista_itens{
    int tipo;
    Itens* item;
    int quantidade;
    Lista_Itens* proxItem;
};

struct pedido{
    int id;
    Lista_Itens* lista;
    Status_Pedido status;
    double total_pedido;
};

Lista_Itens* criar_lista(void){
    return NULL;
}

Lista_Itens* inserir_item(Lista_Itens* lista, Itens* item, int quantidade, int tipo){
    Lista_Itens* novo = (Lista_Itens*) malloc(sizeof(Lista_Itens));
    novo->tipo = tipo;
    novo->item = (Itens*) malloc(sizeof(Itens));
    novo->item->id = item->id;
    strcpy(novo->item->nome, item->nome);
    novo->quantidade = quantidade;
    novo->item->valor = item->valor * quantidade;
    novo->proxItem = lista;
    return novo;
}

void imprimir_lista(Lista_Itens* lista){
    int soma_l = 0;
    int soma_p = 0;
    int coleta = 0;
    Lista_Itens* p;

    for(p = lista; p != NULL; p = p->proxItem){
        if(p->tipo == 0){
            soma_l += 1;
        }
        if(p->tipo == 1){
            soma_p += 1;
        }
        if(p->tipo == 2){
            coleta += 1;
        }
    }
    
    if(soma_l > 0){
        printf("Servicos de lavagem:\n");
        for(p = lista; p != NULL; p = p->proxItem){
            if(p->tipo == 0){
                printf("\t%d\t%s\tValor: R$ %.2lf\n", p->quantidade, p->item->nome, p->quantidade * p->item->valor);
            }
        }
    }
    else{
        printf("Nenhum servico de lavagem incluso.\n");
    }

    if(soma_p > 0){
        printf("Servicos de passadoria:\n");
        for(p = lista; p != NULL; p = p->proxItem){
            if(p->tipo == 1){
                printf("\t%d\t%s\tValor: R$ %.2lf\n", p->quantidade, p->item->nome, p->quantidade * p->item->valor);
            }
        }
    }
    else{
        printf("Nenhum servico de passadoria incluso.\n");
    }

    if(coleta == 1){
        for(p = lista; p != NULL; p = p->proxItem){
            if(p->tipo == 2){
                printf("\t%d\t%s\tValor: R$ %.2lf\n", p->quantidade, p->item->nome, p->item->valor);
            }
        }
    }
    else{
        printf("Nenhum servico de coleta e entrega incluso.\n");
    }
}

Lista_Itens* retirar_item(Lista_Itens* lista, Itens* item){
    Lista_Itens* anterior = NULL;
    Lista_Itens* p = lista;

    while(p != NULL && strcmp(p->item->nome, item->nome) != 0){
        anterior = p;
        p = p->proxItem;
    }

    if(p == NULL){
        return lista;
    }

    if(anterior == NULL){
        lista = p->proxItem;
    }
    else{
        anterior->proxItem = p->proxItem;
    }

    free(p);
    return lista;
}

Lista_Itens* verificar(Lista_Itens* lista, Itens* servico){
    Lista_Itens* p;
    
    for(p = lista; p != NULL; p = p->proxItem){
        if(strcmp(p->item->nome, servico->nome) == 0){
            return p;
        }
    }
    return NULL;
}

void alterar_quantidade(Lista_Itens* lista, Itens* item, int quantidade){
    Lista_Itens* p;

    for(p = lista; p != NULL; p = p->proxItem){
        if(strcmp(p->item->nome, item->nome) == 0){
            p->quantidade = quantidade;
            return;
        }
    } 
}

void realocar_memoria(Itens** novo, int* tamanho){
    (*tamanho)++;
    *novo = (Itens*) realloc(*novo, *tamanho * sizeof(Itens));
    if(*novo == NULL){
        printf("Erro ao alocar memoria.\n");
    }
}

Itens* arrays_itens(FILE* arquivo){
    int tamanho = 0;
    Itens* novo = NULL;

    if(arquivo == NULL){ //declaração e abertura do arquivo no main
        printf("Erro ao abrir arquivo.\n");
    }

    novo = (Itens*) malloc(sizeof(Itens));
    if(novo == NULL){
        printf("Erro ao alocar memoria.\n");
    }

    realocar_memoria(&novo, &tamanho);

    while(fscanf(arquivo, "%d\t%49[^\t]%lf\n", &novo[tamanho - 1].id, novo[tamanho - 1].nome, &novo[tamanho - 1].valor) == 3){
        realocar_memoria(&novo, &tamanho);
    }

    fclose(arquivo);

    return novo;
}

void imprimir_itens(Itens* itens_array, int tamanho){
    int i;
    for(i = 0; i < tamanho; i++){
        printf("%d\t%s\tR$ %.2lf\n", itens_array[i].id, itens_array[i].nome, itens_array[i].valor);
    }
}

void modificar_item(Lista_Itens* lista, Itens* item, Itens* itemAux){
    Lista_Itens* p;

    for(p = lista; p != NULL; p = p->proxItem){
        if(strcmp(p->item->nome, item->nome) == 0){
            p->item->id = itemAux->id;
            strcpy(p->item->nome, itemAux->nome);
            p->item->valor = itemAux->valor;
        }
    }
}

Pedido** preencher_pedido(Pedido** novo_pedido, Lista_Itens** lista){
    Lista_Itens* p;
    double soma = 0;
    (*novo_pedido)->id = rand() % 1000 + 1;
    (*novo_pedido)->lista = *lista;
    int status_encontrado = 0;

    for(p = *lista; p != NULL; p = p->proxItem){
        if(p->tipo == 2 && (p->item->id == 0 || p->item->id == 2)){
            (*novo_pedido)->status = 0;
            status_encontrado = 1;
            break;
        }
    }

    (*novo_pedido)->status = (status_encontrado) ? 0 : 1;

    for(p = *lista; p != NULL; p = p->proxItem){
        soma += p->item->valor;
    }
    (*novo_pedido)->total_pedido = soma;

    return novo_pedido;
}

Pedido* editar_status(Pedido* pedido, int op){
    pedido->status = op;
}

int validar_entrada(const char* print){
    int opcao;
    int valid;

    do{
        printf("%s", print);
        valid = scanf("%d", &opcao);
        if (valid != 1 || (opcao != 0 && opcao != 1)) {
            printf("Opcao invalida, certifique-se de que a opcao digitada seja uma opcao da lista.\n");
            while (getchar() != '\n');  // Limpar o buffer de entrada
        }
    }while(valid != 1 || (opcao != 0 && opcao != 1));

    return opcao;
}

int validar_entrada3(const char* print){
    int opcao;
    int valid;

    do{
        printf("%s", print);
        valid = scanf("%d", &opcao);
        if (valid != 1) {
            printf("Opcao invalida, certifique-se de que a opcao digitada seja uma opcao da lista.\n");
            while (getchar() != '\n');  // Limpar o buffer de entrada
        }
    }while(valid != 1);

    return opcao;
}

int validar_entrada2(const char* print, int min, int max){
    int opcao;
    int valid;

    do{
        printf("%s", print);
        valid = scanf("%d", &opcao);
        if (valid != 1 || opcao < min || opcao > max) {
            printf("Opcao invalida, certifique-se de que a opcao digitada seja uma opcao da lista.\n");
            while (getchar() != '\n');  // Limpar o buffer de entrada
        }
    }while(valid != 1 || opcao < min || opcao > max);

    return opcao;
}

Menu_Pedido opcoes_menu(){
    int opcao;

    opcao = validar_entrada2("\nMenu servicos:\n"
        "  0 - Lavagem\n"
        "  1 - Passadoria\n"
        "  2 - Coleta e entrega\n"
        "  3 - Finalizar pedido\n"
        "  4 - Sair\n"
        "Escolha uma opcao: ", 0, 4);

    return (Menu_Pedido)opcao;
}

void menu_pedido(){
    Menu_Pedido opcao;
    int quantidade;
    int opcao2, opcao3, opcao4, opcao5;
    int alt;
    int fim = 0;
    Pedido* novo_pedido = NULL;
    Lista_Itens* novo_item = NULL;
    Lista_Itens* validar = NULL;

    FILE *arquivo_lavagem;
    FILE *arquivo_passadoria;
    FILE *arquivo_coleta_entrega;

    arquivo_lavagem = fopen("lavagem.txt", "r");
    arquivo_passadoria = fopen("passadoria.txt", "r");
    arquivo_coleta_entrega = fopen("coleta_entrega.txt", "r");

    Itens* lavagem = arrays_itens(arquivo_lavagem);
    Itens* passadoria = arrays_itens(arquivo_passadoria);
    Itens* coleta_entrega = arrays_itens(arquivo_coleta_entrega);
    
    do{
        opcao = opcoes_menu();
        switch(opcao){
            case LAVAGEM:
                imprimir_itens(lavagem, 8);
                opcao2 = validar_entrada("\n0 - Escolher uma opcao:\n1 - Voltar para o menu servicos.\nEscolha uma opcao: ");
                switch(opcao2){
                    case 0:
                        do{
                            opcao3 = validar_entrada2("Digite a opcao a ser adicionada ao pedido:\n", 0, 7);
                            quantidade = validar_entrada3("Digite a quantidade de itens dessa opcao a serem inseridos no pedido.\n");
                            validar = verificar(novo_item, &lavagem[opcao3]);
                            if(validar == NULL){
                                novo_item = inserir_item(novo_item, &lavagem[opcao3], quantidade, 0);
                                printf("Item inserido na lista.\n");
                                opcao4 = validar_entrada("Deseja adicionar outros itens?\n0 - SIM\t 1 - NAO\n");
                            }
                            else{
                                printf("O item ja foi adicionado a lista anteriormente.\n");
                                opcao5 = validar_entrada2("0 - Alterar quantidade\n"
                                    "1 - Excluir item da lista\n"
                                    "2 - Voltar ao menu inicial\n", 0, 2);
                                switch(opcao5){
                                    case 0:
                                        quantidade = validar_entrada3("Digite a quantidade a ser editada:\n");
                                        alterar_quantidade(novo_item, &lavagem[opcao3],quantidade);
                                        break;
                                    case 1:
                                        retirar_item(novo_item, &lavagem[opcao3]);
                                        printf("Item excluido.\n");
                                        break;
                                }
                            } 
                        }while(opcao4 == 0);
                        break;
                    case 1:
                        break;
                }
                break;
            case PASSADORIA:
                imprimir_itens(passadoria, 7);
                opcao2 = validar_entrada("\n0 - Escolher uma opcao:\n1 - Voltar para o menu servicos.\nEscolha uma opcao: ");
                switch(opcao2){
                    case 0:
                        do{
                            opcao3 = validar_entrada2("Digite a opcao a ser adicionada ao pedido:\n", 0, 6);
                            quantidade = validar_entrada3("Digite a quantidade de itens dessa opcao a serem inseridos no pedido.\n");
                            validar = verificar(novo_item, &passadoria[opcao3]);
                            if(validar == NULL){
                                novo_item = inserir_item(novo_item, &passadoria[opcao3], quantidade, 1);
                                printf("Item inserido na lista.\n");
                                opcao4 = validar_entrada("Deseja adicionar outros itens?\n0 - SIM\t 1 - NAO\n");
                            }
                            else{
                                printf("O item ja foi adicionado a lista anteriormente.\n");
                                opcao5 = validar_entrada2("0 - Alterar quantidade\n"
                                    "1 - Excluir item da lista\n"
                                    "2 - Voltar ao menu inicial\n", 0, 2);
                                switch(opcao5){
                                    case 0:
                                        quantidade = validar_entrada3("Digite a quantidade a ser editada:\n");
                                        alterar_quantidade(novo_item, &passadoria[opcao3],quantidade);
                                        break;
                                    case 1:
                                        retirar_item(novo_item, &passadoria[opcao3]);
                                        printf("Item excluido.\n");
                                        break;
                                    case 2:
                                        break;
                                }
                            }   
                        }while(opcao4 == 0);
                        break;
                    case 1:
                        break;
                }
                break;
            case COLETA_ENTREGA:
                imprimir_itens(coleta_entrega, 3);
                opcao2 = validar_entrada("\n0 - Escolher uma opcao:\n1 - Voltar para o menu servicos.\nEscolha uma opcao: ");
                switch(opcao2){
                    case 0:
                        opcao3 = validar_entrada2("Digite a opcao a ser adicionada ao pedido:\n", 0, 2);
                        validar = verificar(novo_item, &coleta_entrega[opcao3]);
                        if(validar == NULL){
                            novo_item = inserir_item(novo_item, &coleta_entrega[opcao3], 1, 2);
                            printf("Servico adicionado a lista.\n");
                        }
                        else{
                            opcao4 = validar_entrada2("Servico ja adicionado a lista.\n"
                                "0 - Modificar servico\n"
                                "1 - Excluir servico\n"
                                "2 - Voltar ao menu inicial\n", 0, 2);
                            switch(opcao4){
                                case 0:
                                    alt = validar_entrada2("Digite a opcao de servico correta a ser inserida na lista:\n", 0, 2);
                                    modificar_item(novo_item, &coleta_entrega[opcao3], &coleta_entrega[alt]);
                                    printf("Item modificado.\n");
                                    break;
                                case 1:
                                    retirar_item(novo_item, &coleta_entrega[opcao3]);
                                    printf("Item excluido.\n");
                                    break;
                                case 2:
                                    break;    
                            }   
                        }
                        break;
                    case 1:
                        break;
                }
                break;
            case FINALIZAR_PEDIDO:
                printf("Pedido final:\n");
                imprimir_lista(novo_item);
                opcao2 = validar_entrada("Tem certeza que seja finalizar o pedido?\n"
                    "0 - SIM\n"
                    "1 - NAO, ADICIONAR OUTROS ITENS\n");
                switch(opcao2){
                    case 0:
                        preencher_pedido(&novo_pedido, &novo_item);
                        printf("Pedido finalizado.\n");
                        fim = 1;
                    case 1:
                        break;
                }
                break;    
            case SAIR:
                fim = 1;
                break;              
        }           
    }while(fim != 1);
}