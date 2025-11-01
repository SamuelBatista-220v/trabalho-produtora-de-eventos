#include <stdlib.h>
#include <string.h>
#include "equipe.h"
#include "status.h" // Inclui o enum StatusOperacao

static int proximo_id_equipe = 1;

// Exemplo da função de inserir
StatusOperacao inserir_equipe(Listaequipe** lista, equipe nova_equipe) {
    Listaequipe* novo_no = (Listaequipe*) malloc(sizeof(Listaequipe));
    if (novo_no == NULL) {
        return ERRO_ALOCACAO_MEMORIA;
    }

    nova_equipe.id = proximo_id_equipe++;
    novo_no->conteudo = nova_equipe;
    novo_no->prox = NULL;

    if (*lista == NULL) {
        *lista = novo_no;
    } else {
        Listaequipe* atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_no;
    }
    return OPERACAO_SUCESSO;
}

// Função para buscar um membro da equipe por ID
Listaequipe* buscar_equipe_por_id(Listaequipe* lista, int id_busca) {
    Listaequipe* atual = lista;
    while (atual != NULL) {
        if (atual->conteudo.id == id_busca) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

// Função para atualizar os dados de um membro da equipe
StatusOperacao atualizar_equipe_por_id(Listaequipe* lista, int id_busca, equipe equipeAtualizada) {
    Listaequipe* atual = lista;
    while (atual != NULL) {
        if (atual->conteudo.id == id_busca) {
            atual->conteudo = equipeAtualizada;
            atual->conteudo.id = id_busca; // Garante que o ID não mude
            return OPERACAO_SUCESSO;
        }
        atual = atual->prox;
    }
    return ERRO_NAO_ENCONTRADO; // Pode criar um ERRO_EQUIPE_NAO_ENCONTRADA se preferir
}

// Função para desativar um membro da equipe (soft delete)
StatusOperacao desativar_equipe_por_id(Listaequipe* lista, int id_busca) {
    Listaequipe* no_equipe = buscar_equipe_por_id(lista, id_busca);
    if (no_equipe == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_equipe->conteudo.ativo == 0) {
        return ERRO_JA_INATIVO; // Pode criar um ERRO_EQUIPE_JA_INATIVA
    }
    no_equipe->conteudo.ativo = 0;
    return OPERACAO_SUCESSO;
}

// Função para remover fisicamente um membro da equipe da lista
StatusOperacao remover_fisico_equipe_por_id(Listaequipe** lista, int id_busca) {
    Listaequipe* atual = *lista;
    Listaequipe* anterior = NULL;

    while (atual != NULL && atual->conteudo.id != id_busca) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }

    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    return OPERACAO_SUCESSO;
}

// Função para ativar um membro da equipe
StatusOperacao ativar_equipe_por_id(Listaequipe* lista, int id_busca) {
    Listaequipe* no_equipe = buscar_equipe_por_id(lista, id_busca);
    if (no_equipe == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_equipe->conteudo.ativo == 1) {
        return ERRO_JA_ATIVO; // Pode criar um ERRO_EQUIPE_JA_ATIVA
    }
    no_equipe->conteudo.ativo = 1;
    return OPERACAO_SUCESSO;
}

// Não se esqueça da função para liberar a memória da lista!
void liberar_lista_equipe(Listaequipe** lista) {
    Listaequipe* atual = *lista;
    Listaequipe* proximo_no;
    while (atual != NULL) {
        proximo_no = atual->prox;
        free(atual);
        atual = proximo_no;
    }
    *lista = NULL;
}