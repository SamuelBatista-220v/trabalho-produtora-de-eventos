#include <stdio.h>
#include "cliente_controller.h"
#include "../view/view.h"

// Esta função tem seu próprio loop e gerencia apenas o submódulo de clientes.
void controller_gerenciar_clientes(ListaCliente** lista_clientes) {
    int opcao = -1;

    do {
        view_exibir_menu_clientes(); // Chama o menu específico de clientes
        opcao = view_ler_opcao();

        switch (opcao) {
            case 1: { // Inserir
                Cliente novo_cliente;
                view_ler_dados_cliente(&novo_cliente);
                novo_cliente.ativo = 1;
                StatusOperacao status = inserir_cliente(lista_clientes, novo_cliente);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: Cliente inserido.");
                } else if (status == ERRO_ALOCACAO_MEMORIA) {
                    view_exibir_mensagem("\n>> ERRO GRAVE: Falha ao alocar memoria.");
                }
                break;
            }
            case 2: { // Buscar
                view_exibir_mensagem("Digite o Codigo (ID) do cliente a ser buscado: ");
                int id_busca = view_ler_opcao();
                if (id_busca > 0) {
                    ListaCliente* cliente_encontrado = buscar_cliente_por_id(*lista_clientes, id_busca);
                    if (cliente_encontrado != NULL) {
                        view_exibir_mensagem("\n>> Cliente encontrado:");
                        view_imprimir_cliente_unico(cliente_encontrado);
                    } else {
                        char msg_erro[100];
                        sprintf(msg_erro, "\n>> AVISO: Cliente com Codigo %d nao encontrado.", id_busca);
                        view_exibir_mensagem(msg_erro);
                    }
                } else {
                    view_exibir_mensagem(">> Codigo invalido.");
                }
                break;
            }
            
            // --- CÓDIGO QUE FALTAVA ---
            
            case 3: { // Atualizar dados de um cliente
                view_exibir_mensagem("Digite o Codigo (ID) do cliente a ser atualizado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }

                ListaCliente* no_cliente = buscar_cliente_por_id(*lista_clientes, id_busca);

                if (no_cliente == NULL) {
                    view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
                } else {
                    printf("\n--- Digite os NOVOS dados para o cliente de ID %d ---\n", id_busca);
                    Cliente cliente_atualizado;
                    view_ler_dados_cliente(&cliente_atualizado); 
                    
                    cliente_atualizado.ativo = no_cliente->conteudo.ativo; 

                    StatusOperacao status = atualizar_cliente_por_id(*lista_clientes, id_busca, cliente_atualizado);

                    if (status == OPERACAO_SUCESSO) {
                        view_exibir_mensagem("\n>> SUCESSO: Cliente atualizado.");
                    } else {
                        view_exibir_mensagem("\n>> ERRO: Falha inesperada ao atualizar o cliente.");
                    }
                }
                break;
            }

            case 4: { // Desativar cliente
                view_exibir_mensagem("Digite o Codigo (ID) do cliente a ser desativado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                StatusOperacao status = desativar_cliente_por_id(*lista_clientes, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: Cliente desativado.");
                } else if (status == ERRO_CLIENTE_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
                } else if (status == ERRO_CLIENTE_JA_INATIVO) {
                    view_exibir_mensagem("\n>> AVISO: O cliente ja esta inativo.");
                }
                break;
            }

            case 5: { // Remover cliente (fisicamente)
                view_exibir_mensagem("Digite o Codigo (ID) do cliente a ser removido: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                // Passamos 'lista_clientes' diretamente, pois a função espera um ponteiro duplo (ListaCliente**)
                StatusOperacao status = remover_fisico_cliente_por_id(lista_clientes, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: Cliente removido fisicamente.");
                } else if (status == ERRO_CLIENTE_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
                }
                break;
            }
            
            case 6: { // Ativar cliente
                view_exibir_mensagem("Digite o Codigo (ID) do cliente a ser ativado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }
                StatusOperacao status = ativar_cliente_por_id(*lista_clientes, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: Cliente ativado.");
                } else if (status == ERRO_CLIENTE_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
                } else if (status == ERRO_CLIENTE_JA_ATIVO) {
                    view_exibir_mensagem("\n>> AVISO: O cliente ja esta ativo.");
                }
                break;
            }
            
            // --- FIM DO CÓDIGO QUE FALTAVA ---

            case 7: { // Listar
                view_imprimir_lista(*lista_clientes);
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