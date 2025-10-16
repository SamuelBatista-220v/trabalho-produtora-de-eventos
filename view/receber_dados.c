#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "receber_dados.h"
#include "../validacoes/validacoes.h"

static void limpar_buffer_teclado() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

static void ler_campo_validado(const char* prompt, char* destino, int tamanho_destino, int (*funcao_validacao)(const char*), const char* msg_erro) {
    char buffer[256];
    int valido;
    do {
        printf("%s", prompt);
        fgets(buffer, sizeof(buffer), stdin);
        if (strchr(buffer, '\n') == NULL) limpar_buffer_teclado();
        buffer[strcspn(buffer, "\n")] = 0;

        if (funcao_validacao != NULL) {
            valido = funcao_validacao(buffer);
        } else {
            valido = (strlen(buffer) > 0);
        }

        if (!valido) {
            if (msg_erro != NULL) {
                printf(">> %s Tente novamente.\n", msg_erro);
            } else if (strlen(buffer) == 0) {
                printf(">> ERRO: O campo nao pode ser vazio. Tente novamente.\n");
            }
        }
    } while (!valido);
    strncpy(destino, buffer, tamanho_destino - 1);
    destino[tamanho_destino - 1] = '\0';
}


int view_ler_opcao() {
    char buffer[20];
    printf("Escolha uma opcao: ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (strchr(buffer, '\n') == NULL) limpar_buffer_teclado();
        return atoi(buffer);
    }
    return -1;
}

void view_ler_dados_cliente(Cliente* cliente) {
    char buffer_leitura[256];
    int tipo_escolha = 0;

    do {
        printf("\nSelecione o tipo de cliente:\n1. Pessoa Fisica (CPF)\n2. Pessoa Juridica (CNPJ)\nEscolha: ");
        fgets(buffer_leitura, sizeof(buffer_leitura), stdin);
        if (strchr(buffer_leitura, '\n') == NULL) limpar_buffer_teclado();
        tipo_escolha = atoi(buffer_leitura);
    } while (tipo_escolha != 1 && tipo_escolha != 2);

    if (tipo_escolha == 1) {
        cliente->tipo = PESSOA_FISICA;
        ler_campo_validado("Digite o nome: ", cliente->doc.pf.nome, sizeof(cliente->doc.pf.nome), validar_apenas_letras, "ERRO: O nome deve conter apenas letras e espacos.");
        ler_campo_validado("Digite o CPF (11 numeros): ", cliente->doc.pf.cpf, sizeof(cliente->doc.pf.cpf), validar_cpf, "Erro: CPF invalido.");
    } else {
        cliente->tipo = PESSOA_JURIDICA;
        ler_campo_validado("Digite a Razao Social: ", cliente->doc.pj.razao_social, sizeof(cliente->doc.pj.razao_social), NULL, NULL);
        ler_campo_validado("Digite o CNPJ (14 numeros): ", cliente->doc.pj.cnpj, sizeof(cliente->doc.pj.cnpj), validar_cnpj, "Erro: CNPJ invalido.");
    }
    
    ler_campo_validado("Digite o endereco completo: ", cliente->endereco_completo, sizeof(cliente->endereco_completo), NULL, NULL);
    ler_campo_validado("Digite o telefone (10 ou 11 numeros): ", cliente->telefone, sizeof(cliente->telefone), validar_telefone, "Erro: Telefone invalido.");
    ler_campo_validado("Digite o email: ", cliente->email, sizeof(cliente->email), validar_email, "Erro: Email invalido (deve conter '@').");
    ler_campo_validado("Digite o nome de contato: ", cliente->nome_contato, sizeof(cliente->nome_contato), validar_apenas_letras, "Erro: O nome de contato deve conter apenas letras.");
}

void view_ler_dados_equipe(Equipe* equipe) {
    char buffer_float[32];
    ler_campo_validado("Digite o nome do membro da equipe: ", equipe->nome, sizeof(equipe->nome), validar_apenas_letras, "ERRO: O nome deve conter apenas letras.");
    ler_campo_validado("Digite o CPF (11 numeros): ", equipe->cpf, sizeof(equipe->cpf), validar_cpf, "Erro: CPF invalido.");
    ler_campo_validado("Digite a funcao (Ex: Produtor): ", equipe->funcao, sizeof(equipe->funcao), NULL, NULL);
    
    printf("Digite o valor da diaria: ");
    fgets(buffer_float, sizeof(buffer_float), stdin);
    if (strchr(buffer_float, '\n') == NULL) limpar_buffer_teclado();
    equipe->valor_diaria = atof(buffer_float);
}

void view_ler_dados_fornecedor(fornecedor* fornecedor) {
    printf("\n--- Cadastro de Novo Fornecedor ---\n");
    ler_campo_validado("Digite o Nome Fantasia: ", fornecedor->nome_fantasia, sizeof(fornecedor->nome_fantasia), NULL, NULL);
    ler_campo_validado("Digite a Razao Social: ", fornecedor->razao_social, sizeof(fornecedor->razao_social), NULL, NULL);
    ler_campo_validado("Digite o CNPJ (14 numeros): ", fornecedor->cnpj, sizeof(fornecedor->cnpj), validar_cnpj, "Erro: CNPJ invalido.");
    ler_campo_validado("Digite o endereco completo: ", fornecedor->endereco_completo, sizeof(fornecedor->endereco_completo), NULL, NULL);
    ler_campo_validado("Digite o telefone (10 ou 11 numeros): ", fornecedor->telefone, sizeof(fornecedor->telefone), validar_telefone, "Erro: Telefone invalido.");
    ler_campo_validado("Digite o Tipo de Servico (Ex: Buffet): ", fornecedor->tipo_servico, sizeof(fornecedor->tipo_servico), NULL, NULL);
}