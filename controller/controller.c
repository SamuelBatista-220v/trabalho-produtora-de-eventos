#include <stdio.h>
#include "controller.h"
#include "../view/view.h"
#include "../model/cliente.h"
#include "../model/equipe.h"

// Inclui os headers dos novos sub-controllers
#include "cliente_controller.h"
#include "equipe_controller.h"

// Função principal que gerencia o fluxo da aplicação.
void controller_iniciar_sistema() {
    // Declara uma lista para cada módulo do sistema
    ListaCliente* lista_de_clientes = NULL;
    ListaEquipe* lista_de_equipe = NULL;

    int opcao = -1;

    do {
        // CORREÇÃO AQUI: Chamando a função de menu principal correta
        view_exibir_menu_principal(); 
        opcao = view_ler_opcao();

        switch (opcao) {
            case 1:
                controller_gerenciar_clientes(&lista_de_clientes);
                break;
            case 2:
                controller_gerenciar_equipe(&lista_de_equipe);
                break;
            case 0:
                view_exibir_mensagem("\nSaindo do programa...");
                break;
            default:
                view_exibir_mensagem("\n>> Opcao invalida! Tente novamente.");
                break;
        }
    } while (opcao != 0);

    // Libera a memória de todas as listas antes de encerrar
    liberar_lista(&lista_de_clientes);
    liberar_lista_equipe(&lista_de_equipe);
    view_exibir_mensagem("Memoria liberada com sucesso.");
}