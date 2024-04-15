# Gerenciamento de Lavanderia em C

Este é um projeto desenvolvido em linguagem C para gerenciar as operações básicas de uma lavanderia, incluindo o cadastro de clientes, o registro de pedidos e a atualização do status dos pedidos.

## Funcionalidades

- **Cadastro de clientes:** Permite registrar novos clientes na lavanderia, incluindo informações como nome, contato e CPF.
- **Registro de pedidos:** Permite aos funcionários registrar novos pedidos de lavagem para os clientes, incluindo informações como tipo de serviço, quantidade de peças e data de entrega.
- **Atualização do status dos pedidos:** Os funcionários podem atualizar o status dos pedidos, indicando se foram concluídos, aguardando retirada, etc.
- **Busca de clientes e pedidos:** Oferece funcionalidades para buscar clientes por nome ou CPF, bem como buscar pedidos por número de pedido ou status.

## Pré-requisitos

- Compilador de C compatível com o padrão C99.
- Sistema operacional compatível com a execução de programas em linguagem C.
- Conhecimento básico de C e estruturas de dados.

## Como usar

1. Clone este repositório para o seu computador
2. Compile o programa usando os comandos:
```
gcc -c -Iinclude/ src/pedidos.c -o bin/pedidos.o  
gcc -c -Iinclude/ src/main.c -o bin/main.o
gcc -c -Iinclude/ src/sistema.c -o bin/sistema.o
gcc -c -Iinclude/ src/clientes.c -o bin/clientes.o
gcc bin/pedidos.o bin/main.o bin/clientes.o bin/sistema.o -o bin/main
./bin/main.exe                   
``` 

## Estrutura do Projeto

O projeto é estruturado da seguinte forma:

- **main.c:** Arquivo principal contendo a lógica principal do programa.
- **clientes.h** e **clientes.c:** Arquivos de cabeçalho e implementação das funções relacionadas aos clientes.
- **pedidos.h** e **pedidos.c:** Arquivos de cabeçalho e implementação das funções relacionadas aos pedidos.
- **sistema.h** e **sistema.c:** Arquivos de cabeçalho e implementação de funções utilitárias.
