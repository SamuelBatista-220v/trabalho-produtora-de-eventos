#include <stdio.h>
#include "menus.h"

// void view_exibir_menu_principal() {
//     printf("\n ====== SISTEMA PRODUTORA DE EVENTOS ========\n");
//     printf("   |  1. Gerenciar Clientes                    |\n");
//     printf("   |  2. Gerenciar Equipe                      |\n");
//     printf("   |  0. Sair do Sistema                        |\n");
//     printf("   ==========================================\n");
// }
//  void view_exibir_menu_principal() {
//     printf("\n+-----------------------------------------------+\n");
//     printf("|          MENU PRINCIPAL                       |\n");
//     printf("+-----------------------------------------------+\n");
//     printf("| 1. Gerenciar dados da produtora               |\n");
//     printf("| 2. Gerenciar clientes                         |\n");
//     printf("| 3. Gerenciar equipe interna                   |\n");
//     printf("| 4. Gerenciar recursos e equipamentos          |\n");
//     printf("| 5. Gerenciar fornecedores                     |\n");
//     printf("| 6. Gerenciar operadores do sistema            |\n");
//     printf("+-----------------------------------------------+\n");
//     printf("| 0. Sair do sistema                            |\n");
//     printf("+-----------------------------------------------+\n");
// }
// void view_exibir_menu_principal() {
//     printf("\n ====== SISTEMA PRODUTORA DE EVENTOS ========\n");
//     printf("   |  1. Gerenciar Produtora (Principal)    |\n"); // Ajustei conforme seu controller
//     printf("   |  2. Gerenciar Clientes                 |\n");
//     printf("   |  3. Gerenciar Equipe                   |\n");
//     printf("   |  4. Gerenciar Recursos                 |\n");
//     printf("   |  5. Gerenciar Fornecedores             |\n");
//     printf("   |  6. Gerenciar Operadores               |\n");
//     printf("   |----------------------------------------|\n");
//     printf("   |  7. Mudar Modo de Salvamento (TXT/BIN) |\n"); // <--- NOVA OPÇÃO
//     printf("   |  0. Sair e Salvar                      |\n");
//     printf("   ==========================================\n");
// }
void view_exibir_menu_principal() {
    printf("\n ====== SISTEMA PRODUTORA DE EVENTOS ========\n");
    printf("   |  1. Gerenciar Produtora (Principal)    |\n");
    printf("   |  2. Gerenciar Clientes                 |\n");
    printf("   |  3. Gerenciar Equipe                   |\n");
    printf("   |  4. Gerenciar Recursos                 |\n");
    printf("   |  5. Gerenciar Fornecedores             |\n");
    printf("   |  6. Gerenciar Operadores               |\n");
    printf("   |----------------------------------------|\n");
    printf("   |  7. Mudar Modo de Salvamento (TXT/BIN) |\n");
    printf("   |  8. GESTAO DE ORCAMENTOS E EVENTOS     |\n"); // <--- AQUI
    printf("   |  0. Sair e Salvar                      |\n");
    printf("   ==========================================\n");
}
//  void view_exibir_menu_produtora() {
//     printf("\n+----------------------------------------------+\n");
//     printf("|          MODULO DA PRODUTORA                  |\n");
//     printf("+-----------------------------------------------+\n");
//     printf("| 1. Inserir novo membro                        |\n");
//     printf("| 2. Buscar membro por Codigo                   |\n");
//     printf("| 3. Atualizar dados de um membro               |\n");
//     printf("| 4. Desativar membro                           |\n");
//     printf("| 5. Remover membro (exclusao permanente)       |\n");
//     printf("| 6. Ativar membro                              |\n");
//     printf("| 7. Listar todos os membros                    |\n");
//     printf("+-----------------------------------------------+\n");
//     printf("| 0. Voltar ao menu principal                   |\n");
//     printf("+-----------------------------------------------+\n");
// }
// Em: view/menus.c

 void view_exibir_menu_produtora() {
    printf("\n+-----------------------------------------------+\n");
    printf("|          MODULO DA PRODUTORA                  |\n");
    printf("+-----------------------------------------------+\n");
    printf("| 1. Ver dados da Produtora                     |\n");
    printf("| 2. Atualizar dados da Produtora               |\n");
    printf("| 7. Listar todos os membros (Apenas para teste)|\n"); // Mantido para depuração
    printf("+-----------------------------------------------+\n");
    printf("| 0. Voltar ao menu principal                   |\n");
    printf("+-----------------------------------------------+\n");
}

