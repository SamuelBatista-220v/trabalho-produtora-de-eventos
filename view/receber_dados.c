// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
// #include "receber_dados.h"
// #include "../validacoes/validacoes.h"

// static void limpar_buffer_teclado() {
//     int ch;
//     while ((ch = getchar()) != '\n' && ch != EOF);
// }

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


// int view_ler_opcao() {
//     char buffer[20];
//     printf("digite a opcao: ");
//     if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
//         if (strchr(buffer, '\n') == NULL) limpar_buffer_teclado();
//         return atoi(buffer);
//     }
//     return -1;
// }

// void view_ler_dados_cliente(Cliente* cliente) {
//     char buffer_leitura[150];
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

// void view_ler_dados_equipe(equipe* equipe) {
//     char buffer_float[30];
//     ler_campo_validado("Digite o nome do membro da equipe: ", equipe->nome, sizeof(equipe->nome), validar_apenas_letras, "ERRO: O nome deve conter apenas letras.");
//     ler_campo_validado("Digite o CPF (11 numeros): ", equipe->cpf, sizeof(equipe->cpf), validar_cpf, "Erro: CPF invalido.");
//     ler_campo_validado("Digite a funcao (Ex: Produtor): ", equipe->funcao, sizeof(equipe->funcao), NULL, NULL);
    
//     ler_campo_validado("Digite o valor da diaria: ", buffer_float, sizeof(buffer_float), NULL, NULL);
//     equipe->valor_diaria = atof(buffer_float);

// }

// void view_ler_dados_fornecedor(fornecedor* fornecedor) {
//      char buffer_leitura[150];
//     int tipo_escolha = 0;
//     do {
//         printf("\nSelecione o tipo de fornecedor:\n1. Pessoa Fisica (CPF)\n2. Pessoa Juridica (CNPJ)\nEscolha: ");
//         fgets(buffer_leitura, sizeof(buffer_leitura), stdin);
//         if (strchr(buffer_leitura, '\n') == NULL) limpar_buffer_teclado();
//         tipo_escolha = atoi(buffer_leitura);
//     } while (tipo_escolha != 1 && tipo_escolha != 2);

//     if (tipo_escolha == 1) {
//         fornecedor->tipoF = PESSOA_FISICA;
//         ler_campo_validado("Digite o CPF (11 numeros): ", fornecedor->docfornecedor.pf.cpf, sizeof(fornecedor->docfornecedor.pf.cpf), validar_cpf, "Erro: CPF invalido.");
//     } else {
//         fornecedor->tipoF = PESSOA_JURIDICA;
//         ler_campo_validado("Digite o CNPJ (14 numeros): ", fornecedor->docfornecedor.pj.cnpj, sizeof(fornecedor->docfornecedor.pj.cnpj), validar_cnpj, "Erro: CNPJ invalido.");
//     }
//     ler_campo_validado("Digite o Nome Fantasia: ", fornecedor->nome_fantasia, sizeof(fornecedor->nome_fantasia), NULL, NULL);
//     ler_campo_validado("Digite a Razao Social: ", fornecedor->razao_social, sizeof(fornecedor->razao_social), NULL, NULL);
//     ler_campo_validado("Digite o endereco completo: ", fornecedor->endereco_completo, sizeof(fornecedor->endereco_completo), NULL, NULL);
//     ler_campo_validado("Digite o telefone (10 ou 11 numeros): ", fornecedor->telefone, sizeof(fornecedor->telefone), validar_telefone, "Erro: Telefone invalido.");
//     ler_campo_validado("Digite o Tipo de Servico (Ex: Buffet): ", fornecedor->tipo_servico, sizeof(fornecedor->tipo_servico), NULL, NULL);
// }

// void view_ler_dados_operador(operador* operador) {

//     ler_campo_validado("Digite o Nome: ", operador->nome, sizeof(operador->nome), NULL, NULL);
//     ler_campo_validado("Digite o Usuario: ", operador->usuario, sizeof(operador->usuario), NULL, NULL);
//     // ler_campo_validado("Digite a Senha (numerica): ", operador->senha, sizeof(operador->senha), NULL, NULL);
    
