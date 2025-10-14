// Arquivo: controller.c (Refatorado para tratar os códigos de retorno do Model)

#include <stdio.h>
#include "controller.h"
#include "view.h"
#include "cliente.h"

#include <stdio.h>
#include "controller.h"
#include "view.h"
#include "cliente.h"

// Função principal que gerencia o fluxo da aplicação.
void controller_iniciar_sistema() {
    ListaCliente* minha_lista = NULL;
    int opcao = -1;

    do {
        view_exibir_menu();
        opcao = view_ler_opcao();

        switch (opcao) {
            case 1: { // Inserir novo cliente
                Cliente novo_cliente;
                view_ler_dados_cliente(&novo_cliente);
                novo_cliente.ativo = 1; // Clientes novos são sempre criados como ativos
                
                StatusOperacao status = inserir_cliente(&minha_lista, novo_cliente);
                
                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: Cliente inserido.");
                } else if (status == ERRO_ALOCACAO_MEMORIA) {
                    view_exibir_mensagem("\n>> ERRO GRAVE: Falha ao alocar memoria.");
                }
                break;
            }

            case 2: { // Buscar cliente por ID
                view_exibir_mensagem("Digite o Codigo (ID) do cliente a ser buscado: ");
                int id_busca = view_ler_opcao();

                if (id_busca > 0) {
                    ListaCliente* cliente_encontrado = buscar_cliente_por_id(minha_lista, id_busca);
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

            case 3: { // Atualizar dados de um cliente
                view_exibir_mensagem("Digite o Codigo (ID) do cliente a ser atualizado: ");
                int id_busca = view_ler_opcao();
                if (id_busca <= 0) {
                    view_exibir_mensagem(">> Codigo invalido.");
                    break;
                }

                ListaCliente* no_cliente = buscar_cliente_por_id(minha_lista, id_busca);

                if (no_cliente == NULL) {
                    view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
                } else {
                    printf("\n--- Digite os NOVOS dados para o cliente de ID %d ---\n", id_busca);
                    Cliente cliente_atualizado;
                    
                    view_ler_dados_cliente(&cliente_atualizado); 
                    
                    // Preserva o status 'ativo' original do cliente para evitar corrupção de dados
                    cliente_atualizado.ativo = no_cliente->conteudo.ativo; 

                    StatusOperacao status = atualizar_cliente_por_id(minha_lista, id_busca, cliente_atualizado);

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
            
                StatusOperacao status = desativar_cliente_por_id(minha_lista, id_busca);
            
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

                StatusOperacao status = remover_fisico_cliente_por_id(&minha_lista, id_busca);

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

                StatusOperacao status = ativar_cliente_por_id(minha_lista, id_busca);

                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: Cliente ativado.");
                } else if (status == ERRO_CLIENTE_NAO_ENCONTRADO) {
                    view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
                } else if (status == ERRO_CLIENTE_JA_ATIVO) {
                    view_exibir_mensagem("\n>> AVISO: O cliente ja esta ativo.");
                }
                break;
            }

            case 7: { // Listar todos os clientes
                view_imprimir_lista(minha_lista);
                break;
            }

            case 0: { // Sair
                view_exibir_mensagem("\nSaindo do programa...");
                break;
            }

            default: { // Opção inválida
                view_exibir_mensagem("\n>> Opcao invalida! Tente novamente.");
                break;
            }
        }
    } while (opcao != 0);

    // Libera a memória alocada para a lista antes de encerrar o programa.
    liberar_lista(&minha_lista);
    view_exibir_mensagem("Memoria liberada com sucesso. Adeus!");
}
// void controller_iniciar_sistema() {
//     ListaCliente* minha_lista = NULL;
//     int opcao = -1;

//     do {
//         view_exibir_menu();
//         opcao = view_ler_opcao();

//         switch (opcao) {
//             case 1: { // Inserir
//                 Cliente novo_cliente;
//                 view_ler_dados_cliente(&novo_cliente);
//                 novo_cliente.ativo = 1;
                
//                 // ADICIONADO: Captura o status da operação do Model.
//                 StatusOperacao status = inserir_cliente(&minha_lista, novo_cliente);
                
//                 // ADICIONADO: Controller interpreta o status e chama a View.
//                 if (status == OPERACAO_SUCESSO) {
//                     view_exibir_mensagem("\n>> Cliente inserido com sucesso!");
//                 } else if (status == ERRO_ALOCACAO_MEMORIA) {
//                     view_exibir_mensagem("\n>> ERRO GRAVE: Falha ao alocar memoria.");
//                 }
//                 break;
//             }
//             case 2: { // Buscar
//                 view_exibir_mensagem("Digite o Codigo (ID) do cliente a ser buscado: ");
//                 int id_busca = view_ler_opcao();
//                 if (id_busca > 0) {
//                     ListaCliente* cliente_encontrado = buscar_cliente_por_id(minha_lista, id_busca);
//                     if (cliente_encontrado != NULL) {
//                         view_exibir_mensagem("\n>> Cliente encontrado:");
//                         view_imprimir_cliente_unico(cliente_encontrado);
//                     } else {
//                          // O Controller formata a mensagem de erro para a View
//                         char msg_erro[100];
//                         sprintf(msg_erro, "\n>> AVISO: Cliente com Codigo %d nao encontrado.", id_busca);
//                         view_exibir_mensagem(msg_erro);
//                     }
//                 } else {
//                     view_exibir_mensagem(">> Codigo invalido.");
//                 }
//                 break;
//             }
//              case 3: { // Atualizar
//                 view_exibir_mensagem("Digite o Codigo (ID) do cliente a ser atualizado: ");
//                 int id_busca = view_ler_opcao();
//                 if(id_busca <= 0) {
//                     view_exibir_mensagem(">> Codigo invalido.");
//                     break;
//                 }

//                 // Passo 1: Verificar se o cliente existe antes de continuar
//                 ListaCliente* no_cliente = buscar_cliente_por_id(minha_lista, id_busca);

//                 if (no_cliente == NULL) {
//                     view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
//                 } else {
//                     // Passo 2: O cliente existe, então pedimos os novos dados
//                     printf("\n--- Digite os NOVOS dados para o cliente de ID %d ---\n", id_busca);
//                     Cliente cliente_atualizado; // A variável que estava faltando
                    
//                     // Reutilizamos a função da view para ler os dados
//                     view_ler_dados_cliente(&cliente_atualizado); 
                    
//                     // Mantém o status 'ativo' original do cliente
//                     cliente_atualizado.ativo = no_cliente->conteudo.ativo; 

//                     // Passo 3: Chamar a função do model com os 3 argumentos corretos
//                     StatusOperacao status = atualizar_cliente_por_id(minha_lista, id_busca, cliente_atualizado);

//                     // Passo 4: Tratar o resultado
//                     if (status == OPERACAO_SUCESSO) {
//                         view_exibir_mensagem("\n>> SUCESSO: Cliente atualizado.");
//                     } else {
//                         // Este erro não deveria acontecer se a busca funcionou, mas é bom ter
//                         view_exibir_mensagem("\n>> ERRO: Falha ao atualizar o cliente.");
//                     }
//                 }
//                 break;
//             }
//             case 4:   // Desativar
//             case 5:   // Remover
//             case 6: { // Ativar
//                 view_exibir_mensagem("Digite o Codigo (ID) do cliente: ");
//                 int id_busca = view_ler_opcao();
//                 if(id_busca <= 0) {
//                     view_exibir_mensagem(">> Codigo invalido.");
//                     break;
//                 }

//                 StatusOperacao status;
//                 if (opcao == 3) {
                    
//                     // status = atualizar_cliente_por_id(minha_lista, id_busca);
//                     // // O printf de sucesso da atualização é especial, pois a interação já aconteceu
//                     // if(status == OPERACAO_SUCESSO) view_exibir_mensagem("\n>> SUCESSO: Cliente atualizado.");
//                 }
//                 if (opcao == 4) status = desativar_cliente_por_id(minha_lista, id_busca);
//                 if (opcao == 5) status = remover_fisico_cliente_por_id(&minha_lista, id_busca);
//                 if (opcao == 6) status = ativar_cliente_por_id(minha_lista, id_busca);

//                 // Bloco centralizado para tratar os status comuns
//                 switch (status) {
//                     case OPERACAO_SUCESSO:
//                         if(opcao != 3) view_exibir_mensagem("\n>> SUCESSO: Operacao realizada.");
//                         break;
//                     case ERRO_CLIENTE_NAO_ENCONTRADO:
//                         view_exibir_mensagem("\n>> ERRO: Cliente nao encontrado.");
//                         break;
//                     case ERRO_CLIENTE_JA_ATIVO:
//                         view_exibir_mensagem("\n>> AVISO: O cliente ja esta ativo.");
//                         break;
//                     case ERRO_CLIENTE_JA_INATIVO:
//                         view_exibir_mensagem("\n>> AVISO: O cliente ja esta inativo.");
//                         break;
//                     default:
//                         // Para outros casos como ERRO_ALOCACAO_MEMORIA, se aplicável.
//                         break;
//                 }
//                 break;
//             }
//             case 7: { // Listar
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

//     liberar_lista(&minha_lista);
//     view_exibir_mensagem("Memoria liberada com sucesso. Adeus!");
// }