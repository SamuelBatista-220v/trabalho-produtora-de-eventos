

// #ifndef RELATORIOS_CONTROLLER_H
// #define RELATORIOS_CONTROLLER_H

// #include "../model/cliente.h"
// #include "../model/orcamento.h"
// #include "../model/financeiro.h"
// #include "../model/produtora.h"
// #include "../model/fornecedor.h"
// #include "../model/recurso.h"
// #include "../model/equipe.h"

// // Menu Principal
// void controller_menu_relatorios(
//     ListaCliente* l_cli, 
//     ListaOrcamento* l_orc, 
//     ListaCaixa* l_cx,
//     ListaContaReceber* l_cr, 
//     ListaContaPagar* l_cp,
//     Listarecurso* l_rec,
//     Listafornecedor* l_for,
//     Listaequipe* l_eq
// );

// // Funções Internas (agora expostas para garantir consistência)
// void processar_relatorio_eventos(ListaOrcamento* lista, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq);
// void processar_relatorio_financeiro_completo(void* lista, int tipo_conta, ListaCliente* l_cli, Listafornecedor* l_for);
// void processar_relatorio_recursos_completo(Listarecurso* lista);
// void processar_relatorio_clientes(ListaCliente* lista);
// void processar_relatorio_caixa(ListaCaixa* lista);
// void processar_balanco_financeiro(ListaContaReceber* l_cr, ListaContaPagar* l_cp);

// #endif

#ifndef RELATORIOS_CONTROLLER_H
#define RELATORIOS_CONTROLLER_H

#include "../model/cliente.h"
#include "../model/orcamento.h"
#include "../model/financeiro.h"
#include "../model/produtora.h"
#include "../model/fornecedor.h"
#include "../model/recurso.h"
#include "../model/equipe.h"

// Menu Principal
void controller_menu_relatorios(
    ListaCliente* l_cli, 
    ListaOrcamento* l_orc, 
    ListaCaixa* l_cx,
    ListaContaReceber* l_cr, 
    ListaContaPagar* l_cp,
    Listarecurso* l_rec,
    Listafornecedor* l_for,
    Listaequipe* l_eq
);

// Funções Internas
void processar_relatorio_eventos(ListaOrcamento* lista, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq);
void processar_relatorio_financeiro_completo(void* lista, int tipo_conta, ListaCliente* l_cli, Listafornecedor* l_for);
void processar_relatorio_recursos_completo(Listarecurso* lista);
void processar_relatorio_clientes(ListaCliente* lista);
void processar_relatorio_caixa(ListaCaixa* lista);
void processar_balanco_financeiro(ListaContaReceber* l_cr, ListaContaPagar* l_cp);


void processar_relatorio_cronograma_geral(ListaOrcamento* l_orc, Listarecurso* l_rec);

#endif
