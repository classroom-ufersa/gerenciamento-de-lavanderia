#include "pedidos.h"

Clientes* inicializar_lista_clientes(void){
    return NULL;
}// verificado

Clientes* inserir_cliente(Clientes* lista, char nome[50], char contato[15]){
    Clientes* novo_cliente = (Clientes*) malloc(sizeof(Clientes));
    if(novo_cliente == NULL){
        printf("Erro ao alocar mem�ria para novo cliente.\n");
        return lista;
    }

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
    Clientes* novo;

    do{
        printf("Digite o nome do cliente: ");
        scanf(" %[^\n]", nome);
        nome[strcspn(nome, "\n")] = '\0';
    }while(validar_nome(nome) == 1);
    formatar_nome(nome);

    do{
        printf("\n Digite o n�mero de contato do cliente: ");
        scanf(" %[^\n]", contato);
        contato[strcspn(contato, "\n")] = '\0';

        if (validar_contato(contato) == 0){
            printf("N�mero de telefone inv�lido. O n�mero deve conter 11 d�gitos.\n");
        }
        else{
            formatar_contato(contato);
            break;
        }
    }while(validar_contato(contato) == 1);

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
        printf("Cliente n�o encontrado na lista.\n");
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
        printf("Digite o nome do cliente: ");
        scanf(" %[^\n]", nome);
        nome[strcspn(nome, "\n")] = '\0';
    }while(validar_nome(nome) == 1);
    formatar_nome(nome);
    
    while(auxiliar != NULL && strcmp(auxiliar->nome, nome) != 0){
        auxiliar = auxiliar->prox;
    }
    
    if(auxiliar == NULL){
        printf("Cliente n�o encontrado no sistema.\n");
        return NULL;
    }

    return auxiliar;
}// verificado

Lista_Pedidos* inicializar_lista_pedidos(void){
    return NULL;
}// verificado

void adicionar_pedidos(Clientes* cliente, struct pedido* pedido){
    Lista_Pedidos* novo_pedido = (Lista_Pedidos*) malloc(sizeof(Lista_Pedidos));
    if(novo_pedido == NULL){
        printf("Erro ao alocar mem�ria.\n");
        return;
    }

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
        printf("Pedido n�o encontrado na lista.\n");
        return cliente->lista;
    }

    if(anterior == NULL){
        cliente->lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Pedido retirado do sistema.\n");
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
            printf("Nome inv�lido, por favor, digite novamente.\n");
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

void modificar_status(struct pedido* pedido){
    int status;
    printf("Status do pedido: %d\n", pedido->status);
    status = validar_entrada("Atualizar pedido para qual status?\n"
    "1 - EM PROCESSAMENTO\n"
    "2 - PRONTO PARA ENTREGA\n"
    "3 - CONCLU�DO\n", 1, 3);

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

void escrever_arquivo(Clientes* lista, FILE* arquivo){
    Clientes* auxiliar;
    Lista_Itens* itens;
    Lista_Pedidos* pedidos;

    for(auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->prox){
        fprintf(arquivo, "Nome: %s\nContato: %s\nLista de pedidos:\n", auxiliar->nome, auxiliar->contato);

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
            fprintf(arquivo, "Lista de pedidos: 0\n");
        }

        fprintf(arquivo, "\n");
    }
}

void imprimir_clientes_pedidos(Clientes* lista){
    Clientes* auxiliar;
    Lista_Itens* itens;
    Lista_Pedidos* pedidos;

    for(auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->prox){
        printf("Nome: %s\n Contato: %s\n Lista de pedidos:\n", auxiliar->nome, auxiliar->contato);

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
            printf("Lista de pedidos: 0\n");
        }

        printf("\n");
    }
}