#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtora.h"

#include "status.h"

// Variável estática para controlar o próximo ID de produtora
static int proximo_id_produtora = 1;

StatusOperacao inserir_produtora(Listaprodutora** lista, produtora novo_produtora) {
    Listaprodutora* novo_no = (Listaprodutora*) malloc(sizeof(Listaprodutora));
    if (novo_no == NULL) {
        return ERRO_ALOCACAO_MEMORIA;
    }

    novo_produtora.id = proximo_id_produtora++; // Atribui e incrementa o ID global
    novo_no->conteudo = novo_produtora;
    novo_no->prox = NULL;

    if (*lista == NULL) {
        *lista = novo_no;
    } else {
        Listaprodutora* atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_no;
    }
    return OPERACAO_SUCESSO;
}


Listaprodutora* buscar_produtora_por_id(Listaprodutora* lista, int id_busca) {
    Listaprodutora* atual = lista;
    while (atual != NULL) {
        if (atual->conteudo.id == id_busca) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}


StatusOperacao atualizar_produtora_por_id(Listaprodutora* lista, int id_busca, produtora produtora_atualizado) {
    Listaprodutora* no_produtora = buscar_produtora_por_id(lista, id_busca);
    if (no_produtora == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }

    // Preserva o ID original e o status de ativo, que não devem ser alterados aqui
    produtora_atualizado.id = no_produtora->conteudo.id;
    produtora_atualizado.ativo = no_produtora->conteudo.ativo;

    no_produtora->conteudo = produtora_atualizado;



    return OPERACAO_SUCESSO;
}


StatusOperacao desativar_produtora_por_id(Listaprodutora* lista, int id_busca) {
    Listaprodutora* no_produtora = buscar_produtora_por_id(lista, id_busca);
    if (no_produtora == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_produtora->conteudo.ativo == 0) {
        return ERRO_JA_INATIVO;
    }
    no_produtora->conteudo.ativo = 0;
    return OPERACAO_SUCESSO;
}


StatusOperacao ativar_produtora_por_id(Listaprodutora* lista, int id_busca) {
    Listaprodutora* no_produtora = buscar_produtora_por_id(lista, id_busca);
    if (no_produtora == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_produtora->conteudo.ativo == 1) {
        return ERRO_JA_ATIVO;
    }
    no_produtora->conteudo.ativo = 1;
    return OPERACAO_SUCESSO;
}


StatusOperacao remover_fisico_produtora_por_id(Listaprodutora** lista, int id_busca) {
    Listaprodutora* atual = *lista;
    Listaprodutora* anterior = NULL;

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

void liberar_lista_produtora(Listaprodutora** lista) {
    Listaprodutora* atual = *lista;
    Listaprodutora* proximo_no;
    while (atual != NULL) {
        proximo_no = atual->prox;
        free(atual);
        atual = proximo_no;
    }
    *lista = NULL;
}

