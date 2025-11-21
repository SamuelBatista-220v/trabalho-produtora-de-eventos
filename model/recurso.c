#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recurso.h"

#include "status.h"

// Variável estática para controlar o próximo ID de recurso
static int proximo_id_recurso = 1;

StatusOperacao inserir_recurso(Listarecurso** lista, recurso novo_recurso) {
    Listarecurso* novo_no = (Listarecurso*) malloc(sizeof(Listarecurso));
    if (novo_no == NULL) {
        return ERRO_ALOCACAO_MEMORIA;
    }

    novo_recurso.id = proximo_id_recurso++; // Atribui e incrementa o ID global
    novo_no->conteudo = novo_recurso;
    novo_no->prox = NULL;

    if (*lista == NULL) {
        *lista = novo_no;
    } else {
        Listarecurso* atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_no;
    }
    return OPERACAO_SUCESSO;
}


Listarecurso* buscar_recurso_por_id(Listarecurso* lista, int id_busca) {
    Listarecurso* atual = lista;
    while (atual != NULL) {
        if (atual->conteudo.id == id_busca) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}


StatusOperacao atualizar_recurso_por_id(Listarecurso* lista, int id_busca, recurso recurso_atualizado) {
    Listarecurso* no_recurso = buscar_recurso_por_id(lista, id_busca);
    if (no_recurso == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }

    // Preserva o ID original e o status de ativo, que não devem ser alterados aqui
    recurso_atualizado.id = no_recurso->conteudo.id;
    recurso_atualizado.ativo = no_recurso->conteudo.ativo;

    no_recurso->conteudo = recurso_atualizado;



    return OPERACAO_SUCESSO;
}


StatusOperacao desativar_recurso_por_id(Listarecurso* lista, int id_busca) {
    Listarecurso* no_recurso = buscar_recurso_por_id(lista, id_busca);
    if (no_recurso == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_recurso->conteudo.ativo == 0) {
        return ERRO_JA_INATIVO;
    }
    no_recurso->conteudo.ativo = 0;
    return OPERACAO_SUCESSO;
}


StatusOperacao ativar_recurso_por_id(Listarecurso* lista, int id_busca) {
    Listarecurso* no_recurso = buscar_recurso_por_id(lista, id_busca);
    if (no_recurso == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_recurso->conteudo.ativo == 1) {
        return ERRO_JA_ATIVO;
    }
    no_recurso->conteudo.ativo = 1;
    return OPERACAO_SUCESSO;
}


StatusOperacao remover_fisico_recurso_por_id(Listarecurso** lista, int id_busca) {
    Listarecurso* atual = *lista;
    Listarecurso* anterior = NULL;

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

void liberar_lista_recurso(Listarecurso** lista) {
    Listarecurso* atual = *lista;
    Listarecurso* proximo_no;
    while (atual != NULL) {
        proximo_no = atual->prox;
        free(atual);
        atual = proximo_no;
    }
    *lista = NULL;
}

// Persistência
StatusOperacao salvar_recurso_txt(Listarecurso* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "w");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    Listarecurso* atual = lista;
    while (atual) {
        recurso* r = &atual->conteudo;
        fprintf(f, "%d;%s;%s;%d;%.2f;%.2f;%d\n",
            r->id, r->descricao, r->categoria, r->quantidade, r->preco_de_custo, r->valor_da_locacao, r->ativo);
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

StatusOperacao carregar_recurso_txt(Listarecurso** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    liberar_lista_recurso(lista);
    recurso r;
    while (fscanf(f, "%d;%[^;];%[^;];%d;%f;%f;%d\n",
        &r.id, r.descricao, r.categoria, &r.quantidade, &r.preco_de_custo, &r.valor_da_locacao, &r.ativo) == 7) {
        inserir_recurso(lista, r);
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

StatusOperacao salvar_recurso_bin(Listarecurso* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "wb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    Listarecurso* atual = lista;
    while (atual) {
        fwrite(&atual->conteudo, sizeof(recurso), 1, f);
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

StatusOperacao carregar_recurso_bin(Listarecurso** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "rb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    liberar_lista_recurso(lista);
    recurso r;
    while (fread(&r, sizeof(recurso), 1, f) == 1) inserir_recurso(lista, r);
    fclose(f);
    return OPERACAO_SUCESSO;
}