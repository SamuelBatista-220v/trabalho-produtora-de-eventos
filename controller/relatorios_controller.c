// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "relatorios_controller.h"
// #include "../view/relatorios_view.h"
// #include "../view/mostrar_dados.h" // Reutiliza as views de impressão de itens
// #include "../view/receber_dados.h"

// // --- FUNÇÕES AUXILIARES ---

// // Helper para converter data DD/MM/AAAA em Inteiro YYYYMMDD
// long helper_data_int(const char* data_str) {
//     int d, m, a;
//     if (sscanf(data_str, "%d/%d/%d", &d, &m, &a) != 3) return 0;
//     return (a * 10000) + (m * 100) + d;
// }

// int comparar_clientes_nome(const void* a, const void* b) {
//     Cliente* c1 = *(Cliente**)a;
//     Cliente* c2 = *(Cliente**)b;
//     char* n1 = (c1->tipo == PESSOA_FISICA) ? c1->doc.pf.nome : c1->doc.pj.razao_social;
//     char* n2 = (c2->tipo == PESSOA_FISICA) ? c2->doc.pf.nome : c2->doc.pj.razao_social;
//     return strcmp(n1, n2);
// }

// // --- LÓGICA DE EVENTOS (Completa) ---
// void processar_relatorio_eventos(ListaOrcamento* lista, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq) {
//     int filtro = view_relatorio_menu_filtro_eventos();
//     int destino = view_relatorio_pedir_destino();
    
//     // Variáveis de Filtro
//     int id_cli_filtro = -1;
//     int status_filtro = -1;
//     long dt_ini = 0, dt_fim = 0;

//     if (filtro == 1) id_cli_filtro = view_relatorio_pedir_id("Cliente");
//     else if (filtro == 2) {
//         char s_ini[20], s_fim[20];
//         view_relatorio_pedir_periodo(s_ini, s_fim);
//         dt_ini = helper_data_int(s_ini);
//         dt_fim = helper_data_int(s_fim);
//     }
//     else if (filtro == 3) status_filtro = view_relatorio_pedir_status();

//     view_relatorio_msg_aguarde();

//     FILE* f = NULL;
//     if (destino == 2) {
//         f = fopen("relatorio_eventos.csv", "w");
//         if(f) fprintf(f, "ID;EVENTO;CLIENTE;DATA_INICIO;STATUS;VALOR_TOTAL\n");
//         else { view_relatorio_msg_erro_arquivo(); return; }
//     } else {
//         view_relatorio_msg_cabecalho("EVENTOS");
//     }

//     float total_geral = 0;
//     while(lista) {
//         int passa_filtro = 1;
//         Orcamento* o = &lista->conteudo;
//         long data_evt = (o->ano_inicio * 10000) + (o->mes_inicio * 100) + o->dia_inicio;

//         if (filtro == 1 && o->id_cliente != id_cli_filtro) passa_filtro = 0;
//         if (filtro == 2 && (data_evt < dt_ini || data_evt > dt_fim)) passa_filtro = 0;
//         if (filtro == 3 && o->status != status_filtro) passa_filtro = 0;

//         if (passa_filtro) {
//             total_geral += o->valor_total_geral;
//             if (destino == 1) {
//                 view_imprimir_orcamento_unico(o, l_rec, l_for, l_eq);
//             } else {
//                 fprintf(f, "%d;%s;%d;%02d/%02d/%d;%d;%.2f\n", 
//                     o->id, o->nome_evento, o->id_cliente, 
//                     o->dia_inicio, o->mes_inicio, o->ano_inicio, o->status, o->valor_total_geral);
//             }
//         }
//         lista = lista->prox;
//     }

//     if (destino == 2 && f) { fclose(f); view_relatorio_msg_sucesso_csv("relatorio_eventos.csv"); }
//     else if (destino == 1) view_relatorio_totalizador(total_geral);
// }

