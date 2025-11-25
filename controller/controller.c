

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
#include "../model/orcamento.h" // <--- IMPORTANTE

// Includes dos Controllers
#include "produtora_controller.h"
#include "cliente_controller.h"
#include "equipe_controller.h"
#include "recurso_controller.h"
#include "fornecedor_controller.h"
#include "operador_controller.h"
#include "orcamento_controller.h" // <--- IMPORTANTE

static int modo_armazenamento = 1; 

// --- 1. PROTÓTIPOS ATUALIZADOS (Adicionado l_orc) ---
static void carregar_tudo(Listaprodutora** l_prod, ListaCliente** l_cli, Listaequipe** l_eq, Listarecurso** l_rec, Listafornecedor** l_for, Listaoperador** l_op, ListaOrcamento** l_orc);
static void salvar_tudo(Listaprodutora* l_prod, ListaCliente* l_cli, Listaequipe* l_eq, Listarecurso* l_rec, Listafornecedor* l_for, Listaoperador* l_op, ListaOrcamento* l_orc);
static void controller_setup_inicial(Listaprodutora** lista_prod, Listaoperador** lista_op);

void controller_iniciar_sistema() {
    // Declara listas
    Listaprodutora* lista_produtora = NULL;
    ListaCliente* lista_cliente = NULL;
    Listaequipe* lista_equipe = NULL;
    Listarecurso* lista_recurso = NULL;
    Listafornecedor* lista_fornecedor = NULL;
    Listaoperador* lista_operador = NULL;
    ListaOrcamento* lista_orcamento = NULL; // <--- DECLARAÇÃO DA LISTA

    // --- PASSO 1: MODO DE ARMAZENAMENTO ---
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
    
    // --- 2. CHAMADA ATUALIZADA (Passando &lista_orcamento) ---
    carregar_tudo(&lista_produtora, &lista_cliente, &lista_equipe, &lista_recurso, &lista_fornecedor, &lista_operador, &lista_orcamento);

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
                // Salva tudo imediatamente no novo formato
                salvar_tudo(lista_produtora, lista_cliente, lista_equipe, lista_recurso, lista_fornecedor, lista_operador, lista_orcamento);
                break;
            }

            // // --- CASE 8: ORÇAMENTOS ---
            // case 8: 
            //     controller_gerenciar_orcamentos(&lista_orcamento, lista_cliente, lista_recurso, lista_fornecedor);
            //     break;
             case 8: 
                controller_gerenciar_orcamentos(&lista_orcamento, lista_cliente, lista_recurso, lista_fornecedor, lista_equipe);
                break;
            case 0: 
                view_exibir_mensagem("\nSalvando dados e saindo...");
                // Chamada de salvamento atualizada
                salvar_tudo(lista_produtora, lista_cliente, lista_equipe, lista_recurso, lista_fornecedor, lista_operador, lista_orcamento);
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
    liberar_lista_orcamento(&lista_orcamento); // Libera orçamentos
    
    view_exibir_mensagem("Memoria liberada. Ate logo!");
}

// --- 3. IMPLEMENTAÇÕES ATUALIZADAS (Adicionado parâmetro l_orc) ---

static void carregar_tudo(Listaprodutora** l_prod, ListaCliente** l_cli, Listaequipe** l_eq, Listarecurso** l_rec, Listafornecedor** l_for, Listaoperador** l_op, ListaOrcamento** l_orc) {
    if (modo_armazenamento == 1) {
        // Carrega TXT
        carregar_produtora_txt(l_prod, "db_produtora.csv");
        carregar_clientes_txt(l_cli, "db_clientes.csv");
        carregar_equipe_txt(l_eq, "db_equipe.csv");
        carregar_recurso_txt(l_rec, "db_recurso.csv");
        carregar_fornecedor_txt(l_for, "db_fornecedor.csv");
        carregar_operador_txt(l_op, "db_operador.csv");
        
        // AQUI ESTAVA O ERRO: Agora usamos l_orc corretamente
        carregar_orcamento_txt(l_orc, "db_orcamento.csv"); 
    } else {
        // Carrega BIN
        carregar_produtora_bin(l_prod, "db_produtora.bin");
        carregar_clientes_bin(l_cli, "db_clientes.bin");
        carregar_equipe_bin(l_eq, "db_equipe.bin");
        carregar_recurso_bin(l_rec, "db_recurso.bin");
        carregar_fornecedor_bin(l_for, "db_fornecedor.bin");
        carregar_operador_bin(l_op, "db_operador.bin");
        
        // AQUI TAMBÉM: Usamos l_orc
        carregar_orcamento_bin(l_orc, "db_orcamento.bin");
    }
}

