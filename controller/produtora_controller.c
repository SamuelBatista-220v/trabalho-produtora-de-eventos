#include <stdio.h>
#include "produtora_controller.h"
#include "../view/menus.h"


#include "../view/mostrar_dados.h"
#include "../view/receber_dados.h"

// Em: controller/produtora_controller.c

// Esta função tem seu próprio loop e gerencia apenas o submódulo de produtora.
void controller_gerenciar_produtora(Listaprodutora** lista_produtora) {
    int opcao = -1;
    const int ID_PRODUTORA = 1; // ID Fixo para a única produtora

    do {
        view_exibir_menu_produtora(); // Chama o menu específico de produtora
        opcao = view_ler_opcao();

        switch (opcao) {
            
            // REMOVIDO: case 1 (Inserir) - Agora é feito no setup

            case 1: { // Ver Dados (antigo Case 2: Buscar)
                Listaprodutora* produtora_encontrado = buscar_produtora_por_id(*lista_produtora, ID_PRODUTORA);
                if (produtora_encontrado != NULL) {
                    view_exibir_mensagem("\n>> Dados da Produtora:");
                    view_imprimir_produtora_unico(produtora_encontrado);
                } else {
                    view_exibir_mensagem("\n>> ERRO: Produtora (ID 1) nao encontrada.");
                }
                break;
            }
            
            case 2: { // Atualizar (antigo Case 3)
                Listaprodutora* no_produtora = buscar_produtora_por_id(*lista_produtora, ID_PRODUTORA);

                if (no_produtora == NULL) {
                    view_exibir_mensagem("\n>> ERRO: Produtora (ID 1) nao encontrada.");
                } else {
                    printf("\n--- Digite os NOVOS dados para a Produtora ---\n");
                    produtora produtora_atualizado;
                    view_ler_dados_produtora(&produtora_atualizado); 
                    
                    produtora_atualizado.ativo = no_produtora->conteudo.ativo; // Preserva o status

                    StatusOperacao status = atualizar_produtora_por_id(*lista_produtora, ID_PRODUTORA, produtora_atualizado);

                    if (status == OPERACAO_SUCESSO) {
                        view_exibir_mensagem("\n>> SUCESSO: Produtora atualizada.");
                    } else {
                        view_exibir_mensagem("\n>> ERRO: Falha inesperada ao atualizar a produtora.");
                    }
                }
                break;
            }

            // REMOVIDO: case 4 (Desativar)
            // REMOVIDO: case 5 (Remover)
            // REMOVIDO: case 6 (Ativar)
            
            case 3: { // Listar (Mantido para fins de teste)
                view_exibir_mensagem("[Modo Teste] Listando todas as produtoras registadas...");
                view_imprimir_lista_produtora(*lista_produtora);
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
// Esta função tem seu próprio loop e gerencia apenas o submódulo de produtora.
// void controller_gerenciar_produtora(Listaprodutora** lista_produtora) {
//     int opcao = -1;

//     do {
//         view_exibir_menu_produtora(); // Chama o menu específico de produtora
//         opcao = view_ler_opcao();

//         switch (opcao) {
//             case 1: { // Inserir
//                 produtora novo_produtora;
//                 view_ler_dados_produtora(&novo_produtora);
//                 novo_produtora.ativo = 1;
//                 StatusOperacao status = inserir_produtora(lista_produtora, novo_produtora);
//                 if (status == OPERACAO_SUCESSO) {
//                     view_exibir_mensagem("\n>> SUCESSO: produtora inserido.");
//                 } else if (status == ERRO_ALOCACAO_MEMORIA) {
//                     view_exibir_mensagem("\n>> ERRO GRAVE: Falha ao alocar memoria.");
//                 }
//                 break;
//             }
//             case 2: { // Buscar
//                 view_exibir_mensagem("Digite o Codigo (ID) do produtora a ser buscado: ");
//                 int id_busca = view_ler_opcao();
//                 if (id_busca > 0) {
//                     Listaprodutora* produtora_encontrado = buscar_produtora_por_id(*lista_produtora, id_busca);
//                     if (produtora_encontrado != NULL) {
//                         view_exibir_mensagem("\n>> produtora encontrado:");
//                         view_imprimir_produtora_unico(produtora_encontrado);
//                     } else {
//                         char msg_erro[100];
//                         sprintf(msg_erro, "\n>> AVISO: produtora com Codigo %d nao encontrado.", id_busca);
//                         view_exibir_mensagem(msg_erro);
//                     }
//                 } else {
//                     view_exibir_mensagem(">> Codigo invalido.");
//                 }
//                 break;
//             }
            
//             // --- CÓDIGO QUE FALTAVA ---
            
//             case 3: { // Atualizar dados de um produtora
//                 view_exibir_mensagem("Digite o Codigo (ID) do produtora a ser atualizado: ");
//                 int id_busca = view_ler_opcao();
//                 if (id_busca <= 0) {
//                     view_exibir_mensagem(">> Codigo invalido.");
//                     break;
//                 }

//                 Listaprodutora* no_produtora = buscar_produtora_por_id(*lista_produtora, id_busca);

//                 if (no_produtora == NULL) {
//                     view_exibir_mensagem("\n>> ERRO: produtora nao encontrado.");
//                 } else {
//                     printf("\n--- Digite os NOVOS dados para o produtora de ID %d ---\n", id_busca);
//                     produtora produtora_atualizado;
//                     view_ler_dados_produtora(&produtora_atualizado); 
                    
//                     produtora_atualizado.ativo = no_produtora->conteudo.ativo; 

//                     StatusOperacao status = atualizar_produtora_por_id(*lista_produtora, id_busca, produtora_atualizado);

//                     if (status == OPERACAO_SUCESSO) {
//                         view_exibir_mensagem("\n>> SUCESSO: produtora atualizado.");
//                     } else {
//                         view_exibir_mensagem("\n>> ERRO: Falha inesperada ao atualizar o produtora.");
//                     }
//                 }
//                 break;
//             }

//             case 4: { // Desativar produtora
//                 view_exibir_mensagem("Digite o Codigo (ID) do produtora a ser desativado: ");
//                 int id_busca = view_ler_opcao();
//                 if (id_busca <= 0) {
//                     view_exibir_mensagem(">> Codigo invalido.");
//                     break;
//                 }
//                 StatusOperacao status = desativar_produtora_por_id(*lista_produtora, id_busca);
//                 if (status == OPERACAO_SUCESSO) {
//                     view_exibir_mensagem("\n>> SUCESSO: produtora desativado.");
//                 } else if (status == ERRO_NAO_ENCONTRADO) {
//                     view_exibir_mensagem("\n>> ERRO: produtora nao encontrado.");
//                 } else if (status == ERRO_JA_INATIVO) {
//                     view_exibir_mensagem("\n>> AVISO: O produtora ja esta inativo.");
//                 }
//                 break;
//             }

//             case 5: { // Remover produtora (fisicamente)
//                 view_exibir_mensagem("Digite o Codigo (ID) do produtora a ser removido: ");
//                 int id_busca = view_ler_opcao();
//                 if (id_busca <= 0) {
//                     view_exibir_mensagem(">> Codigo invalido.");
//                     break;
//                 }
//                 // Passamos 'lista_produtora' diretamente, pois a função espera um ponteiro duplo (Listaprodutora**)
//                 StatusOperacao status = remover_fisico_produtora_por_id(lista_produtora, id_busca);
//                 if (status == OPERACAO_SUCESSO) {
//                     view_exibir_mensagem("\n>> SUCESSO: produtora removido fisicamente.");
//                 } else if (status == ERRO_NAO_ENCONTRADO) {
//                     view_exibir_mensagem("\n>> ERRO: produtora nao encontrado.");
//                 }
//                 break;
//             }
            
//             case 6: { // Ativar produtora
//                 view_exibir_mensagem("Digite o Codigo (ID) do produtora a ser ativado: ");
//                 int id_busca = view_ler_opcao();
//                 if (id_busca <= 0) {
//                     view_exibir_mensagem(">> Codigo invalido.");
//                     break;
//                 }
//                 StatusOperacao status = ativar_produtora_por_id(*lista_produtora, id_busca);
//                 if (status == OPERACAO_SUCESSO) {
//                     view_exibir_mensagem("\n>> SUCESSO: produtora ativado.");
//                 } else if (status == ERRO_NAO_ENCONTRADO) {
//                     view_exibir_mensagem("\n>> ERRO: produtora nao encontrado.");
//                 } else if (status == ERRO_JA_ATIVO) {
//                     view_exibir_mensagem("\n>> AVISO: O produtora ja esta ativo.");
//                 }
//                 break;
//             }
            
//             // --- FIM DO CÓDIGO QUE FALTAVA ---

//             case 7: { // Listar
//                 view_imprimir_lista_produtora(*lista_produtora);
//                 break;
//             }
//             case 0:
//                 view_exibir_mensagem("\nRetornando ao menu principal...");
//                 break;
//             default:
//                 view_exibir_mensagem("\n>> Opcao invalida! Tente novamente.");
//                 break;
//         }
//     } while (opcao != 0);
// }