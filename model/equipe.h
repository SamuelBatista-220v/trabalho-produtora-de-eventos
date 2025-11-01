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
} equipe;

typedef struct no_equipe Listaequipe;

struct no_equipe {
    equipe conteudo;
    Listaequipe* prox;
};

// As funções já retornam o tipo correto (StatusOperacao)
StatusOperacao inserir_equipe(Listaequipe** lista, equipe nova_equipe);
Listaequipe* buscar_equipe_por_id(Listaequipe* lista, int id_busca);
StatusOperacao atualizar_equipe_por_id(Listaequipe* lista, int id, equipe equipe_atualizada);
StatusOperacao remover_fisico_equipe_por_id(Listaequipe** lista, int id_busca);
StatusOperacao desativar_equipe_por_id(Listaequipe* lista, int id_busca);
StatusOperacao ativar_equipe_por_id(Listaequipe* lista, int id_busca);
void liberar_lista_equipe(Listaequipe** lista);

#endif // equipe_H