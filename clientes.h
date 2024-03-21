
typedef struct Cliente clientes;
typedef struct pedidos pedidos;

clientes* lista_cria(void);

void lista_imprime(clientes *l);

clientes* add_clientes(clientes *l, FILE * arquivo_cliente);

clientes* retirar_cliente(clientes *pessoa, FILE *arquivo_cliente);

int verificar_nome(char nome[50]);

int verificar_numero(char numero[15]);

void limpabuffer();

void busca_de_cliente(clientes *pessoa);

pedidos* add_pedidos(pedidos *lista_pedidos, Pedido *pedido);

pedidos *remover_pedido(pedidos *lista_pedidos, Pedido *pedido);

