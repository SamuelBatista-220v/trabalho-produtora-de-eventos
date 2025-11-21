#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operador.h"

#include "status.h"

// Variável estática para controlar o próximo ID de operador
static int proximo_id_operador = 1;

StatusOperacao inserir_operador(Listaoperador** lista, operador novo_operador) {
    Listaoperador* novo_no = (Listaoperador*) malloc(sizeof(Listaoperador));
    if (novo_no == NULL) {
        return ERRO_ALOCACAO_MEMORIA;
    }

    novo_operador.id = proximo_id_operador++; // Atribui e incrementa o ID global
    novo_no->conteudo = novo_operador;
    novo_no->prox = NULL;

    if (*lista == NULL) {
        *lista = novo_no;
    } else {
        Listaoperador* atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_no;
    }
    return OPERACAO_SUCESSO;
}


Listaoperador* buscar_operador_por_id(Listaoperador* lista, int id_busca) {
    Listaoperador* atual = lista;
    while (atual != NULL) {
        if (atual->conteudo.id == id_busca) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}


StatusOperacao atualizar_operador_por_id(Listaoperador* lista, int id_busca, operador operador_atualizado) {
    Listaoperador* no_operador = buscar_operador_por_id(lista, id_busca);
    if (no_operador == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }

    // Preserva o ID original e o status de ativo, que não devem ser alterados aqui
    operador_atualizado.id = no_operador->conteudo.id;
    operador_atualizado.ativo = no_operador->conteudo.ativo;

    no_operador->conteudo = operador_atualizado;



    return OPERACAO_SUCESSO;
}


StatusOperacao desativar_operador_por_id(Listaoperador* lista, int id_busca) {
    Listaoperador* no_operador = buscar_operador_por_id(lista, id_busca);
    if (no_operador == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_operador->conteudo.ativo == 0) {
        return ERRO_JA_INATIVO;
    }
    no_operador->conteudo.ativo = 0;
    return OPERACAO_SUCESSO;
}


StatusOperacao ativar_operador_por_id(Listaoperador* lista, int id_busca) {
    Listaoperador* no_operador = buscar_operador_por_id(lista, id_busca);
    if (no_operador == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_operador->conteudo.ativo == 1) {
        return ERRO_JA_ATIVO;
    }
    no_operador->conteudo.ativo = 1;
    return OPERACAO_SUCESSO;
}


StatusOperacao remover_fisico_operador_por_id(Listaoperador** lista, int id_busca) {
    Listaoperador* atual = *lista;
    Listaoperador* anterior = NULL;

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

void liberar_lista_operador(Listaoperador** lista) {
    Listaoperador* atual = *lista;
    Listaoperador* proximo_no;
    while (atual != NULL) {
        proximo_no = atual->prox;
        free(atual);
        atual = proximo_no;
    }
    *lista = NULL;
}

// Persistência
StatusOperacao salvar_operador_txt(Listaoperador* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "w");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    Listaoperador* atual = lista;
    while (atual) {
        operador* op = &atual->conteudo;
        fprintf(f, "%d;%s;%s;%d;%d\n",
            op->id, op->nome, op->usuario, op->senha, op->ativo);
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

StatusOperacao carregar_operador_txt(Listaoperador** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    liberar_lista_operador(lista);
    operador op;
    while (fscanf(f, "%d;%[^;];%[^;];%d;%d\n",
        &op.id, op.nome, op.usuario, &op.senha, &op.ativo) == 5) {
        inserir_operador(lista, op);
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

StatusOperacao salvar_operador_bin(Listaoperador* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "wb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    Listaoperador* atual = lista;
    while (atual) {
        fwrite(&atual->conteudo, sizeof(operador), 1, f);
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

StatusOperacao carregar_operador_bin(Listaoperador** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "rb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    liberar_lista_operador(lista);
    operador op;
    while (fread(&op, sizeof(operador), 1, f) == 1) inserir_operador(lista, op);
    fclose(f);
    return OPERACAO_SUCESSO;
}

