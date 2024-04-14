#include "pedidos.h"

Lista_Itens* inicializar_lista_itens(void){
    return NULL;
}

Lista_Itens* inserir_item(Lista_Itens* lista, Itens* item, int quantidade, Menu_Pedido tipo){
    Lista_Itens* novo_item = (Lista_Itens*) malloc(sizeof(Lista_Itens));
    if(novo_item == NULL){
        printf("Erro ao alocar memória.\n");
        return lista;
    }

    novo_item->tipo = tipo;
    novo_item->quantidade = quantidade;

    novo_item->item = (Itens*) malloc(sizeof(Itens));
    if(novo_item->item == NULL){
        printf("Erro ao alocar memória para o novo item.\n");
        free(novo_item);
        return lista;
    }

    strcpy(novo_item->item->nome, item->nome);
    novo_item->item->valor = item->valor;
    novo_item->proxItem = lista;

    return novo_item;
}// verificado

Lista_Itens* remover_item(Lista_Itens* lista, Itens* item){
    Lista_Itens* item_atual = lista;
    Lista_Itens* item_anterior = NULL;

    while(item_atual != NULL && strcmp(item_atual->item->nome, item->nome) != 0){
        item_anterior = item_atual;
        item_atual = item_atual->proxItem;
    }

    if(item_atual == NULL){
        printf("Item não encontrado na lista.\n");
        return lista;
    }

    if(item_anterior == NULL){
        lista = item_atual->proxItem;
    }
    else{
        item_anterior->proxItem = item_atual->proxItem;
    }

    free(item_atual);
    printf("Item removido da lista.\n");
    return lista;
} //verificado

Lista_Itens* verificar_existencia(Lista_Itens* lista, Itens* item, Menu_Pedido tipo){
    Lista_Itens* auxiliar;
    
    for(auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->proxItem){
        if(tipo == LAVAGEM){
            if(tipo == auxiliar->tipo && strcmp(auxiliar->item->nome, item->nome) == 0){
                return auxiliar;
            }
        }
        else if(tipo == PASSADORIA){
            if(auxiliar->tipo == PASSADORIA){
                return auxiliar;
            }
        }
        else if(tipo == COLETA_ENTREGA){
            if(auxiliar->tipo == COLETA_ENTREGA){
                return auxiliar;
            }
        }
    }
    return NULL;
}// verificado

void alterar_quantidade(Lista_Itens* lista, Itens* item, int quantidade){
    if(lista == NULL || item == NULL){
        printf("Erro: lista ou item inválido.\n");
        return;
    }
    Lista_Itens* auxiliar;

    for(auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->proxItem){
        if(strcmp(auxiliar->item->nome, item->nome) == 0){
            auxiliar->quantidade = quantidade;
            return;
        }
    } 
}// verificado

void modificar_item(Lista_Itens* lista, Itens* item, Itens* itemAux){
    Lista_Itens* auxiliar;

    for(auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->proxItem){
        if(strcmp(auxiliar->item->nome, item->nome) == 0){
            strcpy(auxiliar->item->nome, itemAux->nome);
            auxiliar->item->valor = itemAux->valor;
            break;
        }
    }
}// verificado

void imprimir_lista_itens(Lista_Itens* lista){
    Lista_Itens* auxiliar = lista;
    
    printf("\tLista de itens:\n");
    while(auxiliar != NULL){
        printf("\t\t%dx %s\t%.2lf\n", auxiliar->quantidade, auxiliar->item->nome, auxiliar->item->valor * auxiliar->quantidade);
        auxiliar = auxiliar->proxItem;
    }
}// verificado

void realocar_memoria(Itens** novo, int* tamanho){
    (*tamanho)++;
    *novo = (Itens*) realloc(*novo, *tamanho * sizeof(Itens));
    if(*novo == NULL){
        printf("Erro ao realocar memória.\n");
        exit(EXIT_FAILURE);
    }
}// verificado

Itens* arrays_itens(FILE* arquivo){
    int tamanho = 0;
    Itens* novo = NULL;

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo para leitura.\n");
        return NULL;
    }

    novo = (Itens*) malloc(sizeof(Itens));
    if(novo == NULL){
        printf("Erro ao alocar memória para leitura.\n");
        return NULL;
    }

    realocar_memoria(&novo, &tamanho);

    while(fscanf(arquivo, "%49[^\t]%lf\n", novo[tamanho - 1].nome, &novo[tamanho - 1].valor) == 2){
        realocar_memoria(&novo, &tamanho);
    }

    fclose(arquivo);

    return novo;
}// verificado

