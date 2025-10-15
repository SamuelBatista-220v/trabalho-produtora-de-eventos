// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
// #include "../model/cliente.h"
// #include "../model/equipe.h"
// #include "view.h"
// #include "../validacoes/validacoes.h"

// // --- PROTÓTIPOS PRIVADOS ---
// static void limpar_buffer_teclado();
// static void imprimir_cpf_formatado(const char* cpf);
// static void imprimir_cnpj_formatado(const char* cnpj);
// static void imprimir_telefone_formatado(const char* telefone);
// // Função auxiliar genérica para ler e validar qualquer campo de texto
// static void ler_campo_validado(const char* prompt, char* destino, int tamanho_destino, int (*funcao_validacao)(const char*), const char* msg_erro);

// // =============================================================================
// // --- FUNÇÕES DE MENU ---
// // =============================================================================

// void view_exibir_menu_principal() {
//     printf("\n ====== SISTEMA PRODUTORA DE EVENTOS ========\n");
//     printf("   |  1. Gerenciar Clientes                 |\n");
//     printf("   |  2. Gerenciar Equipe                   |\n");
//     printf("   |  0. Sair do Sistema                    |\n");
//     printf("   ==========================================\n");
// }

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

// void view_exibir_menu_equipe() {
//     printf("\n ====== Modulo de Equipe ========\n");
//     printf("   |  1. Inserir novo membro               |\n");
//     printf("   |  2. Listar membros da equipe          |\n");
//     // Futuramente, adicionar opções de buscar, atualizar, remover...
//     printf("   |  0. Voltar ao menu principal          |\n");
//     printf("   ==================================\n");
// }

// // =============================================================================
// // --- FUNÇÕES DE INTERAÇÃO (Leitura e Exibição) ---
// // =============================================================================

// void view_exibir_mensagem(const char* mensagem) {
//     printf(">> %s\n", mensagem);
// }

// int view_ler_opcao() {
//     char buffer[20];
//     printf("Escolha uma opcao: ");
//     if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
//         if (strchr(buffer, '\n') == NULL) limpar_buffer_teclado();
//         return atoi(buffer);
//     }
//     return -1;
// }

// // --- Funções de Leitura de Dados ---

// void view_ler_dados_cliente(Cliente* cliente) {
//     char buffer_leitura[256];
//     int tipo_escolha = 0;

//     do {
//         printf("\nSelecione o tipo de cliente:\n1. Pessoa Fisica (CPF)\n2. Pessoa Juridica (CNPJ)\nEscolha: ");
//         fgets(buffer_leitura, sizeof(buffer_leitura), stdin);
//         if (strchr(buffer_leitura, '\n') == NULL) limpar_buffer_teclado();
//         tipo_escolha = atoi(buffer_leitura);
//     } while (tipo_escolha != 1 && tipo_escolha != 2);

//     if (tipo_escolha == 1) {
//         cliente->tipo = PESSOA_FISICA;
//         ler_campo_validado("Digite o nome: ", cliente->doc.pf.nome, sizeof(cliente->doc.pf.nome), validar_apenas_letras, "ERRO: O nome deve conter apenas letras e espacos.");
//         ler_campo_validado("Digite o CPF (11 numeros): ", cliente->doc.pf.cpf, sizeof(cliente->doc.pf.cpf), validar_cpf, "Erro: CPF invalido.");
//     } else {
//         cliente->tipo = PESSOA_JURIDICA;
//         ler_campo_validado("Digite a Razao Social: ", cliente->doc.pj.razao_social, sizeof(cliente->doc.pj.razao_social), NULL, NULL);
//         ler_campo_validado("Digite o CNPJ (14 numeros): ", cliente->doc.pj.cnpj, sizeof(cliente->doc.pj.cnpj), validar_cnpj, "Erro: CNPJ invalido.");
//     }
    
//     ler_campo_validado("Digite o endereco completo: ", cliente->endereco_completo, sizeof(cliente->endereco_completo), NULL, NULL);
//     ler_campo_validado("Digite o telefone (10 ou 11 numeros): ", cliente->telefone, sizeof(cliente->telefone), validar_telefone, "Erro: Telefone invalido.");
//     ler_campo_validado("Digite o email: ", cliente->email, sizeof(cliente->email), validar_email, "Erro: Email invalido (deve conter '@').");
//     ler_campo_validado("Digite o nome de contato: ", cliente->nome_contato, sizeof(cliente->nome_contato), validar_apenas_letras, "Erro: O nome de contato deve conter apenas letras.");
// }

// void view_ler_dados_equipe(Equipe* equipe) {
//     char buffer_float[32];
//     ler_campo_validado("Digite o nome do membro da equipe: ", equipe->nome, sizeof(equipe->nome), validar_apenas_letras, "ERRO: O nome deve conter apenas letras.");
//     ler_campo_validado("Digite o CPF (11 numeros): ", equipe->cpf, sizeof(equipe->cpf), validar_cpf, "Erro: CPF invalido.");
//     ler_campo_validado("Digite a funcao (Ex: Produtor): ", equipe->funcao, sizeof(equipe->funcao), NULL, NULL);
    
