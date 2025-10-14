
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cliente.h"    // Essencial para saber o que é um 'Cliente' e 'ListaCliente'.
#include "view.h"       // Para as próprias declarações da view.
#include "validacoes.h" // Fornece as funções de validação.

// --- PROTÓTIPOS PRIVADOS ---
// Apenas as funções de formatação que são usadas SÓ neste ficheiro
// devem ser declaradas como 'static'.
static void imprimir_cpf_formatado(const char* cpf);
static void imprimir_cnpj_formatado(const char* cnpj);
static void imprimir_telefone_formatado(const char* telefone);
static void limpar_buffer_teclado();

// Exibe o menu principal de opções para o usuário.
void view_exibir_menu() {
    printf("\n ====== Sistema de Gestao de Clientes ========\n");
    printf("   |  1. Inserir novo cliente              |\n");
    printf("   |  2. Buscar cliente por Codigo         |\n");
    printf("   |  3. Atualizar dados de um cliente     |\n");
    printf("   |  4. Desativar cliente (soft delete)   |\n");
    printf("   |  5. Remover cliente (fisicamente)     |\n");
    printf("   |  6. Ativar cliente                    |\n");
    printf("   |  7. Listar todos os clientes          |\n");
    printf("   |  0. Sair                              |\n");
    printf("   =========================================\n");
}

// Exibe uma mensagem genérica na tela. Útil para feedback ao usuário.
void view_exibir_mensagem(const char* mensagem) {
    printf(">> %s\n", mensagem);
}

// Pede ao usuário para digitar uma opção e retorna o número lido.
int view_ler_opcao() {
    char buffer_input[20];
    printf("Escolha uma opcao: ");
    if (fgets(buffer_input, sizeof(buffer_input), stdin) != NULL) {
        // Se a entrada for longa demais, limpa o buffer.
        if (strchr(buffer_input, '\n') == NULL) {
            limpar_buffer_teclado();
        }
        return atoi(buffer_input);
    }
    return -1;
}

