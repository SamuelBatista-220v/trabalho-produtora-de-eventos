
// #ifndef FINANCEIRO_CONTROLLER_H
// #define FINANCEIRO_CONTROLLER_H

// #include "../model/financeiro.h"
// #include "../model/recurso.h"
// #include "../model/produtora.h"

// // Função principal para processar compras (ATUALIZADO: Recebe Caixa)
// void processar_entrada_nota_fiscal(Listarecurso* lista_recursos, ListaContaPagar** lista_pagar, Listaprodutora* lista_produtora, ListaCaixa** lista_caixa);

// void listar_contas_financeiras(ListaContaPagar* l_cp, ListaContaReceber* l_cr);
// void realizar_pagamento_conta(ListaContaPagar* l_cp, ListaCaixa** l_cx);
// void realizar_recebimento_conta(ListaContaReceber* l_cr, ListaCaixa** l_cx);
// void exibir_extrato_caixa(ListaCaixa* l_cx);

// void controller_gerenciar_financeiro(ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp, Listarecurso* l_rec, Listaprodutora* l_prod);

// #endif

// #ifndef FINANCEIRO_CONTROLLER_H
// #define FINANCEIRO_CONTROLLER_H

// #include "../model/financeiro.h"
// #include "../model/recurso.h"
// #include "../model/produtora.h"

// // Função principal para processar compras (Entrada de Nota Fiscal)
// // [MODIFICADO] Agora recebe ListaCaixa para lançar pagamentos à vista/entradas
// void processar_entrada_nota_fiscal(
//     Listarecurso* lista_recursos, 
//     ListaContaPagar** lista_pagar, 
//     Listaprodutora* lista_produtora, 
//     ListaCaixa** lista_caixa
// );

// // Funções de Relatório e Operação
// void listar_contas_financeiras(ListaContaPagar* l_cp, ListaContaReceber* l_cr);
// void realizar_pagamento_conta(ListaContaPagar* l_cp, ListaCaixa** l_cx);
// void realizar_recebimento_conta(ListaContaReceber* l_cr, ListaCaixa** l_cx);
// void exibir_extrato_caixa(ListaCaixa* l_cx);

// // Menu Principal do Financeiro
// void controller_gerenciar_financeiro(
//     ListaCaixa** l_cx, 
//     ListaContaReceber** l_cr, 
//     ListaContaPagar** l_cp, 
//     Listarecurso* l_rec, 
//     Listaprodutora* l_prod
// );

// #endif

#ifndef FINANCEIRO_CONTROLLER_H
#define FINANCEIRO_CONTROLLER_H

#include "../model/financeiro.h"
#include "../model/recurso.h"
#include "../model/produtora.h"

void processar_entrada_nota_fiscal(
    Listarecurso* lista_recursos, 
    ListaContaPagar** lista_pagar, 
    Listaprodutora* lista_produtora, 
    ListaCaixa** lista_caixa
);

void listar_contas_financeiras(ListaContaPagar* l_cp, ListaContaReceber* l_cr);

// [MODIFICADO] Agora recebem ponteiro duplo para poder remover da lista
void realizar_pagamento_conta(ListaContaPagar** l_cp, ListaCaixa** l_cx);
void realizar_recebimento_conta(ListaContaReceber** l_cr, ListaCaixa** l_cx);

void exibir_extrato_caixa(ListaCaixa* l_cx);

void controller_gerenciar_financeiro(
    ListaCaixa** l_cx, 
    ListaContaReceber** l_cr, 
    ListaContaPagar** l_cp, 
    Listarecurso* l_rec, 
    Listaprodutora* l_prod
);

#endif