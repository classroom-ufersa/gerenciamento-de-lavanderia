#include "../include/pedidos.h"

Clientes* inicializar_lista_clientes(void){
    return NULL;
}// verificado

Clientes* inserir_cliente(Clientes* lista, char nome[50], char contato[15]){
    Clientes* novo_cliente = alocar_memoria(sizeof(Clientes));

    strcpy(novo_cliente->nome, nome);
    strcpy(novo_cliente->contato, contato);

    Lista_Pedidos* lista_pedidos = inicializar_lista_pedidos();
    novo_cliente->lista = lista_pedidos;

    if(lista == NULL || strcmp(nome, lista->nome) < 0){
        novo_cliente->prox = lista;
        return novo_cliente;
    }

    Clientes* atual = lista;
    Clientes* anterior = NULL;

    while(atual != NULL && strcmp(nome, atual->nome) > 0){
        anterior = atual;
        atual = atual->prox;
    }

    anterior->prox = novo_cliente;
    novo_cliente->prox = atual;

    return lista;
}// verificado

Clientes* adicionar_clientes(Clientes* lista){
    char nome[50];
    char contato[20];
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

        if (validar_contato(contato) == 0){
            printf("Número de telefone inválido. O número deve conter 11 dígitos.\n");
        }
        else{
            formatar_contato(contato);
            break;
        }
    }while(validar_contato(contato) == 1);

    do{
        printf("Digite o CPF do cliente: ");
        scanf(" %[^\n]", cpf);
        cpf[strcspn(cpf, "\n")] = '\0';

        if (validar_cpf(cpf) == 0){
            printf("CPF inválido. O CPF deve conter 11 dígitos.\n");
        }
        else{
            break;
        }
    
    }while(validar_cpf(cpf) == 1);

    novo = inserir_cliente(lista, nome, contato);
    return novo;
}// verificado

Clientes* remover_cliente(Clientes* lista){
    char nome[50];

    do{
        printf("Digite o nome do cliente: ");
        scanf(" %[^\n]", nome);
        nome[strcspn(nome, "\n")] = '\0';
    }while(validar_nome(nome) == 1);
    formatar_nome(nome);

    Clientes* atual = lista;
    Clientes* anterior = NULL;

    while(atual != NULL && strcmp(atual->nome, nome) != 0){
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL){
        printf("Cliente não encontrado na lista.\n");
        return lista;
    }

    if(anterior == NULL){
        lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    
    free(atual);
    printf("Cliente %s removido da lista e arquivo atualizado.\n", nome);
    return lista;
}// verificado

Clientes* buscar_cliente(Clientes* lista){
    char nome[50];
    Clientes* auxiliar = lista;

    do{
        printf("\nDigite o nome do cliente: ");
        scanf(" %[^\n]", nome);
        nome[strcspn(nome, "\n")] = '\0';
    }while(validar_nome(nome) == 1);
    formatar_nome(nome);
    
    while(auxiliar != NULL && strcmp(auxiliar->nome, nome) != 0){
        auxiliar = auxiliar->prox;
    }
    
    if(auxiliar == NULL){
        printf("Cliente não encontrado no sistema.\n");
        return NULL;
    }

    return auxiliar;
}// verificado

Lista_Pedidos* inicializar_lista_pedidos(void){
    return NULL;
}// verificado

void adicionar_pedidos(Clientes* cliente, Pedido* pedido){
    Lista_Pedidos* novo_pedido = alocar_memoria(sizeof(Lista_Pedidos));

    novo_pedido->pedido = pedido;
    novo_pedido->prox = NULL;

    Lista_Pedidos* atual = cliente->lista;
    Lista_Pedidos* anterior = NULL;

    while(atual != NULL && atual->pedido->id < pedido->id){
        anterior = atual;
        atual = atual->prox;
    }

    if(anterior == NULL){
        novo_pedido->prox = cliente->lista;
        cliente->lista = novo_pedido;
    }
    else{
        anterior->prox = novo_pedido;
        novo_pedido->prox = atual;
    }
}// verificado

Lista_Pedidos* remover_pedido(Clientes* cliente, Pedido* pedido){
    Lista_Pedidos* atual = cliente->lista;
    Lista_Pedidos* anterior = NULL;

    while(atual != NULL && atual->pedido != pedido){
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL){
        printf("Pedido não encontrado na lista.\n");
        return cliente->lista;
    }

    if(anterior == NULL){
        cliente->lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Pedido retirado da lista.\n");
    return cliente->lista;
}// verificado

void limpabuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validar_nome(char nome[50]){
    int tamanho_da_string = strlen(nome);
    for (int i = 0; i < tamanho_da_string; i++) {
         if (!isalpha(nome[i]) && nome[i] != ' '){
            limpabuffer();
            printf("Nome inválido, por favor, digite novamente.\n");
            return 1;
        }
    }
    return 0;
}// verificado

void formatar_nome(char *nome){
    int tamanho = strlen(nome);
    int capitalizar = 1;

    for(int i = 0; i < tamanho; i++){
        if(isspace(nome[i])){
            capitalizar = 1;
        } else{
            if(capitalizar){
                nome[i] = toupper(nome[i]);
                capitalizar = 0;
            } else{
                nome[i] = tolower(nome[i]);
            }
        }
    }
}// verificado

int validar_contato(char entrada[15]){
    int tamanho = strlen(entrada);
    int contadorDigitos = 0;

    for (int i = 0; i < tamanho; i++) {
        if (!isdigit(entrada[i]) && entrada[i] != ' ' && entrada[i] != '-') {
            return 0;
        }
        if (isdigit(entrada[i])) {
            contadorDigitos++;
        }
    }

    if (contadorDigitos == 11) {
        return 1;
    } else {
        return 0;
    }
}// verificado

void formatar_contato(char *numero){
    int tamanho = strlen(numero);
    char novoNumero[20];
    int pos = 0;

    for (int i = 0; i < tamanho; i++){
        if (isdigit(numero[i])) {
            if (pos == 0) {
                novoNumero[pos++] = '(';
                novoNumero[pos++] = numero[i];
                novoNumero[pos++] = numero[i + 1];
                novoNumero[pos++] = ')';
                novoNumero[pos++] = ' ';
                i++;
            } else if (pos == 3) {
                novoNumero[pos++] = ' ';
                novoNumero[pos++] = numero[i];
            } else if (pos == 10) {
                novoNumero[pos++] = ' ';
                novoNumero[pos++] = numero[i];
            } else {
                novoNumero[pos++] = numero[i];
            }
        }
    }

    novoNumero[pos] = '\0';
    strcpy(numero, novoNumero);
}// verificado


int validar_cpf(char entrada[15]) {
    int tamanho = strlen(entrada);
    int contadorDigitos = 0;

    for (int i = 0; i < tamanho; i++) {
        if (!isdigit(entrada[i])) {
            return 0;
        }
        contadorDigitos++;
    }

    if (contadorDigitos == 11) {
        return 1;
    } else {
        return 0;
    }
}

void imprimir_lista_pedidos(Clientes* cliente){
    Lista_Pedidos* auxiliar;

    for(auxiliar = cliente->lista; auxiliar != NULL; auxiliar = auxiliar->prox){
        imprimir_pedido(auxiliar->pedido);
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
        fprintf(arquivo, "Cliente:\nNome: %s\nContato: %s\nLista de pedidos:\n", auxiliar->nome, auxiliar->contato);

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
            printf("\nCliente:\nNome: %s\nContato: %s\nLista de pedidos:\n", auxiliar->nome, auxiliar->contato);

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