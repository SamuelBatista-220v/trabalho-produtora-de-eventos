#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fornecedor.h"

#include "status.h"

// Variável estática para controlar o próximo ID de fornecedor
static int proximo_id_fornecedor = 1;

StatusOperacao inserir_fornecedor(Listafornecedor** lista, fornecedor novo_fornecedor) {
    Listafornecedor* novo_no = (Listafornecedor*) malloc(sizeof(Listafornecedor));
    if (novo_no == NULL) {
        return ERRO_ALOCACAO_MEMORIA;
    }

    novo_fornecedor.id = proximo_id_fornecedor++; // Atribui e incrementa o ID global
    novo_no->conteudo = novo_fornecedor;
    novo_no->prox = NULL;

    if (*lista == NULL) {
        *lista = novo_no;
    } else {
        Listafornecedor* atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_no;
    }
    return OPERACAO_SUCESSO;
}


Listafornecedor* buscar_fornecedor_por_id(Listafornecedor* lista, int id_busca) {
    Listafornecedor* atual = lista;
    while (atual != NULL) {
        if (atual->conteudo.id == id_busca) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}


StatusOperacao atualizar_fornecedor_por_id(Listafornecedor* lista, int id_busca, fornecedor fornecedor_atualizado) {
    Listafornecedor* no_fornecedor = buscar_fornecedor_por_id(lista, id_busca);
    if (no_fornecedor == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }

    // Preserva o ID original e o status de ativo, que não devem ser alterados aqui
    fornecedor_atualizado.id = no_fornecedor->conteudo.id;
    fornecedor_atualizado.ativo = no_fornecedor->conteudo.ativo;

    no_fornecedor->conteudo = fornecedor_atualizado;



    return OPERACAO_SUCESSO;
}


StatusOperacao desativar_fornecedor_por_id(Listafornecedor* lista, int id_busca) {
    Listafornecedor* no_fornecedor = buscar_fornecedor_por_id(lista, id_busca);
    if (no_fornecedor == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_fornecedor->conteudo.ativo == 0) {
        return ERRO_JA_INATIVO;
    }
    no_fornecedor->conteudo.ativo = 0;
    return OPERACAO_SUCESSO;
}


StatusOperacao ativar_fornecedor_por_id(Listafornecedor* lista, int id_busca) {
    Listafornecedor* no_fornecedor = buscar_fornecedor_por_id(lista, id_busca);
    if (no_fornecedor == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_fornecedor->conteudo.ativo == 1) {
        return ERRO_JA_ATIVO;
    }
    no_fornecedor->conteudo.ativo = 1;
    return OPERACAO_SUCESSO;
}


StatusOperacao remover_fisico_fornecedor_por_id(Listafornecedor** lista, int id_busca) {
    Listafornecedor* atual = *lista;
    Listafornecedor* anterior = NULL;

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

void liberar_lista_fornecedor(Listafornecedor** lista) {
    Listafornecedor* atual = *lista;
    Listafornecedor* proximo_no;
    while (atual != NULL) {
        proximo_no = atual->prox;
        free(atual);
        atual = proximo_no;
    }
    *lista = NULL;
}


// #include <stdlib.h>
// #include <string.h>
// #include "fornecedor.h"


// static int proximo_id_fornecedores = 1;

// // Exemplo da função de inserir
// StatusOperacao inserir_fornecedores(Listafornecedores** lista, fornecedores nova_fornecedores) {
//     Listafornecedores* novo_no = (Listafornecedores*) malloc(sizeof(Listafornecedores));
//     if (novo_no == NULL) {
//         return ERRO_ALOCACAO_MEMORIA;
//     }

//     nova_fornecedores.id = proximo_id_fornecedores++;
//     novo_no->conteudo = nova_fornecedores;
//     novo_no->prox = NULL;

//     if (*lista == NULL) {
//         *lista = novo_no;
//     } else {
//         Listafornecedores* atual = *lista;
//         while (atual->prox != NULL) {
//             atual = atual->prox;
//         }
//         atual->prox = novo_no;
//     }
//     return OPERACAO_SUCESSO;
// }

// // Função para buscar um membro da fornecedores por ID
// Listafornecedores* buscar_fornecedores_por_id(Listafornecedores* lista, int id_busca) {
//     Listafornecedores* atual = lista;
//     while (atual != NULL) {
//         if (atual->conteudo.id == id_busca) {
//             return atual;
//         }
//         atual = atual->prox;
//     }
//     return NULL;
// }

// // Função para atualizar os dados de um membro da fornecedores
// StatusOperacao atualizar_fornecedores_por_id(Listafornecedores* lista, int id_busca, fornecedores fornecedoresAtualizada) {
//     Listafornecedores* atual = lista;
//     while (atual != NULL) {
//         if (atual->conteudo.id == id_busca) {
//             atual->conteudo = fornecedoresAtualizada;
//             atual->conteudo.id = id_busca; // Garante que o ID não mude
//             return OPERACAO_SUCESSO;
//         }
//         atual = atual->prox;
//     }
//     return ERRO_CLIENTE_NAO_ENCONTRADO; // Pode criar um ERRO_fornecedores_NAO_ENCONTRADA se preferir
// }

// // Função para desativar um membro da fornecedores (soft delete)
// StatusOperacao desativar_fornecedores_por_id(Listafornecedores* lista, int id_busca) {
//     Listafornecedores* no_fornecedores = buscar_fornecedores_por_id(lista, id_busca);
//     if (no_fornecedores == NULL) {
//         return ERRO_CLIENTE_NAO_ENCONTRADO;
//     }
//     if (no_fornecedores->conteudo.ativo == 0) {
//         return ERRO_CLIENTE_JA_INATIVO; // Pode criar um ERRO_fornecedores_JA_INATIVA
//     }
//     no_fornecedores->conteudo.ativo = 0;
//     return OPERACAO_SUCESSO;
// }

// // Função para remover fisicamente um membro da fornecedores da lista
// StatusOperacao remover_fisico_fornecedores_por_id(Listafornecedores** lista, int id_busca) {
//     Listafornecedores* atual = *lista;
//     Listafornecedores* anterior = NULL;

//     while (atual != NULL && atual->conteudo.id != id_busca) {
//         anterior = atual;
//         atual = atual->prox;
//     }

//     if (atual == NULL) {
//         return ERRO_CLIENTE_NAO_ENCONTRADO;
//     }

//     if (anterior == NULL) {
//         *lista = atual->prox;
//     } else {
//         anterior->prox = atual->prox;
//     }

//     free(atual);
//     return OPERACAO_SUCESSO;
// }

// // Função para ativar um membro da fornecedores
// StatusOperacao ativar_fornecedores_por_id(Listafornecedores* lista, int id_busca) {
//     Listafornecedores* no_fornecedores = buscar_fornecedores_por_id(lista, id_busca);
//     if (no_fornecedores == NULL) {
//         return ERRO_CLIENTE_NAO_ENCONTRADO;
//     }
//     if (no_fornecedores->conteudo.ativo == 1) {
//         return ERRO_CLIENTE_JA_ATIVO; // Pode criar um ERRO_fornecedores_JA_ATIVA
//     }
//     no_fornecedores->conteudo.ativo = 1;
//     return OPERACAO_SUCESSO;
// }

// // Não se esqueça da função para liberar a memória da lista!
// void liberar_lista_fornecedores(Listafornecedores** lista) {
//     Listafornecedores* atual = *lista;
//     Listafornecedores* proximo_no;
//     while (atual != NULL) {
//         proximo_no = atual->prox;
//         free(atual);
//         atual = proximo_no;
//     }
//     *lista = NULL;
// }