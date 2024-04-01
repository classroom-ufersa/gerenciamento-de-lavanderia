#include <stdbool.h>
#include "pedidos.h"
#include "clientes.h"

Lista_Itens* inicializar_lista_itens(void){
    return NULL;
}// verificado

Lista_Itens* inserir_item(Lista_Itens* lista, Itens* item, int quantidade, int tipo){
    Lista_Itens* novo = (Lista_Itens*) malloc(sizeof(Lista_Itens));
    if(novo == NULL){
        printf("Erro ao alocar memï¿½ria.\n");
        return lista;
    }

    novo->tipo = tipo;
    novo->item = (Itens*) malloc(sizeof(Itens));
    if(novo->item == NULL){
        printf("Erro ao alocar memï¿½ria para o novo item.\n");
        free(novo);
        return lista;
    }

    novo->item->id = item->id;
    strcpy(novo->item->nome, item->nome);
    novo->quantidade = quantidade;
    novo->item->valor = item->valor;
    novo->proxItem = lista;
    return novo;
}// verificado

Lista_Itens* remover_item(Lista_Itens* lista, Itens* item, int tipo){
    Lista_Itens* atual = lista;
    Lista_Itens* anterior = NULL;

    while(atual != NULL && atual->tipo == tipo && strcmp(atual->item->nome, item->nome) != 0){
        anterior = atual;
        atual = atual->proxItem;
    }

    if(atual == NULL){
        printf("Item nï¿½o encontrado na lista.\n");
        return lista;
    }

    if(anterior == NULL){
        lista = atual->proxItem;
    }
    else{
        anterior->proxItem = atual->proxItem;
    }

    free(atual);
    printf("Item removido da lista.\n");
    return lista;
} //verificado

Lista_Itens* verificar_existencia(Lista_Itens* lista, Itens* item, int tipo){
    Lista_Itens* auxiliar;
    
    for(auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->proxItem){
        if(tipo == auxiliar->tipo && (strcmp(auxiliar->item->nome, item->nome) == 0)){
            return auxiliar;
        }
    }
    return NULL;
}// verificado

void alterar_quantidade(Lista_Itens* lista, Itens* item, int quantidade, int tipo){
    if(lista == NULL || item == NULL){
        printf("Erro: lista ou item invï¿½lido.\n");
        return;
    }
    Lista_Itens* auxiliar;

    for(auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->proxItem){
        if(auxiliar->tipo == tipo && (auxiliar->item->nome, item->nome) == 0){
            auxiliar->quantidade = quantidade;
            return;
        }
    } 
}// verificado

void modificar_item(Lista_Itens* lista, Itens* item, Itens* itemAux, int tipo){
    Lista_Itens* auxiliar;

    for(auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->proxItem){
        if(auxiliar->tipo == tipo && (auxiliar->item->nome, item->nome) == 0){
            auxiliar->item->id = itemAux->id;
            strcpy(auxiliar->item->nome, itemAux->nome);
            auxiliar->item->valor = itemAux->valor;
            break;
        }
    }
}// verificado

void imprimir_lista_itens(Lista_Itens* lista){
    int lavagem = 0;
    int passadoria = 0;
    int coleta_entrega = 0;
    Lista_Itens* auxiliar;

    for(auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->proxItem){
        if(auxiliar->tipo == 1){
            lavagem = 1;
        }
        if(auxiliar->tipo == 2){
            passadoria = 1;
        }
        if(auxiliar->tipo == 3){
            coleta_entrega = 1;
        }
    }
    
    if(lavagem){
        printf("Servicos de lavagem:\n");
        for(auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->proxItem){
            if(auxiliar->tipo == 1){
                printf("\t%d\t%s\n", auxiliar->quantidade, auxiliar->item->nome);
            } // MODIFICAR IMPRESSï¿½O
        }
    }
    else{
        printf("Nenhum serviï¿½o de lavagem incluso.\n");
    }

    if(passadoria){
        printf("Serviï¿½os de passadoria:\n");
        for(auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->proxItem){
            if(auxiliar->tipo == 2){
                printf("\t%d\t%s\n", auxiliar->quantidade, auxiliar->item->nome);
            }
        }
    }
    else{
        printf("Nenhum serviï¿½o de passadoria incluso.\n");
    }

    if(coleta_entrega){
        for(auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->proxItem){
            if(auxiliar->tipo == 3){
                printf("\t%d\t%s\n", auxiliar->quantidade, auxiliar->item->nome);
            }
        }
    }
    else{
        printf("Nenhum serviï¿½o de coleta e entrega incluso.\n");
    }
}// verificado

