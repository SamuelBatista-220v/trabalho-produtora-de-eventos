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
            
            // REMOVIDO: case 1 (Inserir) - Agora é feito no inicio do sistema

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
                   view_exibir_cabecalho_atualizacao("Produtora", ID_PRODUTORA);
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

      //funçao sem utilidada 
            case 3: { 
                view_exibir_mensagem("[Teste] Listando todas as produtoras registadas...");
                view_imprimir_lista_produtora(*lista_produtora);
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
