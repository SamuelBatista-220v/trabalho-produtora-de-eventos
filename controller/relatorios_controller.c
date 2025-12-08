
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> 
#include "relatorios_controller.h"
#include "../view/relatorios_view.h"
#include "../view/mostrar_dados.h"
#include "../view/receber_dados.h"

long helper_data_int(const char* data_str) {
    int d, m, a;
    if (sscanf(data_str, "%d/%d/%d", &d, &m, &a) == 3) return (a*10000)+(m*100)+d;
    if (sscanf(data_str, "%d %d %d", &d, &m, &a) == 3) return (a*10000)+(m*100)+d;
    return 0; 
}

int comparar_clientes_nome(const void* a, const void* b) {
    const Cliente* c1 = *(const Cliente**)a;
    const Cliente* c2 = *(const Cliente**)b;
    if (!c1 || !c2) return 0;

    const char* n1 = (c1->tipo == PESSOA_FISICA) ? c1->doc.pf.nome : c1->doc.pj.razao_social;
    const char* n2 = (c2->tipo == PESSOA_FISICA) ? c2->doc.pf.nome : c2->doc.pj.razao_social;
    return strcmp(n1, n2);
}

void fprintf_money_csv(FILE* f, float valor) {
    char buffer[50];
    sprintf(buffer, "%.2f", valor);
    for(int i=0; buffer[i]; i++) {
        if(buffer[i] == '.') buffer[i] = ','; 
    }
    fprintf(f, "%s", buffer);
}

// --- RELATÓRIOS REFATORADOS ---