void realocar_memoria(Itens** novo, int* tamanho){
    (*tamanho)++;
    *novo = (Itens*) realloc(*novo, *tamanho * sizeof(Itens));
    if(*novo == NULL){
        printf("Erro ao alocar memoria.\n");
        exit(EXIT_FAILURE);
    }
}// verificado

Itens* arrays_itens(FILE* arquivo){
    int tamanho = 0;
    Itens* novo = NULL;

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo.\n");
        return NULL;
    }

    novo = (Itens*) malloc(sizeof(Itens));
    if(novo == NULL){
        printf("Erro ao alocar memï¿½ria.\n");
        return NULL;
    }

    realocar_memoria(&novo, &tamanho);

    while(fscanf(arquivo, "%d\t%49[^\t]%lf\n", &novo[tamanho - 1].id, novo[tamanho - 1].nome, &novo[tamanho - 1].valor) == 3){
        realocar_memoria(&novo, &tamanho);
    }

    fclose(arquivo);

    return novo;
}// verificado

void imprimir_itens(Itens* itens_array, int tamanho){
    int i;
    for(i = 0; i < tamanho; i++){
        printf("%d\t%s\tR$ %.2lf\n", itens_array[i].id, itens_array[i].nome, itens_array[i].valor);
    }
}// verificado

Pedido* preencher_pedido(Pedido** novo_pedido, Lista_Itens** lista){
    (*novo_pedido) = (Pedido*) malloc(sizeof(Pedido));
    if((*novo_pedido) == NULL){
        printf("Erro ao alocar memï¿½ria para novo pedido.\n");
        return NULL;
    }

    Lista_Itens* auxiliar;
    double soma = 0;
    (*novo_pedido)->id = rand() % 1000 + 1;
    (*novo_pedido)->lista = *lista;
    int status_encontrado = 0;

    for(auxiliar = *lista; auxiliar != NULL; auxiliar = auxiliar->proxItem){
        if(auxiliar->tipo == 3 && (auxiliar->item->id == 0 || auxiliar->item->id == 2)){
            (*novo_pedido)->status = 0;
            status_encontrado = 1;
            break;
        }
    }

    (*novo_pedido)->status = (status_encontrado) ? 0 : 1;

    for(auxiliar = *lista; auxiliar != NULL; auxiliar = auxiliar->proxItem){
        soma += auxiliar->item->valor;
    }
    (*novo_pedido)->total_pedido = soma;

    return *novo_pedido;
}// verificado

int validar_entrada(const char* print, int min, int max){
    int opcao;
    int valid;
    
    if(max == 0 && min == 0){
        do{
            printf("%s", print);
            valid = scanf("%d", &opcao);
            if (valid != 1) {
                printf("Opcao invalida, certifique-se de que a opcao digitada seja uma opcao da lista.\n");
                while (getchar() != '\n'); 
            }
        }while(valid != 1);
    }
    else{
        do{
            printf("%s", print);
            valid = scanf("%d", &opcao);
            if (valid != 1 || opcao < min || opcao > max) {
                printf("Opcao invalida, certifique-se de que a opcao digitada seja uma opcao da lista.\n");
                while (getchar() != '\n');
            }
        }while(valid != 1 || opcao < min || opcao > max);
    }
    
    return opcao;
}// verificado

Menu_Pedido opcoes_menu(){
    int opcao;

    opcao = validar_entrada("\nMENU SERVIï¿½OS\n"
        "  1 - Lavagem\n"
        "  2 - Passadoria\n"
        "  3 - Coleta e entrega\n"
        "  4 - Finalizar pedido\n"
        "  5 - Sair\n"
        "Escolha uma opcao: ", 1, 5);

    return (Menu_Pedido)opcao;
}// verificado