// // --- LÓGICA DE CAIXA (Completa) ---
// void processar_relatorio_caixa(ListaCaixa* lista) {
//     char s_ini[20], s_fim[20];
//     view_relatorio_pedir_periodo(s_ini, s_fim);
//     long dt_ini = helper_data_int(s_ini);
//     long dt_fim = helper_data_int(s_fim);
//     int destino = view_relatorio_pedir_destino();

//     FILE* f = NULL;
//     if (destino == 2) {
//         f = fopen("relatorio_caixa.csv", "w");
//         if(f) fprintf(f, "DATA;TIPO;VALOR;DESCRICAO\n");
//     } else {
//         view_relatorio_msg_cabecalho("FLUXO DE CAIXA");
//         printf("DATA       | TIPO | VALOR      | DESCRICAO\n");
//     }

//     float saldo = 0;
//     while(lista) {
//         long d = helper_data_int(lista->conteudo.data);
//         if (d >= dt_ini && d <= dt_fim) {
//             float val = lista->conteudo.valor;
//             if (lista->conteudo.tipo == 1) saldo += val; else saldo -= val;

//             if (destino == 1) {
//                 printf("%-10s | %s  | R$ %8.2f | %s\n", 
//                     lista->conteudo.data, (lista->conteudo.tipo==1?"(+)":"(-)"), val, lista->conteudo.descricao);
//             } else {
//                 fprintf(f, "%s;%d;%.2f;%s\n", lista->conteudo.data, lista->conteudo.tipo, val, lista->conteudo.descricao);
//             }
//         }
//         lista = lista->prox;
//     }

//     if (destino == 2 && f) { fclose(f); view_relatorio_msg_sucesso_csv("relatorio_caixa.csv"); }
//     else if (destino == 1) view_relatorio_totalizador(saldo);
// }

// // --- CLIENTES (Reutilizada e Ajustada) ---
// void processar_relatorio_clientes(ListaCliente* lista) {
//     int ordem = view_relatorio_pedir_tipo_filtro_cliente();
//     int destino = view_relatorio_pedir_destino();
    
//     int qtd = 0; 
//     for(ListaCliente* a = lista; a; a=a->prox) qtd++;
//     if(qtd==0) return;

//     Cliente** v = malloc(qtd * sizeof(Cliente*));
//     int i=0; for(ListaCliente* a = lista; a; a=a->prox) v[i++] = &a->conteudo;

//     if (ordem == 2) qsort(v, qtd, sizeof(Cliente*), comparar_clientes_nome);

//     FILE* f = NULL;
//     if (destino == 2) {
//         f = fopen("relatorio_clientes.csv", "w");
//         fprintf(f, "ID;NOME;DOC;TELEFONE\n");
//     } else view_relatorio_msg_cabecalho("CLIENTES");

//     for(int j=0; j<qtd; j++) {
//         if (destino == 1) {
//              ListaCliente tmp; tmp.conteudo = *v[j]; tmp.prox=NULL;
//              view_imprimir_cliente_unico(&tmp);
//         } else {
//             char* nome = (v[j]->tipo==PESSOA_FISICA) ? v[j]->doc.pf.nome : v[j]->doc.pj.razao_social;
//             char* doc = (v[j]->tipo==PESSOA_FISICA) ? v[j]->doc.pf.cpf : v[j]->doc.pj.cnpj;
//             fprintf(f, "%d;%s;%s;%s\n", v[j]->id, nome, doc, v[j]->telefone);
//         }
//     }
//     if(f) { fclose(f); view_relatorio_msg_sucesso_csv("relatorio_clientes.csv"); }
//     free(v);
// }

// // --- CONTAS A RECEBER/PAGAR ---
// void processar_relatorio_financeiro(void* lista, int tipo_conta) { // 1=Receber, 2=Pagar
//     int filtro = view_relatorio_menu_filtro_financeiro();
//     int id_entidade = -1;
//     long dt_ini=0, dt_fim=0;