// Guia o usuário no preenchimento dos dados de um novo cliente.
void view_ler_dados_cliente(Cliente* cliente) {
    char buffer_leitura[256]; // Usamos um buffer grande para todas as leituras
    int tipo_escolha = 0;

    do {
        printf("\nSelecione o tipo de cliente:\n1. Pessoa Fisica (CPF)\n2. Pessoa Juridica (CNPJ)\nEscolha: ");
        fgets(buffer_leitura, sizeof(buffer_leitura), stdin);
        if (strchr(buffer_leitura, '\n') == NULL) limpar_buffer_teclado();
        tipo_escolha = atoi(buffer_leitura);
    } while (tipo_escolha != 1 && tipo_escolha != 2);

    if (tipo_escolha == 1) {
        cliente->tipo = PESSOA_FISICA;
        
        int nome_valido;
        do {
            printf("Digite o nome: ");
            fgets(cliente->doc.pf.nome, sizeof(cliente->doc.pf.nome), stdin);
            if (strchr(cliente->doc.pf.nome, '\n') == NULL) limpar_buffer_teclado(); //limpa o buffer
            cliente->doc.pf.nome[strcspn(cliente->doc.pf.nome, "\n")] = 0; // Remove o caractere de nova linha '\n' do final da string

            nome_valido = validar_apenas_letras(cliente->doc.pf.nome);
            if (!nome_valido) { // Se a validação falhou, verifica o motivo
                if (cliente->doc.pf.nome[0] == '\0') { // checa se a falha foi por o campo estar vazio
                     printf(">> ERRO: O nome nao pode ser vazio. Tente novamente.\n");
                } else { //se nao foi erro de caracteres
                     printf(">> ERRO: O nome deve conter apenas letras e espacos.\n");
                }
            }
        } while (!nome_valido); // so sai do loop se for valido
        // do {
        //     printf("Digite o nome: ");
        //     fgets(cliente->doc.pf.nome, sizeof(cliente->doc.pf.nome), stdin);
        //     if (strchr(cliente->doc.pf.nome, '\n') == NULL) limpar_buffer_teclado();
        //     cliente->doc.pf.nome[strcspn(cliente->doc.pf.nome, "\n")] = 0;
        // } while (!validar_apenas_letras(cliente->doc.pf.nome));

        do {
            printf("Digite o CPF (11 numeros): ");
            fgets(buffer_leitura, sizeof(buffer_leitura), stdin);
            if (strchr(buffer_leitura, '\n') == NULL) limpar_buffer_teclado();
            buffer_leitura[strcspn(buffer_leitura, "\n")] = 0;
            if(!validar_cpf(buffer_leitura)) {
                printf("Erro: CPF invalido. Tente novamente.\n");
            }
        } while (!validar_cpf(buffer_leitura));
        strcpy(cliente->doc.pf.cpf, buffer_leitura);

    } else { // Pessoa Jurídica
        cliente->tipo = PESSOA_JURIDICA;
        // Validação robusta para Razão Social
        do {
            printf("Digite a Razao Social: ");
            fgets(cliente->doc.pj.razao_social, sizeof(cliente->doc.pj.razao_social), stdin);
            if (strchr(cliente->doc.pj.razao_social, '\n') == NULL) limpar_buffer_teclado();
            cliente->doc.pj.razao_social[strcspn(cliente->doc.pj.razao_social, "\n")] = 0;
        } while (strlen(cliente->doc.pj.razao_social) == 0);

        // Validação robusta para CNPJ
        do {
            printf("Digite o CNPJ (14 numeros): ");
            fgets(buffer_leitura, sizeof(buffer_leitura), stdin);
            if (strchr(buffer_leitura, '\n') == NULL) limpar_buffer_teclado();
            buffer_leitura[strcspn(buffer_leitura, "\n")] = 0;
            if(!validar_cnpj(buffer_leitura)) {
                printf("Erro: CNPJ invalido. Tente novamente.\n");
            }
        } while (!validar_cnpj(buffer_leitura));
        strcpy(cliente->doc.pj.cnpj, buffer_leitura);
    }
    
    do {
        printf("Digite o endereco completo: ");
        fgets(cliente->endereco_completo, sizeof(cliente->endereco_completo), stdin);
        if (strchr(cliente->endereco_completo, '\n') == NULL) limpar_buffer_teclado();
        cliente->endereco_completo[strcspn(cliente->endereco_completo, "\n")] = 0;
        if(strlen(cliente->endereco_completo) == 0) printf("Erro: O endereco nao pode ser vazio.\n");
    } while (strlen(cliente->endereco_completo) == 0);

    do {
        printf("Digite o telefone (10 ou 11 numeros): ");
        fgets(buffer_leitura, sizeof(buffer_leitura), stdin);
        if (strchr(buffer_leitura, '\n') == NULL) limpar_buffer_teclado();
        buffer_leitura[strcspn(buffer_leitura, "\n")] = 0;
        if(!validar_telefone(buffer_leitura)) printf("Erro: Telefone invalido. Deve conter 10 ou 11 digitos.\n");
    } while (!validar_telefone(buffer_leitura));
    strcpy(cliente->telefone, buffer_leitura);

    do {
        printf("Digite o email: ");
        fgets(buffer_leitura, sizeof(buffer_leitura), stdin);
        if (strchr(buffer_leitura, '\n') == NULL) limpar_buffer_teclado();
        buffer_leitura[strcspn(buffer_leitura, "\n")] = 0;
        if(!validar_email(buffer_leitura)) printf("Erro: Email invalido. Deve conter '@'.\n");
    } while (!validar_email(buffer_leitura));
    strcpy(cliente->email, buffer_leitura);

    do {
        printf("Digite o nome de contato: ");
        fgets(cliente->nome_contato, sizeof(cliente->nome_contato), stdin);
        if (strchr(cliente->nome_contato, '\n') == NULL) limpar_buffer_teclado();
        cliente->nome_contato[strcspn(cliente->nome_contato, "\n")] = 0;
        if(!validar_apenas_letras(cliente->nome_contato)) printf("Erro: O nome de contato deve conter apenas letras.\n");
    } while (!validar_apenas_letras(cliente->nome_contato));
    
    // // Leitura dos campos comuns
    // printf("Digite o endereco completo: ");
    // fgets(cliente->endereco_completo, sizeof(cliente->endereco_completo), stdin);
    // if (strchr(cliente->endereco_completo, '\n') == NULL) limpar_buffer_teclado();
    // cliente->endereco_completo[strcspn(cliente->endereco_completo, "\n")] = 0;

    // printf("Digite o telefone (10 ou 11 numeros): ");
    // fgets(cliente->telefone, sizeof(cliente->telefone), stdin);
    // if (strchr(cliente->telefone, '\n') == NULL) limpar_buffer_teclado();
    // cliente->telefone[strcspn(cliente->telefone, "\n")] = 0;
    // if(!validar_telefone(buffer_leitura)) {
    //             printf("Erro: telefone invalido. Tente novamente.\n");
    //         }

    // printf("Digite o email: ");
    // fgets(cliente->email, sizeof(cliente->email), stdin);
    // if (strchr(cliente->email, '\n') == NULL) limpar_buffer_teclado();
    // cliente->email[strcspn(cliente->email, "\n")] = 0;

    // printf("Digite o nome de contato: ");
    // fgets(cliente->nome_contato, sizeof(cliente->nome_contato), stdin);
    // if (strchr(cliente->nome_contato, '\n') == NULL) limpar_buffer_teclado();
    // cliente->nome_contato[strcspn(cliente->nome_contato, "\n")] = 0;
}