void imprimir_itens(Itens* itens_array, int tamanho){
    int i;
    for(i = 0; i < tamanho; i++){
        printf("%d\t%s\tR$ %.2lf\n", i, itens_array[i].nome, itens_array[i].valor);
    }
}// verificado

Pedido* preencher_pedido(Pedido** novo_pedido, Lista_Itens** lista){
    (*novo_pedido) = (Pedido*) malloc(sizeof(Pedido));
    if((*novo_pedido) == NULL){
        printf("Erro ao alocar memória para novo pedido.\n");
        return NULL;
    }

    Lista_Itens* auxiliar;
    double soma = 0;
    (*novo_pedido)->id = rand() % 1000 + 1;
    (*novo_pedido)->lista = *lista;
    int status_encontrado = 0;

    for(auxiliar = *lista; auxiliar != NULL; auxiliar = auxiliar->proxItem){
        if(auxiliar->tipo == COLETA_ENTREGA && (strcmp(auxiliar->item->nome, "Apenas coleta") == 0 || strcmp(auxiliar->item->nome, "Coleta e entrega") == 0)){
            status_encontrado = 1;
            break;
        }
    }

    (*novo_pedido)->status = (status_encontrado) ? PENDENTE_PROCESSAMENTO : PENDENTE_COLETA;

    for(auxiliar = *lista; auxiliar != NULL; auxiliar = auxiliar->proxItem){
        soma += (auxiliar->quantidade * auxiliar->item->valor);
    }
    (*novo_pedido)->total_pedido = soma;

    return *novo_pedido;
}// verificado

void imprimir_pedido(Pedido* pedido){
    printf("\tId: %d\n", pedido->id);
    imprimir_lista_itens(pedido->lista);
    imprimir_status_pedido(pedido);
    printf("\tTotal do pedido: %.2lf\n", pedido->total_pedido);
}

int validar_entrada(const char* print, int min, int max){
    int opcao;
    
    if(max == 0 && min == 0){
        do{
            printf("%s", print);
            char entrada[50];
            scanf(" %[^\n]", entrada);
            entrada[strcspn(entrada, "\n")] = '\0';

            int tamanho = strlen(entrada);

            if(tamanho > 0 && isdigit(entrada[0])){
                opcao = atoi(entrada);
                break;
            }
            else{
                printf("Quantidade inválida, certifique-se de digitar um número inteiro.\n");
            }
        }while(1);
    }
    else{
        do{
            printf("%s", print);
            char entrada[50];
            scanf(" %[^\n]", entrada);
            entrada[strcspn(entrada, "\n")] = '\0';

            int tamanho = strlen(entrada);

            if(tamanho == 1 && isdigit(entrada[0])){
                opcao = atoi(entrada);
                if (opcao >= min && opcao <= max) {
                    break;
                } 
                else{
                    printf("Opção inválida, certifique-se de que a opcao digitada seja uma opção da lista.\n");
                }
            } 
            else{
                printf("Opção inválida, certifique-se de que a opcao digitada seja uma opção da lista.\n");
            }
        }while(1);
    }
    return opcao;
}

Menu_Pedido opcoes_menu(void){
    int opcao;

    opcao = validar_entrada("\nMENU SERVIÇOS\n"
        "  1 - Ver tabela de preços\n"
        "  2 - Finalizar pedido\n"
        "  3 - Cancelar pedido e sair para o menu principal\n"
        "Escolha uma opção: ", 1, 5);

    return (Menu_Pedido)opcao;
}// verificado