//     if (filtro == 1) id_entidade = view_relatorio_pedir_id(tipo_conta==1 ? "Cliente" : "Fornecedor");
//     else {
//         char s1[20], s2[20]; view_relatorio_pedir_periodo(s1, s2);
//         dt_ini = helper_data_int(s1); dt_fim = helper_data_int(s2);
//     }
//     int destino = view_relatorio_pedir_destino();
    
//     // Simplificação: Reutiliza a função de view existente para TELA se não for CSV
//     // Para CSV, precisaria de loop específico. Vamos fazer o loop genérico:
    
//     FILE* f = NULL;
//     if (destino == 2) {
//         f = fopen(tipo_conta==1?"rel_receber.csv":"rel_pagar.csv", "w");
//         fprintf(f, "ID;DESC;VALOR;VENCIMENTO\n");
//     } else view_relatorio_msg_cabecalho(tipo_conta==1?"CONTAS A RECEBER":"CONTAS A PAGAR");

//     float total = 0;
    
//     // Loop genérico é difícil em C sem generics, vamos fazer cast bruto pois structs sao parecidas
//     // ou separar. Separando para segurança:
//     if (tipo_conta == 1) {
//         ListaContaReceber* l = (ListaContaReceber*)lista;
//         while(l) {
//             int passa = 1;
//             long dv = helper_data_int(l->conteudo.data_vencimento);
//             if (filtro==1 && l->conteudo.id_cliente != id_entidade) passa=0;
//             if (filtro==2 && (dv < dt_ini || dv > dt_fim)) passa=0;
            
//             if(passa) {
//                 total += l->conteudo.valor_total;
//                 if(destino==1) printf("ID: %d | R$ %.2f | %s | %s\n", l->conteudo.id, l->conteudo.valor_total, l->conteudo.data_vencimento, l->conteudo.descricao);
//                 else fprintf(f, "%d;%s;%.2f;%s\n", l->conteudo.id, l->conteudo.descricao, l->conteudo.valor_total, l->conteudo.data_vencimento);
//             }
//             l = l->prox;
//         }
//     } else {
//         ListaContaPagar* l = (ListaContaPagar*)lista;
//         while(l) {
//             int passa = 1;
//             long dv = helper_data_int(l->conteudo.data_vencimento);
//             if (filtro==1 && l->conteudo.id_fornecedor != id_entidade) passa=0;
//             if (filtro==2 && (dv < dt_ini || dv > dt_fim)) passa=0;
            
//             if(passa) {
//                 total += l->conteudo.valor_total;
//                 if(destino==1) printf("ID: %d | R$ %.2f | %s | %s\n", l->conteudo.id, l->conteudo.valor_total, l->conteudo.data_vencimento, l->conteudo.descricao);
//                 else fprintf(f, "%d;%s;%.2f;%s\n", l->conteudo.id, l->conteudo.descricao, l->conteudo.valor_total, l->conteudo.data_vencimento);
//             }
//             l = l->prox;
//         }
//     }
//     if(f) fclose(f);
//     else view_relatorio_totalizador(total);
// }
// void processar_relatorio_recursos(Listarecurso* lista) {
//     int filtro = view_relatorio_menu_filtro_recursos();
//     char categoria[50] = "";
//     if (filtro == 2) view_relatorio_pedir_categoria(categoria);
    
//     int destino = view_relatorio_pedir_destino();

//     FILE* f = NULL;
//     if (destino == 2) {
//         f = fopen("relatorio_recursos.csv", "w");
//         fprintf(f, "ID;DESCRICAO;CATEGORIA;QTD;VALOR_LOCACAO\n");
//     } else view_relatorio_msg_cabecalho("RECURSOS / EQUIPAMENTOS");

//     while(lista) {
//         int passa = 1;
//         if (filtro == 2 && strcasecmp(lista->conteudo.categoria, categoria) != 0) passa = 0; // strcasecmp não padrao ANSI, usar strcmp se der erro
        
