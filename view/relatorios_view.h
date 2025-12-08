

#ifndef RELATORIOS_VIEW_H
#define RELATORIOS_VIEW_H

// Menus
void view_exibir_menu_relatorios_principal();

// Menus de Filtros Específicos
int view_relatorio_menu_filtro_eventos();     // 1-Cliente, 2-Periodo, 3-Status
int view_relatorio_menu_filtro_recursos();    // 1-Todos, 2-Categoria
int view_relatorio_menu_filtro_financeiro();  // 1-Entidade, 2-Periodo

// Inputs de Filtros
int view_relatorio_pedir_tipo_filtro_cliente(); 
int view_relatorio_pedir_destino(); 
void view_relatorio_pedir_periodo(char* data_ini, char* data_fim);
int view_relatorio_pedir_id(const char* entidade);
int view_relatorio_pedir_status(); 
void view_relatorio_pedir_categoria(char* categoria);

// Mensagens
void view_relatorio_msg_sucesso_csv(const char* nome_arquivo);
void view_relatorio_msg_erro_arquivo();
void view_relatorio_msg_cabecalho(const char* titulo);
void view_relatorio_msg_aguarde();
void view_relatorio_totalizador(float valor); 


void view_relatorio_print_linha_cliente(int id, char* nome, char* doc, char* fone);
void view_relatorio_print_linha_financeiro(int id, char* nome_entidade, float valor, char* vencimento, char* status);
void view_relatorio_print_linha_recurso(int id, char* desc, int qtd, float custo, float venda);
void view_relatorio_print_linha_cronograma(char* data_ini, char* data_fim, char* evento, char* status, int id_rec, char* nome_rec, int qtd);
void view_relatorio_print_linha_caixa(char* data, char* tipo, float valor, char* desc);
void view_relatorio_print_balanco(float rec_prev, float rec_real, float des_prev, float des_real);

#endif