//     char buffer_senha[20];
//     ler_campo_validado("Digite a Senha (numerica): ", buffer_senha, sizeof(buffer_senha), NULL, NULL);
//     operador->senha = atoi(buffer_senha);

// }



// void view_ler_dados_produtora(produtora* produtora) {   
//     char buffer_float[30]; 
    
//     printf("\n--- Cadastro da Produtora ---\n");

//     ler_campo_validado("Digite o Nome Fantasia: ", produtora->nome_fantasia, sizeof(produtora->nome_fantasia), NULL, NULL);
//     ler_campo_validado("Digite a Razao Social: ", produtora->razao_social, sizeof(produtora->razao_social), NULL, NULL);
//     ler_campo_validado("Digite a Inscricao Estadual: ", produtora->inscricao_estadual, sizeof(produtora->inscricao_estadual), NULL, NULL);
//     ler_campo_validado("Digite o CNPJ (14 numeros): ", produtora->cnpj, sizeof(produtora->cnpj), validar_cnpj, "Erro: CNPJ invalido.");
//     ler_campo_validado("Digite o endereco completo: ", produtora->endereco_completo, sizeof(produtora->endereco_completo), NULL, NULL);
//     ler_campo_validado("Digite o telefone (10 ou 11 numeros): ", produtora->telefone, sizeof(produtora->telefone), validar_telefone, "Erro: Telefone invalido.");
//     ler_campo_validado("Digite o email: ", produtora->email, sizeof(produtora->email), validar_email, "Erro: Email invalido (deve conter '@').");
//     ler_campo_validado("Digite o nome do responsavel: ", produtora->nome_responsavel, sizeof(produtora->nome_responsavel), validar_apenas_letras, "Erro: O nome do responsavel deve conter apenas letras.");
//     ler_campo_validado("Digite o telefone do responsavel: ", produtora->telefone_responsavel, sizeof(produtora->telefone_responsavel), validar_telefone, "Erro: Telefone invalido.");

//     printf("Digite a Margem de Lucro Padrao (%%) [Ex: 20]: ");
//     fgets(buffer_float, sizeof(buffer_float), stdin);
//     if (strchr(buffer_float, '\n') == NULL) limpar_buffer_teclado();
//     produtora->margem_lucro_padrao = atof(buffer_float);
// }

// void view_ler_dados_recurso(recurso* recurso) {
//     char buffer_float[50];

//     ler_campo_validado("Digite a descricao (caixa de som, projetor, etc): ", recurso->descricao, sizeof(recurso->descricao), NULL, NULL);
//     ler_campo_validado("Digite a categoria (ilumincao, sonorizacao, etc): ", recurso->categoria, sizeof(recurso->categoria), NULL, NULL);
//     ler_campo_validado("Digite a quantidade em estoque: ", buffer_float, sizeof(buffer_float), NULL, NULL);
//     recurso->quantidade = atoi(buffer_float);

//     ler_campo_validado("Digite o preco de custo: ", buffer_float, sizeof(buffer_float), NULL, NULL);
//     recurso->preco_de_custo = atof(buffer_float);


//     ler_campo_validado("Digite o valor da locacao: ", buffer_float, sizeof(buffer_float), NULL, NULL);
//     recurso->valor_da_locacao = atof(buffer_float);
  

// }


// void view_ler_dados_base_orcamento(Orcamento* orcamento) {
//     char buffer[50]; // Buffer auxiliar para leitura segura de datas
    
//     printf("\n--- Dados do Evento ---\n");
    
//     ler_campo_validado("Nome do Evento: ", orcamento->nome_evento, sizeof(orcamento->nome_evento), NULL, NULL);
//     ler_campo_validado("Local do Evento: ", orcamento->local, sizeof(orcamento->local), NULL, NULL);

//     // Usamos fgets para garantir que o ENTER anterior não atrapalhe
    
//     printf("Data de Inicio (DD MM AAAA): ");
//     fgets(buffer, sizeof(buffer), stdin); 
//     if (sscanf(buffer, "%d %d %d", &orcamento->dia_inicio, &orcamento->mes_inicio, &orcamento->ano_inicio) != 3) {
//         printf(">> Aviso: Data invalida lida. Definindo data padrao.\n");
//         orcamento->dia_inicio = 1; orcamento->mes_inicio = 1; orcamento->ano_inicio = 2025;
//     }

