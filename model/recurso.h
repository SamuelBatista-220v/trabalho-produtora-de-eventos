#ifndef RECURSO_H
#define RECURSO_H

#include "status.h" // Inclui o enum StatusOperacao

// Estrutura principal com todos os dados de um recurso (agora apenas PJ)
typedef struct {
    int id;
    char descricao[150];
    char categoria[100];
    int  quantidade;
    float preco_de_custo;  
    float valor_da_locacao;
    int ativo; // 1 para ativo, 0 para inativo
} recurso;

// Estrutura do nó da lista ligada de recursoes
typedef struct no_recurso Listarecurso;

struct no_recurso {
    recurso conteudo;
    Listarecurso* prox;
};


// --- DECLARAÇÃO DAS FUNÇÕES (PROTÓTIPOS) ---

// Funções para manipulação da lista (CRUD)
StatusOperacao inserir_recurso(Listarecurso** lista, recurso novo_recurso);
Listarecurso* buscar_recurso_por_id(Listarecurso* lista, int id_busca);
StatusOperacao atualizar_recurso_por_id(Listarecurso* lista, int id_busca, recurso recurso_atualizado);
StatusOperacao desativar_recurso_por_id(Listarecurso* lista, int id_busca);
StatusOperacao ativar_recurso_por_id(Listarecurso* lista, int id_busca);
StatusOperacao remover_fisico_recurso_por_id(Listarecurso** lista, int id_busca);
void liberar_lista_recurso(Listarecurso** lista);

// (Opcional) Funções de Persistência
// StatusOperacao salvar_recursoes(Listarecurso* lista, const char* nome_arquivo);
// StatusOperacao carregar_recursoes(Listarecurso** lista, const char* nome_arquivo);

StatusOperacao salvar_recurso_txt(Listarecurso* lista, const char* nome_arquivo);
StatusOperacao carregar_recurso_txt(Listarecurso** lista, const char* nome_arquivo);
StatusOperacao salvar_recurso_bin(Listarecurso* lista, const char* nome_arquivo);
StatusOperacao carregar_recurso_bin(Listarecurso** lista, const char* nome_arquivo);

#endif // recurso_H