void processar_servico(Itens* servico, Lista_Itens** novo_item, int tipo, int quantidade_itens){
    int opcao3, opcao4, opcao5, quantidade, alt;
    Lista_Itens* validar = NULL;

    do{
        opcao3 = validar_entrada("Digite o cï¿½digo do item desejado: ", 0, quantidade_itens - 1);

        validar = verificar_existencia(*novo_item, &servico[opcao3], tipo);
        if(validar == NULL){
            if(tipo == 3){
                *novo_item = inserir_item(*novo_item, &servico[opcao3], 1, tipo);
                printf("Serviï¿½o de coleta e entrega adicionado ao pedido.\n");
                break;
            } 
            else{
                quantidade = validar_entrada("Digite a quantidade de itens dessa opção:\n - ", 0, 0);
                *novo_item = inserir_item(*novo_item, &servico[opcao3], quantidade, tipo);
                printf("Item adicionado ao pedido.\n");
            }
        } 
        else{
            printf("O item jï¿½ foi adicionado ï¿½ lista anteriormente.\n");
            opcao4 = validar_entrada("1 - Alterar quantidade\n2 - Excluir item da lista\n3 - Voltar ao menu inicial\nEscolha uma opï¿½ï¿½o: ", 1, 3);
            switch(opcao4){
                case 1:
                    if(tipo == 3){
                        opcao5 = validar_entrada("1 - Modificar serviï¿½o\n2 - Excluir serviï¿½o\n3 - Voltar ao menu inicial\nEscolha uma opï¿½ï¿½o: ", 1, 3);
                        switch(opcao5){
                            case 1:
                                alt = validar_entrada("Digite a opï¿½ï¿½o de serviï¿½o correta a ser inserida na lista: ", 0, 2);
                                modificar_item(*novo_item, &servico[opcao3], &servico[alt], tipo);
                                printf("Item modificado.\n");
                                break;
                            case 2:
                                remover_item(*novo_item, &servico[opcao3], tipo);
                                printf("Item de coleta e entrega excluï¿½do.\n");
                                break;
                            case 3:
                                break;
                        }
                    } 
                    else{
                        quantidade = validar_entrada("Digite a nova quantidade: ", 0, 0);
                        alterar_quantidade(*novo_item, &servico[opcao3], quantidade, tipo);
                    }
                    break;
                case 2:
                    remover_item(*novo_item, &servico[opcao3], tipo);
                    printf("Item excluï¿½do.\n");
                    break;
                case 3:
                    break;
            }
        }
        opcao4 = validar_entrada("Deseja adicionar outros itens?\n1 - Sim\t2 - Nï¿½o\nEscolha uma opï¿½ï¿½o: ", 1, 2);
    }while(opcao4 == 1);
}// vericado