//     printf("Data de Termino (DD MM AAAA): ");
//     fgets(buffer, sizeof(buffer), stdin);
//     if (sscanf(buffer, "%d %d %d", &orcamento->dia_fim, &orcamento->mes_fim, &orcamento->ano_fim) != 3) {
//         printf(">> Aviso: Data invalida lida. Definindo data padrao.\n");
//         orcamento->dia_fim = 1; orcamento->mes_fim = 1; orcamento->ano_fim = 2025;
//     }
// }

// // Lê os valores totais da Nota Fiscal
// void view_ler_totais_nota_fiscal(float* produtos, float* frete, float* impostos) {
//     char buffer[50];
//     printf("\n--- VALORES DA NOTA FISCAL ---\n");
    
//     // Usamos NULL nos validadores para aceitar qualquer número por enquanto
//     ler_campo_validado("Valor Total dos Produtos (R$): ", buffer, 50, NULL, NULL);
//     *produtos = atof(buffer);

//     ler_campo_validado("Valor Total do Frete (R$): ", buffer, 50, NULL, NULL);
//     *frete = atof(buffer);

//     ler_campo_validado("Valor Total de Impostos (R$): ", buffer, 50, NULL, NULL);
//     *impostos = atof(buffer);
// }

// // Lê um item da nota. Retorna 0 se o usuário digitar ID 0 (sair), 1 se leu ok.
// int view_ler_item_nota_fiscal(int* id_rec, int* qtd, float* custo) {
//     char buffer[50];
    
//     printf("\nDigite o ID do Recurso comprado (0 para encerrar): ");
//     if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 0;
//     *id_rec = atoi(buffer);

//     if (*id_rec == 0) return 0; // Encerra loop

//     ler_campo_validado("Quantidade comprada: ", buffer, 50, NULL, NULL);
//     *qtd = atoi(buffer);

//     ler_campo_validado("Preco de Custo Unitario (R$): ", buffer, 50, NULL, NULL);
//     *custo = atof(buffer);

//     return 1;
// }

// // Lê os dados do pagamento (A vista ou Prazo)
// void view_ler_dados_pagamento(int* forma_pag, char* data_venc, float* entrada, int* parcelas) {
//     char buffer[50];
    
//     printf("\n--- CONDICOES DE PAGAMENTO ---\n");
//     printf("1. A Vista (Debito imediato)\n");
//     printf("2. A Prazo (   Sem juros   )\n");
//     ler_campo_validado("Opcao: ", buffer, 50, NULL, NULL);
//     *forma_pag = atoi(buffer);

//     ler_campo_validado("Data Base/Vencimento (DD/MM/AAAA): ", data_venc, 20, NULL, NULL);

//     // Inicializa valores opcionais
//     *entrada = 0;
//     *parcelas = 1;

//     if (*forma_pag == 2) {
//         ler_campo_validado("Valor de Entrada (0 se nao houver): ", buffer, 50, NULL, NULL);
//         *entrada = atof(buffer);

//         ler_campo_validado("Numero de Parcelas (restante): ", buffer, 50, NULL, NULL);
//         *parcelas = atoi(buffer);
//     }
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "receber_dados.h"
#include "../validacoes/validacoes.h"
#include "formatacao.h" // Importante para usar a função blindada

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

        if (funcao_validacao != NULL) valido = funcao_validacao(buffer);
        else valido = (strlen(buffer) > 0);

        if (!valido) {
            if (msg_erro != NULL) printf(">> %s Tente novamente.\n", msg_erro);
            else if (strlen(buffer) == 0) printf(">> ERRO: O campo nao pode ser vazio.\n");
        }
    } while (!valido);
    strncpy(destino, buffer, tamanho_destino - 1);
    destino[tamanho_destino - 1] = '\0';
}

int view_ler_opcao() {
    char buffer[20];
    printf("digite a opcao: ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (strchr(buffer, '\n') == NULL) limpar_buffer_teclado();
        return atoi(buffer);
    }
    return -1;
}

