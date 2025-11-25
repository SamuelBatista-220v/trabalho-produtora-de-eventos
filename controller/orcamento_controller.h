

#ifndef ORCAMENTO_CONTROLLER_H
#define ORCAMENTO_CONTROLLER_H

#include "../model/orcamento.h"
#include "../model/cliente.h"
#include "../model/recurso.h"
#include "../model/fornecedor.h"
#include "../model/equipe.h"
#include "../model/financeiro.h" 

void controller_gerenciar_orcamentos(
    ListaOrcamento** lista_orcamentos, 
    ListaCliente* lista_clientes,
    Listarecurso* lista_recursos,
    Listafornecedor* lista_fornecedores,
    Listaequipe* lista_equipe,
    ListaContaReceber** lista_receber,
    ListaCaixa** lista_caixa 
);

#endif