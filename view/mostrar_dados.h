#ifndef MOSTRAR_DADOS_H
#define MOSTRAR_DADOS_H


#include "../model/produtora.h"
#include "../model/cliente.h"
#include "../model/equipe.h"
#include "../model/recurso.h"
#include "../model/fornecedor.h"
#include "../model/produtora.h"
#include "../model/operador.h"

void view_exibir_mensagem(const char* mensagem);

void view_imprimir_lista_produtora(Listaprodutora* lista);
void view_imprimir_produtora_unico(Listaprodutora* no_produtora);

void view_imprimir_lista(ListaCliente* lista);
void view_imprimir_cliente_unico(ListaCliente* no_cliente);

void view_imprimir_equipe_unico(Listaequipe* no_equipe);
void view_imprimir_lista_equipe(Listaequipe* lista);

void view_imprimir_lista_recurso(Listarecurso* lista);
void view_imprimir_recurso_unico(Listarecurso* no_recurso);

void view_imprimir_fornecedor_unico(Listafornecedor* no_fornecedor);
void view_imprimir_lista_fornecedor(Listafornecedor* lista);

void view_imprimir_lista_operador(Listaoperador* lista);
void view_imprimir_operador_unico(Listaoperador* no_operador);


#include "../model/orcamento.h"


void view_exibir_ocupacao_recurso(int id_recurso, char* nome, int dia_i, int mes_i, int ano_i, int dia_f, int mes_f, int ano_f, int qtd);

void view_imprimir_orcamento_unico(Orcamento* o, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq);

void view_imprimir_lista_orcamento(ListaOrcamento* lista, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq);

void view_imprimir_lista_orcamento_por_status(ListaOrcamento* lista, int status_filtro, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq);

void view_exibir_ocupacao_recurso(int id_recurso, char* nome, int dia_i, int mes_i, int ano_i, int dia_f, int mes_f, int ano_f, int qtd);



#include "../model/financeiro.h" 


void view_imprimir_relatorio_financeiro(ListaContaPagar* l_cp, ListaContaReceber* l_cr);
void view_imprimir_extrato_caixa_detalhado(ListaCaixa* lista);

void view_imprimir_nota_fiscal_detalhada(void* lista_itens, int qtd_itens, float total_prod, float total_frete, float total_imp);
#endif 