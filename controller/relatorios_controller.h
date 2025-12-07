#ifndef RELATORIOS_CONTROLLER_H
#define RELATORIOS_CONTROLLER_H

// Incluir TODOS os models para que os tipos sejam reconhecidos
#include "../model/cliente.h"
#include "../model/orcamento.h"
#include "../model/financeiro.h"   // <--- Essencial para ListaContaReceber
#include "../model/produtora.h"
#include "../model/fornecedor.h"
#include "../model/recurso.h"
#include "../model/equipe.h"

// Protótipo atualizado com TODOS os parâmetros
void controller_menu_relatorios(
    ListaCliente* l_cli, 
    ListaOrcamento* l_orc, 
    ListaCaixa* l_cx,
    ListaContaReceber* l_cr, // <--- Agora aceita receber
    ListaContaPagar* l_cp,
    Listarecurso* l_rec,
    Listafornecedor* l_for,
    Listaequipe* l_eq
);

#endif