// Exibe a lista completa de clientes cadastrados.
void view_imprimir_lista(ListaCliente* lista) {
    if (lista == NULL) {
        printf("\n>> A lista de clientes esta vazia.\n");
        return;
    }
    printf("\n--- Lista de Clientes Cadastrados ---\n");
    ListaCliente* aux = lista;
    while (aux != NULL) {
        view_imprimir_cliente_unico(aux);
        aux = aux->prox;
    }
}

// Exibe os detalhes de um único cliente de forma formatada.
void view_imprimir_cliente_unico(ListaCliente* no_cliente) {
    if (no_cliente == NULL) return;
    printf("----------------------------------------\n");
    printf("Codigo : %d\n", no_cliente->conteudo.id);
    if (no_cliente->conteudo.tipo == PESSOA_FISICA) {
        printf("Nome   : %s\n", no_cliente->conteudo.doc.pf.nome);
        printf("CPF    : ");
        imprimir_cpf_formatado(no_cliente->conteudo.doc.pf.cpf);
    } else {
        printf("Razao Social: %s\n", no_cliente->conteudo.doc.pj.razao_social);
        printf("CNPJ        : ");
        imprimir_cnpj_formatado(no_cliente->conteudo.doc.pj.cnpj);
    }
    printf("\nEndereco: %s\n", no_cliente->conteudo.endereco_completo);
    printf("Telefone: ");
    imprimir_telefone_formatado(no_cliente->conteudo.telefone);
    printf("\nEmail   : %s\n", no_cliente->conteudo.email);
    printf("Contato : %s\n", no_cliente->conteudo.nome_contato);
    printf("Status  : %s\n", no_cliente->conteudo.ativo ? "Ativo" : "Inativo");
}


// --- Implementação das Funções Privadas ---

static void limpar_buffer_teclado() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

