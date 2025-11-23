// #ifndef ORCAMENTO_CONTROLLER_H
// #define ORCAMENTO_CONTROLLER_H

// #include "../model/orcamento.h"
// #include "../model/cliente.h"
// #include "../model/recurso.h"
// #include "../model/fornecedor.h"

// // Menu principal do módulo de orçamentos
// void controller_gerenciar_orcamentos(
//     ListaOrcamento** lista_orcamentos, 
//     ListaCliente* lista_clientes,
//     Listarecurso* lista_recursos,
//     Listafornecedor* lista_fornecedores
// );

// #endif

#ifndef ORCAMENTO_CONTROLLER_H
#define ORCAMENTO_CONTROLLER_H

#include "../model/orcamento.h"
#include "../model/cliente.h"
#include "../model/recurso.h"
#include "../model/fornecedor.h"
#include "../model/equipe.h" // <--- NOVO

void controller_gerenciar_orcamentos(
    ListaOrcamento** lista_orcamentos, 
    ListaCliente* lista_clientes,
    Listarecurso* lista_recursos,
    Listafornecedor* lista_fornecedores,
    Listaequipe* lista_equipe // <--- NOVO PARAMETRO
);

#endif