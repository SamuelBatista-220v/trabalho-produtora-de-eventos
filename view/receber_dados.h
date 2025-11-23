#ifndef RECEBER_DADOS_H
#define RECEBER_DADOS_H

#include "../model/cliente.h"
#include "../model/equipe.h"
#include "../model/fornecedor.h"
#include "../model/operador.h"
#include "../model/produtora.h"
#include "../model/recurso.h"

int view_ler_opcao();
void view_ler_dados_cliente(Cliente* cliente);
void view_ler_dados_equipe(equipe* equipe);
void view_ler_dados_fornecedor(fornecedor* fornecedor);
void view_ler_dados_operador(operador* operador);
void view_ler_dados_produtora(produtora* produtora);
void view_ler_dados_recurso(recurso* recurso);

// Adicione no topo, junto com os outros includes
#include "../model/orcamento.h"

// Adicione no final, junto com os outros protótipos
void view_ler_dados_base_orcamento(Orcamento* orcamento);

#endif // RECEBER_DADOS_H