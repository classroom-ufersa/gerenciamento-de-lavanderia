#include "../include/pedidos.h"

/*
 * @brief Limpa o buffer do teclado
 *
 * @param void
 * @param void
 *
 * @return void
 *  */
void limpabuffer(void);

/*
 * @brief Valida o nome do cliente
 *
 * @param char nome[50] Nome do cliente
 *
 * @return int Retorna 1 se o nome for valido e 0 caso contrario
 *  */
int validar_nome(char nome[50]);

/*
 * @brief Formata o nome do cliente
 *
 * @param char *nome Nome do cliente
 *
 * @return void
 *  */
void formatar_nome(char *nome);

/*
 * @brief Valida o contato do cliente
 *
 * @param char entrada[15] Contato do cliente
 *
 * @return int Retorna 1 se o contato for v�lido e 0 caso contr�rio
 *  */
int validar_contato(char entrada[15]);

/*
 * @brief Formata o contato do cliente
 *
 * @param char *numero Contato do cliente
 *
 * @return void
 *  */
void formatar_contato(char *numero);

/*
 * @brief Valida o CPF do cliente
 *
 * @param char entrada[15] CPF do cliente
 *
 * @return int Retorna 1 se o CPF for v�lido e 0 caso contr�rio
 *  */

int validar_cpf(char entrada[15]);

/*
 * @brief Formata o CPF do cliente
 *
 * @param char *cpf CPF do cliente
 *
 * @return void
 *  */
void formatar_cpf(char *cpf);

/*
 * @brief aloca memoria
 *
 * @param size_t tamanho Tamanho da memoria a ser alocada
 *
 * @return void 
 *  */
void* alocar_memoria(size_t tamanho);

/*
 * @brief Valida a entrada do usuario
 *
 * @param const char* print Mensagem a ser exibida
 * @param int min Valor minimo aceitavel
 * @param int max Valor maximo aceitavel
 *
 * @return int Retorna o valor digitado pelo usuario
 *  */
int validar_entrada(const char* print, int min, int max);