#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "xml_controller.h"
#include "../view/receber_dados.h"
#include "../view/formatacao.h" 

// --- FUNÇÕES AUXILIARES ---

void trim(char * s) {
    char * p = s;
    int l = strlen(p);
    while(isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;
    memmove(s, p, l + 1);
}

int xml_extrair_tag(const char* linha, const char* tag, char* destino) {
    char tag_ini[100], tag_fim[100];
    sprintf(tag_ini, "<%s>", tag);
    sprintf(tag_fim, "</%s>", tag);

    char* inicio = strstr(linha, tag_ini);
    if (inicio) {
        inicio += strlen(tag_ini);
        char* fim = strstr(inicio, tag_fim);
        if (fim) {
            int len = fim - inicio;
            if(len >= 2000) len = 1999; // Aumentado para caber listas longas
            strncpy(destino, inicio, len);
            destino[len] = '\0';
            trim(destino);
            return 1;
        }
    }
    return 0;
}

// --- EXPORTAÇÃO ---

void exportar_clientes(FILE* f, ListaCliente* lista) {
    fprintf(f, "  <tabela-cliente>\n");
    while(lista) {
        Cliente* c = &lista->conteudo;
        fprintf(f, "    <registro>\n");
        fprintf(f, "      <codigo>%d</codigo>\n", c->id);
        fprintf(f, "      <tipo>%d</tipo>\n", c->tipo);
        if(c->tipo == PESSOA_FISICA) {
            fprintf(f, "      <nome>%s</nome>\n", c->doc.pf.nome);
            fprintf(f, "      <cpf>%s</cpf>\n", c->doc.pf.cpf);
        } else {
            fprintf(f, "      <razao_social>%s</razao_social>\n", c->doc.pj.razao_social);
            fprintf(f, "      <cnpj>%s</cnpj>\n", c->doc.pj.cnpj);
        }
        fprintf(f, "      <endereco>%s</endereco>\n", c->endereco_completo);
        fprintf(f, "      <telefone>%s</telefone>\n", c->telefone);
        fprintf(f, "      <email>%s</email>\n", c->email);
        fprintf(f, "      <nome_contato>%s</nome_contato>\n", c->nome_contato);
        fprintf(f, "      <ativo>%d</ativo>\n", c->ativo);
        fprintf(f, "    </registro>\n");
        lista = lista->prox;
    }
    fprintf(f, "  </tabela-cliente>\n");
}

void exportar_equipamentos(FILE* f, Listarecurso* lista) {
    fprintf(f, "  <tabela-equipamento>\n");
    while(lista) {
        recurso* r = &lista->conteudo;
        fprintf(f, "    <registro>\n");
        fprintf(f, "      <codigo>%d</codigo>\n", r->id);
        fprintf(f, "      <descricao>%s</descricao>\n", r->descricao);
        fprintf(f, "      <categoria>%s</categoria>\n", r->categoria);
        fprintf(f, "      <quantidade_estoque>%d</quantidade_estoque>\n", r->quantidade);
        fprintf(f, "      <preco_custo>%.2f</preco_custo>\n", r->preco_de_custo);
        fprintf(f, "      <valor_locacao>%.2f</valor_locacao>\n", r->valor_da_locacao);
        fprintf(f, "      <ativo>%d</ativo>\n", r->ativo);
        fprintf(f, "    </registro>\n");
        lista = lista->prox;
    }
    fprintf(f, "  </tabela-equipamento>\n");
}

void exportar_eventos(FILE* f, ListaOrcamento* lista) {
    fprintf(f, "  <tabela-evento>\n");
    while(lista) {
        Orcamento* o = &lista->conteudo;
        fprintf(f, "    <registro>\n");
        fprintf(f, "      <codigo_evento>%d</codigo_evento>\n", o->id);
        fprintf(f, "      <nome_evento>%s</nome_evento>\n", o->nome_evento);
        fprintf(f, "      <codigo_cliente>%d</codigo_cliente>\n", o->id_cliente);
        fprintf(f, "      <local>%s</local>\n", o->local);
        fprintf(f, "      <data_inicio>%02d/%02d/%d</data_inicio>\n", o->dia_inicio, o->mes_inicio, o->ano_inicio);
        fprintf(f, "      <data_fim>%02d/%02d/%d</data_fim>\n", o->dia_fim, o->mes_fim, o->ano_fim);
        fprintf(f, "      <status>%d</status>\n", o->status);
        fprintf(f, "      <total>%.2f</total>\n", o->valor_total_geral);
        fprintf(f, "      <ativo>%d</ativo>\n", o->ativo);

        // --- SALVAR ITENS (CORREÇÃO CRÍTICA) ---
        // Recursos
        fprintf(f, "      <itens_recursos>");
        for(int i=0; i<o->qtd_recursos_selecionados; i++) {
            fprintf(f, "%d:%d:%.2f|", o->lista_recursos[i].id_recurso, o->lista_recursos[i].quantidade, o->lista_recursos[i].valor_unitario_momento);
        }
        fprintf(f, "</itens_recursos>\n");

        // Equipe
        fprintf(f, "      <itens_equipe>");
        for(int i=0; i<o->qtd_equipe_selecionada; i++) {
            fprintf(f, "%d:%d:%.2f|", o->lista_equipe[i].id_membro_equipe, o->lista_equipe[i].dias_trabalhados, o->lista_equipe[i].valor_diaria_momento);
        }
        fprintf(f, "</itens_equipe>\n");

        // Servicos
        fprintf(f, "      <itens_servicos>");
        for(int i=0; i<o->qtd_servicos_selecionados; i++) {
            fprintf(f, "%d:%.2f|", o->lista_servicos[i].id_fornecedor, o->lista_servicos[i].valor_combinado);
        }
        fprintf(f, "</itens_servicos>\n");
        // ---------------------------------------

        fprintf(f, "    </registro>\n");
        lista = lista->prox;
    }
    fprintf(f, "  </tabela-evento>\n");
}

void exportar_fornecedores(FILE* f, Listafornecedor* lista) {
    fprintf(f, "  <tabela-fornecedor>\n");
    while(lista) {
        fornecedor* fo = &lista->conteudo;
        fprintf(f, "    <registro>\n");
        fprintf(f, "      <codigo>%d</codigo>\n", fo->id);
        fprintf(f, "      <tipo>%d</tipo>\n", fo->tipoF);
        if(fo->tipoF == PESSOA_FISICA_FOR) fprintf(f, "      <cpf>%s</cpf>\n", fo->docfornecedor.pf.cpf);
        else fprintf(f, "      <cnpj>%s</cnpj>\n", fo->docfornecedor.pj.cnpj);
        
        fprintf(f, "      <nome_fantasia>%s</nome_fantasia>\n", fo->nome_fantasia);
        fprintf(f, "      <razao_social>%s</razao_social>\n", fo->razao_social);
        fprintf(f, "      <endereco>%s</endereco>\n", fo->endereco_completo);
        fprintf(f, "      <telefone>%s</telefone>\n", fo->telefone);
        fprintf(f, "      <tipo_servico>%s</tipo_servico>\n", fo->tipo_servico);
        fprintf(f, "      <ativo>%d</ativo>\n", fo->ativo);
        fprintf(f, "    </registro>\n");
        lista = lista->prox;
    }
    fprintf(f, "  </tabela-fornecedor>\n");
}

void exportar_equipe(FILE* f, Listaequipe* lista) {
    fprintf(f, "  <tabela-equipe>\n");
    while(lista) {
        equipe* e = &lista->conteudo;
        fprintf(f, "    <registro>\n");
        fprintf(f, "      <codigo>%d</codigo>\n", e->id);
        fprintf(f, "      <nome>%s</nome>\n", e->nome);
        fprintf(f, "      <cpf>%s</cpf>\n", e->cpf);
        fprintf(f, "      <funcao>%s</funcao>\n", e->funcao);
        fprintf(f, "      <valor_diaria>%.2f</valor_diaria>\n", e->valor_diaria);
        fprintf(f, "      <ativo>%d</ativo>\n", e->ativo);
        fprintf(f, "    </registro>\n");
        lista = lista->prox;
    }
    fprintf(f, "  </tabela-equipe>\n");
}

void exportar_operadores(FILE* f, Listaoperador* lista) {
    fprintf(f, "  <tabela-operador>\n");
    while(lista) {
        operador* op = &lista->conteudo;
        fprintf(f, "    <registro>\n");
        fprintf(f, "      <codigo>%d</codigo>\n", op->id);
        fprintf(f, "      <nome>%s</nome>\n", op->nome);
        fprintf(f, "      <usuario>%s</usuario>\n", op->usuario);
        fprintf(f, "      <senha>%d</senha>\n", op->senha);
        fprintf(f, "      <ativo>%d</ativo>\n", op->ativo);
        fprintf(f, "    </registro>\n");
        lista = lista->prox;
    }
    fprintf(f, "  </tabela-operador>\n");
}

void exportar_financeiro(FILE* f, ListaCaixa* cx, ListaContaReceber* cr, ListaContaPagar* cp) {
    fprintf(f, "  <financeiro-caixa>\n");
    while(cx) {
        fprintf(f, "    <registro>\n");
        fprintf(f, "      <id>%d</id>\n", cx->conteudo.id);
        fprintf(f, "      <data>%s</data>\n", cx->conteudo.data);
        fprintf(f, "      <descricao>%s</descricao>\n", cx->conteudo.descricao);
        fprintf(f, "      <valor>%.2f</valor>\n", cx->conteudo.valor);
        fprintf(f, "      <tipo>%d</tipo>\n", cx->conteudo.tipo);
        fprintf(f, "    </registro>\n");
        cx = cx->prox;
    }
    fprintf(f, "  </financeiro-caixa>\n");

    fprintf(f, "  <financeiro-receber>\n");
    while(cr) {
        fprintf(f, "    <registro>\n");
        fprintf(f, "      <id>%d</id>\n", cr->conteudo.id);
        fprintf(f, "      <id_cliente>%d</id_cliente>\n", cr->conteudo.id_cliente);
        fprintf(f, "      <id_origem>%d</id_origem>\n", cr->conteudo.id_evento_origem);
        fprintf(f, "      <descricao>%s</descricao>\n", cr->conteudo.descricao);
        fprintf(f, "      <valor>%.2f</valor>\n", cr->conteudo.valor_total);
        fprintf(f, "      <vencimento>%s</vencimento>\n", cr->conteudo.data_vencimento);
        fprintf(f, "      <recebimento>%s</recebimento>\n", cr->conteudo.data_recebimento);
        fprintf(f, "      <status>%d</status>\n", cr->conteudo.status);
        fprintf(f, "    </registro>\n");
        cr = cr->prox;
    }
    fprintf(f, "  </financeiro-receber>\n");

    fprintf(f, "  <financeiro-pagar>\n");
    while(cp) {
        fprintf(f, "    <registro>\n");
        fprintf(f, "      <id>%d</id>\n", cp->conteudo.id);
        fprintf(f, "      <id_fornecedor>%d</id_fornecedor>\n", cp->conteudo.id_fornecedor);
        fprintf(f, "      <descricao>%s</descricao>\n", cp->conteudo.descricao);
        fprintf(f, "      <valor>%.2f</valor>\n", cp->conteudo.valor_total);
        fprintf(f, "      <vencimento>%s</vencimento>\n", cp->conteudo.data_vencimento);
        fprintf(f, "      <pagamento>%s</pagamento>\n", cp->conteudo.data_pagamento);
        fprintf(f, "      <status>%d</status>\n", cp->conteudo.status);
        fprintf(f, "    </registro>\n");
        cp = cp->prox;
    }
    fprintf(f, "  </financeiro-pagar>\n");
}

void executar_exportacao(int selecao,
    ListaCliente* l_cli, Listarecurso* l_rec, ListaOrcamento* l_orc,
    Listafornecedor* l_for, Listaequipe* l_eq, Listaoperador* l_op,
    ListaCaixa* l_cx, ListaContaReceber* l_cr, ListaContaPagar* l_cp) 
{
    FILE* f = fopen("dados_sistema.xml", "w");
    if (!f) { printf(">> Erro ao criar arquivo.\n"); return; }

    fprintf(f, "<dados>\n");
    if (selecao == 1 || selecao == 2) exportar_clientes(f, l_cli);
    if (selecao == 1 || selecao == 3) exportar_equipamentos(f, l_rec);
    if (selecao == 1 || selecao == 4) exportar_eventos(f, l_orc);
    if (selecao == 1 || selecao == 5) exportar_fornecedores(f, l_for);
    if (selecao == 1 || selecao == 6) exportar_equipe(f, l_eq);
    if (selecao == 1 || selecao == 7) exportar_operadores(f, l_op);
    if (selecao == 1 || selecao == 8) exportar_financeiro(f, l_cx, l_cr, l_cp);
    
    fprintf(f, "</dados>\n");
    fclose(f);
    printf("\n>> SUCESSO: Dados exportados para 'dados_sistema.xml'!\n");
}

// --- IMPORTAÇÃO ---

void importar_clientes(FILE* f, ListaCliente** lista) {
    char buffer[2048], valor[500]; // Buffers aumentados
    Cliente t; memset(&t, 0, sizeof(Cliente));
    int dentro = 0;
    while(fgets(buffer, sizeof(buffer), f)) {
        if(strstr(buffer, "</tabela-cliente>")) break;
        if(strstr(buffer, "<registro>")) { dentro=1; memset(&t,0,sizeof(Cliente)); t.ativo=1; }
        else if(strstr(buffer, "</registro>")) { if(dentro) { inserir_cliente(lista, t); dentro=0; } }
        else if(dentro) {
            if(xml_extrair_tag(buffer, "codigo", valor)) t.id = atoi(valor);
            if(xml_extrair_tag(buffer, "tipo", valor)) t.tipo = atoi(valor);
            if(xml_extrair_tag(buffer, "nome", valor)) strcpy(t.doc.pf.nome, valor);
            if(xml_extrair_tag(buffer, "cpf", valor)) strcpy(t.doc.pf.cpf, valor);
            if(xml_extrair_tag(buffer, "razao_social", valor)) strcpy(t.doc.pj.razao_social, valor);
            if(xml_extrair_tag(buffer, "cnpj", valor)) strcpy(t.doc.pj.cnpj, valor);
            if(xml_extrair_tag(buffer, "endereco", valor)) strcpy(t.endereco_completo, valor);
            if(xml_extrair_tag(buffer, "telefone", valor)) strcpy(t.telefone, valor);
            if(xml_extrair_tag(buffer, "email", valor)) strcpy(t.email, valor);
            if(xml_extrair_tag(buffer, "nome_contato", valor)) strcpy(t.nome_contato, valor);
            if(xml_extrair_tag(buffer, "ativo", valor)) t.ativo = atoi(valor);
        }
    }
    printf(">> Clientes importados.\n");
}

void importar_equipamentos(FILE* f, Listarecurso** lista) {
    char buffer[2048], valor[500];
    recurso t; memset(&t, 0, sizeof(recurso));
    int dentro = 0;
    while(fgets(buffer, sizeof(buffer), f)) {
        if(strstr(buffer, "</tabela-equipamento>")) break;
        if(strstr(buffer, "<registro>")) { dentro=1; memset(&t,0,sizeof(recurso)); t.ativo=1; }
        else if(strstr(buffer, "</registro>")) { if(dentro) { inserir_recurso(lista, t); dentro=0; } }
        else if(dentro) {
            if(xml_extrair_tag(buffer, "codigo", valor)) t.id = atoi(valor);
            if(xml_extrair_tag(buffer, "descricao", valor)) strcpy(t.descricao, valor);
            if(xml_extrair_tag(buffer, "categoria", valor)) strcpy(t.categoria, valor);
            if(xml_extrair_tag(buffer, "quantidade_estoque", valor)) t.quantidade = atoi(valor);
            if(xml_extrair_tag(buffer, "preco_custo", valor)) t.preco_de_custo = string_para_float_universal(valor);
            if(xml_extrair_tag(buffer, "valor_locacao", valor)) t.valor_da_locacao = string_para_float_universal(valor);
            if(xml_extrair_tag(buffer, "ativo", valor)) t.ativo = atoi(valor);
        }
    }
    printf(">> Equipamentos importados.\n");
}

void importar_eventos(FILE* f, ListaOrcamento** lista) {
    char buffer[2048], valor[2000]; // Buffer gigante para caber a string de itens
    Orcamento t; memset(&t, 0, sizeof(Orcamento));
    int dentro = 0;
    while(fgets(buffer, sizeof(buffer), f)) {
        if(strstr(buffer, "</tabela-evento>")) break;
        if(strstr(buffer, "<registro>")) { dentro=1; memset(&t,0,sizeof(Orcamento)); t.ativo=1; }
        else if(strstr(buffer, "</registro>")) { 
            if(dentro) { 
                t.qtd_dias = (t.dia_fim - t.dia_inicio) + 1;
                if(t.qtd_dias < 1) t.qtd_dias = 1;
                inserir_orcamento(lista, t); 
                dentro=0; 
            } 
        }
        else if(dentro) {
            if(xml_extrair_tag(buffer, "codigo_evento", valor)) t.id = atoi(valor);
            if(xml_extrair_tag(buffer, "nome_evento", valor)) strcpy(t.nome_evento, valor);
            if(xml_extrair_tag(buffer, "codigo_cliente", valor)) t.id_cliente = atoi(valor);
            if(xml_extrair_tag(buffer, "local", valor)) strcpy(t.local, valor);
            if(xml_extrair_tag(buffer, "status", valor)) t.status = atoi(valor);
            if(xml_extrair_tag(buffer, "total", valor)) t.valor_total_geral = string_para_float_universal(valor);
            if(xml_extrair_tag(buffer, "ativo", valor)) t.ativo = atoi(valor);
            if(xml_extrair_tag(buffer, "data_inicio", valor)) sscanf(valor, "%d/%d/%d", &t.dia_inicio, &t.mes_inicio, &t.ano_inicio);
            if(xml_extrair_tag(buffer, "data_fim", valor)) sscanf(valor, "%d/%d/%d", &t.dia_fim, &t.mes_fim, &t.ano_fim);

            // --- IMPORTAR ITENS (PARSING MANUAL DA STRING) ---
            if(xml_extrair_tag(buffer, "itens_recursos", valor)) {
                char* ptr = valor; int id, qtd, n; float val;
                while(sscanf(ptr, "%d:%d:%f|%n", &id, &qtd, &val, &n) == 3) {
                    if(t.qtd_recursos_selecionados < 50) {
                        int i = t.qtd_recursos_selecionados++;
                        t.lista_recursos[i].id_recurso = id;
                        t.lista_recursos[i].quantidade = qtd;
                        t.lista_recursos[i].valor_unitario_momento = val;
                    }
                    ptr += n;
                }
            }
            if(xml_extrair_tag(buffer, "itens_equipe", valor)) {
                char* ptr = valor; int id, dias, n; float val;
                while(sscanf(ptr, "%d:%d:%f|%n", &id, &dias, &val, &n) == 3) {
                    if(t.qtd_equipe_selecionada < 50) {
                        int i = t.qtd_equipe_selecionada++;
                        t.lista_equipe[i].id_membro_equipe = id;
                        t.lista_equipe[i].dias_trabalhados = dias;
                        t.lista_equipe[i].valor_diaria_momento = val;
                    }
                    ptr += n;
                }
            }
            if(xml_extrair_tag(buffer, "itens_servicos", valor)) {
                char* ptr = valor; int id, n; float val;
                while(sscanf(ptr, "%d:%f|%n", &id, &val, &n) == 2) {
                    if(t.qtd_servicos_selecionados < 50) {
                        int i = t.qtd_servicos_selecionados++;
                        t.lista_servicos[i].id_fornecedor = id;
                        t.lista_servicos[i].valor_combinado = val;
                    }
                    ptr += n;
                }
            }
        }
    }
    printf(">> Eventos importados.\n");
}

void importar_fornecedores(FILE* f, Listafornecedor** lista) {
    char buffer[512], valor[200];
    fornecedor t; memset(&t, 0, sizeof(fornecedor));
    int dentro = 0;
    while(fgets(buffer, sizeof(buffer), f)) {
        if(strstr(buffer, "</tabela-fornecedor>")) break;
        if(strstr(buffer, "<registro>")) { dentro=1; memset(&t,0,sizeof(fornecedor)); t.ativo=1; }
        else if(strstr(buffer, "</registro>")) { if(dentro) { inserir_fornecedor(lista, t); dentro=0; } }
        else if(dentro) {
            if(xml_extrair_tag(buffer, "codigo", valor)) t.id = atoi(valor);
            if(xml_extrair_tag(buffer, "tipo", valor)) t.tipoF = atoi(valor);
            if(xml_extrair_tag(buffer, "cpf", valor)) strcpy(t.docfornecedor.pf.cpf, valor);
            if(xml_extrair_tag(buffer, "cnpj", valor)) strcpy(t.docfornecedor.pj.cnpj, valor);
            if(xml_extrair_tag(buffer, "nome_fantasia", valor)) strcpy(t.nome_fantasia, valor);
            if(xml_extrair_tag(buffer, "razao_social", valor)) strcpy(t.razao_social, valor);
            if(xml_extrair_tag(buffer, "endereco", valor)) strcpy(t.endereco_completo, valor);
            if(xml_extrair_tag(buffer, "telefone", valor)) strcpy(t.telefone, valor);
            if(xml_extrair_tag(buffer, "tipo_servico", valor)) strcpy(t.tipo_servico, valor);
            if(xml_extrair_tag(buffer, "ativo", valor)) t.ativo = atoi(valor);
        }
    }
    printf(">> Fornecedores importados.\n");
}

void importar_equipe(FILE* f, Listaequipe** lista) {
    char buffer[512], valor[200];
    equipe t; memset(&t, 0, sizeof(equipe));
    int dentro = 0;
    while(fgets(buffer, sizeof(buffer), f)) {
        if(strstr(buffer, "</tabela-equipe>")) break;
        if(strstr(buffer, "<registro>")) { dentro=1; memset(&t,0,sizeof(equipe)); t.ativo=1; }
        else if(strstr(buffer, "</registro>")) { if(dentro) { inserir_equipe(lista, t); dentro=0; } }
        else if(dentro) {
            if(xml_extrair_tag(buffer, "codigo", valor)) t.id = atoi(valor);
            if(xml_extrair_tag(buffer, "nome", valor)) strcpy(t.nome, valor);
            if(xml_extrair_tag(buffer, "cpf", valor)) strcpy(t.cpf, valor);
            if(xml_extrair_tag(buffer, "funcao", valor)) strcpy(t.funcao, valor);
            if(xml_extrair_tag(buffer, "valor_diaria", valor)) t.valor_diaria = string_para_float_universal(valor);
            if(xml_extrair_tag(buffer, "ativo", valor)) t.ativo = atoi(valor);
        }
    }
    printf(">> Equipe importada.\n");
}

void importar_operadores(FILE* f, Listaoperador** lista) {
    char buffer[512], valor[200];
    operador t; memset(&t, 0, sizeof(operador));
    int dentro = 0;
    while(fgets(buffer, sizeof(buffer), f)) {
        if(strstr(buffer, "</tabela-operador>")) break;
        if(strstr(buffer, "<registro>")) { dentro=1; memset(&t,0,sizeof(operador)); t.ativo=1; }
        else if(strstr(buffer, "</registro>")) { if(dentro) { inserir_operador(lista, t); dentro=0; } }
        else if(dentro) {
            if(xml_extrair_tag(buffer, "codigo", valor)) t.id = atoi(valor);
            if(xml_extrair_tag(buffer, "nome", valor)) strcpy(t.nome, valor);
            if(xml_extrair_tag(buffer, "usuario", valor)) strcpy(t.usuario, valor);
            if(xml_extrair_tag(buffer, "senha", valor)) t.senha = atoi(valor);
            if(xml_extrair_tag(buffer, "ativo", valor)) t.ativo = atoi(valor);
        }
    }
    printf(">> Operadores importados.\n");
}

void importar_financeiro(FILE* f, ListaCaixa** cx, ListaContaReceber** cr, ListaContaPagar** cp) {
    char buffer[512], valor[200];
    LancamentoCaixa c; int dentroC = 0;
    ContaReceber r; int dentroR = 0;
    ContaPagar p; int dentroP = 0;

    while(fgets(buffer, sizeof(buffer), f)) {
        if(strstr(buffer, "</dados>")) break;

        if(strstr(buffer, "<financeiro-caixa>")) continue; 
        if(strstr(buffer, "<financeiro-receber>")) { dentroC=0; continue; }
        if(strstr(buffer, "<financeiro-pagar>")) { dentroR=0; continue; }

        if(strstr(buffer, "<registro>")) { 
            if(strstr(buffer, "<financeiro-caixa>") || (!dentroR && !dentroP)) { dentroC=1; memset(&c,0,sizeof(LancamentoCaixa)); }
            else if(dentroR) memset(&r,0,sizeof(ContaReceber));
            else if(dentroP) memset(&p,0,sizeof(ContaPagar));
            continue;
        }

        if(strstr(buffer, "</registro>")) {
            if(dentroC) { inserir_caixa(cx, c); dentroC=0; }
            if(dentroR) { inserir_conta_receber(cr, r); dentroR=0; }
            if(dentroP) { inserir_conta_pagar(cp, p); dentroP=0; }
            continue;
        }

        if(dentroC) {
            if(xml_extrair_tag(buffer, "id", valor)) c.id = atoi(valor);
            if(xml_extrair_tag(buffer, "data", valor)) strcpy(c.data, valor);
            if(xml_extrair_tag(buffer, "descricao", valor)) strcpy(c.descricao, valor);
            if(xml_extrair_tag(buffer, "valor", valor)) c.valor = string_para_float_universal(valor);
            if(xml_extrair_tag(buffer, "tipo", valor)) c.tipo = atoi(valor);
        }
        if(dentroR) {
            if(xml_extrair_tag(buffer, "id", valor)) r.id = atoi(valor);
            if(xml_extrair_tag(buffer, "id_cliente", valor)) r.id_cliente = atoi(valor);
            if(xml_extrair_tag(buffer, "id_origem", valor)) r.id_evento_origem = atoi(valor);
            if(xml_extrair_tag(buffer, "descricao", valor)) strcpy(r.descricao, valor);
            if(xml_extrair_tag(buffer, "valor", valor)) r.valor_total = string_para_float_universal(valor);
            if(xml_extrair_tag(buffer, "vencimento", valor)) strcpy(r.data_vencimento, valor);
            if(xml_extrair_tag(buffer, "recebimento", valor)) strcpy(r.data_recebimento, valor);
            if(xml_extrair_tag(buffer, "status", valor)) r.status = atoi(valor);
        }
        if(dentroP) {
            if(xml_extrair_tag(buffer, "id", valor)) p.id = atoi(valor);
            if(xml_extrair_tag(buffer, "id_fornecedor", valor)) p.id_fornecedor = atoi(valor);
            if(xml_extrair_tag(buffer, "descricao", valor)) strcpy(p.descricao, valor);
            if(xml_extrair_tag(buffer, "valor", valor)) p.valor_total = string_para_float_universal(valor);
            if(xml_extrair_tag(buffer, "vencimento", valor)) strcpy(p.data_vencimento, valor);
            if(xml_extrair_tag(buffer, "pagamento", valor)) strcpy(p.data_pagamento, valor);
            if(xml_extrair_tag(buffer, "status", valor)) p.status = atoi(valor);
        }
    }
    printf(">> Financeiro importado.\n");
}

void executar_importacao(int selecao,
    ListaCliente** l_cli, Listarecurso** l_rec, ListaOrcamento** l_orc,
    Listafornecedor** l_for, Listaequipe** l_eq, Listaoperador** l_op,
    ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp) 
{
    FILE* f = fopen("dados_sistema.xml", "r");
    if (!f) { printf(">> Erro: Arquivo 'dados_sistema.xml' nao encontrado.\n"); return; }

    char buffer[2048];
    printf("\n>> Iniciando IMPORTACAO SELETIVA...\n");

    if (selecao == 1 || selecao == 2) { fseek(f, 0, SEEK_SET); while(fgets(buffer,2048,f)) if(strstr(buffer,"<tabela-cliente>")) importar_clientes(f, l_cli); }
    if (selecao == 1 || selecao == 3) { fseek(f, 0, SEEK_SET); while(fgets(buffer,2048,f)) if(strstr(buffer,"<tabela-equipamento>")) importar_equipamentos(f, l_rec); }
    if (selecao == 1 || selecao == 4) { fseek(f, 0, SEEK_SET); while(fgets(buffer,2048,f)) if(strstr(buffer,"<tabela-evento>")) importar_eventos(f, l_orc); }
    if (selecao == 1 || selecao == 5) { fseek(f, 0, SEEK_SET); while(fgets(buffer,2048,f)) if(strstr(buffer,"<tabela-fornecedor>")) importar_fornecedores(f, l_for); }
    if (selecao == 1 || selecao == 6) { fseek(f, 0, SEEK_SET); while(fgets(buffer,2048,f)) if(strstr(buffer,"<tabela-equipe>")) importar_equipe(f, l_eq); }
    if (selecao == 1 || selecao == 7) { fseek(f, 0, SEEK_SET); while(fgets(buffer,2048,f)) if(strstr(buffer,"<tabela-operador>")) importar_operadores(f, l_op); }
    if (selecao == 1 || selecao == 8) { fseek(f, 0, SEEK_SET); importar_financeiro(f, l_cx, l_cr, l_cp); }

    fclose(f);
    printf(">> Importacao Concluida!\n");
}

void controller_menu_xml(
    ListaCliente** l_cli, Listarecurso** l_rec, ListaOrcamento** l_orc,
    Listafornecedor** l_for, Listaequipe** l_eq, Listaoperador** l_op,
    ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp
) {
    int opcao = 0;
    do {
        printf("\n=== IMPORTACAO E EXPORTACAO (XML) ===\n");
        printf("1. Exportar Dados (Gerar XML)\n");
        printf("2. Importar Dados (Ler XML)\n");
        printf("0. Voltar\n");
        opcao = view_ler_opcao();

        if (opcao == 1 || opcao == 2) {
            int sub_op = 0;
            printf("\n--- Selecione a Tabela ---\n");
            printf("1. TUDO (Backup Completo)\n");
            printf("2. Clientes\n");
            printf("3. Equipamentos (Recursos)\n");
            printf("4. Eventos (Orcamentos)\n");
            printf("5. Fornecedores\n");
            printf("6. Equipe\n");
            printf("7. Operadores\n");
            printf("8. Financeiro (Caixa e Contas)\n");
            printf("0. Cancelar\n");
            sub_op = view_ler_opcao();

            if (sub_op > 0 && sub_op <= 8) {
                if (opcao == 1) executar_exportacao(sub_op, *l_cli, *l_rec, *l_orc, *l_for, *l_eq, *l_op, *l_cx, *l_cr, *l_cp);
                else            executar_importacao(sub_op, l_cli, l_rec, l_orc, l_for, l_eq, l_op, l_cx, l_cr, l_cp);
            }
        }
    } while (opcao != 0);
}