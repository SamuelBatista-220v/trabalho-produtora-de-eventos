#include <stdio.h>
#include "fornecedor_controller.h"
#include "../view/menus.h"


#include "../view/mostrar_dados.h"
#include "../view/receber_dados.h"

// Esta função tem seu próprio loop e gerencia apenas o submódulo de fornecedor.
void controller_gerenciar_fornecedor(Listafornecedor** lista_fornecedor) {
    int opcao = -1;

    do {
        view_exibir_menu_fornecedor(); // Chama o menu específico de fornecedor
        opcao = view_ler_opcao();

        switch (opcao) {
            case 1: { // Inserir
                fornecedor novo_fornecedor;
                view_ler_dados_fornecedor(&novo_fornecedor);
                novo_fornecedor.ativo = 1;
                StatusOperacao status = inserir_fornecedor(lista_fornecedor, novo_fornecedor);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: fornecedor inserido.");
                } else if (status == ERRO_ALOCACAO_MEMORIA) {
                    view_exibir_mensagem("\n>> ERRO GRAVE: Falha ao alocar memoria.");
                }
                break;
            }
            case 2: { // Buscar
                view_exibir_mensagem("Digite o Codigo (ID) do fornecedor a ser buscado: ");
                int id_busca = view_ler_opcao();
                if (id_busca > 0) {
                    Listafornecedor* fornecedor_encontrado = buscar_fornecedor_por_id(*lista_fornecedor, id_busca);
                    if (fornecedor_encontrado != NULL) {
                        view_exibir_mensagem("\n>> fornecedor encontrado:");
                        view_imprimir_fornecedor_unico(fornecedor_encontrado);
                    } else {
                        char msg_erro[100];
                        sprintf(msg_erro, "\n>> AVISO: fornecedor com Codigo %d nao encontrado.", id_busca);
                        view_exibir_mensagem(msg_erro);
                    }
                } else {
                    view_exibir_mensagem(">> Codigo invalido.");
                }
                break;
            }
            
            // --- CÓDIGO QUE FALTAVA ---
            
            case 3: { // Atualizar dados de um fornecedor
                view_exibir_mensagem("Digite o Codigo (ID) do fornecedor a ser atualizado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }

                Listafornecedor* no_fornecedor = buscar_fornecedor_por_id(*lista_fornecedor, id_busca);

                if (no_fornecedor == NULL) {
                    view_exibir_mensagem("\n>> ERRO: fornecedor nao encontrado.");
                } else {
                    printf("\n--- Digite os NOVOS dados para o fornecedor de ID %d ---\n", id_busca);
                    fornecedor fornecedor_atualizado;
                    view_ler_dados_fornecedor(&fornecedor_atualizado); 
                    
                    fornecedor_atualizado.ativo = no_fornecedor->conteudo.ativo; 

                    StatusOperacao status = atualizar_fornecedor_por_id(*lista_fornecedor, id_busca, fornecedor_atualizado);

                    if (status == OPERACAO_SUCESSO) {
                        view_exibir_mensagem("\n>> SUCESSO: fornecedor atualizado.");
                    } else {
                        view_exibir_mensagem("\n>> ERRO: Falha inesperada ao atualizar o fornecedor.");
                    }
                }
                break;
            }

            case 4: { // Desativar fornecedor
                view_exibir_mensagem("Digite o Codigo (ID) do fornecedor a ser desativado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                StatusOperacao status = desativar_fornecedor_por_id(*lista_fornecedor, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: fornecedor desativado.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: fornecedor nao encontrado.");
                } else if (status == ERRO_JA_INATIVO) {
                    view_exibir_mensagem("\n>> AVISO: O fornecedor ja esta inativo.");
                }
                break;
            }

            case 5: { // Remover fornecedor (fisicamente)
                view_exibir_mensagem("Digite o Codigo (ID) do fornecedor a ser removido: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                // Passamos 'lista_fornecedor' diretamente, pois a função espera um ponteiro duplo (Listafornecedor**)
                StatusOperacao status = remover_fisico_fornecedor_por_id(lista_fornecedor, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: fornecedor removido fisicamente.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: fornecedor nao encontrado.");
                }
                break;
            }
            
            case 6: { // Ativar fornecedor
                view_exibir_mensagem("Digite o Codigo (ID) do fornecedor a ser ativado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                StatusOperacao status = ativar_fornecedor_por_id(*lista_fornecedor, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: fornecedor ativado.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: fornecedor nao encontrado.");
                } else if (status == ERRO_JA_ATIVO) {
                    view_exibir_mensagem("\n>> AVISO: O fornecedor ja esta ativo.");
                }
                break;
            }
            
            // --- FIM DO CÓDIGO QUE FALTAVA ---

            case 7: { // Listar
                view_imprimir_lista_fornecedor(*lista_fornecedor);
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