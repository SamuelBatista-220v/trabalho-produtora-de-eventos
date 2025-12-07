// #ifndef RELATORIOS_VIEW_H
// #define RELATORIOS_VIEW_H

// // Menus
// void view_exibir_menu_relatorios_principal();

// // Menus de Filtros Específicos
// int view_relatorio_menu_filtro_eventos();     // Retorna 1-Cliente, 2-Data, 3-Status
// int view_relatorio_menu_filtro_recursos();    // Retorna 1-Codigo, 2-Categoria
// int view_relatorio_menu_filtro_financeiro();  // Retorna 1-Entidade(Cli/Forn), 2-Periodo

// // Inputs de Filtros
// int view_relatorio_pedir_tipo_filtro_cliente(); 
// int view_relatorio_pedir_destino(); 
// void view_relatorio_pedir_periodo(char* data_ini, char* data_fim);
// int view_relatorio_pedir_id(const char* entidade);
// int view_relatorio_pedir_status(); // Para eventos
// void view_relatorio_pedir_categoria(char* categoria);

// // Mensagens
// void view_relatorio_msg_sucesso_csv(const char* nome_arquivo);
// void view_relatorio_msg_erro_arquivo();
// void view_relatorio_msg_cabecalho(const char* titulo);
// void view_relatorio_msg_aguarde();
// void view_relatorio_totalizador(float valor); // Para mostrar totais monetários

// #endif

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

#endif