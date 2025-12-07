#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controller.h"

#include "../view/menus.h"
#include "../view/receber_dados.h"
#include "../view/mostrar_dados.h" 

// Includes dos Models
#include "../model/produtora.h"
#include "../model/cliente.h"
#include "../model/equipe.h"
#include "../model/recurso.h"
#include "../model/fornecedor.h"
#include "../model/operador.h"
#include "../model/orcamento.h" 
#include "../model/financeiro.h" 
// Includes dos Controllers
#include "produtora_controller.h"
#include "cliente_controller.h"
#include "equipe_controller.h"
#include "recurso_controller.h"
#include "fornecedor_controller.h"
#include "operador_controller.h"
#include "orcamento_controller.h" 
#include "financeiro_controller.h" // Financeiro

// No topo
#include "relatorios_controller.h"

static int modo_armazenamento = 1; 


static void carregar_tudo(
    Listaprodutora** l_prod, ListaCliente** l_cli, Listaequipe** l_eq, 
    Listarecurso** l_rec, Listafornecedor** l_for, Listaoperador** l_op, 
    ListaOrcamento** l_orc,
    ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp 
);


static void salvar_tudo(
    Listaprodutora* l_prod, ListaCliente* l_cli, Listaequipe* l_eq, 
    Listarecurso* l_rec, Listafornecedor* l_for, Listaoperador* l_op, 
    ListaOrcamento* l_orc, 
    ListaCaixa* l_cx, ListaContaReceber* l_cr, ListaContaPagar* l_cp 
);

static void controller_setup_inicial(Listaprodutora** lista_prod, Listaoperador** lista_op);

void controller_iniciar_sistema() {
    // Declara listas
    Listaprodutora* lista_produtora = NULL;
    ListaCliente* lista_cliente = NULL;
    Listaequipe* lista_equipe = NULL;
    Listarecurso* lista_recurso = NULL;
    Listafornecedor* lista_fornecedor = NULL;
    Listaoperador* lista_operador = NULL;
    ListaOrcamento* lista_orcamento = NULL;

    // Listas Financeiras
    ListaCaixa* lista_caixa = NULL;
    ListaContaReceber* lista_receber = NULL;
    ListaContaPagar* lista_pagar = NULL;

    //  MODO DE ARMAZENAMENTO ---
    view_exibir_mensagem("\n=== CONFIGURACAO DE ARMAZENAMENTO ===");
    view_exibir_mensagem("Escolha o formato para carregar/salvar os dados:");
    view_exibir_mensagem("1. Texto (CSV)");
    view_exibir_mensagem("2. Binario (.bin)");
    view_exibir_mensagem("Opcao: ");
    
    int opcao_modo = view_ler_opcao();
    if (opcao_modo == 2) {
        modo_armazenamento = 2;
        view_exibir_mensagem(">> Modo selecionado: BINARIO");
    } else {
        modo_armazenamento = 1;
        view_exibir_mensagem(">> Modo selecionado: TEXTO (CSV)");
    }

    // --- PASSO 2: CARREGAR TUDO ---
    view_exibir_mensagem("\n>> Tentando carregar dados existentes...");
    carregar_tudo(&lista_produtora, &lista_cliente, &lista_equipe, &lista_recurso, 
                  &lista_fornecedor, &lista_operador, &lista_orcamento,
                  &lista_caixa, &lista_receber, &lista_pagar);

    // --- PASSO 3: SETUP INICIAL ---
    controller_setup_inicial(&lista_produtora, &lista_operador);

    int opcao = -1;
    do {
        view_exibir_menu_principal(); 
        opcao = view_ler_opcao();

        switch (opcao) {
            case 1: controller_gerenciar_produtora(&lista_produtora); break;
            case 2: controller_gerenciar_clientes(&lista_cliente); break;
            case 3: controller_gerenciar_equipe(&lista_equipe); break;
            case 4: controller_gerenciar_recurso(&lista_recurso); break;
            case 5: controller_gerenciar_fornecedor(&lista_fornecedor); break;
            case 6: controller_gerenciar_operador(&lista_operador); break;
            
            case 7: { // Troca de Modo
                if (modo_armazenamento == 1) {
                    modo_armazenamento = 2;
                    view_exibir_mensagem("\n>> MODO ALTERADO PARA: BINARIO (.bin)");
                } else {
                    modo_armazenamento = 1;
                    view_exibir_mensagem("\n>> MODO ALTERADO PARA: TEXTO (.csv)");
                }
                salvar_tudo(lista_produtora, lista_cliente, lista_equipe, lista_recurso, 
                            lista_fornecedor, lista_operador, lista_orcamento,
                            lista_caixa, lista_receber, lista_pagar);
                break;
            }

            case 8: 
                // controller_gerenciar_orcamentos(&lista_orcamento, lista_cliente, lista_recurso, lista_fornecedor, lista_equipe, &lista_receber);
                   // Case 8 corrigido (com &lista_caixa no final)
                        controller_gerenciar_orcamentos(
                         &lista_orcamento, 
                          lista_cliente, 
                          lista_recurso, 
                          lista_fornecedor, 
                          lista_equipe, 
                         &lista_receber, 
                         &lista_caixa 
                    );
             
                break;
            
            
            case 9: // FINANCEIRO
                controller_gerenciar_financeiro(&lista_caixa, &lista_receber, &lista_pagar, lista_recurso, lista_produtora);
                break;

               case 10: 
                controller_menu_relatorios(
                    lista_cliente, 
                    lista_orcamento, 
                    lista_caixa, 
                    lista_receber, 
                    lista_pagar,
                    lista_recurso,
                    lista_fornecedor,
                    lista_equipe
                );
                break;
            case 0: 
                view_exibir_mensagem("\nSalvando dados e saindo...");
                salvar_tudo(lista_produtora, lista_cliente, lista_equipe, lista_recurso, 
                            lista_fornecedor, lista_operador, lista_orcamento,
                            lista_caixa, lista_receber, lista_pagar);
                break;
            default: view_exibir_mensagem("\n>> Opcao invalida!"); break;
        }
    } while (opcao != 0);

    // Libera memória
    liberar_lista(&lista_cliente);
    liberar_lista_equipe(&lista_equipe);
    liberar_lista_fornecedor(&lista_fornecedor);
    liberar_lista_produtora(&lista_produtora);
    liberar_lista_recurso(&lista_recurso);
    liberar_lista_operador(&lista_operador);
    liberar_lista_orcamento(&lista_orcamento);
    
    // ESTAVA FALTANDO: Liberar o financeiro
    liberar_listas_financeiro(&lista_caixa, &lista_receber, &lista_pagar);
    
    view_exibir_mensagem("Memoria liberada. Ate logo!");
}