//         if (passa) {
//             if(destino == 1) view_imprimir_recurso_unico(lista);
//             else fprintf(f, "%d;%s;%s;%d;%.2f\n", lista->conteudo.id, lista->conteudo.descricao, lista->conteudo.categoria, lista->conteudo.quantidade, lista->conteudo.valor_da_locacao);
//         }
//         lista = lista->prox;
//     }
//     if(f) fclose(f);
// }

// // --- MENU PRINCIPAL ---
// void controller_menu_relatorios(
//     ListaCliente* l_cli, ListaOrcamento* l_orc, ListaCaixa* l_cx,
//     ListaContaReceber* l_cr, ListaContaPagar* l_cp,
//     Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq
// ) {
//     int op = -1;
//     do {
//         view_exibir_menu_relatorios_principal();
//         op = view_ler_opcao();
//         switch (op) {
//             case 1: processar_relatorio_clientes(l_cli); break;
//             case 2: processar_relatorio_eventos(l_orc, l_rec, l_for, l_eq); break;
//             case 3: processar_relatorio_recursos(l_rec); break;
//             case 4: printf(">> Cronograma: use a opcao no menu de Orcamentos.\n"); break; // Ja existe no menu 8-5
//             case 5: processar_relatorio_financeiro(l_cr, 1); break;
//             case 6: processar_relatorio_financeiro(l_cp, 2); break;
//             case 7: processar_relatorio_caixa(l_cx); break;
//         }
//         if(op != 0) { printf("\n[ENTER] para voltar..."); getchar(); }
//     } while (op != 0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorios_controller.h"
#include "../view/relatorios_view.h"
#include "../view/mostrar_dados.h"
#include "../view/receber_dados.h"

// --- AUXILIARES ---
long helper_data_int(const char* data_str) {
    int d, m, a;
    if (sscanf(data_str, "%d/%d/%d", &d, &m, &a) != 3) return 0;
    return (a * 10000) + (m * 100) + d;
}

int comparar_clientes_nome(const void* a, const void* b) {
    Cliente* c1 = *(Cliente**)a;
    Cliente* c2 = *(Cliente**)b;
    char* n1 = (c1->tipo == PESSOA_FISICA) ? c1->doc.pf.nome : c1->doc.pj.razao_social;
    char* n2 = (c2->tipo == PESSOA_FISICA) ? c2->doc.pf.nome : c2->doc.pj.razao_social;
    return strcmp(n1, n2);
}

// --- RELATÓRIO DE CLIENTES ---
void processar_relatorio_clientes(ListaCliente* lista) {
    int ordem = view_relatorio_pedir_tipo_filtro_cliente();
    int destino = view_relatorio_pedir_destino();
    
    int qtd = 0; for(ListaCliente* a = lista; a; a=a->prox) qtd++;
    if(qtd==0) { printf(">> Lista vazia.\n"); return; }

    Cliente** v = malloc(qtd * sizeof(Cliente*));
    int i=0; for(ListaCliente* a = lista; a; a=a->prox) v[i++] = &a->conteudo;

    if (ordem == 2) qsort(v, qtd, sizeof(Cliente*), comparar_clientes_nome);

    FILE* f = NULL;
    if (destino == 2) {
        f = fopen("relatorio_clientes.csv", "w");
        // CORREÇÃO: Cabeçalho completo
        fprintf(f, "ID;TIPO;NOME_RAZAO;DOC;ENDERECO;TELEFONE;EMAIL;CONTATO;STATUS\n");
    } else view_relatorio_msg_cabecalho("CLIENTES");

    for(int j=0; j<qtd; j++) {
        if (destino == 1) {
             ListaCliente tmp; tmp.conteudo = *v[j]; tmp.prox=NULL;
             view_imprimir_cliente_unico(&tmp);
        } else {
            // CORREÇÃO: Gravação de todos os campos
            char* nome = (v[j]->tipo==PESSOA_FISICA) ? v[j]->doc.pf.nome : v[j]->doc.pj.razao_social;
            char* doc = (v[j]->tipo==PESSOA_FISICA) ? v[j]->doc.pf.cpf : v[j]->doc.pj.cnpj;
            char* tipo_str = (v[j]->tipo==PESSOA_FISICA) ? "PF" : "PJ";
            
            fprintf(f, "%d;%s;%s;%s;%s;%s;%s;%s;%d\n", 
                v[j]->id, tipo_str, nome, doc, 
                v[j]->endereco_completo, v[j]->telefone, v[j]->email, 
                v[j]->nome_contato, v[j]->ativo);
        }
    }
    if(f) { fclose(f); view_relatorio_msg_sucesso_csv("relatorio_clientes.csv"); }
    free(v);
}

