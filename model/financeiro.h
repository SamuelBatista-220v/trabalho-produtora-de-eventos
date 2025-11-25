#ifndef FINANCEIRO_H
#define FINANCEIRO_H

#include "status.h"

// --- CAIXA (Dinheiro Físico/Bancário) ---
typedef struct {
    int id;
    char data[11]; // DD/MM/AAAA
    char descricao[300];
    float valor; // Valor absoluto
    int tipo;    // 1=Entrada (Receita), 2=Saída (Despesa)
    float saldo_apos_transacao; // Para histórico
} LancamentoCaixa;

typedef struct no_caixa ListaCaixa;
struct no_caixa {
    LancamentoCaixa conteudo;
    ListaCaixa* prox;
};

// --- CONTAS A RECEBER (O que clientes devem) ---
typedef struct {
    int id;
    int id_cliente;
    int id_evento_origem; // Para rastreabilidade
    char descricao[100];
    float valor_total;
    char data_vencimento[11];
    char data_recebimento[11]; // Vazio se pendente
    int status; // 0=Pendente, 1=Pago
} ContaReceber;

typedef struct no_receber ListaContaReceber;
struct no_receber {
    ContaReceber conteudo;
    ListaContaReceber* prox;
};

// --- CONTAS A PAGAR (O que a produtora deve) ---
typedef struct {
    int id;
    int id_fornecedor; // 0 se for despesa avulsa (ex: conta de luz)
    char descricao[300];
    float valor_total;
    char data_vencimento[11];
    char data_pagamento[11]; // Vazio se pendente
    int status; // 0=Pendente, 1=Pago
} ContaPagar;

typedef struct no_pagar ListaContaPagar;
struct no_pagar {
    ContaPagar conteudo;
    ListaContaPagar* prox;
};

// --- PROTÓTIPOS DE MANIPULAÇÃO ---

// Inserção
StatusOperacao inserir_caixa(ListaCaixa** lista, LancamentoCaixa novo);
StatusOperacao inserir_conta_receber(ListaContaReceber** lista, ContaReceber nova);
StatusOperacao inserir_conta_pagar(ListaContaPagar** lista, ContaPagar nova);

// Buscas
ListaContaReceber* buscar_conta_receber_por_id(ListaContaReceber* lista, int id);
ListaContaPagar* buscar_conta_pagar_por_id(ListaContaPagar* lista, int id);

// Persistência (Binário - Mais seguro para dados financeiros)
StatusOperacao salvar_financeiro_bin(ListaCaixa* l_cx, ListaContaReceber* l_cr, ListaContaPagar* l_cp, const char* nome_arq);
StatusOperacao carregar_financeiro_bin(ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp, const char* nome_arq);

// Limpeza
void liberar_listas_financeiro(ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp);

// Estrutura auxiliar para visualização da Nota Fiscal (Input)
typedef struct {
    int id;
    char nome[300];
    int qtd;
    float custo;
} ItemCompraTemp;


// Persistência em Texto (CSV) - 
StatusOperacao salvar_financeiro_txt(ListaCaixa* l_cx, ListaContaReceber* l_cr, ListaContaPagar* l_cp);
StatusOperacao carregar_financeiro_txt(ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp);

#endif

