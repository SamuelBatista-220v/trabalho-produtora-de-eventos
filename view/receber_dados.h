// #ifndef RECEBER_DADOS_H
// #define RECEBER_DADOS_H

// #include "../model/cliente.h"
// #include "../model/equipe.h"
// #include "../model/fornecedor.h"
// #include "../model/operador.h"
// #include "../model/produtora.h"
// #include "../model/recurso.h"

// int view_ler_opcao();
// void view_ler_dados_cliente(Cliente* cliente);
// void view_ler_dados_equipe(equipe* equipe);
// void view_ler_dados_fornecedor(fornecedor* fornecedor);
// void view_ler_dados_operador(operador* operador);
// void view_ler_dados_produtora(produtora* produtora);
// void view_ler_dados_recurso(recurso* recurso);

// // Adicione no topo, junto com os outros includes
// #include "../model/orcamento.h"

// // Adicione no final, junto com os outros protótipos
// void view_ler_dados_base_orcamento(Orcamento* orcamento);

// #endif // RECEBER_DADOS_H

#ifndef RECEBER_DADOS_H
#define RECEBER_DADOS_H

#include "../model/cliente.h"
#include "../model/equipe.h"
#include "../model/fornecedor.h"
#include "../model/operador.h"
#include "../model/produtora.h"
#include "../model/recurso.h"
#include "../model/orcamento.h" // Garanta que tem este include

int view_ler_opcao();
void view_ler_dados_cliente(Cliente* cliente);
void view_ler_dados_equipe(equipe* equipe);
void view_ler_dados_fornecedor(fornecedor* fornecedor);
void view_ler_dados_operador(operador* operador);
void view_ler_dados_produtora(produtora* produtora);
void view_ler_dados_recurso(recurso* recurso);
void view_ler_dados_base_orcamento(Orcamento* orcamento);

// --- NOVAS FUNÇÕES FINANCEIRAS (ADICIONE ISTO) ---
void view_ler_totais_nota_fiscal(float* produtos, float* frete, float* impostos);
int view_ler_item_nota_fiscal(int* id_rec, int* qtd, float* custo);
void view_ler_dados_pagamento(int* forma_pag, char* data_venc, float* entrada, int* parcelas);

#endif // RECEBER_DADOS_H