// Arquivo: cliente.c (Refatorado para ser um Model "puro")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

static int proximo_id = 1;

// Função alterada para retornar StatusOperacao
StatusOperacao inserir_cliente(ListaCliente** lista, Cliente novo_cliente) {
    ListaCliente* novo_no = (ListaCliente*) malloc(sizeof(ListaCliente));
    if (novo_no == NULL) {
        // REMOVIDO: printf de erro.
        // ADICIONADO: Retorno de status de erro.
        return ERRO_ALOCACAO_MEMORIA;
    }
    
    novo_cliente.id = proximo_id++;
    novo_no->conteudo = novo_cliente;
    novo_no->prox = NULL;
    
    if (*lista == NULL) {
        *lista = novo_no;
    } else {
        ListaCliente* atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_no;
    }
    // ADICIONADO: Retorno de status de sucesso.
    return OPERACAO_SUCESSO;
}

// Sem alterações nesta função
void liberar_lista(ListaCliente** lista) {
    ListaCliente* atual = *lista;
    ListaCliente* proximo_no;
    while (atual != NULL) {
        proximo_no = atual->prox;
        free(atual);
        atual = proximo_no;
    }
    *lista = NULL;
}

// Sem alterações nesta função
ListaCliente* buscar_cliente_por_id(ListaCliente* lista, int id_busca) {
    ListaCliente* atual = lista;
    while (atual != NULL) {
        if (atual->conteudo.id == id_busca) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}


StatusOperacao atualizar_cliente_por_id(ListaCliente* lista, int id_busca, Cliente clienteAtualizado)  {
    // Variavel auxiliar para percorrer a lista
    ListaCliente *atual = lista;

    // Enquanto o nó atual não for nulo, avança
    while (atual != NULL) {
        // Se o id do cliente atual for o id que eu quero, atualiza os dados
        // CORREÇÃO: Usamos 'conteudo' em vez de 'cliente'
        if (atual->conteudo.id == id_busca) {
            // CORREÇÃO: Copia a struct completa com os novos dados
            atual->conteudo = clienteAtualizado;
            
            // Garante que o id não foi alterado acidentalmente
            atual->conteudo.id = id_busca; 
            
            return OPERACAO_SUCESSO; // Sucesso
        }
        atual = atual->prox;
    }

    // Se chegar aqui, não achou o cliente
    return ERRO_CLIENTE_NAO_ENCONTRADO;
}

// Função alterada para retornar StatusOperacao
// StatusOperacao atualizar_cliente_por_id(ListaCliente* lista, int id_busca) {
//     ListaCliente* no_cliente = buscar_cliente_por_id(lista, id_busca);
//     if (no_cliente == NULL) {
//         // REMOVIDO: printf de aviso.
//         return ERRO_CLIENTE_NAO_ENCONTRADO;
//     }

//     // NOTA: Os printf e fgets a seguir são para interação durante a atualização.
//     // Em uma arquitetura 100% pura, essa interação seria gerenciada pelo
//     // Controller e pela View, mas para um app de console, manter aqui é uma
//     // simplificação prática e aceitável.
//     printf("\n--- Atualizando dados do Cliente ID: %d ---\n", id_busca);
//     printf("(Deixe em branco e pressione Enter para manter o dado atual)\n\n");
    
//     Cliente* cliente = &no_cliente->conteudo;
//     char buffer[256];

//     // ... (lógica de fgets para cada campo continua a mesma) ...
//     if (cliente->tipo == PESSOA_FISICA) {
//         printf("Nome atual: %s\nNovo nome: ", cliente->doc.pf.nome);
//         fgets(buffer, sizeof(buffer), stdin);
//         if (buffer[0] != '\n') {
//             buffer[strcspn(buffer, "\n")] = 0;
//             strcpy(cliente->doc.pf.nome, buffer);
//         }
//     } else {
//         printf("Razao Social atual: %s\nNova Razao Social: ", cliente->doc.pj.razao_social);
//         fgets(buffer, sizeof(buffer), stdin);
//         if (buffer[0] != '\n') {
//             buffer[strcspn(buffer, "\n")] = 0;
//             strcpy(cliente->doc.pj.razao_social, buffer);
//         }
//     }
//     // ... etc para os outros campos ...

//     // REMOVIDO: printf de sucesso.
//     return OPERACAO_SUCESSO;
// }

// Função alterada para retornar StatusOperacao
StatusOperacao desativar_cliente_por_id(ListaCliente* lista, int id_busca) {
    ListaCliente* no_cliente = buscar_cliente_por_id(lista, id_busca);
    if (no_cliente == NULL) {
        return ERRO_CLIENTE_NAO_ENCONTRADO;
    }
    if (no_cliente->conteudo.ativo == 0) {
        return ERRO_CLIENTE_JA_INATIVO;
    }
    no_cliente->conteudo.ativo = 0;
    return OPERACAO_SUCESSO;
}

// Função alterada para retornar StatusOperacao
StatusOperacao remover_fisico_cliente_por_id(ListaCliente** lista, int id_busca) {
    ListaCliente* atual = *lista;
    ListaCliente* anterior = NULL;

    while (atual != NULL && atual->conteudo.id != id_busca) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return ERRO_CLIENTE_NAO_ENCONTRADO;
    }

    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    return OPERACAO_SUCESSO;
}

// Função alterada para retornar StatusOperacao
StatusOperacao ativar_cliente_por_id(ListaCliente* lista, int id_busca) {
    ListaCliente* no_cliente = buscar_cliente_por_id(lista, id_busca);
    if (no_cliente == NULL) {
        return ERRO_CLIENTE_NAO_ENCONTRADO;
    }
    if (no_cliente->conteudo.ativo == 1) {
        return ERRO_CLIENTE_JA_ATIVO;
    }
    no_cliente->conteudo.ativo = 1;
    return OPERACAO_SUCESSO;
}