#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recurso.h"

#include "status.h"

// Variável estática para controlar o próximo ID de recurso
static int proximo_id_recurso = 1;

// Insere um novo recurso no final da lista encadeada.
// Recebe Listarecurso** lista para permitir a alteração do ponteiro de cabeça da lista.
StatusOperacao inserir_recurso(Listarecurso** lista, recurso novo_recurso) {
    //Aloca dinamicamente memória para o novo nó.
    Listarecurso* novo_no = (Listarecurso*) malloc(sizeof(Listarecurso));
    if (novo_no == NULL) {
        return ERRO_ALOCACAO_MEMORIA;
    }

 if (novo_recurso.id > 0) {
        if (novo_recurso.id >= proximo_id_recurso) {
            proximo_id_recurso = novo_recurso.id + 1;
        }
    } else {
        novo_recurso.id = proximo_id_recurso++;
    }// Atribui e incrementa o ID global
    novo_no->conteudo = novo_recurso;//copia os dados do recurso
    novo_no->prox = NULL;// Define o novo nó como o último.

    //Lógica de Inserção (Lista Vazia vs. Lista Cheia)
    if (*lista == NULL) {
        // Se a lista está vazia, o novo nó se torna a cabeça.
        *lista = novo_no;
    } else {
        // Percorre a lista até o último nó.
        Listarecurso* atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        // Anexa o novo nó ao final
        atual->prox = novo_no;
    }
    return OPERACAO_SUCESSO;
}

// Busca um recurso na lista pelo ID.
// Retorna o ponteiro para o nó encontrado ou NULL.
Listarecurso* buscar_recurso_por_id(Listarecurso* lista, int id_busca) {
    Listarecurso* atual = lista;
    while (atual != NULL) {
        if (atual->conteudo.id == id_busca) {
            return atual;//encontrado
        }
        atual = atual->prox;//move para o proximo no
    }
    return NULL;//nao encontrado
}

// Atualiza os dados internos de um recurso pelo ID.
StatusOperacao atualizar_recurso_por_id(Listarecurso* lista, int id_busca, recurso recurso_atualizado) {
    Listarecurso* no_recurso = buscar_recurso_por_id(lista, id_busca);
    if (no_recurso == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }

    // Preserva o ID original e o status de ativo, que não devem ser alterados aqui
    recurso_atualizado.id = no_recurso->conteudo.id;
    recurso_atualizado.ativo = no_recurso->conteudo.ativo;

    //Copia a estrutura atualizada para o conteúdo do nó.
    no_recurso->conteudo = recurso_atualizado;



    return OPERACAO_SUCESSO;
}

// Desativa um recurso (remoção lógica).
StatusOperacao desativar_recurso_por_id(Listarecurso* lista, int id_busca) {
    Listarecurso* no_recurso = buscar_recurso_por_id(lista, id_busca);
    if (no_recurso == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_recurso->conteudo.ativo == 0) {
        return ERRO_JA_INATIVO;
    }
    // Altera o campo de controle 'ativo' para 0.
    no_recurso->conteudo.ativo = 0;
    return OPERACAO_SUCESSO;
}

// Ativa um recurso.
StatusOperacao ativar_recurso_por_id(Listarecurso* lista, int id_busca) {
    Listarecurso* no_recurso = buscar_recurso_por_id(lista, id_busca);
    if (no_recurso == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_recurso->conteudo.ativo == 1) {
        return ERRO_JA_ATIVO;
    }
    // Altera o campo de controle 'ativo' para 1.
    no_recurso->conteudo.ativo = 1;
    return OPERACAO_SUCESSO;
}

// Remove fisicamente (e desaloca) um nó da lista.
// Recebe Listarecurso** lista pois pode alterar o ponteiro de cabeça
StatusOperacao remover_fisico_recurso_por_id(Listarecurso** lista, int id_busca) {
    Listarecurso* atual = *lista;
    Listarecurso* anterior = NULL;

    //Rastreia o nó a ser removido ('atual') e seu antecessor ('anterior').
    while (atual != NULL && atual->conteudo.id != id_busca) {
        anterior = atual;
        atual = atual->prox;
    }
// Caso: Remoção do primeiro nó. A cabeça da lista é movida.
    if (atual == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }

    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        //Remoção no meio/fim. O nó anterior "pula" o nó atual
        anterior->prox = atual->prox;
    }

    free(atual);
    return OPERACAO_SUCESSO;
}

// Libera toda a memória alocada dinamicamente para a lista.
void liberar_lista_recurso(Listarecurso** lista) {
    Listarecurso* atual = *lista;
    Listarecurso* proximo_no;
    while (atual != NULL) {
        proximo_no = atual->prox;// Salva o próximo endereço antes de liberar.
        free(atual);// Libera o nó atual.
        atual = proximo_no;
    }
    *lista = NULL;// Zera o ponteiro de cabeça para indicar lista vazia.
}

// Salva a lista em formato de texto (CSV).
StatusOperacao salvar_recurso_txt(Listarecurso* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "w");
    if (!f) return ERRO_ABRIR_ARQUIVO;// Abre o arquivo em modo de escrita ('w').

    Listarecurso* atual = lista;
    while (atual) {
        recurso* r = &atual->conteudo;
        // Usa fprintf para escrever os 7 campos em formato delimitado (CSV), terminando com \n.
        fprintf(f, "%d;%s;%s;%d;%.2f;%.2f;%d\n",
            r->id, r->descricao, r->categoria, r->quantidade, r->preco_de_custo, r->valor_da_locacao, r->ativo);
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

// Carrega a lista a partir de um arquivo de texto (CSV)
StatusOperacao carregar_recurso_txt(Listarecurso** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");// Abre o arquivo em modo de leitura ('r').

    if (!f) return ERRO_ABRIR_ARQUIVO;
    liberar_lista_recurso(lista);
    recurso r;
    // Loop de leitura. fscanf usa %[^;] para strings e tenta ler 7 campos (== 7)
    while (fscanf(f, "%d;%[^;];%[^;];%d;%f;%f;%d\n",
        &r.id, r.descricao, r.categoria, &r.quantidade, &r.preco_de_custo, &r.valor_da_locacao, &r.ativo) == 7) {
        inserir_recurso(lista, r);
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

// Salva a lista em formato binário.
StatusOperacao salvar_recurso_bin(Listarecurso* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "wb");// Abre em modo de escrita binária ('wb').
    if (!f) return ERRO_ABRIR_ARQUIVO;

    Listarecurso* atual = lista;
    while (atual) {
        // fwrite copia os bytes brutos da estrutura 'recurso' para o arquivo.
        fwrite(&atual->conteudo, sizeof(recurso), 1, f);
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

// Carrega a lista a partir de um arquivo binário.
StatusOperacao carregar_recurso_bin(Listarecurso** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "rb");// Abre em modo de leitura binária ('rb').
    if (!f) return ERRO_ABRIR_ARQUIVO;

    liberar_lista_recurso(lista);// Limpa a lista atual na memória.

    recurso r;
    // Loop: fread lê blocos de dados do tamanho de uma 'recurso'.
    while (fread(&r, sizeof(recurso), 1, f) == 1) inserir_recurso(lista, r);
    fclose(f);
    return OPERACAO_SUCESSO;
}