static void carregar_tudo(
    Listaprodutora** l_prod, ListaCliente** l_cli, Listaequipe** l_eq, 
    Listarecurso** l_rec, Listafornecedor** l_for, Listaoperador** l_op, 
    ListaOrcamento** l_orc,
    ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp) 
{
    if (modo_armazenamento == 1) {
        // MODO TEXTO (CSV)
        carregar_produtora_txt(l_prod, "db_produtora.csv");
        carregar_clientes_txt(l_cli, "db_clientes.csv");
        carregar_equipe_txt(l_eq, "db_equipe.csv");
        carregar_recurso_txt(l_rec, "db_recurso.csv");
        carregar_fornecedor_txt(l_for, "db_fornecedor.csv");
        carregar_operador_txt(l_op, "db_operador.csv");
        carregar_orcamento_txt(l_orc, "db_orcamento.csv");
        // NOVO: Carrega Financeiro em TXT
        carregar_financeiro_txt(l_cx, l_cr, l_cp);
    } else {
        // MODO BINÁRIO
        carregar_produtora_bin(l_prod, "db_produtora.bin");
        carregar_clientes_bin(l_cli, "db_clientes.bin");
        carregar_equipe_bin(l_eq, "db_equipe.bin");
        carregar_recurso_bin(l_rec, "db_recurso.bin");
        carregar_fornecedor_bin(l_for, "db_fornecedor.bin");
        carregar_operador_bin(l_op, "db_operador.bin");
        carregar_orcamento_bin(l_orc, "db_orcamento.bin");
        // NOVO: Carrega Financeiro em BIN
        carregar_financeiro_bin(l_cx, l_cr, l_cp, "db_financeiro.bin");
    }
}

static void salvar_tudo(
    Listaprodutora* l_prod, ListaCliente* l_cli, Listaequipe* l_eq, 
    Listarecurso* l_rec, Listafornecedor* l_for, Listaoperador* l_op, 
    ListaOrcamento* l_orc,
    ListaCaixa* l_cx, ListaContaReceber* l_cr, ListaContaPagar* l_cp) 
{
    if (modo_armazenamento == 1) {
        // MODO TEXTO (CSV)
        salvar_produtora_txt(l_prod, "db_produtora.csv");
        salvar_clientes_txt(l_cli, "db_clientes.csv");
        salvar_equipe_txt(l_eq, "db_equipe.csv");
        salvar_recurso_txt(l_rec, "db_recurso.csv");
        salvar_fornecedor_txt(l_for, "db_fornecedor.csv");
        salvar_operador_txt(l_op, "db_operador.csv");
        salvar_orcamento_txt(l_orc, "db_orcamento.csv");
        // NOVO: Salva Financeiro em TXT (Gera 3 arquivos)
        salvar_financeiro_txt(l_cx, l_cr, l_cp);
    } else {
        // MODO BINÁRIO
        salvar_produtora_bin(l_prod, "db_produtora.bin");
        salvar_clientes_bin(l_cli, "db_clientes.bin");
        salvar_equipe_bin(l_eq, "db_equipe.bin");
        salvar_recurso_bin(l_rec, "db_recurso.bin");
        salvar_fornecedor_bin(l_for, "db_fornecedor.bin");
        salvar_operador_bin(l_op, "db_operador.bin");
        salvar_orcamento_bin(l_orc, "db_orcamento.bin");
        // NOVO: Salva Financeiro em BIN
        salvar_financeiro_bin(l_cx, l_cr, l_cp, "db_financeiro.bin");
    }
}

static void controller_setup_inicial(Listaprodutora** lista_prod, Listaoperador** lista_op) {
    if (*lista_prod == NULL) {
        view_exibir_mensagem("\n--- CONFIGURACAO INICIAL NECESSARIA ---");
        view_exibir_mensagem("Nenhuma Produtora encontrada. Vamos cadastrar:");
        produtora nova;
        view_ler_dados_produtora(&nova);
        nova.ativo = 1;
        inserir_produtora(lista_prod, nova);
    }
    if (*lista_op == NULL) {
        view_exibir_mensagem("\nNenhum Operador encontrado. Criando 'admin' padrao...");
        operador admin;
        strcpy(admin.nome, "Admin Padrao");
        strcpy(admin.usuario, "admin");
        admin.senha = 1234;
        admin.ativo = 1;
        inserir_operador(lista_op, admin);
    }
}
