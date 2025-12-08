#ifndef XML_CONTROLLER_H
#define XML_CONTROLLER_H

// Importa todos os modelos para conhecer as estruturas
#include "../model/cliente.h"
#include "../model/recurso.h"
#include "../model/orcamento.h"
#include "../model/fornecedor.h"
#include "../model/equipe.h"
#include "../model/operador.h"
#include "../model/financeiro.h"

// Função principal do módulo XML
void controller_menu_xml(
    ListaCliente** l_cli, 
    Listarecurso** l_rec, 
    ListaOrcamento** l_orc,
    Listafornecedor** l_for,
    Listaequipe** l_eq,
    Listaoperador** l_op,
    ListaCaixa** l_cx,
    ListaContaReceber** l_cr,
    ListaContaPagar** l_cp
);

#endif