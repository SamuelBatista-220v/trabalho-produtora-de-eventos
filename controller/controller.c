#include <stdio.h>
#include "controller.h"

#include <string.h> // Necessário para o strcpy do operador padrão

// #include "../view/view.h"
// Em cliente_controller.c
#include "../view/menus.h"
#include "../view/mostrar_dados.h"
#include "../view/receber_dados.h"

#include "../model/cliente.h"
#include "../model/equipe.h"
#include "../model/fornecedor.h"
#include "../model/produtora.h"
#include "../model/recurso.h"
#include "../model/operador.h"

// Inclui os headers dos novos sub-controllers
#include "cliente_controller.h"
#include "equipe_controller.h"
#include "fornecedor_controller.h"
#include "produtora_controller.h"
#include "recurso_controller.h"
#include "operador_controller.h"

static void controller_setup_inicial(Listaprodutora** lista_prod, Listaoperador** lista_op);

// Função principal que gerencia o fluxo da aplicação.
void controller_iniciar_sistema() {
    // Declara uma lista para cada módulo do sistema
    Listaprodutora* lista_de_produtora = NULL;
    ListaCliente* lista_de_clientes = NULL;
    Listaequipe* lista_de_equipe = NULL;
    Listarecurso* lista_de_recurso = NULL;
    Listafornecedor* lista_de_fornecedor = NULL;
    Listaoperador* lista_de_operador= NULL;
                    

    int opcao = -1;

    controller_setup_inicial(&lista_de_produtora, &lista_de_operador);

    do {
        // CORREÇÃO AQUI: Chamando a função de menu principal correta
        view_exibir_menu_principal(); 
        opcao = view_ler_opcao();

        switch (opcao) {
            case 1:
                controller_gerenciar_produtora(&lista_de_produtora);
                break;
            case 2:
                controller_gerenciar_clientes(&lista_de_clientes);
                break;
            case 3:
                controller_gerenciar_equipe(&lista_de_equipe);
                break; 
            case 4:
                controller_gerenciar_recurso(&lista_de_recurso);
                break;
            case 5:
                controller_gerenciar_fornecedor(&lista_de_fornecedor);
                break;
            case 6:
                controller_gerenciar_operador(&lista_de_operador);
                break;
            case 0:
                view_exibir_mensagem("\nSaindo do programa...");
                break;
            default:
                view_exibir_mensagem("\n>> Opcao invalida! Tente novamente.");
                break;
        }
    } while (opcao != 0);


    liberar_lista(&lista_de_clientes);
  liberar_lista_equipe(&lista_de_equipe);
  liberar_lista_fornecedor(&lista_de_fornecedor);
  liberar_lista_produtora(&lista_de_produtora);
  liberar_lista_recurso(&lista_de_recurso);
  liberar_lista_operador(&lista_de_operador);
  view_exibir_mensagem("Memoria liberada com sucesso.");

    // Libera a memória de todas as listas antes de encerrar
    // liberar_lista(&lista_de_clientes);
    // liberar_lista_equipe(&lista_de_equipe);
    // view_exibir_mensagem("Memoria liberada com sucesso.");
}
// Em: controller/controller.c (no final do ficheiro)

static void controller_setup_inicial(Listaprodutora** lista_prod, Listaoperador** lista_op) {
    
    // REQUERIMENTO 1: Criar a Produtora (se ela não existir)
    if (*lista_prod == NULL) {
        view_exibir_mensagem("\n--- BEM-VINDO AO SISTEMA ---");
        view_exibir_mensagem("Vamos registar os dados da sua Produtora (isto so sera feito uma vez).");
        
        produtora nova_produtora;
        view_ler_dados_produtora(&nova_produtora);
        nova_produtora.ativo = 1;
        
        inserir_produtora(lista_prod, nova_produtora);
        view_exibir_mensagem(">> SUCESSO: Produtora principal registada.");
    }

    // REQUERIMENTO 2: Criar o Operador "admin" (se ele não existir)
    if (*lista_op == NULL) {
        view_exibir_mensagem("\nA criar operador 'admin' padrao...");
        
        operador admin;
        strcpy(admin.nome, "Administrador Padrao");
        strcpy(admin.usuario, "admin");
        admin.senha = 1234; // Você leu a senha como int no receber_dados.c
        admin.ativo = 1;

        inserir_operador(lista_op, admin);
        view_exibir_mensagem(">> SUCESSO: Operador 'admin' (senha: 1234) criado.");
    }

    printf("\n(Pressione Enter para continuar...)");
    getchar(); // Pausa para o utilizador ler as mensagens de setup
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