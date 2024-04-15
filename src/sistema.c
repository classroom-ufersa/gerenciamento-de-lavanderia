#include "../include/pedidos.h"
#include "../include/sistema.h"

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

int validar_contato(char entrada[15]) {
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

    if (tamanho != 11) {
        return 0; 
    }

    for (int i = 0; i < tamanho; i++) {
        if (!isdigit(entrada[i])) {
            return 0; 
        }
    }

    return 1; 
}

void formatar_cpf(char *cpf){
    int tamanho = strlen(cpf);
    char novo_cpf[15]; 
    int pos = 0;

    for (int i = 0; i < tamanho; i++){
        if (isdigit(cpf[i])) {
            if (pos == 3 || pos == 7) {
                novo_cpf[pos++] = '.';
            } else if (pos == 11) {
                novo_cpf[pos++] = '-';
            }
            novo_cpf[pos++] = cpf[i];
        }
    }

    novo_cpf[pos] = '\0';
    strcpy(cpf, novo_cpf);
}

void* alocar_memoria(size_t tamanho){
    void* ptr = malloc(tamanho);
    if (ptr == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
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
                if(opcao > 0){
                    break;
                }
                else{
                    printf("\nQuantidade inválida, certifique-se de digitar um número inteiro e maior que 0.\n");
                }
                
            }
            else{
                printf("\nQuantidade inválida, certifique-se de digitar um número inteiro.\n");
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