#include <stdio.h>
#include "operador_controller.h"
#include "../view/menus.h"


#include "../view/mostrar_dados.h"
#include "../view/receber_dados.h"

// Esta função tem seu próprio loop e gerencia apenas o submódulo de operador.
void controller_gerenciar_operador(Listaoperador** lista_operador) {
    int opcao = -1;

    do {
        view_exibir_menu_operador(); // Chama o menu específico de operador
        opcao = view_ler_opcao();

        switch (opcao) {
            case 1: { // Inserir
                operador novo_operador;
                view_ler_dados_operador(&novo_operador);
                novo_operador.ativo = 1;
                StatusOperacao status = inserir_operador(lista_operador, novo_operador);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: operador inserido.");
                } else if (status == ERRO_ALOCACAO_MEMORIA) {
                    view_exibir_mensagem("\n>> ERRO GRAVE: Falha ao alocar memoria.");
                }
                break;
            }
            case 2: { // Buscar
                view_exibir_mensagem("Digite o Codigo (ID) do operador a ser buscado: ");
                int id_busca = view_ler_opcao();
                if (id_busca > 0) {
                    Listaoperador* operador_encontrado = buscar_operador_por_id(*lista_operador, id_busca);
                    if (operador_encontrado != NULL) {
                        view_exibir_mensagem("\n>> operador encontrado:");
                        view_imprimir_operador_unico(operador_encontrado);
                    } else {
                        view_exibir_erro_busca_id("Operador", id_busca);
                    }
                } else {
                    view_exibir_mensagem(">> Codigo invalido.");
                }
                break;
            }
            
  
            
            case 3: { // Atualizar dados de um operador
                view_exibir_mensagem("Digite o Codigo (ID) do operador a ser atualizado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }

                Listaoperador* no_operador = buscar_operador_por_id(*lista_operador, id_busca);

                if (no_operador == NULL) {
                    view_exibir_mensagem("\n>> ERRO: operador nao encontrado.");
                } else {
                   view_exibir_cabecalho_atualizacao("Operador", id_busca);
                    operador operador_atualizado;
                    view_ler_dados_operador(&operador_atualizado); 
                    
                    operador_atualizado.ativo = no_operador->conteudo.ativo; 

                    StatusOperacao status = atualizar_operador_por_id(*lista_operador, id_busca, operador_atualizado);

                    if (status == OPERACAO_SUCESSO) {
                        view_exibir_mensagem("\n>> SUCESSO: operador atualizado.");
                    } else {
                        view_exibir_mensagem("\n>> ERRO: Falha inesperada ao atualizar o operador.");
                    }
                }
                break;
            }

            case 4: { // Desativar operador
                view_exibir_mensagem("Digite o Codigo (ID) do operador a ser desativado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                StatusOperacao status = desativar_operador_por_id(*lista_operador, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: operador desativado.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: operador nao encontrado.");
                } else if (status == ERRO_JA_INATIVO) {
                    view_exibir_mensagem("\n>> AVISO: O operador ja esta inativo.");
                }
                break;
            }

            case 5: { // Remover operador (fisicamente)
                view_exibir_mensagem("Digite o Codigo (ID) do operador a ser removido: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                // Passamos 'lista_operador' diretamente, pois a função espera um ponteiro duplo (Listaoperador**)
                StatusOperacao status = remover_fisico_operador_por_id(lista_operador, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: operador removido fisicamente.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: operador nao encontrado.");
                }
                break;
            }
            
            case 6: { // Ativar operador
                view_exibir_mensagem("Digite o Codigo (ID) do operador a ser ativado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                StatusOperacao status = ativar_operador_por_id(*lista_operador, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: operador ativado.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: operador nao encontrado.");
                } else if (status == ERRO_JA_ATIVO) {
                    view_exibir_mensagem("\n>> AVISO: O operador ja esta ativo.");
                }
                break;
            }
            


            case 7: { // Listar
                view_imprimir_lista_operador(*lista_operador);
                break;
            }
            case 0:
                view_exibir_msg_retornando();
                break;
            default:
                view_exibir_mensagem("\n>> Opcao invalida! Tente novamente.");
                break;
        }
    } while (opcao != 0);
}