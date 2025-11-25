#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orcamento.h"

static int proximo_id_orcamento = 1;



StatusOperacao inserir_orcamento(ListaOrcamento** lista, Orcamento novo) {
    ListaOrcamento* novo_no = (ListaOrcamento*) malloc(sizeof(ListaOrcamento));
    if (!novo_no) return ERRO_ALOCACAO_MEMORIA;

    if (novo.id <= 0) novo.id = proximo_id_orcamento++;
    else if (novo.id >= proximo_id_orcamento) proximo_id_orcamento = novo.id + 1;

    novo_no->conteudo = novo;
    novo_no->prox = NULL;

    if (*lista == NULL) {
        *lista = novo_no;
    } else {
        ListaOrcamento* aux = *lista;
        while (aux->prox) aux = aux->prox;
        aux->prox = novo_no;
    }
    return OPERACAO_SUCESSO;
}

ListaOrcamento* buscar_orcamento_por_id(ListaOrcamento* lista, int id) {
    while (lista) {
        if (lista->conteudo.id == id) return lista;
        lista = lista->prox;
    }
    return NULL;
}

void liberar_lista_orcamento(ListaOrcamento** lista) {
    ListaOrcamento* atual = *lista;
    while (atual) {
        ListaOrcamento* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    *lista = NULL;
}



StatusOperacao salvar_orcamento_bin(ListaOrcamento* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "wb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    while (lista) {
        fwrite(&lista->conteudo, sizeof(Orcamento), 1, f);
        lista = lista->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

StatusOperacao carregar_orcamento_bin(ListaOrcamento** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "rb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    
    liberar_lista_orcamento(lista);
    proximo_id_orcamento = 1;
    
    Orcamento temp;
    while (fread(&temp, sizeof(Orcamento), 1, f) == 1) {
        inserir_orcamento(lista, temp);
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}



StatusOperacao remover_fisico_orcamento(ListaOrcamento** lista, int id) {
    ListaOrcamento* atual = *lista;
    ListaOrcamento* anterior = NULL;

    // Procura o nó
    while (atual != NULL && atual->conteudo.id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    // Se não encontrou
    if (atual == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }

    // Se for o primeiro da lista
    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        // Se for do meio ou fim
        anterior->prox = atual->prox;
    }

    free(atual); // Libera a memória
    return OPERACAO_SUCESSO;
}

StatusOperacao salvar_orcamento_txt(ListaOrcamento* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "w");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    
    // Cabeçalho Expandido
    fprintf(f, "ID;Cliente;Evento;Local;Inicio;Fim;Status;Total;ITENS_RECURSOS;ITENS_EQUIPE\n");

    while (lista) {
        Orcamento* o = &lista->conteudo;
        fprintf(f, "%d;%d;%s;%s;%02d/%02d/%d;%02d/%02d/%d;%d;%.2f;",
            o->id, o->id_cliente, o->nome_evento, o->local,
            o->dia_inicio, o->mes_inicio, o->ano_inicio,
            o->dia_fim, o->mes_fim, o->ano_fim,
            o->status, o->valor_total_geral);

        // Salva Recursos: "ID:Qtd|ID:Qtd"
        if (o->qtd_recursos_selecionados == 0) fprintf(f, "NONE");
        else {
            for(int i=0; i<o->qtd_recursos_selecionados; i++) {
                fprintf(f, "%d:%d|", o->lista_recursos[i].id_recurso, o->lista_recursos[i].quantidade);
            }
        }
        fprintf(f, ";");

        // Salva Equipe: "ID:Dias|ID:Dias"
        if (o->qtd_equipe_selecionada == 0) fprintf(f, "NONE");
        else {
            for(int i=0; i<o->qtd_equipe_selecionada; i++) {
                fprintf(f, "%d:%d|", o->lista_equipe[i].id_membro_equipe, o->lista_equipe[i].dias_trabalhados);
            }
        }
        fprintf(f, "\n");

        lista = lista->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

// Carregamento Simplificado (Lê estrutura base, ignora detalhes complexos para evitar bugs de parsing agora)

StatusOperacao carregar_orcamento_txt(ListaOrcamento** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    
    liberar_lista_orcamento(lista);
    char buffer[1024];
    fgets(buffer, 1024, f); // Pula header

    Orcamento o;
    // Lemos apenas os dados principais para restaurar o histórico básico
    // O %*s ignora as colunas de itens complexos
    while (fscanf(f, "%d;%d;%[^;];%[^;];%d/%d/%d;%d/%d/%d;%d;%f;%*[^;];%*s\n",
        &o.id, &o.id_cliente, o.nome_evento, o.local,
        &o.dia_inicio, &o.mes_inicio, &o.ano_inicio,
        &o.dia_fim, &o.mes_fim, &o.ano_fim,
        (int*)&o.status, &o.valor_total_geral) == 12) {
        
        o.qtd_dias = (o.dia_fim - o.dia_inicio) + 1;
        // Zera listas internas pois o TXT simples não restaura detalhe profundo (apenas Binário faz isso perfeito)
        o.qtd_recursos_selecionados = 0; 
        o.qtd_equipe_selecionada = 0;
        o.ativo = 1;
        
        inserir_orcamento(lista, o);
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}