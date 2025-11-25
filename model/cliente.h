

#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdlib.h>
#include "status.h" // <<< AQUI ESTÁ A CORREÇÃO: Inclui o enum em vez de o redefinir
#include "status.h" // Inclui o enum StatusOperacao
// --- Definições das Estruturas de Dados ---
typedef enum { PESSOA_FISICA, PESSOA_JURIDICA } TipoCliente;//enum é um tipo de dado definido pelo usuario que consiste em um conjunto de constante inteiras nomeadas

typedef union {  //Uma union é um tipo especial de estrutura em C que permite que todos os seus membros compartilhem o mesmo local de memória.
    struct { char nome[100]; char cpf[12]; } pf; 
    struct { char razao_social[100]; char cnpj[15]; } pj;
} Documento;

typedef struct {
    int id;
    TipoCliente tipo; //identifica se é PF ou PJ
    Documento doc;   // conteiner de dados
    char endereco_completo[150];
    char telefone[12];
    char email[100];
    char nome_contato[100];
    int ativo;
} Cliente;

typedef struct no ListaCliente;

struct no {
    Cliente conteudo;
    ListaCliente* prox;
};

//essas funções recebem ListaCliente** lista porque precisam alterar o ponteiro de início da lista
StatusOperacao inserir_cliente(ListaCliente** lista, Cliente novo_cliente);
void liberar_lista(ListaCliente** lista);
ListaCliente* buscar_cliente_por_id(ListaCliente* lista, int id_busca);
StatusOperacao desativar_cliente_por_id(ListaCliente* lista, int id_busca);
StatusOperacao remover_fisico_cliente_por_id(ListaCliente** lista, int id_busca);
StatusOperacao ativar_cliente_por_id(ListaCliente* lista, int id_busca);
StatusOperacao atualizar_cliente_por_id(ListaCliente* lista, int id, Cliente clienteAtualizado);

// No final de model/cliente.h
StatusOperacao salvar_clientes_txt(ListaCliente* lista, const char* nome_arquivo);
StatusOperacao carregar_clientes_txt(ListaCliente** lista, const char* nome_arquivo);
StatusOperacao salvar_clientes_bin(ListaCliente* lista, const char* nome_arquivo);
StatusOperacao carregar_clientes_bin(ListaCliente** lista, const char* nome_arquivo);

#endif
