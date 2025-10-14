// Arquivo: main.c
// Ponto de entrada principal do programa.

#include "controller.h" // Inclui apenas o controller.

/**
 * @brief A função main.
 * Sua única responsabilidade na arquitetura MVC é iniciar o sistema
 * chamando a função principal do Controller.
 * @return 0 em caso de sucesso.
 */
int main() {
    // Inicia a aplicação. Todo o fluxo será gerenciado pelo controller.
    controller_iniciar_sistema();
    return 0;
}