// 1. Clientes
void processar_relatorio_clientes(ListaCliente* lista) {
    int ordem = view_relatorio_pedir_tipo_filtro_cliente();
    int destino = view_relatorio_pedir_destino();
    
    int qtd = 0; 
    for(ListaCliente* a = lista; a; a=a->prox) qtd++;
    if(qtd==0) { view_exibir_mensagem("Lista vazia."); return; }

    Cliente** v = malloc(qtd * sizeof(Cliente*));
    if (!v) return;

    int i=0; 
    for(ListaCliente* a = lista; a; a=a->prox) v[i++] = &a->conteudo;

    if (ordem == 2) qsort(v, qtd, sizeof(Cliente*), comparar_clientes_nome);

    FILE* f = NULL;
    if (destino == 2) {
        f = fopen("relatorio_clientes.csv", "w");
        if(f) fprintf(f, "ID;TIPO;NOME_RAZAO;DOC;ENDERECO;TELEFONE;EMAIL;CONTATO;STATUS\n");
    } else {
        view_generico_imprimir_titulo("LISTAGEM DE CLIENTES");
        view_relatorio_imprimir_cabecalho_tabela("ID   | NOME                      | DOCUMENTO       | TELEFONE");
    }

    for(int j=0; j<qtd; j++) {
        if (destino == 1) {
             char* nome = (v[j]->tipo==PESSOA_FISICA) ? v[j]->doc.pf.nome : v[j]->doc.pj.razao_social;
             char* doc = (v[j]->tipo==PESSOA_FISICA) ? v[j]->doc.pf.cpf : v[j]->doc.pj.cnpj;
             
             // CHAMADA DA VIEW PARA LINHA
             view_relatorio_print_linha_cliente(v[j]->id, nome, doc, v[j]->telefone);

        } else if(f) {
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
    else view_generico_imprimir_total((double)qtd, "TOTAL DE REGISTROS");
    
    free(v);
}

// 2. Recursos
void processar_relatorio_recursos_completo(Listarecurso* lista) {
    int filtro = view_relatorio_menu_filtro_recursos();
    char categoria[50] = "";
    if (filtro == 2) view_relatorio_pedir_categoria(categoria);
    int destino = view_relatorio_pedir_destino();

    FILE* f = NULL;
    if (destino == 2) {
        f = fopen("relatorio_recursos.csv", "w");
        if(f) fprintf(f, "ID;DESCRICAO;CATEGORIA;QTD;CUSTO_UN;ALUGUEL_UN;TOTAL_PATRIMONIO;STATUS\n");
    } else {
        view_generico_imprimir_titulo("RECURSOS / ESTOQUE");
        view_relatorio_imprimir_cabecalho_tabela("ID   | DESCRICAO                 | QTD | CUSTO   | LOCACAO");
    }

    float patrimonio_total = 0;

    while(lista) {
        int passa = 1;
        if (filtro == 2 && strstr(lista->conteudo.categoria, categoria) == NULL) passa = 0;
        
        if (passa) {
            float total_item = lista->conteudo.quantidade * lista->conteudo.preco_de_custo;
            patrimonio_total += total_item;

            if(destino == 1) {
                // CHAMADA DA VIEW PARA LINHA
                view_relatorio_print_linha_recurso(
                    lista->conteudo.id, 
                    lista->conteudo.descricao, 
                    lista->conteudo.quantidade, 
                    lista->conteudo.preco_de_custo, 
                    lista->conteudo.valor_da_locacao
                );
            }
            else if(f) {
                recurso* r = &lista->conteudo;
                fprintf(f, "%d;%s;%s;%d;", r->id, r->descricao, r->categoria, r->quantidade);
                fprintf_money_csv(f, r->preco_de_custo); fprintf(f, ";");
                fprintf_money_csv(f, r->valor_da_locacao); fprintf(f, ";");
                fprintf_money_csv(f, total_item); 
                fprintf(f, ";%s\n", r->ativo ? "Ativo" : "Inativo");
            }
        }
        lista = lista->prox;
    }
    if(f) { fclose(f); view_relatorio_msg_sucesso_csv("relatorio_recursos.csv"); }
    else view_generico_imprimir_total(patrimonio_total, "PATRIMONIO TOTAL (Custo)");
}

// 3. Eventos
void processar_relatorio_eventos(ListaOrcamento* lista, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq) {
    int filtro = view_relatorio_menu_filtro_eventos();
    
    int id_cli_filtro = -1;
    int status_filtro = -1;
    long dt_ini = 0, dt_fim = 0;

    if (filtro == 1) id_cli_filtro = view_relatorio_pedir_id("Cliente");
    else if (filtro == 2) {
        char s_ini[20], s_fim[20]; 
        view_relatorio_pedir_periodo(s_ini, s_fim);
        dt_ini = helper_data_int(s_ini); 
        dt_fim = helper_data_int(s_fim);
    }
    else if (filtro == 3) status_filtro = view_relatorio_pedir_status();

    int destino = view_relatorio_pedir_destino();
    view_relatorio_msg_aguarde();

    FILE* f = NULL;
    if (destino == 2) {
        f = fopen("relatorio_eventos.csv", "w");
        if(f) fprintf(f, "ID;CLIENTE;EVENTO;LOCAL;INICIO;FIM;STATUS;TOTAL;ITENS_RECURSOS;ITENS_EQUIPE;ITENS_SERVICOS\n");
    } else view_generico_imprimir_titulo("RELATORIO DE EVENTOS");

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
            
            if (destino == 1) {
                // Aqui usamos a função de impressão já existente na View para orçamentos, pois é detalhada
                view_imprimir_orcamento_unico(o, l_rec, l_for, l_eq);
            } else if(f) {
                char status_str[20];
                if(o->status == 0) strcpy(status_str, "Em Analise");
                else if(o->status == 1) strcpy(status_str, "Aprovado");
                else if(o->status == 2) strcpy(status_str, "Finalizado");
                else strcpy(status_str, "Cancelado");

                fprintf(f, "%d;%d;%s;%s;%02d/%02d/%d;%02d/%02d/%d;%s;", 
                    o->id, o->id_cliente, o->nome_evento, o->local,
                    o->dia_inicio, o->mes_inicio, o->ano_inicio,
                    o->dia_fim, o->mes_fim, o->ano_fim,
                    status_str);
                
                fprintf_money_csv(f, o->valor_total_geral); fprintf(f, ";");

                if(o->qtd_recursos_selecionados == 0) fprintf(f, "NONE");
                else {
                    for(int i=0; i<o->qtd_recursos_selecionados; i++) {
                        fprintf(f, "%d:%d:%.2f|", o->lista_recursos[i].id_recurso, o->lista_recursos[i].quantidade, o->lista_recursos[i].valor_unitario_momento);
                    }
                }
                fprintf(f, ";");

                if(o->qtd_equipe_selecionada == 0) fprintf(f, "NONE");
                else {
                    for(int i=0; i<o->qtd_equipe_selecionada; i++) {
                        fprintf(f, "%d:%d:%.2f|", o->lista_equipe[i].id_membro_equipe, o->lista_equipe[i].dias_trabalhados, o->lista_equipe[i].valor_diaria_momento);
                    }
                }
                fprintf(f, ";");

                if(o->qtd_servicos_selecionados == 0) fprintf(f, "NONE");
                else {
                    for(int i=0; i<o->qtd_servicos_selecionados; i++) {
                        fprintf(f, "%d:%.2f|", o->lista_servicos[i].id_fornecedor, o->lista_servicos[i].valor_combinado);
                    }
                }
                fprintf(f, "\n");
            }
        }
        lista = lista->prox;
    }
    if(f) { fclose(f); view_relatorio_msg_sucesso_csv("relatorio_eventos.csv"); }
    else if(destino == 1) view_relatorio_totalizador(total_geral);
}