void processar_servico(Itens* servico, Lista_Itens** novo_item, Menu_Pedido opcao, int quantidade_itens){
    int opcao3, opcao4, opcao5, quantidade, alt;
    Lista_Itens* validar = NULL;

    do{
        if(opcao == LAVAGEM){
            opcao3 = validar_entrada("\nDigite o código do item desejado: ", 0, quantidade_itens - 1);

            validar = verificar_existencia(*novo_item, &servico[opcao3], opcao);
            if(validar == NULL){
                quantidade = validar_entrada("Digite a quantidade de itens dessa opção: ", 0, 0);
                *novo_item = inserir_item(*novo_item, &servico[opcao3], quantidade, opcao);
                printf("Item adicionado ao pedido.\n\n");
            }
            else{
                printf("O item já foi adicionado à lista anteriormente");
                opcao4 = validar_entrada("1 - Alterar quantidade\n2 - Excluir item da lista\n3 - Voltar ao menu serviços\nEscolha uma opção: ", 1, 3);
                switch(opcao4){
                    case 1:
                        quantidade = validar_entrada("Digite a nova quantidade: ", 0, 0);
                        alterar_quantidade(*novo_item, &servico[opcao3], quantidade);
                        break;
                    case 2:
                        remover_item(*novo_item, &servico[opcao3]);
                        printf("Item excluído da lista.\n");
                        break;
                    case 3:
                        break;
                }
            }
        }
        else if(opcao == COLETA_ENTREGA){
            opcao3 = validar_entrada("\nDigite o código do item desejado: ", 0, quantidade_itens - 1);

            validar = verificar_existencia(*novo_item, &servico[opcao3], opcao);
            if(validar == NULL){
                *novo_item = inserir_item(*novo_item, &servico[opcao3], 1, opcao);
                printf("Item adicionado ao pedido.\n");
            }
            else{
                printf("\nO item já foi adicionado à lista anteriormente.\n");
                opcao4 = validar_entrada("1 - Modificar serviço\n2 - Excluir serviço\n3 - Voltar ao menu serviços\nEscolha uma opção: ", 1, 3);
                switch(opcao4){
                    case 1:
                        alt = validar_entrada("\nDigite a opção correta a ser inserida na lista: ", 0, 2);
                        modificar_item(*novo_item, &servico[opcao3], &servico[alt]);
                        printf("Item modificado.\n");
                        break;
                    case 2:
                        remover_item(*novo_item, &servico[opcao3]);
                        printf("Item de coleta e entrega excluído.\n");
                        break;
                    case 3:
                        break;
                }
            }
        }

        opcao4 = validar_entrada("Deseja adicionar outros itens?\n1 - Sim\n2 - Não\nEscolha uma opção: ", 1, 2);
    }while(opcao4 == 1);
}// vericado


Pedido* menu_pedido(void){
    Menu_Pedido opcao;
    int quantidade;
    int opcao2, opcao3, opcao4, opcao5, alt;
    int fim = 0;
    char* auxiliar[50];
    Itens* item_auxiliar;
    Pedido* novo_pedido = NULL;
    Pedido* preenchido = NULL;
    Lista_Itens* novo_item = NULL;
    Lista_Itens* validar = NULL;

    FILE *arquivo_lavagem, *arquivo_coleta_entrega;
    arquivo_lavagem = fopen("lavagem.txt", "r");
    arquivo_coleta_entrega = fopen("coleta_entrega.txt", "r");

    Itens* lavagem = arrays_itens(arquivo_lavagem);
    Itens* coleta_entrega = arrays_itens(arquivo_coleta_entrega);

    fclose(arquivo_lavagem);
    fclose(arquivo_coleta_entrega);
    
    do{
        opcao = opcoes_menu();
        switch(opcao){
            case LAVAGEM:
                printf("\nTabela de preços:\n");
                imprimir_itens(lavagem, 8);
                opcao2 = validar_entrada("\n1 - Escolher uma opção:\n2 - Voltar para o menu serviços\nEscolha um opção: ", 1, 2);
                switch(opcao2){
                    case 1:
                        processar_servico(lavagem, &novo_item, opcao, 8);
                        break;
                    case 2:
                        break;
                }
                break;
            case FINALIZAR_PEDIDO:
                opcao3 = validar_entrada("\nDeseja adicionar serviço de passadoria?\n1 - Sim\n2 - Não\nEscolha uma opção: ", 1, 2);
                switch(opcao3){
                    case 1:
                        item_auxiliar = (Itens*) malloc(sizeof(Itens));
                        if(item_auxiliar == NULL){
                            printf("Erro ao alocar memória para item auxiliar.\n");
                            exit(EXIT_FAILURE);
                        }
                        strcpy(item_auxiliar->nome, "Serviço de passadoria                             ");
                        item_auxiliar->valor = 50;
                        validar = verificar_existencia(novo_item, item_auxiliar, PASSADORIA);
                        if(validar == NULL){
                            novo_item = inserir_item(novo_item, item_auxiliar, 1, PASSADORIA);
                            printf("Item adicionado ao pedido.\n");
                        }
                        else{
                            printf("Serviço de passadoria já adicionado ao pedido.\n");
                            opcao3 = validar_entrada("Deseja remover o serviço de passadoria do pedido?\n1 - Sim\n2 - Não, voltar ao menu pedido\nEscolha uma opção: ", 1, 2);
                            switch(opcao3){
                                case 1:
                                    remover_item(novo_item, item_auxiliar);
                                    printf("Serviço de passadoria excluído do pedido.\n");
                                    break;
                                case 2:
                                    break;
                            }
                        }
                        break;
                    case 2:
                        break;
                }
                opcao4 = validar_entrada("\nDeseja adicionar serviço de coleta e entrega?\n1 - Sim\n2 - Não\nEscolha uma opção: ", 1, 2);
                switch(opcao4){
                    case 1:
                        printf("\nOpções de serviços de coleta e entrega:\n");
                        imprimir_itens(coleta_entrega, 3);
                        opcao2 = validar_entrada("\n1 - Escolher uma opção:\n2 - Voltar para o menu serviços\nEscolha uma opcao: ", 1, 2);
                        switch(opcao2){
                            case 1:
                                processar_servico(coleta_entrega, &novo_item, COLETA_ENTREGA, 3);
                                break;
                            case 2:
                                break;
                        }
                        break;
                    case 2:
                        break;
                }
                printf("Pedido final:\n");
                imprimir_lista_itens(novo_item);
                opcao2 = validar_entrada("\nTem certeza que deseja finalizar o pedido?\n"
                    "1 - Sim\n"
                    "2 - Não, voltar ao menu serviços\nEscolha um opção: ", 1, 2);
                switch(opcao2){
                    case 1:
                        preenchido = preencher_pedido(&novo_pedido, &novo_item);
                        if(preenchido != NULL){
                            printf("\nPedido finalizado.\n");
                            return preenchido;
                        }
                        else{
                            printf("Erro ao preencher pedido.\n");
                        }
                        break;
                    case 2:
                        break;
                }
                break;    
            case SAIR:
                fim = 1;
                break;              
        }           
    }while(fim != 1);

    free(lavagem);
    free(coleta_entrega);

    return NULL;
}// verificado