//     printf("Digite o valor da diaria: ");
//     fgets(buffer_float, sizeof(buffer_float), stdin);
//     if (strchr(buffer_float, '\n') == NULL) limpar_buffer_teclado();
//     equipe->valor_diaria = atof(buffer_float);
// }

// // --- Funções de Impressão ---

// void view_imprimir_lista(ListaCliente* lista) {
//     if (lista == NULL) {
//         printf("\n>> A lista de clientes esta vazia.\n");
//         return;
//     }
//     printf("\n--- Lista de Clientes Cadastrados ---\n");
//     for (ListaCliente* aux = lista; aux != NULL; aux = aux->prox) {
//         view_imprimir_cliente_unico(aux);
//     }
// }

// void view_imprimir_cliente_unico(ListaCliente* no_cliente) {
//     if (no_cliente == NULL) return;
//     printf("----------------------------------------\n");
//     printf("Codigo : %d\n", no_cliente->conteudo.id);
//     if (no_cliente->conteudo.tipo == PESSOA_FISICA) {
//         printf("Nome   : %s\n", no_cliente->conteudo.doc.pf.nome);
//         printf("CPF    : ");
//         imprimir_cpf_formatado(no_cliente->conteudo.doc.pf.cpf);
//     } else {
//         printf("Razao Social: %s\n", no_cliente->conteudo.doc.pj.razao_social);
//         printf("CNPJ        : ");
//         imprimir_cnpj_formatado(no_cliente->conteudo.doc.pj.cnpj);
//     }
//     printf("\nEndereco: %s\n", no_cliente->conteudo.endereco_completo);
//     printf("Telefone: ");
//     imprimir_telefone_formatado(no_cliente->conteudo.telefone);
//     printf("\nEmail   : %s\n", no_cliente->conteudo.email);
//     printf("Contato : %s\n", no_cliente->conteudo.nome_contato);
//     printf("Status  : %s\n", no_cliente->conteudo.ativo ? "Ativo" : "Inativo");
// }

// void view_imprimir_lista_equipe(ListaEquipe* lista) {
//     if (lista == NULL) {
//         printf("\n>> Nenhum membro de equipe cadastrado.\n");
//         return;
//     }
//     printf("\n--- Lista de Membros da Equipe ---\n");
//     for (ListaEquipe* aux = lista; aux != NULL; aux = aux->prox) {
//         printf("----------------------------------------\n");
//         printf("Codigo      : %d\n", aux->conteudo.id);
//         printf("Nome        : %s\n", aux->conteudo.nome);
//         printf("CPF         : ");
//         imprimir_cpf_formatado(aux->conteudo.cpf);
//         printf("\n");
//         printf("Funcao      : %s\n", aux->conteudo.funcao);
//         printf("Valor Diaria: R$ %.2f\n", aux->conteudo.valor_diaria);
//         printf("Status      : %s\n", aux->conteudo.ativo ? "Ativo" : "Inativo");
//     }
// }

// // =============================================================================
// // --- FUNÇÕES PRIVADAS ---
// // =============================================================================

// static void ler_campo_validado(const char* prompt, char* destino, int tamanho_destino, int (*funcao_validacao)(const char*), const char* msg_erro) {
//     char buffer[256];
//     int valido;
//     do {
//         printf("%s", prompt);
//         fgets(buffer, sizeof(buffer), stdin);
//         if (strchr(buffer, '\n') == NULL) limpar_buffer_teclado();
//         buffer[strcspn(buffer, "\n")] = 0;

//         if (funcao_validacao != NULL) {
//             valido = funcao_validacao(buffer);
//         } else {
//             valido = (strlen(buffer) > 0);
//         }

//         if (!valido) {
//             if (msg_erro != NULL) {
//                 printf(">> %s Tente novamente.\n", msg_erro);
//             } else if (strlen(buffer) == 0) {
//                 printf(">> ERRO: O campo nao pode ser vazio. Tente novamente.\n");
//             }
//         }
//     } while (!valido);
//     strncpy(destino, buffer, tamanho_destino - 1);
//     destino[tamanho_destino - 1] = '\0';
// }

// static void limpar_buffer_teclado() {
//     int ch;
//     while ((ch = getchar()) != '\n' && ch != EOF);
// }

// static void imprimir_cpf_formatado(const char* cpf) {
//     if (cpf != NULL && strlen(cpf) == 11) {
//         printf("%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
//     } else {
//         printf("%s", cpf);
//     }
// }

// static void imprimir_cnpj_formatado(const char* cnpj) {
//     if (cnpj != NULL && strlen(cnpj) == 14) {
//         printf("%.2s.%.3s.%.3s/%.4s-%.2s", cnpj, cnpj + 2, cnpj + 5, cnpj + 8, cnpj + 12);
//     } else {
//         printf("%s", cnpj);
//     }
// }

// static void imprimir_telefone_formatado(const char* telefone) {
//     if (telefone == NULL) return;
//     size_t len = strlen(telefone);
//     if (len == 11) {
//         printf("(%.2s) %.1s %.4s-%.4s", telefone, telefone + 2, telefone + 3, telefone + 7);
//     } else if (len == 10) {
//         printf("(%.2s) %.4s-%.4s", telefone, telefone + 2, telefone + 6);
//     } else {
//         printf("%s", telefone);
//     }
// }