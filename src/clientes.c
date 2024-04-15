#include "../include/sistema.h"
#include "../include/pedidos.h"

Clientes* inicializar_lista_clientes(void){
    return NULL;
}

Lista_Pedidos* inicializar_lista_pedidos(void){
    return NULL;
}

Clientes* inserir_cliente(Clientes* lista, char nome[50], char contato[15], char cpf[15]){
    Clientes* novo_cliente = alocar_memoria(sizeof(Clientes));

    strcpy(novo_cliente->nome, nome);
    strcpy(novo_cliente->contato, contato);
    strcpy(novo_cliente->Cpf, cpf);

    Lista_Pedidos* lista_pedidos = inicializar_lista_pedidos();
    novo_cliente->lista = lista_pedidos;

    if(lista == NULL || (strcmp(nome, lista->nome) < 0) || (strcmp(nome, lista->nome) == 0 && strcmp(cpf, lista->Cpf) < 0)){
        novo_cliente->prox = lista;
        return novo_cliente;
    }

    Clientes* anterior = lista;
    while(anterior->prox != NULL && strcmp(nome, anterior->prox->nome) == 0){
        anterior = anterior->prox;
    }

    novo_cliente->prox = anterior->prox;
    anterior->prox = novo_cliente;

    return lista;
}

Clientes* adicionar_clientes(Clientes* lista){
    char nome[50];
    char contato[16];
    char cpf[15];
    Clientes* novo;

    do{
        printf("\nDigite o nome do cliente: ");
        scanf(" %[^\n]", nome);
        nome[strcspn(nome, "\n")] = '\0';
    }while(validar_nome(nome) == 1);
    formatar_nome(nome);

    do{
        printf("Digite o número de contato do cliente: ");
        scanf(" %[^\n]", contato);
        contato[strcspn(contato, "\n")] = '\0';

        if(validar_contato(contato) == 0){
            printf("Número de telefone inválido. O número deve conter exatamente 11 dígitos.\n");
        } 
        else{
            formatar_contato(contato);
            contato[15] = '\0';
            break;
        }
    }while(1);

    do{
        printf("Digite o CPF do cliente: ");
        scanf(" %[^\n]", cpf);
        cpf[strcspn(cpf, "\n")] = '\0';

        if(validar_cpf(cpf) == 0){
            printf("CPF inválido. O CPF deve conter 11 dígitos numéricos.\n");
        } 
        else{
            formatar_cpf(cpf); 

            if (buscar_cliente_por_cpf(lista, cpf) != NULL) {
                printf("Já existe um cliente com o mesmo CPF na lista.\n");
                return lista;
            }
            else{
                printf("Cadastrado com sucesso!\n");
                break;
            }
        }
    }while(1);

    novo = inserir_cliente(lista, nome, contato, cpf);
    return novo;
}