void view_ler_dados_cliente(Cliente* cliente) {
    char buffer_leitura[150];
    int tipo_escolha = 0;
    do {
        printf("\nSelecione o tipo de cliente:\n1. Pessoa Fisica (CPF)\n2. Pessoa Juridica (CNPJ)\nEscolha: ");
        fgets(buffer_leitura, sizeof(buffer_leitura), stdin);
        if (strchr(buffer_leitura, '\n') == NULL) limpar_buffer_teclado();
        tipo_escolha = atoi(buffer_leitura);
    } while (tipo_escolha != 1 && tipo_escolha != 2);

    if (tipo_escolha == 1) {
        cliente->tipo = PESSOA_FISICA;
        ler_campo_validado("Digite o nome: ", cliente->doc.pf.nome, sizeof(cliente->doc.pf.nome), validar_apenas_letras, "ERRO: Apenas letras.");
        ler_campo_validado("Digite o CPF (11 numeros): ", cliente->doc.pf.cpf, sizeof(cliente->doc.pf.cpf), validar_cpf, "Erro: CPF invalido.");
    } else {
        cliente->tipo = PESSOA_JURIDICA;
        ler_campo_validado("Digite a Razao Social: ", cliente->doc.pj.razao_social, sizeof(cliente->doc.pj.razao_social), NULL, NULL);
        ler_campo_validado("Digite o CNPJ (14 numeros): ", cliente->doc.pj.cnpj, sizeof(cliente->doc.pj.cnpj), validar_cnpj, "Erro: CNPJ invalido.");
    }
    ler_campo_validado("Digite o endereco completo: ", cliente->endereco_completo, sizeof(cliente->endereco_completo), NULL, NULL);
    ler_campo_validado("Digite o telefone: ", cliente->telefone, sizeof(cliente->telefone), validar_telefone, "Erro: Telefone invalido.");
    ler_campo_validado("Digite o email: ", cliente->email, sizeof(cliente->email), validar_email, "Erro: Email invalido.");
    ler_campo_validado("Digite o nome de contato: ", cliente->nome_contato, sizeof(cliente->nome_contato), validar_apenas_letras, "Erro: Apenas letras.");
}

void view_ler_dados_equipe(equipe* equipe) {
    char buffer_float[30];
    ler_campo_validado("Digite o nome: ", equipe->nome, sizeof(equipe->nome), validar_apenas_letras, "ERRO: Apenas letras.");
    ler_campo_validado("Digite o CPF: ", equipe->cpf, sizeof(equipe->cpf), validar_cpf, "Erro: CPF invalido.");
    ler_campo_validado("Digite a funcao: ", equipe->funcao, sizeof(equipe->funcao), NULL, NULL);
    
    ler_campo_validado("Digite o valor da diaria: ", buffer_float, sizeof(buffer_float), NULL, NULL);
    equipe->valor_diaria = string_para_float_universal(buffer_float); // <--- CORRIGIDO
}

void view_ler_dados_fornecedor(fornecedor* fornecedor) {
    char buffer_leitura[150];
    int tipo_escolha = 0;
    do {
        printf("\nTipo fornecedor:\n1. Pessoa Fisica\n2. Pessoa Juridica\nEscolha: ");
        fgets(buffer_leitura, sizeof(buffer_leitura), stdin);
        if (strchr(buffer_leitura, '\n') == NULL) limpar_buffer_teclado();
        tipo_escolha = atoi(buffer_leitura);
    } while (tipo_escolha != 1 && tipo_escolha != 2);

    if (tipo_escolha == 1) {
        fornecedor->tipoF = PESSOA_FISICA_FOR;
        ler_campo_validado("Digite o CPF: ", fornecedor->docfornecedor.pf.cpf, sizeof(fornecedor->docfornecedor.pf.cpf), validar_cpf, "Erro: CPF invalido.");
    } else {
        fornecedor->tipoF = PESSOA_JURIDICA_FOR;
        ler_campo_validado("Digite o CNPJ: ", fornecedor->docfornecedor.pj.cnpj, sizeof(fornecedor->docfornecedor.pj.cnpj), validar_cnpj, "Erro: CNPJ invalido.");
    }
    ler_campo_validado("Nome Fantasia: ", fornecedor->nome_fantasia, sizeof(fornecedor->nome_fantasia), NULL, NULL);
    ler_campo_validado("Razao Social: ", fornecedor->razao_social, sizeof(fornecedor->razao_social), NULL, NULL);
    ler_campo_validado("Endereco: ", fornecedor->endereco_completo, sizeof(fornecedor->endereco_completo), NULL, NULL);
    ler_campo_validado("Telefone: ", fornecedor->telefone, sizeof(fornecedor->telefone), validar_telefone, "Erro: Telefone invalido.");
    ler_campo_validado("Tipo Servico: ", fornecedor->tipo_servico, sizeof(fornecedor->tipo_servico), NULL, NULL);
}