// --- RELATÓRIO DE EVENTOS ---
void processar_relatorio_eventos(ListaOrcamento* lista, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq) {
    int filtro = view_relatorio_menu_filtro_eventos();
    int destino = view_relatorio_pedir_destino();
    
    int id_cli_filtro = -1;
    int status_filtro = -1;
    long dt_ini = 0, dt_fim = 0;

    if (filtro == 1) id_cli_filtro = view_relatorio_pedir_id("Cliente");
    else if (filtro == 2) {
        char s_ini[20], s_fim[20]; view_relatorio_pedir_periodo(s_ini, s_fim);
        dt_ini = helper_data_int(s_ini); dt_fim = helper_data_int(s_fim);
    }
    else if (filtro == 3) status_filtro = view_relatorio_pedir_status();

    view_relatorio_msg_aguarde();

    FILE* f = NULL;
    if (destino == 2) {
        f = fopen("relatorio_eventos.csv", "w");
        // CORREÇÃO: Cabeçalho com Local, Datas e Subtotais
        fprintf(f, "ID;EVENTO;CLIENTE_ID;LOCAL;DATA_INICIO;DATA_FIM;QTD_DIAS;STATUS;TOTAL_RECURSOS;TOTAL_SERVICOS;TOTAL_EQUIPE;VALOR_FINAL\n");
    } else view_relatorio_msg_cabecalho("EVENTOS");

    float total_geral = 0;
    while(lista) {
        int passa = 1;
        Orcamento* o = &lista->conteudo;
        long data_evt = (o->ano_inicio * 10000) + (o->mes_inicio * 100) + o->dia_inicio;

        if (filtro == 1 && o->id_cliente != id_cli_filtro) passa = 0;
        if (filtro == 2 && (data_evt < dt_ini || data_evt > dt_fim)) passa = 0;
        if (filtro == 3 && o->status != status_filtro) passa = 0;

        if (passa) {
            total_geral += o->valor_total_geral;
            if (destino == 1) view_imprimir_orcamento_unico(o, l_rec, l_for, l_eq);
            else {
                // CORREÇÃO: Todos os campos no CSV
                fprintf(f, "%d;%s;%d;%s;%02d/%02d/%d;%02d/%02d/%d;%d;%d;%.2f;%.2f;%.2f;%.2f\n", 
                    o->id, o->nome_evento, o->id_cliente, o->local,
                    o->dia_inicio, o->mes_inicio, o->ano_inicio,
                    o->dia_fim, o->mes_fim, o->ano_fim,
                    o->qtd_dias, o->status,
                    o->valor_total_recursos, o->valor_total_servicos, o->valor_total_equipe,
                    o->valor_total_geral);
            }
        }
        lista = lista->prox;
    }
    if (destino == 2 && f) { fclose(f); view_relatorio_msg_sucesso_csv("relatorio_eventos.csv"); }
    else if (destino == 1) view_relatorio_totalizador(total_geral);
}

