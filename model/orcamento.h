// #ifndef ORCAMENTO_H
// #define ORCAMENTO_H

// #include "status.h"

// #define MAX_ITENS_ORCAMENTO 50
// #define TAM_DATA 20

// // Status do Orçamento/Evento
// typedef enum {
//     STATUS_EM_ANALISE = 0,
//     STATUS_APROVADO = 1,   // Vira um Evento confirmado (Reserva estoque)
//     STATUS_FINALIZADO = 2, // Evento realizado (Libera estoque, Gera financeiro)
//     STATUS_CANCELADO = 3
// } StatusOrcamento;

// // Estrutura auxiliar para guardar qual recurso e quantos dele
// typedef struct {
//     int id_recurso;
//     int quantidade;
//     float valor_unitario_momento; // Guarda o preço na data do orçamento
// } ItemRecursoOrcamento;

// // Estrutura auxiliar para serviços de fornecedores
// typedef struct {
//     int id_fornecedor;
//     float valor_combinado;
//     char descricao_servico[100]; // Ex: "Buffet para 100 pessoas"
// } ItemServicoOrcamento;

// typedef struct {
//     int id;
//     int id_cliente;
    
//     // Dados do Evento
//     char nome_evento[100];
//     char local[150];
    
//     // Datas (Formato string DD/MM/AAAA ou Timestamp)
//     // Usaremos time_t (long long) para facilitar cálculos de colisão, 
//     // mas guardaremos strings para visualização se preferir. 
//     // Vamos simplificar usando dia/mes/ano inteiros para validação lógica
//     int dia_inicio, mes_inicio, ano_inicio;
//     int dia_fim, mes_fim, ano_fim;
    
//     int qtd_dias; // Calculado

//     // Listas de Itens (Arrays Fixos para facilitar Salvamento Binário)
//     ItemRecursoOrcamento lista_recursos[MAX_ITENS_ORCAMENTO];
//     int qtd_recursos_selecionados; // Quantos slots do array acima estão em uso

//     ItemServicoOrcamento lista_servicos[MAX_ITENS_ORCAMENTO];
//     int qtd_servicos_selecionados;

//     // Totais
//     float valor_total_recursos;
//     float valor_total_servicos;
//     float valor_total_geral; // Soma tudo
    
//     StatusOrcamento status;
//     int ativo; // 1 ou 0
// } Orcamento;

// typedef struct no_orcamento ListaOrcamento;
// struct no_orcamento {
//     Orcamento conteudo;
//     ListaOrcamento* prox;
// };

// // --- PROTÓTIPOS ---

// // CRUD
// StatusOperacao inserir_orcamento(ListaOrcamento** lista, Orcamento novo);
// ListaOrcamento* buscar_orcamento_por_id(ListaOrcamento* lista, int id);
// StatusOperacao atualizar_orcamento(ListaOrcamento* lista, int id, Orcamento atualizado);
// StatusOperacao remover_orcamento(ListaOrcamento** lista, int id); // Lógico ou físico dependendo da regra

// // Lógica de Negócio
// StatusOperacao aprovar_orcamento(ListaOrcamento* no_orcamento); // Muda status p/ Aprovado
// StatusOperacao finalizar_evento(ListaOrcamento* no_orcamento); // Muda status p/ Finalizado

// // Persistência
// StatusOperacao salvar_orcamento_txt(ListaOrcamento* lista, const char* nome_arquivo);
// StatusOperacao carregar_orcamento_txt(ListaOrcamento** lista, const char* nome_arquivo);
// StatusOperacao salvar_orcamento_bin(ListaOrcamento* lista, const char* nome_arquivo);
// StatusOperacao carregar_orcamento_bin(ListaOrcamento** lista, const char* nome_arquivo);

// void liberar_lista_orcamento(ListaOrcamento** lista);

// #endif

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
} ItemEquipeOrcamento; // <--- NOVO

typedef struct {
    int id;
    int id_cliente;
    
    char nome_evento[100];
    char local[150];
    
    int dia_inicio, mes_inicio, ano_inicio;
    int dia_fim, mes_fim, ano_fim;
    int qtd_dias;

    // Listas de Itens
    ItemRecursoOrcamento lista_recursos[MAX_ITENS_ORCAMENTO];
    int qtd_recursos_selecionados;

    ItemServicoOrcamento lista_servicos[MAX_ITENS_ORCAMENTO];
    int qtd_servicos_selecionados;

    ItemEquipeOrcamento lista_equipe[MAX_ITENS_ORCAMENTO]; // <--- NOVO
    int qtd_equipe_selecionada; // <--- NOVO

    // Totais
    float valor_total_recursos;
    float valor_total_servicos;
    float valor_total_equipe; // <--- NOVO
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

// PERSISTÊNCIA (TEXTO/CSV) - <--- ESTES FALTAVAM
StatusOperacao salvar_orcamento_txt(ListaOrcamento* lista, const char* nome_arquivo);
StatusOperacao carregar_orcamento_txt(ListaOrcamento** lista, const char* nome_arquivo);
#endif