static void imprimir_cpf_formatado(const char* cpf) {
    if (cpf != NULL && strlen(cpf) == 11) {
        printf("%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
    } else {
        printf("%s", cpf);
    }
}

static void imprimir_cnpj_formatado(const char* cnpj) {
    if (cnpj != NULL && strlen(cnpj) == 14) {
        printf("%.2s.%.3s.%.3s/%.4s-%.2s", cnpj, cnpj + 2, cnpj + 5, cnpj + 8, cnpj + 12);
    } else {
        printf("%s", cnpj);
    }
}
static void imprimir_telefone_formatado(const char* telefone) {
    if (telefone == NULL) return;
    size_t len = strlen(telefone);
    if (len == 11) {
        printf("(%.2s) %.1s %.4s-%.4s", telefone, telefone + 2, telefone + 3, telefone + 7);
    } else if (len == 10) {
        // CORRIGIDO: O número de argumentos agora corresponde ao formato.
        // Eram 4 argumentos para 3 espaços (%s).
        printf("(%.2s) %.4s-%.4s", telefone, telefone + 2, telefone + 6);
    } else {
        printf("%s", telefone);
    }
}
// static void imprimir_telefone_formatado(const char* telefone) {
//     if (telefone == NULL) return;
//     size_t len = strlen(telefone);
//     if (len == 11) {
//         printf("(%.2s) %.1s %.4s-%.4s", telefone, telefone + 2, telefone + 3, telefone + 7);
//     } else if (len == 10) {
//         printf("(%.2s) %.4s-%.4s", telefone, telefone + 2, telefone + 4, telefone + 8);
//     } else {
//         printf("%s", telefone);
//     }
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
// #include "view.h"
// #include "validacoes.h"

// // --- funçoes de validacao ---
// // 'static' faz com que estas funções só possam ser usadas dentro deste arquivo.
// // Elas ajudam a manter o código da view organizado.
// static int validar_apenas_letras(const char* str);
// static int validar_cpf(const char* cpf);
// static int validar_cnpj(const char* cnpj);
// static int validar_telefone(const char* telefone);
// static int validar_email(const char* email);
// static void imprimir_cpf_formatado(const char* cpf);
// static void imprimir_cnpj_formatado(const char* cnpj);
// static void imprimir_telefone_formatado(const char* telefone);




// // Exibe o menu principal de opções para o usuário.
// void view_exibir_menu() {
//     printf("\n ======Sistema de Gestao de Clientes========\n");
//     printf("   |  1. Inserir novo cliente              |\n");          
//     printf("   |  2. Buscar cliente por Codigo         |\n");     
//     printf("   |  3. Atualizar dados de um cliente     |\n");  
//     printf("   |  4. Desativar cliente (soft delete)   |\n");
//     printf("   |  5. Remover cliente (fisicamente)     |\n");
//     printf("   |  6. Ativar cliente                    |\n");
//     printf("   |  7. Listar todos os clientes          |\n");
//     printf("   |  0. Sair                              |\n");
//     printf("   =========================================\n");
// }

// // Exibe uma mensagem genérica na tela. Útil para feedback ao usuário.
// void view_exibir_mensagem(const char* mensagem) {
//     printf("%s\n", mensagem);
// }

// // Pede ao usuário para digitar uma opção e retorna o número lido.
// int view_ler_opcao() {
//     char buffer_input[20];
//     printf("Escolha uma opcao: ");
//     // Lê uma linha inteira para evitar problemas com o buffer do teclado.
//     if (fgets(buffer_input, sizeof(buffer_input), stdin) != NULL) {
//         // Converte a string lida para um número inteiro.
//         return atoi(buffer_input);
//     }
//     return -1; // Retorna -1 em caso de erro de leitura.
// }

// // Guia o usuário no preenchimento dos dados de um novo cliente.
// void view_ler_dados_cliente(Cliente* cliente) {
//     char buffer_input[20];
//     int tipo_escolha;

//     // Loop para garantir que o usuário escolha um tipo válido.
//     do {
//         printf("\nSelecione o tipo de cliente:\n1. Pessoa Fisica (CPF)\n2. Pessoa Juridica (CNPJ)\nEscolha: ");
//         fgets(buffer_input, sizeof(buffer_input), stdin);
//         tipo_escolha = atoi(buffer_input);
//     } while (tipo_escolha != 1 && tipo_escolha != 2);

//     // Lógica para preencher os dados de PF ou PJ.
//     if (tipo_escolha == 1) {
//         cliente->tipo = PESSOA_FISICA;
//         do {
//             printf("Digite o nome (somente letras): ");
//             fgets(cliente->doc.pf.nome, sizeof(cliente->doc.pf.nome), stdin);
//             cliente->doc.pf.nome[strcspn(cliente->doc.pf.nome, "\n")] = 0;
//         } while (!validar_apenas_letras(cliente->doc.pf.nome));
//         do {
//             printf("Digite o CPF (11 numeros): ");
//             fgets(cliente->doc.pf.cpf, sizeof(cliente->doc.pf.cpf), stdin);

//             // Verifica se a entrada foi longa demais (não encontrou o '\n')
//             if (strchr(cliente->doc.pf.cpf, '\n') == NULL) {
//                 // Limpa o buffer de entrada para descartar caracteres extras
//                 int ch;
//                 while ((ch = getchar()) != '\n' && ch != EOF);
//                 // Invalida a leitura atual para forçar a repetição do loop
//                 cliente->doc.pf.cpf[0] = '\0';
//             } else {
//                 // A entrada coube, então removemos o '\n' do final
//                 cliente->doc.pf.cpf[strcspn(cliente->doc.pf.cpf, "\n")] = 0;
//             }

//             // A função validar_cpf agora sempre recebe uma string limpa
//         } while (!validar_cpf(cliente->doc.pf.cpf));
//         // do {
//         //     printf("Digite o CPF (11 numeros): ");
//         //     fgets(cliente->doc.pf.cpf, sizeof(cliente->doc.pf.cpf), stdin);
//         //     cliente->doc.pf.cpf[strcspn(cliente->doc.pf.cpf, "\n")] = 0;
//         // } while (!validar_cpf(cliente->doc.pf.cpf));
//     } else {
//         cliente->tipo = PESSOA_JURIDICA;
//         do {
//             printf("Digite a Razao Social: ");
//             fgets(cliente->doc.pj.razao_social, sizeof(cliente->doc.pj.razao_social), stdin);
//             cliente->doc.pj.razao_social[strcspn(cliente->doc.pj.razao_social, "\n")] = 0;
//         } while(strlen(cliente->doc.pj.razao_social) == 0);
//         do {
//             printf("Digite o CNPJ (14 numeros): ");
//             fgets(cliente->doc.pj.cnpj, sizeof(cliente->doc.pj.cnpj), stdin);
//             cliente->doc.pj.cnpj[strcspn(cliente->doc.pj.cnpj, "\n")] = 0;
//         } while (!validar_cnpj(cliente->doc.pj.cnpj));
//     }

//     // fflush(stdin) não é portável e pode não funcionar. A leitura com fgets já ajuda a limpar o buffer.

//     // Preenchimento dos campos comuns.
//     // do {
//     // printf("Digite o endereco completo: ");
//     // fgets(cliente->endereco_completo, sizeof(cliente->endereco_completo), stdin);
//     // cliente->endereco_completo[strcspn(cliente->endereco_completo, "\n")] = 0;
//     //  } while 
     
//     do {
//     printf("Digite o endereco completo: ");
//     fgets(cliente->endereco_completo, sizeof(cliente->endereco_completo), stdin);
//     cliente->endereco_completo[strcspn(cliente->endereco_completo, "\n")] = 0;

//     // Se o usuário não digitou nada, mostra um erro.
//     if (strlen(cliente->endereco_completo) == 0) {
//         printf("Erro: O endereco nao pode ser vazio. Por favor, digite novamente.\n");
//     }

//     // A condição para repetir o loop é se o comprimento da string for 0.
//     } while (strlen(cliente->endereco_completo) == 0);
     


//     // Loops 'do-while' para garantir que os dados inseridos sejam válidos.
//     do {
//         printf("Digite o telefone (10 ou 11 numeros, com DDD): ");
//         fgets(cliente->telefone, sizeof(cliente->telefone), stdin);
//         cliente->telefone[strcspn(cliente->telefone, "\n")] = 0;
//     } while (!validar_telefone(cliente->telefone));
    
//     do {
//         printf("Digite o email (deve conter '@'): ");
//         fgets(cliente->email, sizeof(cliente->email), stdin);
//         cliente->email[strcspn(cliente->email, "\n")] = 0;
//     } while (!validar_email(cliente->email));

//     do {
//         printf("Digite o nome de contato: ");
//         fgets(cliente->nome_contato, sizeof(cliente->nome_contato), stdin);
//         cliente->nome_contato[strcspn(cliente->nome_contato, "\n")] = 0;
//     } while (!validar_apenas_letras(cliente->nome_contato));
// }

// // Exibe a lista completa de clientes cadastrados.
// void view_imprimir_lista(ListaCliente* lista) {
//     if (lista == NULL) {
//         printf("\n>> A lista de clientes esta vazia.\n");
//         return;
//     }
//     printf("\n--- Lista de Clientes Cadastrados ---\n");
//     ListaCliente* aux = lista;
//     // Percorre a lista e chama a função de imprimir um único cliente para cada nó.
//     while (aux != NULL) {
//         view_imprimir_cliente_unico(aux);
//         aux = aux->prox;
//     }
//     printf("----------------------------------------\n");
// }

// // Exibe os detalhes de um único cliente de forma formatada.
// void view_imprimir_cliente_unico(ListaCliente* no_cliente) {
//     if (no_cliente == NULL) return;

//     printf("----------------------------------------\n");
//     printf("Codigo : %d\n", no_cliente->conteudo.id);

//     if (no_cliente->conteudo.tipo == PESSOA_FISICA) {
//         printf("Nome   : %s\n", no_cliente->conteudo.doc.pf.nome);
//         printf("CPF    : ");
//         imprimir_cpf_formatado(no_cliente->conteudo.doc.pf.cpf);
//         printf("\n");
//     } else {
//         printf("Razao Social: %s\n", no_cliente->conteudo.doc.pj.razao_social);
//         printf("CNPJ        : ");
//         imprimir_cnpj_formatado(no_cliente->conteudo.doc.pj.cnpj);
//         printf("\n");
//     }
//     printf("Endereco: %s\n", no_cliente->conteudo.endereco_completo);
//     printf("Telefone: ");
//     imprimir_telefone_formatado(no_cliente->conteudo.telefone);
//     printf("\n");
//     printf("Email   : %s\n", no_cliente->conteudo.email);
//     printf("Contato : %s\n", no_cliente->conteudo.nome_contato);
//     printf("Status  : %s\n", no_cliente->conteudo.ativo ? "Ativo" : "Inativo");
// }


// // static int validar_apenas_letras(const char* str) {
// //     if (str == NULL || str[0] == '\0') return 0;
// //     for (int i = 0; str[i] != '\0'; i++) {
// //         if (!isalpha((unsigned char)str[i]) && !isspace((unsigned char)str[i])) {
// //             return 0;
// //         }
// //     }
// //     return 1;
// // }
// // Dentro da função view_ler_dados_cliente, substitua o loop do CPF por este:

// // do {
// //     printf("Digite o CPF (11 numeros): ");
// //     fgets(cliente->doc.pf.cpf, sizeof(cliente->doc.pf.cpf), stdin);


// //     if (strchr(cliente->doc.pf.cpf, '\n') == NULL) {     //verifica se passamos do \n (tecla Enter)
// //         // A entrada foi muito longa.
// //         // Vamos limpar o que sobrou no buffer do teclado para não afetar as próximas leituras.
// //         int va; //validaçao
// //         while ((va = getchar()) != '\n' && va != EOF);
// //         //getchar() lê um único caractere do buffer de entrada
// //         //O caractere lido pelo getchar() é imediatamente guardado (atribuído) na variável (va)
// //         //... != '\n' verifica se o caractere (va) nao É o (\n) tecla Enter
// //         //... && va != EOF verifica se o caractere lido nao EOF (End of File ou Fim do Arquivo)

        
// //         cliente->doc.pf.cpf[0] = '\0'; // transfroma a string em vazia.
// //     } else {
// //         // A entrada coube no buffer. Agora sim, removemos o \n
// //         cliente->doc.pf.cpf[strcspn(cliente->doc.pf.cpf, "\n")] = 0;
// //     }

 
// //     // Se a validação falhar, mostramos uma mensagem de erro genérica.
// //     if (!validar_cpf(cliente->doc.pf.cpf)) {
// //         printf("Erro: O CPF deve conter EXATAMENTE 11 digitos numericos. Tente novamente.\n");
// //     }

// // } while (!validar_cpf(cliente->doc.pf.cpf)); 
// // static int validar_cpf(const char* cpf) {
// //     if (cpf == NULL || strlen(cpf) != 11) return 0;
// //     for (int i = 0; cpf[i] != '\0'; i++) {
// //         if (!isdigit((unsigned char)cpf[i])) return 0;
// //     }
// //     return 1;
// // }

// // static int validar_cnpj(const char* cnpj) {
// //     if (cnpj == NULL || strlen(cnpj) != 14) return 0;
// //     for (int i = 0; cnpj[i] != '\0'; i++) {
// //         if (!isdigit((unsigned char)cnpj[i])) return 0;
// //     }
// //     return 1;
// // }

// // static int validar_telefone(const char* telefone) {
// //     if (telefone == NULL) return 0;
// //     size_t len = strlen(telefone);
// //     if (len < 10 || len > 11) return 0;
// //     for (size_t i = 0; i < len; i++) {
// //         if (!isdigit((unsigned char)telefone[i])) return 0;
// //     }
// //     return 1;
// // }

// // static int validar_email(const char* email) {
// //     if (email == NULL || strchr(email, '@') == NULL) {
// //         return 0;
// //     }
// //     return 1;
// // }

// static void imprimir_cpf_formatado(const char* cpf) {
//     if (cpf != NULL && strlen(cpf) == 11) {
//         printf("%c%c%c.%c%c%c.%c%c%c-%c%c", cpf[0], cpf[1], cpf[2], cpf[3], cpf[4], cpf[5], cpf[6], cpf[7], cpf[8], cpf[9], cpf[10]);
//     }
// }

// static void imprimir_cnpj_formatado(const char* cnpj) {
//     if (cnpj != NULL && strlen(cnpj) == 14) {
//         printf("%c%c.%c%c%c.%c%c%c/%c%c%c%c-%c%c", cnpj[0], cnpj[1], cnpj[2], cnpj[3], cnpj[4], cnpj[5], cnpj[6], cnpj[7], cnpj[8], cnpj[9], cnpj[10], cnpj[11], cnpj[12], cnpj[13]);
//     }
// }

// // static void imprimir_telefone_formatado(const char* telefone) {
//     if (telefone == NULL) return;
//     size_t len = strlen(telefone);
//     if (len == 11) {
//         printf("(%c%c) %c %c%c%c%c-%c%c%c%c", telefone[0], telefone[1], telefone[2], telefone[3], telefone[4], telefone[5], telefone[6], telefone[7], telefone[8], telefone[9], telefone[10]);
//     } else if (len == 10) {
//         printf("(%c%c) %c%c%c%c-%c%c%c%c", telefone[0], telefone[1], telefone[2], telefone[3], telefone[4], telefone[5], telefone[6], telefone[7], telefone[8], telefone[9]);
//     } else {
//         printf("%s", telefone);
//     }
// }