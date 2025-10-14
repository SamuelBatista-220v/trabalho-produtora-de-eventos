
#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdlib.h>

// ENUM para padronizar os retornos das funções de manipulação de dados.
// Isso torna o código do Controller muito mais legível.
typedef enum {  //Legibilidade e Manutenção
    OPERACAO_SUCESSO,
    ERRO_CLIENTE_NAO_ENCONTRADO,
    ERRO_CLIENTE_JA_ATIVO,
    ERRO_CLIENTE_JA_INATIVO,
    ERRO_ALOCACAO_MEMORIA //4
} StatusOperacao;


// --- Definições das Estruturas de Dados (sem alteração) ---
typedef enum { PESSOA_FISICA, PESSOA_JURIDICA } TipoCliente;

typedef union {
    struct { char nome[100]; char cpf[12]; } pf;
    struct { char razao_social[100]; char cnpj[15]; } pj;
} Documento;

typedef struct {
    int id;
    TipoCliente tipo;
    Documento doc;
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

// --- Protótipos das Funções (com os tipos de retorno atualizados) ---
StatusOperacao inserir_cliente(ListaCliente** lista, Cliente novo_cliente);
void liberar_lista(ListaCliente** lista);
ListaCliente* buscar_cliente_por_id(ListaCliente* lista, int id_busca);
//StatusOperacao atualizar_cliente_por_id(ListaCliente* lista, int id_busca);
StatusOperacao desativar_cliente_por_id(ListaCliente* lista, int id_busca);
StatusOperacao remover_fisico_cliente_por_id(ListaCliente** lista, int id_busca);
StatusOperacao ativar_cliente_por_id(ListaCliente* lista, int id_busca);

StatusOperacao atualizar_cliente_por_id(ListaCliente* lista, int id, Cliente clienteAtualizado);
#endif