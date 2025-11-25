

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