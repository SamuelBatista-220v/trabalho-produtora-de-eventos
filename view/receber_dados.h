
#ifndef RECEBER_DADOS_H
#define RECEBER_DADOS_H

#include "../model/cliente.h"
#include "../model/equipe.h"
#include "../model/fornecedor.h"
#include "../model/operador.h"
#include "../model/produtora.h"
#include "../model/recurso.h"
#include "../model/orcamento.h" 

int view_ler_opcao();
void view_ler_dados_cliente(Cliente* cliente);
void view_ler_dados_equipe(equipe* equipe);
void view_ler_dados_fornecedor(fornecedor* fornecedor);
void view_ler_dados_operador(operador* operador);
void view_ler_dados_produtora(produtora* produtora);
void view_ler_dados_recurso(recurso* recurso);
void view_ler_dados_base_orcamento(Orcamento* orcamento);

//FUNÇÕES FINANCEIRAS 
void view_ler_totais_nota_fiscal(float* produtos, float* frete, float* impostos);
int view_ler_item_nota_fiscal(int* id_rec, int* qtd, float* custo);
void view_ler_dados_pagamento(int* forma_pag, char* data_venc, float* entrada, int* parcelas);


void view_ler_texto_generico(const char* label, char* destino, int tamanho);
void view_ler_float_generico(const char* label, float* destino);
void view_ler_data_generica(const char* label, char* destino);


void view_ler_texto_simples(char* destino, int tamanho);
void view_ler_float_simples(float* destino);
#endif