Pedido* menu_pedido(void){
    Menu_Pedido opcao;
    int quantidade;
    int opcao2, opcao3, opcao4, opcao5, alt;
    int fim = 0;
    Pedido* novo_pedido = NULL;
    Pedido* preenchido = NULL;
    Lista_Itens* novo_item = NULL;
    Lista_Itens* validar = NULL;

    FILE *arquivo_lavagem, *arquivo_passadoria, *arquivo_coleta_entrega;
    arquivo_lavagem = fopen("lavagem.txt", "r");
    arquivo_passadoria = fopen("passadoria.txt", "r");
    arquivo_coleta_entrega = fopen("coleta_entrega.txt", "r");

    Itens* lavagem = arrays_itens(arquivo_lavagem);
    Itens* passadoria = arrays_itens(arquivo_passadoria);
    Itens* coleta_entrega = arrays_itens(arquivo_coleta_entrega);

    fclose(arquivo_lavagem);
    fclose(arquivo_passadoria);
    fclose(arquivo_coleta_entrega);
    
    do{
        opcao = opcoes_menu();
        switch(opcao){
            case LAVAGEM:
                imprimir_itens(lavagem, 8);
                opcao2 = validar_entrada("\n1 - Escolher uma opï¿½ï¿½o:\n2 - Voltar para o menu serviï¿½os.\n - ", 1, 2);
                switch(opcao2){
                    case 1:
                        processar_servico(lavagem, &novo_item, 1, 8);
                        break;
                    case 2:
                        break;
                }
                break;
            case PASSADORIA:
                imprimir_itens(passadoria, 7);
                opcao2 = validar_entrada("\n1 - Escolher uma opcao:\n2 - Voltar para o menu servicos.\n - ", 1, 2);
                switch(opcao2){
                    case 1:
                        processar_servico(passadoria, &novo_item, 2, 7);
                        break;
                    case 2:
                        break;
                }
                break;
            case COLETA_ENTREGA:
                imprimir_itens(coleta_entrega, 3);
                opcao2 = validar_entrada("\n1 - Escolher uma opcao:\n2 - Voltar para o menu servicos.\nEscolha uma opcao: ", 1, 2);
                switch(opcao2){
                    case 1:
                        processar_servico(coleta_entrega, &novo_item, 3, 3);
                        break;
                    case 2:
                        break;
                }
                break;
            case FINALIZAR_PEDIDO:
                printf("Pedido final:\n");
                imprimir_lista_itens(novo_item);
                opcao2 = validar_entrada("Tem certeza que deseja finalizar o pedido?\n"
                    "1 - SIM\n"
                    "2 - NAO, ADICIONAR OUTROS ITENS\n", 1, 2);
                switch(opcao2){
                    case 1:
                        preenchido = preencher_pedido(&novo_pedido, &novo_item);
                        if(preenchido != NULL){
                            printf("Pedido finalizado.\n");
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
    free(passadoria);
    free(coleta_entrega);

    return NULL;
}// verificado

void imprimir_pedido(Pedido* pedido){
    printf("Identificaï¿½ï¿½o: %d\n", pedido->id);
    imprimir_lista_itens(pedido->lista);
    printf("Status do pedido: %d\n", pedido->status);
    printf("Valor total do pedido: %.2lf\n", pedido->total_pedido);
}// verificado

void escrever_lista_itens_arquivo(Lista_Itens* lista, FILE* arquivo){
    Lista_Itens* auxiliar = lista;
    int lavagem, passadoria, coleta_entrega = 0;

    while(auxiliar != NULL){
        if(auxiliar->tipo == 1){
            lavagem = 1;
        } 
        else if(auxiliar->tipo == 2){
            passadoria = 1;
        } 
        else if(auxiliar->tipo == 3){
            coleta_entrega = 1;
        }
        auxiliar = auxiliar->proxItem;
    }

    fprintf(arquivo, "\tLista de itens:\n");
    if(lavagem == 1){
        fprintf(arquivo, "\t\tServiï¿½os de lavagem:\n");
        auxiliar = lista;
        while(auxiliar != NULL){
            if(auxiliar->tipo == 1){
                fprintf(arquivo, "\t\t\t%dx %s\n", auxiliar->quantidade, auxiliar->item->nome);
            }
            auxiliar = auxiliar->proxItem;
        }
    }

    if(passadoria == 1){
        fprintf(arquivo, "\t\tServiï¿½os de passadoria:\n");
        auxiliar = lista;
        while(auxiliar != NULL){
            if(auxiliar->tipo == 2){
                fprintf(arquivo, "\t\t\t%dx %s\n", auxiliar->quantidade, auxiliar->item->nome);
            }
            auxiliar = auxiliar->proxItem;
        }
    }

    if(coleta_entrega == 1){
        fprintf(arquivo, "\t\tServiï¿½os de coleta e entrega:\n");
        auxiliar = lista;
        while(auxiliar != NULL){
            if(auxiliar->tipo == 3){
                fprintf(arquivo, "\t\t\t%s\n", auxiliar->item->nome);
            }
            auxiliar = auxiliar->proxItem;
        }
    }
}

void escrever_status_pedido(FILE* arquivo, Pedido* pedido){
    switch (pedido->status) {
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
            fprintf(arquivo, "\tStatus do Pedido: Concluï¿½do\n");
            break;
    }
}

void imprimir_status_pedido(Pedido* pedido){
    switch (pedido->status) {
        case PENDENTE_COLETA:
            printf("Status do Pedido: Pendente de Coleta\n");
            break;
        case PENDENTE_PROCESSAMENTO:
            printf("Status do Pedido: Pendente de Processamento\n");
            break;
        case EM_PROCESSAMENTO:
            printf("Status do Pedido: Em Processamento\n");
            break;
        case PRONTO_ENTREGA:
            printf("Status do Pedido: Pronto para Entrega\n");
            break;
        case CONCLUIDO:
            printf("Status do Pedido: Concluï¿½do\n");
            break;
    }
}