// 4. CRONOGRAMA GERAL
void processar_relatorio_cronograma_geral(ListaOrcamento* l_orc, Listarecurso* l_rec) {
    int destino = view_relatorio_pedir_destino(); 
    
    FILE* f = NULL;
    if (destino == 2) {
        f = fopen("relatorio_cronograma.csv", "w");
        if(f) fprintf(f, "DATA_INICIO;DATA_FIM;EVENTO;STATUS;ID_RECURSO;NOME_RECURSO;QTD_ALOCADA\n");
    } else {
        view_generico_imprimir_titulo("CRONOGRAMA DE ALOCACAO");
    }

    int encontrou_algo = 0;

    while (l_orc != NULL) {
        if (l_orc->conteudo.status == 1 || l_orc->conteudo.status == 2) {
            Orcamento* o = &l_orc->conteudo;
            
            for(int i=0; i < o->qtd_recursos_selecionados; i++) {
                encontrou_algo = 1;
                int id_rec = o->lista_recursos[i].id_recurso;
                int qtd = o->lista_recursos[i].quantidade;
                
                char nome_rec[100] = "Recurso Excluido";
                Listarecurso* r = buscar_recurso_por_id(l_rec, id_rec);
                if(r) strcpy(nome_rec, r->conteudo.descricao);

                if (destino == 1) {
                    char data_ini[20], data_fim[20];
                    sprintf(data_ini, "%02d/%02d/%d", o->dia_inicio, o->mes_inicio, o->ano_inicio);
                    sprintf(data_fim, "%02d/%02d/%d", o->dia_fim, o->mes_fim, o->ano_fim);
                    
                    // CHAMADA DA VIEW PARA LINHA
                    view_relatorio_print_linha_cronograma(data_ini, data_fim, o->nome_evento, 
                        (o->status==1?"APROVADO":"FINALIZADO"), id_rec, nome_rec, qtd);

                } else if(f) {
                    fprintf(f, "%02d/%02d/%d;%02d/%02d/%d;%s;%s;%d;%s;%d\n",
                        o->dia_inicio, o->mes_inicio, o->ano_inicio,
                        o->dia_fim, o->mes_fim, o->ano_fim,
                        o->nome_evento, (o->status==1?"APROVADO":"FINALIZADO"),
                        id_rec, nome_rec, qtd);
                }
            }
        }
        l_orc = l_orc->prox;
    }

    if (destino == 2 && f) { 
        fclose(f); 
        view_relatorio_msg_sucesso_csv("relatorio_cronograma.csv"); 
    } else if (destino == 1) {
        if(!encontrou_algo) view_exibir_mensagem("Nenhuma alocacao encontrada em eventos aprovados.");
    }
}

