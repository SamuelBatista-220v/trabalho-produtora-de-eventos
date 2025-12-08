// #include <stdio.h>
// #include "equipe_controller.h"
// // #include "../view/view.h"
// // Em cliente_controller.c
// #include "../view/menus.h"
// #include "../view/mostrar_dados.h"
// #include "../view/receber_dados.h"
// // O model/equipe.h já é incluído pelo equipe_controller.h

#include <stdio.h>
#include "equipe_controller.h"
#include "../view/menus.h"


#include "../view/mostrar_dados.h"
#include "../view/receber_dados.h"

// Esta função tem seu próprio loop e gerencia apenas o submódulo de equipe.
void controller_gerenciar_equipe(Listaequipe** lista_equipe) {
    int opcao = -1;

    do {
        view_exibir_menu_equipe(); // Chama o menu específico de equipe
        opcao = view_ler_opcao();

        switch (opcao) {
            case 1: { // Inserir
                equipe novo_equipe;
                view_ler_dados_equipe(&novo_equipe);
                novo_equipe.ativo = 1;
                StatusOperacao status = inserir_equipe(lista_equipe, novo_equipe);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: equipe inserido.");
                } else if (status == ERRO_ALOCACAO_MEMORIA) {
                    view_exibir_mensagem("\n>> ERRO GRAVE: Falha ao alocar memoria.");
                }
                break;
            }
            case 2: { // Buscar
                view_exibir_mensagem("Digite o Codigo (ID) do equipe a ser buscado: ");
                int id_busca = view_ler_opcao();
                if (id_busca > 0) {
                    Listaequipe* equipe_encontrado = buscar_equipe_por_id(*lista_equipe, id_busca);
                    if (equipe_encontrado != NULL) {
                        view_exibir_mensagem("\n>> equipe encontrado:");
                        view_imprimir_equipe_unico(equipe_encontrado);
                    } else {
                        view_exibir_erro_busca_id("Equipe", id_busca);  
                    }
                } else {
                    view_exibir_mensagem(">> Codigo invalido.");
                }
                break;
            }
            
          
            
            case 3: { // Atualizar dados de um equipe
                view_exibir_mensagem("Digite o Codigo (ID) do equipe a ser atualizado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }

                Listaequipe* no_equipe = buscar_equipe_por_id(*lista_equipe, id_busca);

                if (no_equipe == NULL) {
                    view_exibir_mensagem("\n>> ERRO: equipe nao encontrado.");
                } else {
                    view_exibir_cabecalho_atualizacao("Equipe", id_busca);
                    equipe equipe_atualizado;
                    view_ler_dados_equipe(&equipe_atualizado); 
                    
                    equipe_atualizado.ativo = no_equipe->conteudo.ativo; 

                    StatusOperacao status = atualizar_equipe_por_id(*lista_equipe, id_busca, equipe_atualizado);

                    if (status == OPERACAO_SUCESSO) {
                        view_exibir_mensagem("\n>> SUCESSO: equipe atualizado.");
                    } else {
                        view_exibir_mensagem("\n>> ERRO: Falha inesperada ao atualizar o equipe.");
                    }
                }
                break;
            }

            case 4: { // Desativar equipe
                view_exibir_mensagem("Digite o Codigo (ID) do equipe a ser desativado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                StatusOperacao status = desativar_equipe_por_id(*lista_equipe, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: equipe desativado.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: equipe nao encontrado.");
                } else if (status == ERRO_JA_INATIVO) {
                    view_exibir_mensagem("\n>> AVISO: O equipe ja esta inativo.");
                }
                break;
            }

            case 5: { // Remover equipe (fisicamente)
                view_exibir_mensagem("Digite o Codigo (ID) do equipe a ser removido: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                // Passamos 'lista_equipe' diretamente, pois a função espera um ponteiro duplo (Listaequipe**)
                StatusOperacao status = remover_fisico_equipe_por_id(lista_equipe, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: equipe removido fisicamente.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: equipe nao encontrado.");
                }
                break;
            }
            
            case 6: { // Ativar equipe
                view_exibir_mensagem("Digite o Codigo (ID) do equipe a ser ativado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                StatusOperacao status = ativar_equipe_por_id(*lista_equipe, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: equipe ativado.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: equipe nao encontrado.");
                } else if (status == ERRO_JA_ATIVO) {
                    view_exibir_mensagem("\n>> AVISO: O equipe ja esta ativo.");
                }
                break;
            }
            
 

            case 7: { // Listar
                view_imprimir_lista_equipe(*lista_equipe);
                break;
            }
            case 0:
                // CORREÇÃO: Mensagem padronizada
                view_exibir_msg_retornando();
                break;
            default:
                view_exibir_mensagem("\n>> Opcao invalida! Tente novamente.");
                break;
        }
    } while (opcao != 0);
}