// --- RELATÓRIO DE RECURSOS ---
void processar_relatorio_recursos(Listarecurso* lista) {
    int filtro = view_relatorio_menu_filtro_recursos();
    char categoria[50] = "";
    if (filtro == 2) view_relatorio_pedir_categoria(categoria);
    int destino = view_relatorio_pedir_destino();

    FILE* f = NULL;
    if (destino == 2) {
        f = fopen("relatorio_recursos.csv", "w");
        // CORREÇÃO: Custo e Status adicionados
        fprintf(f, "ID;DESCRICAO;CATEGORIA;QTD_ESTOQUE;PRECO_CUSTO;VALOR_LOCACAO;STATUS\n");
    } else view_relatorio_msg_cabecalho("RECURSOS / EQUIPAMENTOS");

    while(lista) {
        int passa = 1;
        // Comparação simples de string (case sensitive para simplificar C puro)
        if (filtro == 2 && strstr(lista->conteudo.categoria, categoria) == NULL) passa = 0;
        
        if (passa) {
            if(destino == 1) view_imprimir_recurso_unico(lista);
            else {
                recurso* r = &lista->conteudo;
                fprintf(f, "%d;%s;%s;%d;%.2f;%.2f;%d\n", 
                    r->id, r->descricao, r->categoria, r->quantidade, 
                    r->preco_de_custo, r->valor_da_locacao, r->ativo);
            }
        }
        lista = lista->prox;
    }
    if(f) { fclose(f); view_relatorio_msg_sucesso_csv("relatorio_recursos.csv"); }
}

// --- RELATÓRIO FINANCEIRO (RECEBER E PAGAR) ---
void processar_relatorio_financeiro(void* lista, int tipo_conta) { 
    int filtro = view_relatorio_menu_filtro_financeiro();
    int id_entidade = -1;
    long dt_ini=0, dt_fim=0;

    if (filtro == 1) id_entidade = view_relatorio_pedir_id(tipo_conta==1 ? "Cliente" : "Fornecedor");
    else {
        char s1[20], s2[20]; view_relatorio_pedir_periodo(s1, s2);
        dt_ini = helper_data_int(s1); dt_fim = helper_data_int(s2);
    }
    int destino = view_relatorio_pedir_destino();
    
    FILE* f = NULL;
    if (destino == 2) {
        f = fopen(tipo_conta==1?"rel_receber.csv":"rel_pagar.csv", "w");
        // CORREÇÃO: Campos detalhados de ID origem e Datas reais
        if(tipo_conta==1) fprintf(f, "ID;ID_CLIENTE;ID_EVENTO;DESCRICAO;VALOR;VENCIMENTO;RECEBIMENTO;STATUS\n");
        else fprintf(f, "ID;ID_FORNECEDOR;DESCRICAO;VALOR;VENCIMENTO;PAGAMENTO;STATUS\n");
    } else view_relatorio_msg_cabecalho(tipo_conta==1?"CONTAS A RECEBER":"CONTAS A PAGAR");

    float total = 0;
    
    if (tipo_conta == 1) { // RECEBER
        ListaContaReceber* l = (ListaContaReceber*)lista;
        while(l) {
            int passa = 1;
            long dv = helper_data_int(l->conteudo.data_vencimento);
            if (filtro==1 && l->conteudo.id_cliente != id_entidade) passa=0;
            if (filtro==2 && (dv < dt_ini || dv > dt_fim)) passa=0;
            
            if(passa) {
                total += l->conteudo.valor_total;
                if(destino==1) printf("ID: %d | Cli: %d | R$ %.2f | Venc: %s | Status: %d\n", 
                    l->conteudo.id, l->conteudo.id_cliente, l->conteudo.valor_total, l->conteudo.data_vencimento, l->conteudo.status);
                else fprintf(f, "%d;%d;%d;%s;%.2f;%s;%s;%d\n", 
                    l->conteudo.id, l->conteudo.id_cliente, l->conteudo.id_evento_origem,
                    l->conteudo.descricao, l->conteudo.valor_total, 
                    l->conteudo.data_vencimento, l->conteudo.data_recebimento, l->conteudo.status);
            }
            l = l->prox;
        }
    } else { // PAGAR
        ListaContaPagar* l = (ListaContaPagar*)lista;
        while(l) {
            int passa = 1;
            long dv = helper_data_int(l->conteudo.data_vencimento);
            if (filtro==1 && l->conteudo.id_fornecedor != id_entidade) passa=0;
            if (filtro==2 && (dv < dt_ini || dv > dt_fim)) passa=0;
            
            if(passa) {
                total += l->conteudo.valor_total;
                if(destino==1) printf("ID: %d | Forn: %d | R$ %.2f | Venc: %s | Status: %d\n", 
                    l->conteudo.id, l->conteudo.id_fornecedor, l->conteudo.valor_total, l->conteudo.data_vencimento, l->conteudo.status);
                else fprintf(f, "%d;%d;%s;%.2f;%s;%s;%d\n", 
                    l->conteudo.id, l->conteudo.id_fornecedor, l->conteudo.descricao, l->conteudo.valor_total, 
                    l->conteudo.data_vencimento, l->conteudo.data_pagamento, l->conteudo.status);
            }
            l = l->prox;
        }
    }
    if(f) fclose(f); else view_relatorio_totalizador(total);
}

