#ifndef OPERADOR_H
#define OPERADOR_H

#include "status.h" // Inclui o enum StatusOperacao

// Estrutura principal com todos os dados de um operador (agora apenas PJ)
typedef struct {
    int id;
    char nome[100];
    char usuario[50];
    int senha;
    int ativo; // 1 para ativo, 0 para inativo
} operador;

// Estrutura do nó da lista ligada de operadores
typedef struct no_operador Listaoperador;

struct no_operador {
    operador conteudo;
    Listaoperador* prox;
};


// --- DECLARAÇÃO DAS FUNÇÕES (PROTÓTIPOS) ---

// Funções para manipulação da lista (CRUD)
StatusOperacao inserir_operador(Listaoperador** lista, operador novo_operador);
Listaoperador* buscar_operador_por_id(Listaoperador* lista, int id_busca);
StatusOperacao atualizar_operador_por_id(Listaoperador* lista, int id_busca, operador operador_atualizado);
StatusOperacao desativar_operador_por_id(Listaoperador* lista, int id_busca);
StatusOperacao ativar_operador_por_id(Listaoperador* lista, int id_busca);
StatusOperacao remover_fisico_operador_por_id(Listaoperador** lista, int id_busca);
void liberar_lista_operador(Listaoperador** lista);

// (Opcional) Funções de Persistência
// StatusOperacao salvar_operadores(Listaoperador* lista, const char* nome_arquivo);
// StatusOperacao carregar_operadores(Listaoperador** lista, const char* nome_arquivo);

#endif // operador_H


