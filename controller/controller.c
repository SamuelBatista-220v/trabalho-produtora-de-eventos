#include <stdio.h>
#include "controller.h"
// #include "../view/view.h"
// Em cliente_controller.c
#include "../view/menus.h"
#include "../view/mostrar_dados.h"
#include "../view/receber_dados.h"

#include "../model/cliente.h"
#include "../model/equipe.h"

// Inclui os headers dos novos sub-controllers
#include "cliente_controller.h"
#include "equipe_controller.h"

// Função principal que gerencia o fluxo da aplicação.
void controller_iniciar_sistema() {
    // Declara uma lista para cada módulo do sistema
    ListaCliente* lista_de_clientes = NULL;
    ListaEquipe* lista_de_equipe = NULL;

    int opcao = -1;

    do {
        // CORREÇÃO AQUI: Chamando a função de menu principal correta
        view_exibir_menu_principal(); 
        opcao = view_ler_opcao();

        switch (opcao) {
            case 1:
                controller_gerenciar_clientes(&lista_de_clientes);
                break;
            case 2:
                controller_gerenciar_equipe(&lista_de_equipe);
                break;
            case 0:
                view_exibir_mensagem("\nSaindo do programa...");
                break;
            default:
                view_exibir_mensagem("\n>> Opcao invalida! Tente novamente.");
                break;
        }
    } while (opcao != 0);

    // Libera a memória de todas as listas antes de encerrar
    liberar_lista(&lista_de_clientes);
    liberar_lista_equipe(&lista_de_equipe);
    view_exibir_mensagem("Memoria liberada com sucesso.");
}

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