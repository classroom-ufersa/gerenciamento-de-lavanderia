
typedef struct Cliente clientes;

clientes* lista_cria(void);

void lista_imprime(clientes *l);

clientes* add_clientes(clientes *l, FILE * arquivo_cliente);

clientes* retirar_cliente(clientes *pessoa, FILE *arquivo_cliente);
