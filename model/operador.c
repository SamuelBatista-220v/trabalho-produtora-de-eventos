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
//Atribui ID e Inicializa o Nó
    novo_operador.id = proximo_id_operador++; // Atribui e incrementa o ID global
    novo_no->conteudo = novo_operador;
    novo_no->prox = NULL;

    if (*lista == NULL) {
        //// Se a lista estiver vazia, o novo nó se torna a cabeça.
        *lista = novo_no;
    } else {
        //// Se a lista não estiver vazia, percorre até o final.
        Listaoperador* atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_no;
    }
    return OPERACAO_SUCESSO;// Retorna sucesso.
}


Listaoperador* buscar_operador_por_id(Listaoperador* lista, int id_busca) {
    Listaoperador* atual = lista;
    // Verifica se o ID do conteúdo do nó atual é o ID procurado.
    while (atual != NULL) {
        if (atual->conteudo.id == id_busca) {
            return atual;// Retorna o ponteiro para o nó encontrado.
        }
        atual = atual->prox;
    }
    return NULL;// Retorna NULL se o operador não for encontrado.
}

// Função para atualizar os dados de um operador.
StatusOperacao atualizar_operador_por_id(Listaoperador* lista, int id_busca, operador operador_atualizado) {
    Listaoperador* no_operador = buscar_operador_por_id(lista, id_busca);
    if (no_operador == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }

    // Preserva o ID original e o status de ativo, que não devem ser alterados aqui
    operador_atualizado.id = no_operador->conteudo.id;
    operador_atualizado.ativo = no_operador->conteudo.ativo;
//Copia a estrutura atualizada para o conteúdo do nó encontrado.
    no_operador->conteudo = operador_atualizado;



    return OPERACAO_SUCESSO;
}

//funções de status (soft delete/ativção)
// Função para desativar um operador (remoção lógica).
StatusOperacao desativar_operador_por_id(Listaoperador* lista, int id_busca) {
    Listaoperador* no_operador = buscar_operador_por_id(lista, id_busca);
    if (no_operador == NULL) {
        return ERRO_NAO_ENCONTRADO;// Já está inativo, não faz nada
    }
    if (no_operador->conteudo.ativo == 0) {
        return ERRO_JA_INATIVO;
    }
    // Realiza a desativação lógica: altera o campo 'ativo' para 0.
    no_operador->conteudo.ativo = 0;
    return OPERACAO_SUCESSO;
}

// Função para ativar um operador.
StatusOperacao ativar_operador_por_id(Listaoperador* lista, int id_busca) {
    Listaoperador* no_operador = buscar_operador_por_id(lista, id_busca);
    if (no_operador == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_operador->conteudo.ativo == 1) {
        return ERRO_JA_ATIVO;// Já está ativo, não faz nada.
    }
    // Realiza a ativação: altera o campo 'ativo' para 1.
    no_operador->conteudo.ativo = 1;
    return OPERACAO_SUCESSO;
}

// Função para remover fisicamente um operador da lista e liberar a memória.
StatusOperacao remover_fisico_operador_por_id(Listaoperador** lista, int id_busca) {
    Listaoperador* atual = *lista;
    Listaoperador* anterior = NULL;
//Busca o nó, rastreando o nó anterior
    while (atual != NULL && atual->conteudo.id != id_busca) {
        anterior = atual;// O anterior rastreia o nó atual antes de ele avançar.
        atual = atual->prox;
    }

    if (atual == NULL) {
        return ERRO_NAO_ENCONTRADO;// Operador não encontrado.
    }
//Realiza a religação dos ponteiros
    if (anterior == NULL) {
        //Removendo o primeiro nó. A cabeça da lista é movida para o próximo nó.
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
//Libera a memória do nó removido.
    free(atual);
    return OPERACAO_SUCESSO;
}
// Função para liberar toda a memória alocada dinamicamente para a lista.
void liberar_lista_operador(Listaoperador** lista) {
    Listaoperador* atual = *lista;
    Listaoperador* proximo_no;
    // Percorre a lista até o fim
    while (atual != NULL) {
        proximo_no = atual->prox;// Salva o endereço do próximo nó antes de dar free.
        free(atual);// Libera a memória do nó atual.
        atual = proximo_no;// Move para o próximo nó salvo.
    }
    *lista = NULL;// Zera o ponteiro de início da lista principal.
}

// Função para salvar a lista em um arquivo de texto (CSV).
StatusOperacao salvar_operador_txt(Listaoperador* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "w");// Abre o arquivo em modo de escrita ('w'
    if (!f) return ERRO_ABRIR_ARQUIVO;
    Listaoperador* atual = lista;
    while (atual) {
        operador* op = &atual->conteudo;
        // Escreve os campos do operador separados por ponto e vírgula (formato CSV).
        fprintf(f, "%d;%s;%s;%d;%d\n",
            op->id, op->nome, op->usuario, op->senha, op->ativo);
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}
// Função para carregar a lista a partir de um arquivo de texto (CSV).
StatusOperacao carregar_operador_txt(Listaoperador** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");// Abre o arquivo em modo de leitura ('r').
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
// Loop de leitura. fscanf usa %[^;] para ler strings até o delimitador e %d para inteiros.
StatusOperacao salvar_operador_bin(Listaoperador* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "wb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    Listaoperador* atual = lista;
    while (atual) {
        // Grava a estrutura inteira 'operador' em bytes.
        fwrite(&atual->conteudo, sizeof(operador), 1, f);
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}
// Função para carregar a lista a partir de um arquivo binário.
StatusOperacao carregar_operador_bin(Listaoperador** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "rb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    // Limpa a lista atual na memória.
    liberar_lista_operador(lista);
    operador op;
    // Loop de leitura binária. Tenta ler um bloco do tamanho de um 'operador'.
    while (fread(&op, sizeof(operador), 1, f) == 1) inserir_operador(lista, op);
    fclose(f);
    return OPERACAO_SUCESSO;
}

