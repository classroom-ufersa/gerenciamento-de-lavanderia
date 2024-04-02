#include "pedidos.h"
#include "clientes.h"

int main(void){
    int opcao_menu;
    int id_aux;

    Clientes* cliente_lista = inicializar_lista_clientes();

    Clientes* cliente_aux = NULL;
    Pedido* pedido_aux = NULL;

    FILE* arquivo_clientes;
    if((arquivo_clientes = fopen("arquivo_geral.txt", "a+")) == NULL){
        printf("Erro ao abrir arquivo.\n");
    }

    do{
        opcao_menu = validar_entrada("\nMENU PRINCIPAL\n"
        "1 - Adicionar cliente\n"
        "2 - Remover cliente\n"
        "3 - Adicionar pedido\n"
        "4 - Remover pedido\n"
        "5 - Editar status de pedido\n"
        "6 - Buscar cliente por nome\n"
        "7 - Listar clientes e seus pedidos\n"
        "8 - Sair\n", 1, 8);

        switch(opcao_menu){
            case 1:
                cliente_lista = adicionar_clientes(cliente_lista);
                escrever_arquivo(cliente_lista, arquivo_clientes);
                //adicionar verificação dentro da função pra não haver duplicação de clientes
                break;
            case 2:
                cliente_lista = remover_cliente(cliente_lista);
                escrever_arquivo(cliente_lista, arquivo_clientes);
                break;
            case 3:
                cliente_aux = buscar_cliente(cliente_lista);
                if(cliente_aux != NULL){
                    pedido_aux = menu_pedido(); //fazer essa função retornar um pedido
                    adicionar_pedidos(cliente_aux, pedido_aux);
                    escrever_arquivo(cliente_lista, arquivo_clientes);
                }
                break;
            case 4:
                cliente_aux = buscar_cliente(cliente_lista);
                if(cliente_aux != NULL){
                    imprimir_lista_pedidos(cliente_aux);
                    id_aux = validar_entrada("Digite o id do pedido a ser removido:\n - ", 0, 0);
                    pedido_aux = buscar_pedido(cliente_aux, id_aux);
                    remover_pedido(cliente_aux, pedido_aux);
                    escrever_arquivo(cliente_lista, arquivo_clientes);
                }
                break;
            case 5:
                cliente_aux = buscar_cliente(cliente_lista);
                if(cliente_aux != NULL){
                    imprimir_lista_pedidos(cliente_aux);
                    id_aux = validar_entrada("Digite o id do pedido para mudar o status:\n - ", 0, 0);
                    pedido_aux = buscar_pedido(cliente_aux, id_aux);
                    modificar_status(pedido_aux);
                    escrever_arquivo(cliente_lista, arquivo_clientes);
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
    }while(opcao_menu != 8);
    fclose(arquivo_clientes);
    return 0;
}