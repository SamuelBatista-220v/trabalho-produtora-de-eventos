// Arquivo: model/equipe.h (versão final correta)

#ifndef EQUIPE_H
#define EQUIPE_H

#include "status.h" // Inclui o enum StatusOperacao

#include "cliente.h" // Inclui para pegar a definição de StatusOperacao

typedef struct {
    int id;
    char nome[100];
    char cpf[12];
    char funcao[100];
    float valor_diaria;
    int ativo;
} Equipe;

typedef struct no_equipe ListaEquipe;

struct no_equipe {
    Equipe conteudo;
    ListaEquipe* prox;
};

// As funções já retornam o tipo correto (StatusOperacao)
StatusOperacao inserir_equipe(ListaEquipe** lista, Equipe nova_equipe);
ListaEquipe* buscar_equipe_por_id(ListaEquipe* lista, int id_busca);
StatusOperacao atualizar_equipe_por_id(ListaEquipe* lista, int id, Equipe equipe_atualizada);
StatusOperacao remover_fisico_equipe_por_id(ListaEquipe** lista, int id_busca);
void liberar_lista_equipe(ListaEquipe** lista);

#endif // EQUIPE_H