// void view_exibir_menu_clientes() {
//     printf("\n ====== Modulo de Clientes ========\n");
//     printf("   |  1. Inserir novo cliente              |\n");
//     printf("   |  2. Buscar cliente por Codigo         |\n");
//     printf("   |  3. Atualizar dados de um cliente     |\n");
//     printf("   |  4. Desativar cliente (soft delete)   |\n");
//     printf("   |  5. Remover cliente (fisicamente)     |\n");
//     printf("   |  6. Ativar cliente                    |\n");
//     printf("   |  7. Listar todos os clientes          |\n");
//     printf("   |  0. Voltar ao menu principal          |\n");
//     printf("   ========================================\n");
// }
 void view_exibir_menu_clientes() {
    printf("\n+-----------------------------------------------+\n");
    printf("|          MODULO DE CLIENTES                   |\n");
    printf("+-----------------------------------------------+\n");
    printf("| 1. Inserir novo cliente                       |\n");
    printf("| 2. Buscar cliente por Codigo                  |\n");
    printf("| 3. Atualizar dados de um cliente              |\n");
    printf("| 4. Desativar cliente                          |\n");
    printf("| 5. Remover cliente (exclusao permanente)      |\n");
    printf("| 6. Ativar cliente                             |\n");
    printf("| 7. Listar todos os clientes                   |\n");
    printf("+-----------------------------------------------+\n");
    printf("| 0. Voltar ao menu principal                   |\n");
    printf("+-----------------------------------------------+\n");
}

 void view_exibir_menu_equipe() {
    printf("\n+-----------------------------------------------+\n");
    printf("|          MODULO DE EQUIPES                    |\n");
    printf("+-----------------------------------------------+\n");
    printf("| 1. Inserir novo membro                        |\n");
    printf("| 2. Buscar membro por Codigo                   |\n");
    printf("| 3. Atualizar dados de um membro               |\n");
    printf("| 4. Desativar membro                           |\n");
    printf("| 5. Remover membro (exclusao permanente)       |\n");
    printf("| 6. Ativar membro                              |\n");
    printf("| 7. Listar todos os membros                    |\n");
    printf("+-----------------------------------------------+\n");
    printf("| 0. Voltar ao menu principal                   |\n");
    printf("+-----------------------------------------------+\n");
}

 void view_exibir_menu_recurso() {
    printf("\n+-----------------------------------------------+\n");
    printf("|          RECURSOS E EQUIPAMENTOS              |\n");
    printf("+-----------------------------------------------+\n");
    printf("| 1. Inserir novos equipamentos                 |\n");
    printf("| 2. Buscar equipamento por Codigo              |\n");
    printf("| 3. Atualizar dados de um equipamento          |\n");
    printf("| 4. Desativar equipamento                      |\n");
    printf("| 5. Remover equipamentos (exclusao permanente) |\n");
    printf("| 6. Ativar equipamentos                        |\n");
    printf("| 7. Listar todos os equipamentos               |\n");
    printf("+-----------------------------------------------+\n");
    printf("| 0. Voltar ao menu principal                   |\n");
    printf("+-----------------------------------------------+\n");
}

 void view_exibir_menu_fornecedor() {
    printf("\n+----------------------------------------------+\n");
    printf("|          FORNECEDORES E PARCEIROS            |\n");
    printf("+----------------------------------------------+\n");
    printf("| 1. Inserir novo fornecedor                   |\n");
    printf("| 2. Buscar fornecedor por Codigo              |\n");
    printf("| 3. Atualizar dados de um fornecedor          |\n");
    printf("| 4. Desativar fornecedor                      |\n");
    printf("| 5. Remover fornecedor (exclusao permanente)  |\n");
    printf("| 6. Ativar fornecedor                         |\n");
    printf("| 7. Listar todos os fornecedores              |\n");
    printf("+----------------------------------------------+\n");
    printf("| 0. Voltar ao menu principal                  |\n");
    printf("+----------------------------------------------+\n");
}

 void view_exibir_menu_operador() {
    printf("\n+----------------------------------------------+\n");
    printf("|          OPERADORES DO SISTEMA               |\n");
    printf("+----------------------------------------------+\n");
    printf("| 1. Inserir novo operador do sistema          |\n");
    printf("| 2. Buscar operador por Codigo                |\n");
    printf("| 3. Atualizar dados de um operador            |\n");
    printf("| 4. Desativar operador                        |\n");
    printf("| 5. Remover operador (exclusao permanente)    |\n");
    printf("| 6. Ativar operador                           |\n");
    printf("| 7. Listar todos os operadores                |\n");
    printf("+----------------------------------------------+\n");
    printf("| 0. Voltar ao menu principal                  |\n");
    printf("+----------------------------------------------+\n");
}




// void view_exibir_menu_equipe() {
//     printf("\n ====== Modulo de Equipe ========\n");
//     printf("   |  1. Inserir novo membro               |\n");
//     printf("   |  2. Listar membros da equipe          |\n");
//     // Futuramente, adicionar opções de buscar, atualizar, remover...
//     printf("   |  0. Voltar ao menu principal          |\n");
//     printf("   ==================================\n");
// }

