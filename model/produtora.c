#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtora.h"

#include "status.h"

// Variável estática para controlar o próximo ID de produtora
// 'static' garante que esta variável seja acessível apenas dentro deste arquivo.
static int proximo_id_produtora = 1;

// Insere uma nova produtora no final da lista encadeada.
// Recebe Listaprodutora** lista para permitir a alteração do ponteiro de cabeça.
StatusOperacao inserir_produtora(Listaprodutora** lista, produtora novo_produtora) {
    Listaprodutora* novo_no = (Listaprodutora*) malloc(sizeof(Listaprodutora));
    if (novo_no == NULL) {
        return ERRO_ALOCACAO_MEMORIA;// Falha ao alocar memória.
    }
if (novo_produtora.id > 0) {
        if (novo_produtora.id >= proximo_id_produtora) {
            proximo_id_produtora = novo_produtora.id + 1;
        }
    } else {
        novo_produtora.id = proximo_id_produtora++;
    } // Atribui e incrementa o ID global
    novo_no->conteudo = novo_produtora;// Copia os dados para o conteúdo do nó.
    novo_no->prox = NULL;// O novo nó sempre começa apontando para NULL (será o último).

//Lógica de Inserção (Lista Vazia vs. Lista Cheia)
    if (*lista == NULL) {
        // Se a lista está vazia, o novo nó se torna a cabeça.
        *lista = novo_no;
    } else {
        // Se a lista não está vazia, percorre até o último nó.
        Listaprodutora* atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_no;
    }
    return OPERACAO_SUCESSO;
}

// Busca uma produtora na lista pelo ID.
// Retorna o ponteiro para o nó (Listaprodutora*) se encontrado, ou NULL.
Listaprodutora* buscar_produtora_por_id(Listaprodutora* lista, int id_busca) {
    Listaprodutora* atual = lista;

    // Percorre a lista sequencialmente.
    while (atual != NULL) {
        if (atual->conteudo.id == id_busca) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;//nao encontrado
}

//atualiza os dados de uma produtora por ID
StatusOperacao atualizar_produtora_por_id(Listaprodutora* lista, int id_busca, produtora produtora_atualizado) {
    Listaprodutora* no_produtora = buscar_produtora_por_id(lista, id_busca);
    if (no_produtora == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }

    // Preserva o ID original e o status de ativo, que não devem ser alterados aqui
    produtora_atualizado.id = no_produtora->conteudo.id;
    produtora_atualizado.ativo = no_produtora->conteudo.ativo;

    //copia a estrutura atualizada para o conteudo do nó
    no_produtora->conteudo = produtora_atualizado;



    return OPERACAO_SUCESSO;
}

// Desativa uma produtora (remoção lógica).
StatusOperacao desativar_produtora_por_id(Listaprodutora* lista, int id_busca) {
    Listaprodutora* no_produtora = buscar_produtora_por_id(lista, id_busca);
    if (no_produtora == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_produtora->conteudo.ativo == 0) {
        return ERRO_JA_INATIVO;
    }
    // Altera o campo de controle 'ativo' para 0.
    no_produtora->conteudo.ativo = 0;
    return OPERACAO_SUCESSO;
}

// Ativa uma produtora (reverte remoção lógica).
StatusOperacao ativar_produtora_por_id(Listaprodutora* lista, int id_busca) {
    Listaprodutora* no_produtora = buscar_produtora_por_id(lista, id_busca);
    if (no_produtora == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_produtora->conteudo.ativo == 1) {
        return ERRO_JA_ATIVO;// Produtora já está ativa.
    }
    // Produtora já está ativa.
    no_produtora->conteudo.ativo = 1;
    return OPERACAO_SUCESSO;
}

// Remove fisicamente (e desaloca) um nó da lista.
// Recebe Listaprodutora** lista pois pode alterar o ponteiro de cabeça.
StatusOperacao remover_fisico_produtora_por_id(Listaprodutora** lista, int id_busca) {
    Listaprodutora* atual = *lista;
    Listaprodutora* anterior = NULL;
//Busca: Rastreia o nó a ser removido ('atual') e seu antecessor ('anterior').
    while (atual != NULL && atual->conteudo.id != id_busca) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return ERRO_NAO_ENCONTRADO;// Não achou o ID.
    
    }

    if (anterior == NULL) {
        // Se 'anterior' é NULL, o nó a ser removido é o primeiro.
        *lista = atual->prox;
    } else {
        // O nó anterior agora aponta para o nó que vinha depois do nó atual (pulando o nó atual).
        anterior->prox = atual->prox;
    }

    free(atual);// Desaloca a memória do nó removido.
    return OPERACAO_SUCESSO;
}