// 5. Relatório Financeiro
void processar_relatorio_financeiro_completo(void* lista, int tipo_conta, ListaCliente* l_cli, Listafornecedor* l_for) {
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
        if(f) {
            if(tipo_conta==1) fprintf(f, "ID;CLIENTE;DESCRICAO;VENCIMENTO;RECEBIMENTO;STATUS;VALOR\n");
            else fprintf(f, "ID;FORNECEDOR;DESCRICAO;VENCIMENTO;PAGAMENTO;STATUS;VALOR\n");
        }
    } else {
        view_generico_imprimir_titulo(tipo_conta==1?"CONTAS A RECEBER":"CONTAS A PAGAR");
        view_relatorio_imprimir_cabecalho_tabela("ID   | ENTIDADE             | VALOR     | VENCIMENTO | STATUS");
    }

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
                
                char nome_cli[100] = "Desconhecido";
                if(l_cli) {
                    ListaCliente* c = buscar_cliente_por_id(l_cli, l->conteudo.id_cliente);
                    if(c) {
                        if(c->conteudo.tipo == PESSOA_FISICA) strcpy(nome_cli, c->conteudo.doc.pf.nome);
                        else strcpy(nome_cli, c->conteudo.doc.pj.razao_social);
                    }
                }

                if(destino==1) {
                    char status_str[20];
                    strcpy(status_str, l->conteudo.status ? "[RECEBIDO]" : "[PENDENTE]");
                    
                    // CHAMADA DA VIEW
                    view_relatorio_print_linha_financeiro(l->conteudo.id, nome_cli, l->conteudo.valor_total, l->conteudo.data_vencimento, status_str);

                } else if(f) {
                    fprintf(f, "%d;%s;%s;%s;%s;%s;", 
                        l->conteudo.id, nome_cli, l->conteudo.descricao, 
                        l->conteudo.data_vencimento, l->conteudo.data_recebimento, 
                        l->conteudo.status ? "PAGO" : "PENDENTE");
                    fprintf_money_csv(f, l->conteudo.valor_total);
                    fprintf(f, "\n");
                }
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
                
                char nome_for[100] = "Despesa/Outros";
                if(l_for && l->conteudo.id_fornecedor > 0) {
                    Listafornecedor* fo = buscar_fornecedor_por_id(l_for, l->conteudo.id_fornecedor);
                    if(fo) strcpy(nome_for, fo->conteudo.nome_fantasia);
                }

                if(destino==1) {
                    char status_str[20];
                    strcpy(status_str, l->conteudo.status ? "[PAGO]" : "[PENDENTE]");
                    
                    // CHAMADA DA VIEW
                    view_relatorio_print_linha_financeiro(l->conteudo.id, nome_for, l->conteudo.valor_total, l->conteudo.data_vencimento, status_str);

                } else if(f) {
                    fprintf(f, "%d;%s;%s;%s;%s;%s;", 
                        l->conteudo.id, nome_for, l->conteudo.descricao, 
                        l->conteudo.data_vencimento, l->conteudo.data_pagamento,
                        l->conteudo.status ? "PAGO" : "PENDENTE");
                    fprintf_money_csv(f, l->conteudo.valor_total);
                    fprintf(f, "\n");
                }
            }
            l = l->prox;
        }
    }
    if(f) { fclose(f); view_relatorio_msg_sucesso_csv(tipo_conta==1?"rel_receber.csv":"rel_pagar.csv"); }
    else view_generico_imprimir_total(total, "VALOR TOTAL ACUMULADO");
}

