#include <stdio.h>
#include "cliente_controller.h"
#include "../view/menus.h"
#include "../view/mostrar_dados.h"
#include "../view/receber_dados.h"

// Esta função tem seu próprio loop e gerencia apenas o submódulo de clientes.
void controller_gerenciar_clientes(ListaCliente** lista_clientes) {
    int opcao = -1;// Variável para armazenar a opção do menu.

    do {
        view_exibir_menu_clientes(); // Chama o menu específico de clientes
        opcao = view_ler_opcao();//Recebe a opção do usuário.

        switch (opcao) {
            case 1: { // Inserir novo cliente
                Cliente novo_cliente;
                //Coleta todos os dados do cliente com funções de interface.
                view_ler_dados_cliente(&novo_cliente);
                //Define o status inicial do cliente (logicamente ativo).
                novo_cliente.ativo = 1;

          // Chama a função de lógica/algoritmos para inserir o nó.
                StatusOperacao status = inserir_cliente(lista_clientes, novo_cliente);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: Cliente inserido.");
                } else if (status == ERRO_ALOCACAO_MEMORIA) {
                    view_exibir_mensagem("\n>> ERRO GRAVE: Falha ao alocar memoria.");
                }
                break;
            }
            case 2: { // Buscar cliente
                view_exibir_mensagem("Digite o Codigo (ID) do cliente a ser buscado: ");
                int id_busca = view_ler_opcao();// VIEW: Recebe o ID a ser buscado.

                if (id_busca > 0) {
                    // MODEL: Busca o cliente na lista. Nota: Passamos *lista_clientes (ponteiro simples).
                    ListaCliente* cliente_encontrado = buscar_cliente_por_id(*lista_clientes, id_busca);

                    //Exibe o resultado.
                    if (cliente_encontrado != NULL) {
                        view_exibir_mensagem("\n>> Cliente encontrado:");
                        view_imprimir_cliente_unico(cliente_encontrado);// VIEW: Imprime os dados.
                    } else {
                        // Formata a mensagem de erro com o ID específico.
                        char msg_erro[100];
                        sprintf(msg_erro, "\n>> AVISO: Cliente com Codigo %d nao encontrado.", id_busca);
                        view_exibir_mensagem(msg_erro);
                    }
                } else {
                    view_exibir_mensagem(">> Codigo invalido.");
                }
                break;
            }
            
            
            
            case 3: { // Atualizar dados de um cliente
                view_exibir_mensagem("Digite o Codigo (ID) do cliente a ser atualizado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }

                //Verifica se o cliente existe antes de pedir os novos dados.
                ListaCliente* no_cliente = buscar_cliente_por_id(*lista_clientes, id_busca);

                if (no_cliente == NULL) {
                    view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
                } else {
                    printf("\n--- Digite os NOVOS dados para o cliente de ID %d ---\n", id_busca);
                    // VIEW: Coleta os novos dados.
                    Cliente cliente_atualizado;
                    view_ler_dados_cliente(&cliente_atualizado); 

                    // CONTROL: Preserva o status 'ativo' original (garantindo que o UPDATE não desative o cliente acidentalmente).
                    cliente_atualizado.ativo = no_cliente->conteudo.ativo; 

                    // MODEL: Chama a função de atualização. Nota: Passamos *lista_clientes (ponteiro simples).
                    StatusOperacao status = atualizar_cliente_por_id(*lista_clientes, id_busca, cliente_atualizado);

                    if (status == OPERACAO_SUCESSO) {
                        view_exibir_mensagem("\n>> SUCESSO: Cliente atualizado.");
                    } else {
                        // Esta mensagem trata do caso teórico em que o cliente some após a busca inicial,
                         // ou se a função atualizar_cliente_por_id retornasse ERRO_NAO_ENCONTRADO, 
                         // embora tenhamos verificado antes.
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

                // MODEL: Chama a função de remoção lógica.
                StatusOperacao status = desativar_cliente_por_id(*lista_clientes, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: Cliente desativado.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
                } else if (status == ERRO_JA_INATIVO) {
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
                // MODEL: Chama a função de remoção física.
                // IMPORTANTE: Passamos 'lista_clientes' (ListaCliente**) para que a função possa
                // alterar a cabeça da lista se necessário (exigência do hard delete).
                StatusOperacao status = remover_fisico_cliente_por_id(lista_clientes, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: Cliente removido fisicamente.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
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

                // Chama a função de ativação.
                StatusOperacao status = ativar_cliente_por_id(*lista_clientes, id_busca);
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: Cliente ativado.");
                } else if (status == ERRO_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
                } else if (status == ERRO_JA_ATIVO) {
                    view_exibir_mensagem("\n>> AVISO: O cliente ja esta ativo.");
                }
                break;
            }
            
            

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
    } while (opcao != 0);// O loop continua até o usuário escolher a opção 0.
}