Clientes* remover_cliente(Clientes* lista, Clientes* cliente) {
    if (lista == NULL) {
        printf("Lista de clientes vazia.\n");
        return NULL;
    }

    if (cliente == NULL) {
        printf("Cliente não encontrado na lista.\n");
        return lista;
    }

    Clientes* atual = lista;
    Clientes* anterior = NULL;

    while (atual != NULL && strcmp(atual->Cpf, cliente->Cpf) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Cliente não encontrado na lista.\n");
        return lista;
    }

    if (anterior == NULL) {
        lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Cliente removido da lista e arquivo atualizado.\n");
    return lista;
}

Clientes* buscar_cliente(Clientes* lista){
    char nome[50];
    Clientes* auxiliar = lista;
    Clientes* resultados = NULL;

    do {
        printf("\nDigite o nome do cliente: ");
        scanf(" %[^\n]", nome);
        nome[strcspn(nome, "\n")] = '\0';
    } while (validar_nome(nome) == 1);
    formatar_nome(nome);

    while (auxiliar != NULL) {
        if (strcmp(auxiliar->nome, nome) == 0) {
            if (resultados == NULL) {
                resultados = auxiliar;
            } else {
                printf("Foram encontrados mais de um cliente com o mesmo nome.\n");
                printf("Cliente: %s\n", resultados->nome);
                printf("Digite o CPF do cliente desejado para confirmar a operacao: ");
                char cpf[15];
                scanf(" %[^\n]", cpf);
                formatar_cpf(cpf);
                cpf[strcspn(cpf, "\n")] = '\0';

                if (strcmp(auxiliar->Cpf, cpf) == 0) {
                    return auxiliar;
                }
            }
        }
        auxiliar = auxiliar->prox;
    }

    if (resultados == NULL) {
        printf("Cliente não encontrado no sistema.\n");
    }

    return resultados;
}


Clientes* buscar_cliente_por_cpf(Clientes* lista, const char* cpf) {
    Clientes* atual = lista;

    while (atual != NULL) {
        if (strcmp(atual->Cpf, cpf) == 0) {
            return atual;
        }
        atual = atual->prox;
    }

    return NULL;
}

void atualizar_ids_pedidos(Lista_Pedidos* lista) {
    Lista_Pedidos* atual = lista;
    int id_contador = 1;

    while(atual != NULL){
        atual->pedido->id = id_contador;
        id_contador++;
        atual = atual->prox;
    }
}

void adicionar_pedidos(Clientes* lista_principal, Clientes* cliente_aux, Pedido* pedido){
    Lista_Pedidos* novo_pedido = alocar_memoria(sizeof(Lista_Pedidos));
    int id_contador = 1;

    novo_pedido->pedido = pedido;
    novo_pedido->prox = NULL;

    Clientes* atual = lista_principal;
    while(atual != NULL){
        if(strcmp(atual->Cpf, cliente_aux->Cpf) == 0){
            Lista_Pedidos* aux = atual->lista;
            Lista_Pedidos* anterior = NULL;

            while(aux != NULL){
                anterior = aux;
                aux = aux->prox;
                id_contador++;
            }

            if(anterior == NULL){
                novo_pedido->pedido->id = 1;
                novo_pedido->prox = atual->lista;
                atual->lista = novo_pedido;
            } 
            else{
                novo_pedido->pedido->id = id_contador++;
                anterior->prox = novo_pedido;
                novo_pedido->prox = aux;
            }

            break;
        }
        atual = atual->prox;
    }
}

Lista_Pedidos* remover_pedido(Clientes* lista_principal, Clientes* cliente_aux, Pedido* pedido){
    Lista_Pedidos* atual = cliente_aux->lista;
    Lista_Pedidos* anterior = NULL;

    while(atual != NULL && atual->pedido != pedido){
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL){
        printf("Pedido não encontrado na lista.\n");
        return cliente_aux->lista;
    }

    if(anterior == NULL){
        cliente_aux->lista = atual->prox;
    } 
    else{
        anterior->prox = atual->prox;
    }

    free(atual);
    atualizar_ids_pedidos(cliente_aux->lista);
    printf("Pedido retirado da lista.\n");
    return cliente_aux->lista;
}


void imprimir_lista_pedidos(Clientes* cliente){
    Lista_Pedidos* auxiliar;

    for(auxiliar = cliente->lista; auxiliar != NULL; auxiliar = auxiliar->prox){
        imprimir_pedido(auxiliar->pedido);
        printf("\n");
    }
}// verificado

struct pedido* buscar_pedido(Clientes* cliente, int id){
    Lista_Pedidos* auxiliar;

    for(auxiliar = cliente->lista; auxiliar != NULL; auxiliar = auxiliar->prox){
        if(auxiliar->pedido->id == id){
            return auxiliar->pedido;
        }
    }

    return NULL;
}

void escrever_arquivo(Clientes* lista){
    FILE* arquivo;
    if((arquivo = fopen("arquivo_geral.txt", "w+")) == NULL){
        printf("Erro ao abrir arquivo para escrita.\n");
        exit(EXIT_FAILURE);
    }

    Clientes* auxiliar;
    Lista_Itens* itens;
    Lista_Pedidos* pedidos;

    for(auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->prox){
        fprintf(arquivo, "Cliente:\nNome: %s\nContato: %s\nCPF: %s\nLista de pedidos:\n", auxiliar->nome, auxiliar->contato, auxiliar->Cpf);

        pedidos = auxiliar->lista;
        if(pedidos != NULL){
            while(pedidos != NULL){
                itens = pedidos->pedido->lista;

                fprintf(arquivo, "\tId: %d\n", pedidos->pedido->id);
                escrever_lista_itens_arquivo(itens, arquivo);
                escrever_status_pedido(arquivo, pedidos->pedido);
                fprintf(arquivo, "\tTotal do pedido: %.2lf\n", pedidos->pedido->total_pedido);

                pedidos = pedidos->prox;
                fprintf(arquivo, "\n");
            }
        }
        else{
            fprintf(arquivo, "\tSem pedidos adicionados a esse cliente.\n");
            fprintf(arquivo, "\n");
        }

        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}

void imprimir_clientes_pedidos(Clientes* lista){
    Clientes* auxiliar;
    Lista_Itens* itens;
    Lista_Pedidos* pedidos;

    if(lista == NULL){
        printf("\nNenhum cliente na lista.\n");
    }
    else{
        for(auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->prox){
            printf("\nCliente:\nNome: %s\nContato: %s\nCPF: %s\nLista de pedidos:\n", auxiliar->nome, auxiliar->contato, auxiliar->Cpf);

            pedidos = auxiliar->lista;
            if(pedidos != NULL){
                while(pedidos != NULL){
                    itens = pedidos->pedido->lista;

                    printf("\tId: %d\n", pedidos->pedido->id);
                    imprimir_lista_itens(itens);
                    imprimir_status_pedido(pedidos->pedido);
                    printf("\tTotal do pedido: %.2lf\n", pedidos->pedido->total_pedido);

                    pedidos = pedidos->prox;
                    printf("\n");
                }
            }
            else{
                printf("\tNenhum pedido adicionado a este cliente.\n");
            }

            printf("\n");
        }

    }
}

void liberar_memoria_clientes(Clientes* inicio) {
    while (inicio != NULL) {
        Clientes* temp_cliente = inicio;
        inicio = inicio->prox; // Avança para o próximo cliente

        // Libera a lista de pedidos associada a este cliente
        Lista_Pedidos* temp_pedido = temp_cliente->lista;
        while (temp_pedido != NULL) {
            Lista_Pedidos* temp_prox_pedido = temp_pedido->prox;
            
            // Libera a lista de itens associada a este pedido
            Lista_Itens* temp_item = temp_pedido->pedido->lista;
            while (temp_item != NULL) {
                Lista_Itens* temp_prox_item = temp_item->proxItem;
                free(temp_item->item);
                free(temp_item);
                temp_item = temp_prox_item;
            }

            free(temp_pedido->pedido);
            free(temp_pedido);
            temp_pedido = temp_prox_pedido;
        }

        free(temp_cliente);
    }
}

void ler_arquivo_teste(FILE* arquivo, Clientes** lista){
    char linha[200];
    char auxiliar[50];
    double valor_aux;

    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        if(strcmp(linha, "Cliente:\n") == 0){
            Clientes* novo_cliente = alocar_memoria(sizeof(Clientes));

            fgets(linha, sizeof(linha), arquivo);
            sscanf(linha, "Nome: %[^\n]\n", novo_cliente->nome);

            fgets(linha, sizeof(linha), arquivo);
            sscanf(linha, "Contato: %[^\n]\n", novo_cliente->contato);

            fgets(linha, sizeof(linha), arquivo);
            sscanf(linha, "CPF: %[^\n]\n", novo_cliente->Cpf);

            fgets(linha, sizeof(linha), arquivo);

            fgets(linha, sizeof(linha), arquivo);
            if(strcmp(linha, "\tSem pedidos adicionados a esse cliente.\n") != 0){
                novo_cliente->lista = alocar_memoria(sizeof(Lista_Pedidos));

                novo_cliente->lista->pedido = NULL;

                while(strncmp(linha, "\tId:", 4) == 0){    
                    Pedido* novo_pedido = alocar_memoria(sizeof(Pedido));

                    sscanf(linha, "\tId: %d\n", &novo_pedido->id);

                    fgets(linha, sizeof(linha), arquivo);

                    novo_pedido->lista = NULL;

                    while(fgets(linha, sizeof(linha), arquivo) != NULL){
                        if(linha[0] == '\n' || strncmp(linha, "\t\t", 2) != 0){
                            break;
                        }
                        else{
                            Lista_Itens* novo_item = alocar_memoria(sizeof(Lista_Itens));

                            novo_item->item = alocar_memoria(sizeof(Itens));

                            sscanf(linha, "\t\t%dx %[^\t]\t%lf\n", &novo_item->quantidade, novo_item->item->nome, &valor_aux);

                            novo_item->item->valor = valor_aux/novo_item->quantidade;
                            if(strcmp(novo_item->item->nome, "Serviço de passadoria                             ") == 0){
                                novo_item->tipo = PASSADORIA;
                            }
                            else if(strcmp(novo_item->item->nome, "Apenas coleta") == 0 || strcmp(novo_item->item->nome, "Apenas entrega") == 0 || strcmp(novo_item->item->nome, "Coleta e entrega") == 0){
                                novo_item->tipo = COLETA_ENTREGA;
                            }
                            else{
                                novo_item->tipo = LAVAGEM;
                            }

                            if(novo_pedido->lista == NULL){
                                novo_pedido->lista = novo_item;
                                novo_item->proxItem = NULL;
                            }
                            else{
                                Lista_Itens* temp = novo_pedido->lista;
                                while (temp->proxItem != NULL) {
                                    temp = temp->proxItem;
                                }
                                temp->proxItem = novo_item;
                                novo_item->proxItem = NULL;
                            }
                        }
                    }

                    sscanf(linha, "\tStatus do Pedido: %[^\n]\n", auxiliar);
                    if(strcmp(auxiliar, "Pendente de Coleta") == 0){
                        novo_pedido->status = PENDENTE_COLETA;
                    }
                    else if(strcmp(auxiliar, "Pendente de Processamento") == 0){
                        novo_pedido->status = PENDENTE_PROCESSAMENTO;
                    }
                    else if(strcmp(auxiliar, "Em Processamento") == 0){
                        novo_pedido->status = EM_PROCESSAMENTO;
                    }
                    else if(strcmp(auxiliar, "Pronto para Entrega") == 0){
                        novo_pedido->status = PRONTO_ENTREGA;
                    }
                    else if(strcmp(auxiliar, "Concluído") == 0){
                        novo_pedido->status = CONCLUIDO;
                    }

                    fgets(linha, sizeof(linha), arquivo);
                    sscanf(linha, "\tTotal do pedido: %lf\n", &novo_pedido->total_pedido);
                    fgets(linha, sizeof(linha), arquivo);

                    if(novo_cliente->lista->pedido == NULL){
                        novo_cliente->lista->pedido = novo_pedido;
                        novo_cliente->lista->prox = NULL;
                    }
                    else{
                        Lista_Pedidos* temporaria = novo_cliente->lista;
                        while(temporaria->prox != NULL){
                            temporaria = temporaria->prox;
                        }

                        Lista_Pedidos* novo_no_pedido = alocar_memoria(sizeof(Lista_Pedidos));
                    
                        novo_no_pedido->pedido = novo_pedido;
                        novo_no_pedido->prox = NULL;
                        temporaria->prox = novo_no_pedido;
                    }
                    fgets(linha, sizeof(linha), arquivo);
                }
            }
            else{
                fgets(linha, sizeof(linha), arquivo);
                novo_cliente->lista = NULL;
            }

            if(*lista == NULL){
                novo_cliente->prox = NULL;
                *lista = novo_cliente;
                
            } 
            else{
                Clientes *temp = *lista;
                while(temp->prox != NULL){
                    temp = temp->prox;
                }

                temp->prox = novo_cliente;
                novo_cliente->prox = NULL;
            }
        }
        int tamanho_linha = strlen(linha);
        fseek(arquivo, -tamanho_linha, SEEK_CUR);
        fgets(linha, sizeof(linha), arquivo);
    }
}