void view_ler_dados_operador(operador* operador) {
    char buffer_senha[20];
    ler_campo_validado("Nome: ", operador->nome, sizeof(operador->nome), NULL, NULL);
    ler_campo_validado("Usuario: ", operador->usuario, sizeof(operador->usuario), NULL, NULL);
    ler_campo_validado("Senha (numerica): ", buffer_senha, sizeof(buffer_senha), NULL, NULL);
    operador->senha = atoi(buffer_senha);
}

void view_ler_dados_produtora(produtora* produtora) {   
    char buffer_float[30]; 
    printf("\n--- Cadastro da Produtora ---\n");
    ler_campo_validado("Nome Fantasia: ", produtora->nome_fantasia, sizeof(produtora->nome_fantasia), NULL, NULL);
    ler_campo_validado("Razao Social: ", produtora->razao_social, sizeof(produtora->razao_social), NULL, NULL);
    ler_campo_validado("Inscricao Estadual: ", produtora->inscricao_estadual, sizeof(produtora->inscricao_estadual), NULL, NULL);
    ler_campo_validado("CNPJ: ", produtora->cnpj, sizeof(produtora->cnpj), validar_cnpj, "Erro: CNPJ invalido.");
    ler_campo_validado("Endereco: ", produtora->endereco_completo, sizeof(produtora->endereco_completo), NULL, NULL);
    ler_campo_validado("Telefone: ", produtora->telefone, sizeof(produtora->telefone), validar_telefone, "Erro: Telefone invalido.");
    ler_campo_validado("Email: ", produtora->email, sizeof(produtora->email), validar_email, "Erro: Email invalido.");
    ler_campo_validado("Nome Responsavel: ", produtora->nome_responsavel, sizeof(produtora->nome_responsavel), validar_apenas_letras, "Erro: Apenas letras.");
    ler_campo_validado("Tel Responsavel: ", produtora->telefone_responsavel, sizeof(produtora->telefone_responsavel), validar_telefone, "Erro: Telefone invalido.");

    printf("Margem Lucro Padrao (%%): ");
    fgets(buffer_float, sizeof(buffer_float), stdin);
    if (strchr(buffer_float, '\n') == NULL) limpar_buffer_teclado();
    produtora->margem_lucro_padrao = string_para_float_universal(buffer_float); // <--- CORRIGIDO
}

void view_ler_dados_recurso(recurso* recurso) {
    char buffer_float[50];
    ler_campo_validado("Descricao: ", recurso->descricao, sizeof(recurso->descricao), NULL, NULL);
    ler_campo_validado("Categoria: ", recurso->categoria, sizeof(recurso->categoria), NULL, NULL);
    
    ler_campo_validado("Qtd Estoque: ", buffer_float, sizeof(buffer_float), NULL, NULL);
    recurso->quantidade = atoi(buffer_float);

    ler_campo_validado("Preco Custo: ", buffer_float, sizeof(buffer_float), NULL, NULL);
    recurso->preco_de_custo = string_para_float_universal(buffer_float); // <--- CORRIGIDO

    ler_campo_validado("Valor Locacao: ", buffer_float, sizeof(buffer_float), NULL, NULL);
    recurso->valor_da_locacao = string_para_float_universal(buffer_float); // <--- CORRIGIDO
}

