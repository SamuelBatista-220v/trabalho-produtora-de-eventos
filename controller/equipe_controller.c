#include <stdio.h>
#include "equipe_controller.h"
// #include "../view/view.h"
// Em cliente_controller.c
#include "../view/menus.h"
#include "../view/mostrar_dados.h"
#include "../view/receber_dados.h"
// O model/equipe.h já é incluído pelo equipe_controller.h

void controller_gerenciar_equipe(ListaEquipe** lista_de_equipe) {
    int opcao = -1;

    do {
        view_exibir_menu_equipe(); // Chama o menu específico de equipe
        opcao = view_ler_opcao();

        switch (opcao) {
            case 1: { // Inserir novo membro
                Equipe nova_equipe;
                view_ler_dados_equipe(&nova_equipe);
                nova_equipe.ativo = 1;
                StatusOperacao status = inserir_equipe(lista_de_equipe, nova_equipe);

                if (status == OPERACAO_SUCESSO) {
                    view_exibir_mensagem("\n>> SUCESSO: Membro de equipe inserido.");
                } else if (status == ERRO_ALOCACAO_MEMORIA) {
                    view_exibir_mensagem("\n>> ERRO GRAVE: Falha ao alocar memoria.");
                }
                break;
            }
            case 2: { // Listar membros
                view_imprimir_lista_equipe(*lista_de_equipe);
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