#include "../include/pedidos.h"
#include "../include/clientes.h"

int main(void){
    int opcao_menu;
    int id_aux;
    
    FILE* arquivo = fopen("arquivo_geral.txt", "r");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo para leitura.\n");
        exit(EXIT_FAILURE);
    }

    Clientes* cliente_lista = inicializar_lista_clientes();

    Clientes* cliente_aux = NULL;
    Pedido* pedido_aux = NULL;

    ler_arquivo_teste(arquivo, &cliente_lista);
    printf("arquivo lido");
    fclose(arquivo);

    do{
        opcao_menu = validar_entrada("\nMENU PRINCIPAL\n"
        "1 - Adicionar cliente\n"
        "2 - Remover cliente\n"
        "3 - Adicionar pedido\n"
        "4 - Remover pedido\n"
        "5 - Editar status de pedido\n"
        "6 - Buscar cliente por nome\n"
        "7 - Listar clientes e seus pedidos\n"
        "8 - Sair\nEscolha uma opção: ", 1, 8);

        switch(opcao_menu){
            case 1:
                cliente_lista = adicionar_clientes(cliente_lista);
                break;
            case 2:
                cliente_lista = remover_cliente(cliente_lista);
                break;
            case 3:
                cliente_aux = buscar_cliente(cliente_lista);
                if(cliente_aux != NULL){
                    pedido_aux = menu_pedido();
                    if(pedido_aux != NULL){
                        adicionar_pedidos(cliente_aux, pedido_aux);
                    }
                    else{
                        printf("\nPedido cancelado.\n");
                    }
                }
                break;
            case 4:
                cliente_aux = buscar_cliente(cliente_lista);
                if(cliente_aux != NULL){
                    imprimir_lista_pedidos(cliente_aux);
                    id_aux = validar_entrada("Digite o id do pedido a ser removido: ", 0, 0);
                    pedido_aux = buscar_pedido(cliente_aux, id_aux);
                    remover_pedido(cliente_aux, pedido_aux);
                }
                break;
            case 5:
                cliente_aux = buscar_cliente(cliente_lista);
                if(cliente_aux != NULL){
                    imprimir_lista_pedidos(cliente_aux);
                    id_aux = validar_entrada("Digite o id do pedido para mudar o status: ", 0, 0);
                    pedido_aux = buscar_pedido(cliente_aux, id_aux);
                    modificar_status(pedido_aux);
                }
                break;
            case 6:
                buscar_cliente(cliente_lista);
                break;
            case 7:
                imprimir_clientes_pedidos(cliente_lista);
                break;
            case 8:
                printf("Encerrando...");
                break;        
        }
        escrever_arquivo(cliente_lista);
    }while(opcao_menu != 8);
    liberar_memoria_clientes(cliente_lista);
    return 0;
}