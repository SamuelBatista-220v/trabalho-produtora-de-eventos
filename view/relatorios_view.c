
#include <stdio.h>
#include <string.h>
#include "relatorios_view.h"
#include "receber_dados.h" 

void view_exibir_menu_relatorios_principal() {
    printf("\n=== RELATORIOS E FEEDBACK ===\n");
    printf("1. Clientes (Listagem)\n");
    printf("2. Eventos (Orcamentos)\n");
    printf("3. Recursos e Equipamentos\n");
    printf("4. Cronograma de Alocacao\n");
    printf("5. Contas a Receber\n");
    printf("6. Contas a Pagar\n");
    printf("7. Fluxo de Caixa\n");
    printf("0. Voltar\n");
    printf("Escolha uma opcao: ");
}

int view_relatorio_menu_filtro_eventos() {
    printf("\n--- Filtrar Eventos Por: ---\n");
    printf("1. Cliente\n");
    printf("2. Periodo (Data)\n");
    printf("3. Status\n");
    return view_ler_opcao();
}

int view_relatorio_menu_filtro_recursos() {
    printf("\n--- Filtrar Recursos Por: ---\n");
    printf("1. Faixa de Codigos (Todos)\n");
    printf("2. Categoria\n");
    return view_ler_opcao();
}

int view_relatorio_menu_filtro_financeiro() {
    printf("\n--- Filtrar Por: ---\n");
    printf("1. Entidade (Cliente/Fornecedor)\n");
    printf("2. Periodo (Vencimento)\n");
    return view_ler_opcao();
}

int view_relatorio_pedir_tipo_filtro_cliente() {
    printf("\n--- Ordenacao ---\n1. ID (Cadastro)\n2. Alfabetica\nOpcao: ");
    return view_ler_opcao();
}

int view_relatorio_pedir_destino() {
    printf("\n--- Destino ---\n1. TELA\n2. ARQUIVO CSV\nOpcao: ");
    return view_ler_opcao();
}

void view_relatorio_pedir_periodo(char* data_ini, char* data_fim) {
    printf("Data Inicio (DD/MM/AAAA): ");
    char buffer[20];
    fgets(buffer, 20, stdin); buffer[strcspn(buffer, "\n")] = 0;
    strcpy(data_ini, buffer);

    printf("Data Fim    (DD/MM/AAAA): ");
    fgets(buffer, 20, stdin); buffer[strcspn(buffer, "\n")] = 0;
    strcpy(data_fim, buffer);
}

int view_relatorio_pedir_id(const char* entidade) {
    printf("Digite o ID do %s: ", entidade);
    return view_ler_opcao();
}

int view_relatorio_pedir_status() {
    printf("Status (0-Analise, 1-Aprovado, 2-Finalizado, 3-Cancelado): ");
    return view_ler_opcao();
}

void view_relatorio_pedir_categoria(char* categoria) {
    printf("Digite a Categoria: ");
    fgets(categoria, 50, stdin);
    categoria[strcspn(categoria, "\n")] = 0;
}

void view_relatorio_msg_sucesso_csv(const char* nome_arquivo) {
    printf("\n>> SUCESSO: Arquivo '%s' gerado!\n", nome_arquivo);
}

void view_relatorio_msg_erro_arquivo() { printf("\n>> ERRO ao criar arquivo.\n"); }

void view_relatorio_msg_cabecalho(const char* titulo) {
    printf("\n========================================\n RELATORIO: %s\n========================================\n", titulo);
}

void view_relatorio_msg_aguarde() { printf(">> Processando...\n"); }

void view_relatorio_totalizador(float valor) {
    printf("\n----------------------------------------\n TOTAL: R$ %.2f\n----------------------------------------\n", valor);
}



void view_relatorio_print_linha_cliente(int id, char* nome, char* doc, char* fone) {
    // Formatação alinhada
    printf("ID: %04d | %-25.25s | Doc: %-15s | Tel: %s\n", id, nome, doc, fone);
}

void view_relatorio_print_linha_financeiro(int id, char* nome_entidade, float valor, char* vencimento, char* status) {
    printf("ID: %04d | %-20.20s | R$ %9.2f | Venc: %s | %s\n", 
           id, nome_entidade, valor, vencimento, status);
}

void view_relatorio_print_linha_recurso(int id, char* desc, int qtd, float custo, float venda) {
    printf("ID: %04d | %-25.25s | Qtd: %03d | Custo: %7.2f | Loc: %7.2f\n",
           id, desc, qtd, custo, venda);
}

void view_relatorio_print_linha_cronograma(char* data_ini, char* data_fim, char* evento, char* status, int id_rec, char* nome_rec, int qtd) {
    printf("[%s a %s] %-15.15s (%s) | %-20.20s | Qtd: %d\n",
           data_ini, data_fim, evento, status, nome_rec, qtd);
}

void view_relatorio_print_linha_caixa(char* data, char* tipo, float valor, char* desc) {
    printf("[%s] %s R$ %.2f | %s\n", data, tipo, valor, desc);
}

void view_relatorio_print_balanco(float rec_prev, float rec_real, float des_prev, float des_real) {
    printf("\n--- PREVISAO ---\n");
    printf(" (+) Receita Prevista : R$ %.2f\n", rec_prev);
    printf(" (-) Despesa Prevista : R$ %.2f\n", des_prev);
    printf(" (=) LUCRO PROJETADO  : R$ %.2f\n", rec_prev - des_prev);

    printf("\n--- REALIZADO ---\n");
    printf(" (+) Entradas Reais   : R$ %.2f\n", rec_real);
    printf(" (-) Saidas Reais     : R$ %.2f\n", des_real);
    printf(" (=) SALDO REAL       : R$ %.2f\n", rec_real - des_real);
}