// --- RELATÓRIO CAIXA ---
void processar_relatorio_caixa(ListaCaixa* lista) {
    char s_ini[20], s_fim[20]; view_relatorio_pedir_periodo(s_ini, s_fim);
    long dt_ini = helper_data_int(s_ini);
    long dt_fim = helper_data_int(s_fim);
    int destino = view_relatorio_pedir_destino();

    FILE* f = NULL;
    if (destino == 2) {
        f = fopen("relatorio_caixa.csv", "w");
        // CORREÇÃO: ID incluso
        fprintf(f, "ID;DATA;TIPO;VALOR;DESCRICAO\n");
    } else {
        view_relatorio_msg_cabecalho("FLUXO DE CAIXA");
        printf("DATA       | TIPO | VALOR      | DESCRICAO\n");
    }

    float saldo = 0;
    while(lista) {
        long d = helper_data_int(lista->conteudo.data);
        if (d >= dt_ini && d <= dt_fim) {
            float val = lista->conteudo.valor;
            if (lista->conteudo.tipo == 1) saldo += val; else saldo -= val;

            if (destino == 1) {
                printf("%-10s | %s  | R$ %8.2f | %s\n", 
                    lista->conteudo.data, (lista->conteudo.tipo==1?"(+)":"(-)"), val, lista->conteudo.descricao);
            } else {
                fprintf(f, "%d;%s;%d;%.2f;%s\n", 
                    lista->conteudo.id, lista->conteudo.data, lista->conteudo.tipo, val, lista->conteudo.descricao);
            }
        }
        lista = lista->prox;
    }
    if (destino == 2 && f) { fclose(f); view_relatorio_msg_sucesso_csv("relatorio_caixa.csv"); }
    else if (destino == 1) view_relatorio_totalizador(saldo);
}

// --- MENU PRINCIPAL (Integração) ---
void controller_menu_relatorios(
    ListaCliente* l_cli, ListaOrcamento* l_orc, ListaCaixa* l_cx,
    ListaContaReceber* l_cr, ListaContaPagar* l_cp,
    Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq
) {
    int op = -1;
    do {
        view_exibir_menu_relatorios_principal();
        op = view_ler_opcao();
        switch (op) {
            case 1: processar_relatorio_clientes(l_cli); break;
            case 2: processar_relatorio_eventos(l_orc, l_rec, l_for, l_eq); break;
            case 3: processar_relatorio_recursos(l_rec); break;
            case 4: printf(">> Use o menu de Orcamentos para ver Cronograma.\n"); break; 
            case 5: processar_relatorio_financeiro(l_cr, 1); break;
            case 6: processar_relatorio_financeiro(l_cp, 2); break;
            case 7: processar_relatorio_caixa(l_cx); break;
        }
        if(op != 0) { printf("\n[ENTER] para voltar..."); getchar(); }
    } while (op != 0);
}