
#ifndef ORCAMENTO_H
#define ORCAMENTO_H

#include "status.h"

#define MAX_ITENS_ORCAMENTO 50

// Status do Orçamento/Evento
typedef enum {
    STATUS_EM_ANALISE = 0,
    STATUS_APROVADO = 1,   // Reservado (Conta no estoque)
    STATUS_FINALIZADO = 2, // Realizado (Libera estoque, gera financeiro)
    STATUS_CANCELADO = 3
} StatusOrcamento;

// Estruturas auxiliares
typedef struct {
    int id_recurso;
    int quantidade;
    float valor_unitario_momento; 
} ItemRecursoOrcamento;

typedef struct {
    int id_fornecedor;
    float valor_combinado;
    char descricao_servico[100];
} ItemServicoOrcamento;

typedef struct {
    int id_membro_equipe;
    float valor_diaria_momento;
    int dias_trabalhados; // Por padrao igual a qtd_dias do evento
} ItemEquipeOrcamento; 

typedef struct {
    int id;
    int id_cliente;
    
    char nome_evento[100];
    char local[150];
    
    int dia_inicio, mes_inicio, ano_inicio;
    int dia_fim, mes_fim, ano_fim;
    int qtd_dias;


    ItemRecursoOrcamento lista_recursos[MAX_ITENS_ORCAMENTO];
    int qtd_recursos_selecionados;

    ItemServicoOrcamento lista_servicos[MAX_ITENS_ORCAMENTO];
    int qtd_servicos_selecionados;

    ItemEquipeOrcamento lista_equipe[MAX_ITENS_ORCAMENTO]; 
    int qtd_equipe_selecionada; 

    // Totais
    float valor_total_recursos;
    float valor_total_servicos;
    float valor_total_equipe; 
    float valor_total_geral;
    
    StatusOrcamento status;
    int ativo;
} Orcamento;

typedef struct no_orcamento ListaOrcamento;
struct no_orcamento {
    Orcamento conteudo;
    ListaOrcamento* prox;
};

// --- PROTÓTIPOS ---
StatusOperacao inserir_orcamento(ListaOrcamento** lista, Orcamento novo);
ListaOrcamento* buscar_orcamento_por_id(ListaOrcamento* lista, int id);
StatusOperacao salvar_orcamento_txt(ListaOrcamento* lista, const char* nome_arquivo);
StatusOperacao carregar_orcamento_txt(ListaOrcamento** lista, const char* nome_arquivo);
StatusOperacao salvar_orcamento_bin(ListaOrcamento* lista, const char* nome_arquivo);
StatusOperacao carregar_orcamento_bin(ListaOrcamento** lista, const char* nome_arquivo);
void liberar_lista_orcamento(ListaOrcamento** lista);

StatusOperacao remover_fisico_orcamento(ListaOrcamento** lista, int id);

StatusOperacao salvar_orcamento_txt(ListaOrcamento* lista, const char* nome_arquivo);
StatusOperacao carregar_orcamento_txt(ListaOrcamento** lista, const char* nome_arquivo);
#endif