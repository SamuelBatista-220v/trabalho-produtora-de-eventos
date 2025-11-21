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

// Persistência
StatusOperacao salvar_produtora_txt(Listaprodutora* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "w");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    Listaprodutora* atual = lista;
    while (atual) {
        produtora* p = &atual->conteudo;
        fprintf(f, "%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;%.2f;%d\n",
            p->id, p->nome_fantasia, p->razao_social, p->inscricao_estadual,
            p->cnpj, p->endereco_completo, p->telefone, p->email,
            p->nome_responsavel, p->telefone_responsavel, p->margem_lucro_padrao, p->ativo);
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

StatusOperacao carregar_produtora_txt(Listaprodutora** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    liberar_lista_produtora(lista);
    produtora p;
    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%f;%d\n",
        &p.id, p.nome_fantasia, p.razao_social, p.inscricao_estadual,
        p.cnpj, p.endereco_completo, p.telefone, p.email,
        p.nome_responsavel, p.telefone_responsavel, &p.margem_lucro_padrao, &p.ativo) == 12) {
        inserir_produtora(lista, p);
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

StatusOperacao salvar_produtora_bin(Listaprodutora* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "wb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    Listaprodutora* atual = lista;
    while (atual) {
        fwrite(&atual->conteudo, sizeof(produtora), 1, f);
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

StatusOperacao carregar_produtora_bin(Listaprodutora** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "rb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    liberar_lista_produtora(lista);
    produtora p;
    while (fread(&p, sizeof(produtora), 1, f) == 1) inserir_produtora(lista, p);
    fclose(f);
    return OPERACAO_SUCESSO;
}