void view_ler_dados_base_orcamento(Orcamento* orcamento) {
    char buffer[50];
    printf("\n--- Dados do Evento ---\n");
    ler_campo_validado("Nome do Evento: ", orcamento->nome_evento, sizeof(orcamento->nome_evento), NULL, NULL);
    ler_campo_validado("Local do Evento: ", orcamento->local, sizeof(orcamento->local), NULL, NULL);

    printf("Data Inicio (DD MM AAAA): ");
    fgets(buffer, sizeof(buffer), stdin); 
    if (sscanf(buffer, "%d %d %d", &orcamento->dia_inicio, &orcamento->mes_inicio, &orcamento->ano_inicio) != 3) {
        printf(">> Aviso: Data invalida. Usando padrao.\n");
        orcamento->dia_inicio = 1; orcamento->mes_inicio = 1; orcamento->ano_inicio = 2025;
    }

    printf("Data Termino (DD MM AAAA): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d %d %d", &orcamento->dia_fim, &orcamento->mes_fim, &orcamento->ano_fim) != 3) {
        orcamento->dia_fim = 1; orcamento->mes_fim = 1; orcamento->ano_fim = 2025;
    }
}

void view_ler_totais_nota_fiscal(float* produtos, float* frete, float* impostos) {
    char buffer[50];
    printf("\n--- VALORES DA NOTA FISCAL ---\n");
    
    ler_campo_validado("Total Produtos (R$): ", buffer, 50, NULL, NULL);
    *produtos = string_para_float_universal(buffer); // <--- CORRIGIDO

    ler_campo_validado("Total Frete (R$): ", buffer, 50, NULL, NULL);
    *frete = string_para_float_universal(buffer); // <--- CORRIGIDO

    ler_campo_validado("Total Impostos (R$): ", buffer, 50, NULL, NULL);
    *impostos = string_para_float_universal(buffer); // <--- CORRIGIDO
}

int view_ler_item_nota_fiscal(int* id_rec, int* qtd, float* custo) {
    char buffer[50];
    printf("\nID Recurso comprado (0 para encerrar): ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 0;
    *id_rec = atoi(buffer);
    if (*id_rec == 0) return 0;

    ler_campo_validado("Quantidade: ", buffer, 50, NULL, NULL);
    *qtd = atoi(buffer);

    ler_campo_validado("Custo Unitario (R$): ", buffer, 50, NULL, NULL);
    *custo = string_para_float_universal(buffer); // <--- CORRIGIDO
    return 1;
}

void view_ler_dados_pagamento(int* forma_pag, char* data_venc, float* entrada, int* parcelas) {
    char buffer[50];
    printf("\n--- PAGAMENTO ---\n1. A Vista\n2. A Prazo\nOpcao: ");
    ler_campo_validado("Opcao: ", buffer, 50, NULL, NULL);
    *forma_pag = atoi(buffer);

    ler_campo_validado("Data Base/Vencimento (DD/MM/AAAA): ", data_venc, 20, NULL, NULL);
    *entrada = 0; *parcelas = 1;

    if (*forma_pag == 2) {
        ler_campo_validado("Valor Entrada (0 se nao houver): ", buffer, 50, NULL, NULL);
        *entrada = string_para_float_universal(buffer); // <--- CORRIGIDO

        ler_campo_validado("Numero Parcelas: ", buffer, 50, NULL, NULL);
        *parcelas = atoi(buffer);
    }
}



// ... (inclua formatacao.h se não tiver) ...

void view_ler_texto_generico(const char* label, char* destino, int tamanho) {
    printf("%s", label);
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = 0;
}

void view_ler_float_generico(const char* label, float* destino) {
    char buffer[50];
    printf("%s", label);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    *destino = string_para_float_universal(buffer);
}

void view_ler_data_generica(const char* label, char* destino) {
    char buffer[20];
    printf("%s", label);
    fgets(buffer, sizeof(buffer), stdin);
    if (strchr(buffer, '\n') == NULL) { int ch; while((ch=getchar())!='\n' && ch!=EOF); }
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(destino, buffer);
}

#include "formatacao.h" // Necessário para string_para_float_universal
// ...

void view_ler_texto_simples(char* destino, int tamanho) {
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = 0;
}

void view_ler_float_simples(float* destino) {
    char buffer[50];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    *destino = string_para_float_universal(buffer);
}