void escrever_lista_itens_arquivo(Lista_Itens* lista, FILE* arquivo){
    Lista_Itens* auxiliar = lista;

    fprintf(arquivo, "\tLista de itens:\n");
    while(auxiliar != NULL){
        fprintf(arquivo, "\t\t%dx %s\t%lf\n", auxiliar->quantidade, auxiliar->item->nome, auxiliar->item->valor * auxiliar->quantidade);
        auxiliar = auxiliar->proxItem;
    }
}

void escrever_status_pedido(FILE* arquivo, Pedido* pedido){
    switch(pedido->status){
        case PENDENTE_COLETA:
            fprintf(arquivo, "\tStatus do Pedido: Pendente de Coleta\n");
            break;
        case PENDENTE_PROCESSAMENTO:
            fprintf(arquivo, "\tStatus do Pedido: Pendente de Processamento\n");
            break;
        case EM_PROCESSAMENTO:
            fprintf(arquivo, "\tStatus do Pedido: Em Processamento\n");
            break;
        case PRONTO_ENTREGA:
            fprintf(arquivo, "\tStatus do Pedido: Pronto para Entrega\n");
            break;
        case CONCLUIDO:
            fprintf(arquivo, "\tStatus do Pedido: Concluído\n");
            break;
    }
}

void imprimir_status_pedido(Pedido* pedido){
    switch(pedido->status){
        case PENDENTE_COLETA:
            printf("\tStatus do Pedido: Pendente de Coleta\n");
            break;
        case PENDENTE_PROCESSAMENTO:
            printf("\tStatus do Pedido: Pendente de Processamento\n");
            break;
        case EM_PROCESSAMENTO:
            printf("\tStatus do Pedido: Em Processamento\n");
            break;
        case PRONTO_ENTREGA:
            printf("\tStatus do Pedido: Pronto para Entrega\n");
            break;
        case CONCLUIDO:
            printf("\tStatus do Pedido: Concluído\n");
            break;
    }
}

void modificar_status(Pedido* pedido){
    int status;
    imprimir_status_pedido(pedido);
    status = validar_entrada("\nAtualizar pedido para qual status?\n"
    "1 - Em processamento\n"
    "2 - Pronto para entrega\n"
    "3 - Concluído\nEscolha uma opção: ", 1, 3);

    switch(status){
        case 1:
            pedido->status = EM_PROCESSAMENTO;
            break;
        case 2:
            pedido->status = PRONTO_ENTREGA;
            break;
        case 3:
            pedido->status = CONCLUIDO;
            break;
    }
}