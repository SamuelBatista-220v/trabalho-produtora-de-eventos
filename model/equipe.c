#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "equipe.h"
#include "status.h" // Inclui o enum StatusOperacao

static int proximo_id_equipe = 1;//é um contador estático que rastreia o ID a ser atribuído ao próximo membro da equipe.

// Adiciona um novo nó contendo os dados de nova_equipe ao final da lista.
//Usa malloc para criar espaço para o novo nó.
//Se a lista for NULL, o novo nó se torna a cabeça *lista = novo_no . Caso contrário, percorre a lista até o final para anexar o novo nó.
StatusOperacao inserir_equipe(Listaequipe** lista, equipe nova_equipe) {
    Listaequipe* novo_no = (Listaequipe*) malloc(sizeof(Listaequipe));
    if (novo_no == NULL) {
        return ERRO_ALOCACAO_MEMORIA;
    }

if (nova_equipe.id > 0) {
        if (nova_equipe.id >= proximo_id_equipe) {
            proximo_id_equipe = nova_equipe.id + 1;
        }
    } else {
        nova_equipe.id = proximo_id_equipe++;
    }
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

// Percorre a lista sequencialmente, comparando o id_busca com o id de cada membro da equipe.
Listaequipe* buscar_equipe_por_id(Listaequipe* lista, int id_busca) {
    Listaequipe* atual = lista;//Retorna o ponteiro para o nó (Listaequipe*) se encontrar o ID ou NULL se não encontrar.
    while (atual != NULL) {
        if (atual->conteudo.id == id_busca) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

// Função para atualizar os dados de um membro da equipe
//Encontra o nó do membro pelo id_busca e substitui todos os dados
StatusOperacao atualizar_equipe_por_id(Listaequipe* lista, int id_busca, equipe equipeAtualizada) {
    Listaequipe* atual = lista;//Permite a modificação dos dados sem alterar a estrutura da lista. Usa apenas Listaequipe* lista porque a cabeça da lista não é modificada.
    while (atual != NULL) {
        if (atual->conteudo.id == id_busca) {
            atual->conteudo = equipeAtualizada;
            atual->conteudo.id = id_busca; // Garante que o ID não mude
            return OPERACAO_SUCESSO;
        }
        atual = atual->prox;
    }
    return ERRO_NAO_ENCONTRADO; // 
}

// Função para desativar um membro da equipe (soft delete)
//Localiza o membro e apenas altera o campo ativo para 0 (inativo).
StatusOperacao desativar_equipe_por_id(Listaequipe* lista, int id_busca) {
    Listaequipe* no_equipe = buscar_equipe_por_id(lista, id_busca);
    if (no_equipe == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }//Verifica se o membro existe, e se já não está inativo, retornando o StatusOperacao adequado em cada caso.
    if (no_equipe->conteudo.ativo == 0) {
        return ERRO_JA_INATIVO; 
    }
    no_equipe->conteudo.ativo = 0;
    return OPERACAO_SUCESSO;
}

// Função para remover fisicamente um membro da equipe da lista
//Localiza o nó a ser removido, religa os ponteiros do nó anterior para "pular" o nó atual e, em seguida, libera a memória com free(atual)
StatusOperacao remover_fisico_equipe_por_id(Listaequipe** lista, int id_busca) {
    Listaequipe* atual = *lista;
    Listaequipe* anterior = NULL;

//lida com a remoção do primeiro nó, onde é obrigatório usar *lista = atual->prox para mudar o ponteiro de início.
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

//Localiza o membro e altera o campo ativo para 1 (ativo).
//Permite restaurar um registro previamente desativado.
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

// Percorre toda a lista e usa free() em cada nó, liberando a memória alocada

void liberar_lista_equipe(Listaequipe** lista) {
    Listaequipe* atual = *lista;
    Listaequipe* proximo_no;//Salva o endereço do próximo nó antes de liberar o nó atual, garantindo que a travessia continue.
    while (atual != NULL) {
        proximo_no = atual->prox;
        free(atual);
        atual = proximo_no;
    }
    *lista = NULL;//indicar que a lista está vazia.
}

// Abre o arquivo em modo de escrita ("w") e usa fprintf para salvar os dados de cada membro em uma nova linha, separados por ponto e vírgula
StatusOperacao salvar_equipe_txt(Listaequipe* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "w");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    Listaequipe* atual = lista;
    while (atual) {
        equipe* e = &atual->conteudo;
        fprintf(f, "%d;%s;%s;%s;%.2f;%d\n",
            e->id, e->nome, e->cpf, e->funcao, e->valor_diaria, e->ativo);
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}
//Abre o arquivo em modo de leitura ("r"), limpa a lista
StatusOperacao carregar_equipe_txt(Listaequipe** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    liberar_lista_equipe(lista);
    equipe e;
    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%f;%d\n",
        &e.id, e.nome, e.cpf, e.funcao, &e.valor_diaria, &e.ativo) == 6) {
        inserir_equipe(lista, e);
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}
//Abre o arquivo em modo de escrita binária ("wb") e usa fwrite para copiar os bytes brutos da estrutura equipe para o arquivo
StatusOperacao salvar_equipe_bin(Listaequipe* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "wb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    Listaequipe* atual = lista;
    while (atual) {
        fwrite(&atual->conteudo, sizeof(equipe), 1, f);
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}
//Abre o arquivo em modo de leitura binária ("rb"), limpa a lista, e usa fread para ler blocos do tamanho exato de uma equipe diretamente na variável temporária, inserindo-a na lista.
StatusOperacao carregar_equipe_bin(Listaequipe** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "rb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    liberar_lista_equipe(lista);
    equipe e;
    while (fread(&e, sizeof(equipe), 1, f) == 1) inserir_equipe(lista, e);
    fclose(f);
    return OPERACAO_SUCESSO;
}