static void salvar_tudo(Listaprodutora* l_prod, ListaCliente* l_cli, Listaequipe* l_eq, Listarecurso* l_rec, Listafornecedor* l_for, Listaoperador* l_op, ListaOrcamento* l_orc) {
    if (modo_armazenamento == 1) {
        salvar_produtora_txt(l_prod, "db_produtora.csv");
        salvar_clientes_txt(l_cli, "db_clientes.csv");
        salvar_equipe_txt(l_eq, "db_equipe.csv");
        salvar_recurso_txt(l_rec, "db_recurso.csv");
        salvar_fornecedor_txt(l_for, "db_fornecedor.csv");
        salvar_operador_txt(l_op, "db_operador.csv");
        
        // AQUI TAMBÉM: Usamos l_orc
        salvar_orcamento_txt(l_orc, "db_orcamento.csv");
    } else {
        salvar_produtora_bin(l_prod, "db_produtora.bin");
        salvar_clientes_bin(l_cli, "db_clientes.bin");
        salvar_equipe_bin(l_eq, "db_equipe.bin");
        salvar_recurso_bin(l_rec, "db_recurso.bin");
        salvar_fornecedor_bin(l_for, "db_fornecedor.bin");
        salvar_operador_bin(l_op, "db_operador.bin");
        
        // AQUI TAMBÉM: Usamos l_orc
        salvar_orcamento_bin(l_orc, "db_orcamento.bin");
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


// // Função principal que gerencia o fluxo da aplicação.
// void controller_iniciar_sistema() {
//     // Declara uma lista para cada módulo do sistema
//     ListaCliente* lista_de_clientes = NULL;
//     ListaEquipe* lista_de_equipe = NULL;

//     int opcao = -1;

//     do {
//         // CORREÇÃO AQUI: Chamando a função de menu principal correta
//         view_exibir_menu_principal(); 
//         opcao = view_ler_opcao();

//         switch (opcao) {
//             case 1:
//                 controller_gerenciar_clientes(&lista_de_clientes);
//                 break;
//             case 2:
//                 controller_gerenciar_equipe(&lista_de_equipe);
//                 break;
//             case 0:
//                 view_exibir_mensagem("\nSaindo do programa...");
//                 break;
//             default:
//                 view_exibir_mensagem("\n>> Opcao invalida! Tente novamente.");
//                 break;
//         }
//     } while (opcao != 0);

//     // Libera a memória de todas as listas antes de encerrar
//     liberar_lista(&lista_de_clientes);
//     liberar_lista_equipe(&lista_de_equipe);
//     view_exibir_mensagem("Memoria liberada com sucesso.");
// }


///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

//                 if (id_busca <= 0) {
//                     view_exibir_mensagem(">> Codigo invalido.");
//                     break;
//                 }

//                 ListaCliente* no_cliente = buscar_cliente_por_id(minha_lista, id_busca);

//                 if (no_cliente == NULL) {
//                     view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
//                 } else {
//                     printf("\n--- Digite os NOVOS dados para o cliente de ID %d ---\n", id_busca);
//                     Cliente cliente_atualizado;
                    
//                     view_ler_dados_cliente(&cliente_atualizado); 
                    
//                     // Preserva o status 'ativo' original do cliente para evitar corrupção de dados
//                     cliente_atualizado.ativo = no_cliente->conteudo.ativo; 

//                     StatusOperacao status = atualizar_cliente_por_id(minha_lista, id_busca, cliente_atualizado);

//                     if (status == OPERACAO_SUCESSO) {
//                         view_exibir_mensagem("\n>> SUCESSO: Cliente atualizado.");
//                     } else {
//                         view_exibir_mensagem("\n>> ERRO: Falha inesperada ao atualizar o cliente.");
//                     }
//                 }
//                 break;
//             }

//             case 4: { // Desativar cliente
//                 view_exibir_mensagem("Digite o Codigo (ID) do cliente a ser desativado: ");
//                 int id_busca = view_ler_opcao();
//                 if (id_busca <= 0) {
//                     view_exibir_mensagem(">> Codigo invalido.");
//                     break;
//                 }
            
//                 StatusOperacao status = desativar_cliente_por_id(minha_lista, id_busca);
            
//                 if (status == OPERACAO_SUCESSO) {
//                     view_exibir_mensagem("\n>> SUCESSO: Cliente desativado.");
//                 } else if (status == ERRO_CLIENTE_NAO_ENCONTRADO) {
//                     view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
//                 } else if (status == ERRO_CLIENTE_JA_INATIVO) {
//                     view_exibir_mensagem("\n>> AVISO: O cliente ja esta inativo.");
//                 }
//                 break;
//             }

//             case 5: { // Remover cliente (fisicamente)
//                 view_exibir_mensagem("Digite o Codigo (ID) do cliente a ser removido: ");
//                 int id_busca = view_ler_opcao();
//                 if (id_busca <= 0) {
//                     view_exibir_mensagem(">> Codigo invalido.");
//                     break;
//                 }

//                 StatusOperacao status = remover_fisico_cliente_por_id(&minha_lista, id_busca);

//                 if (status == OPERACAO_SUCESSO) {
//                     view_exibir_mensagem("\n>> SUCESSO: Cliente removido fisicamente.");
//                 } else if (status == ERRO_CLIENTE_NAO_ENCONTRADO) {
//                     view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
//                 }
//                 break;
//             }
            
//             case 6: { // Ativar cliente
//                 view_exibir_mensagem("Digite o Codigo (ID) do cliente a ser ativado: ");
//                 int id_busca = view_ler_opcao();
//                 if (id_busca <= 0) {
//                     view_exibir_mensagem(">> Codigo invalido.");
//                     break;
//                 }

//                 StatusOperacao status = ativar_cliente_por_id(minha_lista, id_busca);

//                 if (status == OPERACAO_SUCESSO) {
//                     view_exibir_mensagem("\n>> SUCESSO: Cliente ativado.");
//                 } else if (status == ERRO_CLIENTE_NAO_ENCONTRADO) {
//                     view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
//                 } else if (status == ERRO_CLIENTE_JA_ATIVO) {
//                     view_exibir_mensagem("\n>> AVISO: O cliente ja esta ativo.");
//                 }
//                 break;
//             }

//             case 7: { // Listar todos os clientes
//                 view_imprimir_lista(minha_lista);
//                 break;
//             }

//             case 0: { // Sair
//                 view_exibir_mensagem("\nSaindo do programa...");
//                 break;
//             }

//             default: { // Opção inválida
//                 view_exibir_mensagem("\n>> Opcao invalida! Tente novamente.");
//                 break;
//             }
//         }
//     } while (opcao != 0);

//     // Libera a memória alocada para a lista antes de encerrar o programa.
//     liberar_lista(&minha_lista);
//     view_exibir_mensagem("Memoria liberada com sucesso. Adeus!");
// }