// Libera toda a memória alocada dinamicamente para a lista.
// Recebe Listaprodutora** lista para permitir zerar o ponteiro de cabeça.
void liberar_lista_produtora(Listaprodutora** lista) {
    Listaprodutora* atual = *lista;
    Listaprodutora* proximo_no;
    while (atual != NULL) {
        proximo_no = atual->prox;// Crucial: Salva o endereço do próximo antes de liberar o atual.
        free(atual);
        atual = proximo_no;
    }
    *lista = NULL;// Define o ponteiro de cabeça como NULL.
}

// Salva a lista em formato de texto (CSV)
StatusOperacao salvar_produtora_txt(Listaprodutora* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "w");// Abre em modo de escrita ('w')
    if (!f) return ERRO_ABRIR_ARQUIVO;
    Listaprodutora* atual = lista;
    while (atual) {
        produtora* p = &atual->conteudo;
        // Usa fprintf para escrever todos os 12 campos em formato delimitado (CSV), terminando com \n.
        fprintf(f, "%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;%.2f;%d\n",
            p->id, p->nome_fantasia, p->razao_social, p->inscricao_estadual,
            p->cnpj, p->endereco_completo, p->telefone, p->email,
            p->nome_responsavel, p->telefone_responsavel, p->margem_lucro_padrao, p->ativo);
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

// Carrega a lista a partir de um arquivo de texto (CSV)
StatusOperacao carregar_produtora_txt(Listaprodutora** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");// Abre em modo de leitura ('r').
    if (!f) return ERRO_ABRIR_ARQUIVO;

    liberar_lista_produtora(lista);// Limpa a lista atual.

    produtora p;
    // Loop de leitura. fscanf usa %[^;] para strings delimitadas. Tenta ler 12 campos.

    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%f;%d\n",
        &p.id, p.nome_fantasia, p.razao_social, p.inscricao_estadual,
        p.cnpj, p.endereco_completo, p.telefone, p.email,
        p.nome_responsavel, p.telefone_responsavel, &p.margem_lucro_padrao, &p.ativo) == 12) {

        inserir_produtora(lista, p);// Insere o registro lido na nova lista.
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}
// Salva a lista em formato binário.
StatusOperacao salvar_produtora_bin(Listaprodutora* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "wb");// Abre em modo de escrita binária ('wb')
    if (!f) return ERRO_ABRIR_ARQUIVO;

    Listaprodutora* atual = lista;
    while (atual) {

        // fwrite copia os bytes brutos da estrutura 'produtora' para o arquivo.
        fwrite(&atual->conteudo, sizeof(produtora), 1, f);
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}
// Carrega a lista a partir de um arquivo binário.
StatusOperacao carregar_produtora_bin(Listaprodutora** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "rb");// Abre em modo de leitura binária ('rb').
    if (!f) return ERRO_ABRIR_ARQUIVO;

    liberar_lista_produtora(lista);//limpa a lista atual

    produtora p;
    // Loop: fread lê blocos de dados do tamanho de uma 'produtora'.
    while (fread(&p, sizeof(produtora), 1, f) == 1) inserir_produtora(lista, p);
    fclose(f);
    return OPERACAO_SUCESSO;
}

