#include <stdio.h>
#include "recurso_controller.h"
#include "../view/menus.h"


#include "../view/mostrar_dados.h"
#include "../view/receber_dados.h"

// Esta função tem seu próprio loop e gerencia apenas o submódulo de recurso.
void controller_gerenciar_recurso(Listarecurso** lista_recurso) {
    int opcao = -1;

    do {
        view_exibir_menu_recurso(); // Chama o menu específico de recurso
        opcao = view_ler_opcao();

        switch (opcao) {
            case 1: { // Inserir
                recurso novo_recurso;
                view_ler_dados_recurso(&novo_recurso);
                novo_recurso.ativo = 1;
                StatusOperacao status = inserir_recurso(lista_recurso, novo_recurso);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: recurso inserido.");
                } else if (status == ERRO_ALOCACAO_MEMORIA) {
                    view_exibir_mensagem("\n>> ERRO GRAVE: Falha ao alocar memoria.");
                }
                break;
            }
            case 2: { // Buscar
                view_exibir_mensagem("Digite o Codigo (ID) do recurso a ser buscado: ");
                int id_busca = view_ler_opcao();
                if (id_busca > 0) {
                    Listarecurso* recurso_encontrado = buscar_recurso_por_id(*lista_recurso, id_busca);
                    if (recurso_encontrado != NULL) {
                        view_exibir_mensagem("\n>> recurso encontrado:");
                        view_imprimir_recurso_unico(recurso_encontrado);
                    } else {
                        char msg_erro[100];
                        sprintf(msg_erro, "\n>> AVISO: recurso com Codigo %d nao encontrado.", id_busca);
                        view_exibir_mensagem(msg_erro);
                    }
                } else {
                    view_exibir_mensagem(">> Codigo invalido.");
                }
                break;
            }
            
            // --- CÓDIGO QUE FALTAVA ---
            
            case 3: { // Atualizar dados de um recurso
                view_exibir_mensagem("Digite o Codigo (ID) do recurso a ser atualizado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }

                Listarecurso* no_recurso = buscar_recurso_por_id(*lista_recurso, id_busca);

                if (no_recurso == NULL) {
                    view_exibir_mensagem("\n>> ERRO: recurso nao encontrado.");
                } else {
                    printf("\n--- Digite os NOVOS dados para o recurso de ID %d ---\n", id_busca);
                    recurso recurso_atualizado;
                    view_ler_dados_recurso(&recurso_atualizado); 
                    
                    recurso_atualizado.ativo = no_recurso->conteudo.ativo; 

                    StatusOperacao status = atualizar_recurso_por_id(*lista_recurso, id_busca, recurso_atualizado);

                    if (status == OPERACAO_SUCESSO) {
                        view_exibir_mensagem("\n>> SUCESSO: recurso atualizado.");
                    } else {
                        view_exibir_mensagem("\n>> ERRO: Falha inesperada ao atualizar o recurso.");
                    }
                }
                break;
            }

            case 4: { // Desativar recurso
                view_exibir_mensagem("Digite o Codigo (ID) do recurso a ser desativado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                StatusOperacao status = desativar_recurso_por_id(*lista_recurso, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: recurso desativado.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: recurso nao encontrado.");
                } else if (status == ERRO_JA_INATIVO) {
                    view_exibir_mensagem("\n>> AVISO: O recurso ja esta inativo.");
                }
                break;
            }

            case 5: { // Remover recurso (fisicamente)
                view_exibir_mensagem("Digite o Codigo (ID) do recurso a ser removido: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                // Passamos 'lista_recurso' diretamente, pois a função espera um ponteiro duplo (Listarecurso**)
                StatusOperacao status = remover_fisico_recurso_por_id(lista_recurso, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: recurso removido fisicamente.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: recurso nao encontrado.");
                }
                break;
            }
            
            case 6: { // Ativar recurso
                view_exibir_mensagem("Digite o Codigo (ID) do recurso a ser ativado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                StatusOperacao status = ativar_recurso_por_id(*lista_recurso, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: recurso ativado.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: recurso nao encontrado.");
                } else if (status == ERRO_JA_ATIVO) {
                    view_exibir_mensagem("\n>> AVISO: O recurso ja esta ativo.");
                }
                break;
            }
            
            // --- FIM DO CÓDIGO QUE FALTAVA ---

            case 7: { // Listar
                view_imprimir_lista_recurso(*lista_recurso);
                break;
            }
            case 0:
                view_exibir_mensagem("\nRetornando ao menu principal...");
                break;
            default:
                view_exibir_mensagem("\n>> Opcao invalida! Tente novamente.");
                break;
        }
    } while (opcao != 0);
}