// 6. Fluxo de Caixa
void processar_relatorio_caixa(ListaCaixa* lista) {
    char s_ini[20], s_fim[20]; view_relatorio_pedir_periodo(s_ini, s_fim);
    long dt_ini = helper_data_int(s_ini);
    long dt_fim = helper_data_int(s_fim);
    int destino = view_relatorio_pedir_destino();

    FILE* f = NULL;
    if (destino == 2) {
        f = fopen("relatorio_caixa.csv", "w");
        if(f) fprintf(f, "ID;DATA;TIPO;DESCRICAO;VALOR\n");
    } else view_generico_imprimir_titulo("FLUXO DE CAIXA");

    float saldo = 0;
    while(lista) {
        long d = helper_data_int(lista->conteudo.data);
        if (d >= dt_ini && d <= dt_fim) {
            float val = lista->conteudo.valor;
            if (lista->conteudo.tipo == 1) saldo += val; else saldo -= val;

            if (destino == 1) {
                // CHAMADA DA VIEW
                view_relatorio_print_linha_caixa(
                    lista->conteudo.data, 
                    (lista->conteudo.tipo==1?"(+)":"(-)"), 
                    val, 
                    lista->conteudo.descricao
                );
            } else if(f) {
                fprintf(f, "%d;%s;%s;%s;", lista->conteudo.id, lista->conteudo.data, (lista->conteudo.tipo==1?"ENTRADA":"SAIDA"), lista->conteudo.descricao);
                fprintf_money_csv(f, val);
                fprintf(f, "\n");
            }
        }
        lista = lista->prox;
    }
    if(f) { fclose(f); view_relatorio_msg_sucesso_csv("relatorio_caixa.csv"); }
    else if (destino == 1) view_relatorio_totalizador(saldo);
}

// 7. Balanço (DRE)
void processar_balanco_financeiro(ListaContaReceber* l_cr, ListaContaPagar* l_cp) {
    view_generico_imprimir_titulo("BALANCO FINANCEIRO (PREVISAO)");
    
    float total_receber = 0, total_recebido = 0;
    while(l_cr) {
        total_receber += l_cr->conteudo.valor_total;
        if(l_cr->conteudo.status == 1) total_recebido += l_cr->conteudo.valor_total;
        l_cr = l_cr->prox;
    }

    float total_pagar = 0, total_pago = 0;
    while(l_cp) {
        total_pagar += l_cp->conteudo.valor_total;
        if(l_cp->conteudo.status == 1) total_pago += l_cp->conteudo.valor_total;
        l_cp = l_cp->prox;
    }

    // CHAMADA DA VIEW
    view_relatorio_print_balanco(total_receber, total_recebido, total_pagar, total_pago);
    
    view_exibir_mensagem("[ENTER] para voltar..."); getchar();
}

// MENU PRINCIPAL
void controller_menu_relatorios(
    ListaCliente* l_cli, ListaOrcamento* l_orc, ListaCaixa* l_cx,
    ListaContaReceber* l_cr, ListaContaPagar* l_cp,
    Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq
) {
    int op = -1;
    do {
        view_exibir_menu_relatorios_principal();
        printf("8. BALANCO GERAL (Lucro)\n"); 
        op = view_ler_opcao();
        switch (op) {
            case 1: processar_relatorio_clientes(l_cli); break;
            case 2: processar_relatorio_eventos(l_orc, l_rec, l_for, l_eq); break;
            case 3: processar_relatorio_recursos_completo(l_rec); break;
            case 4: processar_relatorio_cronograma_geral(l_orc, l_rec); break; 
            case 5: processar_relatorio_financeiro_completo(l_cr, 1, l_cli, l_for); break;
            case 6: processar_relatorio_financeiro_completo(l_cp, 2, l_cli, l_for); break;
            case 7: processar_relatorio_caixa(l_cx); break;
            case 8: processar_balanco_financeiro(l_cr, l_cp); break;
        }
        if(op != 0 && op != 8) { 
            // Pequeno hack de view para pausar, aceitável aqui ou pode ser movido para view_pausar()
            printf("\n[ENTER] para voltar..."); getchar(); 
        }
    } while (op != 0);
}