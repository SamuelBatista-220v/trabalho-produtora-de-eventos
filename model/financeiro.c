
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "financeiro.h"
// #include "../view/formatacao.h" // Inclua para usar string_para_float_universal

// // Contadores estáticos
// static int id_seq_caixa = 1;
// static int id_seq_receber = 1;
// static int id_seq_pagar = 1;

// // --- INSERÇÃO ---
// StatusOperacao inserir_caixa(ListaCaixa** lista, LancamentoCaixa novo) {
//     ListaCaixa* node = (ListaCaixa*) malloc(sizeof(ListaCaixa));
//     if (!node) return ERRO_ALOCACAO_MEMORIA;
    
//     if (novo.id <= 0) novo.id = id_seq_caixa++;
//     else if (novo.id >= id_seq_caixa) id_seq_caixa = novo.id + 1;

//     node->conteudo = novo;
//     node->prox = NULL;

//     if (*lista == NULL) *lista = node;
//     else {
//         ListaCaixa* aux = *lista;
//         while (aux->prox) aux = aux->prox;
//         aux->prox = node;
//     }
//     return OPERACAO_SUCESSO;
// }

// StatusOperacao inserir_conta_receber(ListaContaReceber** lista, ContaReceber nova) {
//     ListaContaReceber* node = (ListaContaReceber*) malloc(sizeof(ListaContaReceber));
//     if (!node) return ERRO_ALOCACAO_MEMORIA;

//     if (nova.id <= 0) nova.id = id_seq_receber++;
//     else if (nova.id >= id_seq_receber) id_seq_receber = nova.id + 1;

//     node->conteudo = nova;
//     node->prox = NULL;

//     if (*lista == NULL) *lista = node;
//     else {
//         ListaContaReceber* aux = *lista;
//         while (aux->prox) aux = aux->prox;
//         aux->prox = node;
//     }
//     return OPERACAO_SUCESSO;
// }

// StatusOperacao inserir_conta_pagar(ListaContaPagar** lista, ContaPagar nova) {
//     ListaContaPagar* node = (ListaContaPagar*) malloc(sizeof(ListaContaPagar));
//     if (!node) return ERRO_ALOCACAO_MEMORIA;

//     if (nova.id <= 0) nova.id = id_seq_pagar++;
//     else if (nova.id >= id_seq_pagar) id_seq_pagar = nova.id + 1;

//     node->conteudo = nova;
//     node->prox = NULL;

//     if (*lista == NULL) *lista = node;
//     else {
//         ListaContaPagar* aux = *lista;
//         while (aux->prox) aux = aux->prox;
//         aux->prox = node;
//     }
//     return OPERACAO_SUCESSO;
// }

// // --- BUSCAS ---
// ListaContaReceber* buscar_conta_receber_por_id(ListaContaReceber* lista, int id) {
//     while (lista) {
//         if (lista->conteudo.id == id) return lista;
//         lista = lista->prox;
//     }
//     return NULL;
// }

// ListaContaPagar* buscar_conta_pagar_por_id(ListaContaPagar* lista, int id) {
//     while (lista) {
//         if (lista->conteudo.id == id) return lista;
//         lista = lista->prox;
//     }
//     return NULL;
// }

// // --- LIMPEZA ---
// void liberar_listas_financeiro(ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp) {
//     while (*l_cx) { ListaCaixa* t = *l_cx; *l_cx = t->prox; free(t); }
//     while (*l_cr) { ListaContaReceber* t = *l_cr; *l_cr = t->prox; free(t); }
//     while (*l_cp) { ListaContaPagar* t = *l_cp; *l_cp = t->prox; free(t); }
// }

// // --- PERSISTÊNCIA BINÁRIA ---
// StatusOperacao salvar_financeiro_bin(ListaCaixa* l_cx, ListaContaReceber* l_cr, ListaContaPagar* l_cp, const char* nome_arq) {
//     FILE* f = fopen(nome_arq, "wb");
//     if (!f) return ERRO_ABRIR_ARQUIVO;

//     while (l_cx) { fwrite(&l_cx->conteudo, sizeof(LancamentoCaixa), 1, f); l_cx = l_cx->prox; }
//     LancamentoCaixa fim_cx = { .id = -1 }; fwrite(&fim_cx, sizeof(LancamentoCaixa), 1, f);

//     while (l_cr) { fwrite(&l_cr->conteudo, sizeof(ContaReceber), 1, f); l_cr = l_cr->prox; }
//     ContaReceber fim_cr = { .id = -1 }; fwrite(&fim_cr, sizeof(ContaReceber), 1, f);

//     while (l_cp) { fwrite(&l_cp->conteudo, sizeof(ContaPagar), 1, f); l_cp = l_cp->prox; }
//     ContaPagar fim_cp = { .id = -1 }; fwrite(&fim_cp, sizeof(ContaPagar), 1, f);

//     fclose(f);
//     return OPERACAO_SUCESSO;
// }

// StatusOperacao carregar_financeiro_bin(ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp, const char* nome_arq) {
//     FILE* f = fopen(nome_arq, "rb");
//     if (!f) return ERRO_ABRIR_ARQUIVO;

//     liberar_listas_financeiro(l_cx, l_cr, l_cp);
//     id_seq_caixa = 1; id_seq_receber = 1; id_seq_pagar = 1;

//     LancamentoCaixa cx;
//     while (fread(&cx, sizeof(LancamentoCaixa), 1, f) == 1 && cx.id != -1) {
//         inserir_caixa(l_cx, cx);
//         if (cx.id >= id_seq_caixa) id_seq_caixa = cx.id + 1;
//     }

//     ContaReceber cr;
//     while (fread(&cr, sizeof(ContaReceber), 1, f) == 1 && cr.id != -1) {
//         inserir_conta_receber(l_cr, cr);
//         if (cr.id >= id_seq_receber) id_seq_receber = cr.id + 1;
//     }

//     ContaPagar cp;
//     while (fread(&cp, sizeof(ContaPagar), 1, f) == 1 && cp.id != -1) {
//         inserir_conta_pagar(l_cp, cp);
//         if (cp.id >= id_seq_pagar) id_seq_pagar = cp.id + 1;
//     }

//     fclose(f);
//     return OPERACAO_SUCESSO;
// }

// // --- PERSISTÊNCIA TXT ---
// StatusOperacao salvar_financeiro_txt(ListaCaixa* l_cx, ListaContaReceber* l_cr, ListaContaPagar* l_cp) {
//     FILE* f = fopen("db_fin_caixa.csv", "w");
//     if (!f) return ERRO_ABRIR_ARQUIVO;
//     fprintf(f, "ID;Data;Tipo;Valor;Descricao\n"); 
//     while (l_cx) {
//         fprintf(f, "%d;%s;%d;%.2f;%s\n", 
//             l_cx->conteudo.id, l_cx->conteudo.data, l_cx->conteudo.tipo, l_cx->conteudo.valor, l_cx->conteudo.descricao);
//         l_cx = l_cx->prox;
//     }
//     fclose(f);

//     f = fopen("db_fin_pagar.csv", "w");
//     if (!f) return ERRO_ABRIR_ARQUIVO;
//     fprintf(f, "ID;Descricao;Valor;Vencimento;Pagamento;Status\n");
//     while (l_cp) {
//         char* dt_pag = (strlen(l_cp->conteudo.data_pagamento) > 0) ? l_cp->conteudo.data_pagamento : "-";
//         fprintf(f, "%d;%s;%.2f;%s;%s;%d\n", 
//             l_cp->conteudo.id, l_cp->conteudo.descricao, l_cp->conteudo.valor_total, 
//             l_cp->conteudo.data_vencimento, dt_pag, l_cp->conteudo.status);
//         l_cp = l_cp->prox;
//     }
//     fclose(f);

//     f = fopen("db_fin_receber.csv", "w");
//     if (!f) return ERRO_ABRIR_ARQUIVO;
//     fprintf(f, "ID;ClienteID;EventoID;Descricao;Valor;Vencimento;Recebimento;Status\n");
//     while (l_cr) {
//         char* dt_rec = (strlen(l_cr->conteudo.data_recebimento) > 0) ? l_cr->conteudo.data_recebimento : "-";
//         fprintf(f, "%d;%d;%d;%s;%.2f;%s;%s;%d\n", 
//             l_cr->conteudo.id, l_cr->conteudo.id_cliente, l_cr->conteudo.id_evento_origem,
//             l_cr->conteudo.descricao, l_cr->conteudo.valor_total, 
//             l_cr->conteudo.data_vencimento, dt_rec, l_cr->conteudo.status);
//         l_cr = l_cr->prox;
//     }
//     fclose(f);
//     return OPERACAO_SUCESSO;
// }

// // CORREÇÃO CRÍTICA AQUI: Usando strtok e string_para_float_universal
// StatusOperacao carregar_financeiro_txt(ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp) {
//     liberar_listas_financeiro(l_cx, l_cr, l_cp);
//     id_seq_caixa = 1; id_seq_receber = 1; id_seq_pagar = 1;
//     char buffer[1024];

//     // 1. Carregar Caixa
//     FILE* f = fopen("db_fin_caixa.csv", "r");
//     if (f) {
//         fgets(buffer, 1024, f); // Pula cabeçalho
//         while (fgets(buffer, 1024, f)) {
//             buffer[strcspn(buffer, "\n")] = 0;
//             LancamentoCaixa c;
            
//             char* t = strtok(buffer, ";"); if(!t) continue; c.id = atoi(t);
//             t = strtok(NULL, ";"); if(t) strcpy(c.data, t);
//             t = strtok(NULL, ";"); c.tipo = t ? atoi(t) : 0;
//             t = strtok(NULL, ";"); 
//             c.valor = t ? string_para_float_universal(t) : 0.0f; // Universal
            
//             t = strtok(NULL, ";"); if(t) strcpy(c.descricao, t);
            
//             inserir_caixa(l_cx, c);
//             if (c.id >= id_seq_caixa) id_seq_caixa = c.id + 1;
//         }
//         fclose(f);
//     }

//     // 2. Carregar Pagar
//     f = fopen("db_fin_pagar.csv", "r");
//     if (f) {
//         fgets(buffer, 1024, f); 
//         while (fgets(buffer, 1024, f)) {
//             buffer[strcspn(buffer, "\n")] = 0;
//             ContaPagar p;
            
//             char* t = strtok(buffer, ";"); if(!t) continue; p.id = atoi(t);
//             t = strtok(NULL, ";"); if(t) strcpy(p.descricao, t);
//             t = strtok(NULL, ";"); 
//             p.valor_total = t ? string_para_float_universal(t) : 0.0f; // Universal
            
//             t = strtok(NULL, ";"); if(t) strcpy(p.data_vencimento, t);
//             t = strtok(NULL, ";"); if(t) strcpy(p.data_pagamento, t);
//             t = strtok(NULL, ";"); p.status = t ? atoi(t) : 0;

//             if (strcmp(p.data_pagamento, "-") == 0) strcpy(p.data_pagamento, "");
            
//             inserir_conta_pagar(l_cp, p);
//             if (p.id >= id_seq_pagar) id_seq_pagar = p.id + 1;
//         }
//         fclose(f);
//     }

//     // 3. Carregar Receber 
//     f = fopen("db_fin_receber.csv", "r");
//     if (f) {
//         fgets(buffer, 1024, f);
//         while (fgets(buffer, 1024, f)) {
//             buffer[strcspn(buffer, "\n")] = 0;
//             ContaReceber r;
            
//             char* t = strtok(buffer, ";"); if(!t) continue; r.id = atoi(t);
//             t = strtok(NULL, ";"); r.id_cliente = t ? atoi(t) : 0;
//             t = strtok(NULL, ";"); r.id_evento_origem = t ? atoi(t) : 0;
//             t = strtok(NULL, ";"); if(t) strcpy(r.descricao, t);
//             t = strtok(NULL, ";"); 
//             r.valor_total = t ? string_para_float_universal(t) : 0.0f; // Universal
            
//             t = strtok(NULL, ";"); if(t) strcpy(r.data_vencimento, t);
//             t = strtok(NULL, ";"); if(t) strcpy(r.data_recebimento, t);
//             t = strtok(NULL, ";"); r.status = t ? atoi(t) : 0;

//             if (strcmp(r.data_recebimento, "-") == 0) strcpy(r.data_recebimento, "");

//             inserir_conta_receber(l_cr, r);
//             if (r.id >= id_seq_receber) id_seq_receber = r.id + 1;
//         }
//         fclose(f);
//     }

//     return OPERACAO_SUCESSO;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "financeiro.h"
#include "../view/formatacao.h" // Inclua para usar string_para_float_universal

// Contadores estáticos
static int id_seq_caixa = 1;
static int id_seq_receber = 1;
static int id_seq_pagar = 1;

// --- INSERÇÃO (Com proteção de ID) ---

StatusOperacao inserir_caixa(ListaCaixa** lista, LancamentoCaixa novo) {
    ListaCaixa* node = (ListaCaixa*) malloc(sizeof(ListaCaixa));
    if (!node) return ERRO_ALOCACAO_MEMORIA;
    
    // CORREÇÃO DE ID
    if (novo.id > 0) {
        if (novo.id >= id_seq_caixa) id_seq_caixa = novo.id + 1;
    } else {
        novo.id = id_seq_caixa++;
    }

    node->conteudo = novo;
    node->prox = NULL;

    if (*lista == NULL) *lista = node;
    else {
        ListaCaixa* aux = *lista;
        while (aux->prox) aux = aux->prox;
        aux->prox = node;
    }
    return OPERACAO_SUCESSO;
}

StatusOperacao inserir_conta_receber(ListaContaReceber** lista, ContaReceber nova) {
    ListaContaReceber* node = (ListaContaReceber*) malloc(sizeof(ListaContaReceber));
    if (!node) return ERRO_ALOCACAO_MEMORIA;

    // CORREÇÃO DE ID
    if (nova.id > 0) {
        if (nova.id >= id_seq_receber) id_seq_receber = nova.id + 1;
    } else {
        nova.id = id_seq_receber++;
    }

    node->conteudo = nova;
    node->prox = NULL;

    if (*lista == NULL) *lista = node;
    else {
        ListaContaReceber* aux = *lista;
        while (aux->prox) aux = aux->prox;
        aux->prox = node;
    }
    return OPERACAO_SUCESSO;
}

StatusOperacao inserir_conta_pagar(ListaContaPagar** lista, ContaPagar nova) {
    ListaContaPagar* node = (ListaContaPagar*) malloc(sizeof(ListaContaPagar));
    if (!node) return ERRO_ALOCACAO_MEMORIA;

    // CORREÇÃO DE ID
    if (nova.id > 0) {
        if (nova.id >= id_seq_pagar) id_seq_pagar = nova.id + 1;
    } else {
        nova.id = id_seq_pagar++;
    }

    node->conteudo = nova;
    node->prox = NULL;

    if (*lista == NULL) *lista = node;
    else {
        ListaContaPagar* aux = *lista;
        while (aux->prox) aux = aux->prox;
        aux->prox = node;
    }
    return OPERACAO_SUCESSO;
}

// --- BUSCAS ---
ListaContaReceber* buscar_conta_receber_por_id(ListaContaReceber* lista, int id) {
    while (lista) {
        if (lista->conteudo.id == id) return lista;
        lista = lista->prox;
    }
    return NULL;
}

ListaContaPagar* buscar_conta_pagar_por_id(ListaContaPagar* lista, int id) {
    while (lista) {
        if (lista->conteudo.id == id) return lista;
        lista = lista->prox;
    }
    return NULL;
}

// --- LIMPEZA ---
void liberar_listas_financeiro(ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp) {
    while (*l_cx) { ListaCaixa* t = *l_cx; *l_cx = t->prox; free(t); }
    while (*l_cr) { ListaContaReceber* t = *l_cr; *l_cr = t->prox; free(t); }
    while (*l_cp) { ListaContaPagar* t = *l_cp; *l_cp = t->prox; free(t); }
}

// --- PERSISTÊNCIA BINÁRIA ---
StatusOperacao salvar_financeiro_bin(ListaCaixa* l_cx, ListaContaReceber* l_cr, ListaContaPagar* l_cp, const char* nome_arq) {
    FILE* f = fopen(nome_arq, "wb");
    if (!f) return ERRO_ABRIR_ARQUIVO;

    while (l_cx) { fwrite(&l_cx->conteudo, sizeof(LancamentoCaixa), 1, f); l_cx = l_cx->prox; }
    LancamentoCaixa fim_cx = { .id = -1 }; fwrite(&fim_cx, sizeof(LancamentoCaixa), 1, f);

    while (l_cr) { fwrite(&l_cr->conteudo, sizeof(ContaReceber), 1, f); l_cr = l_cr->prox; }
    ContaReceber fim_cr = { .id = -1 }; fwrite(&fim_cr, sizeof(ContaReceber), 1, f);

    while (l_cp) { fwrite(&l_cp->conteudo, sizeof(ContaPagar), 1, f); l_cp = l_cp->prox; }
    ContaPagar fim_cp = { .id = -1 }; fwrite(&fim_cp, sizeof(ContaPagar), 1, f);

    fclose(f);
    return OPERACAO_SUCESSO;
}

StatusOperacao carregar_financeiro_bin(ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp, const char* nome_arq) {
    FILE* f = fopen(nome_arq, "rb");
    if (!f) return ERRO_ABRIR_ARQUIVO;

    liberar_listas_financeiro(l_cx, l_cr, l_cp);
    id_seq_caixa = 1; id_seq_receber = 1; id_seq_pagar = 1;

    LancamentoCaixa cx;
    while (fread(&cx, sizeof(LancamentoCaixa), 1, f) == 1 && cx.id != -1) {
        inserir_caixa(l_cx, cx);
        if (cx.id >= id_seq_caixa) id_seq_caixa = cx.id + 1;
    }

    ContaReceber cr;
    while (fread(&cr, sizeof(ContaReceber), 1, f) == 1 && cr.id != -1) {
        inserir_conta_receber(l_cr, cr);
        if (cr.id >= id_seq_receber) id_seq_receber = cr.id + 1;
    }

    ContaPagar cp;
    while (fread(&cp, sizeof(ContaPagar), 1, f) == 1 && cp.id != -1) {
        inserir_conta_pagar(l_cp, cp);
        if (cp.id >= id_seq_pagar) id_seq_pagar = cp.id + 1;
    }

    fclose(f);
    return OPERACAO_SUCESSO;
}

// --- PERSISTÊNCIA TXT ---
StatusOperacao salvar_financeiro_txt(ListaCaixa* l_cx, ListaContaReceber* l_cr, ListaContaPagar* l_cp) {
    FILE* f = fopen("db_fin_caixa.csv", "w");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    fprintf(f, "ID;Data;Tipo;Valor;Descricao\n"); 
    while (l_cx) {
        fprintf(f, "%d;%s;%d;%.2f;%s\n", 
            l_cx->conteudo.id, l_cx->conteudo.data, l_cx->conteudo.tipo, l_cx->conteudo.valor, l_cx->conteudo.descricao);
        l_cx = l_cx->prox;
    }
    fclose(f);

    f = fopen("db_fin_pagar.csv", "w");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    fprintf(f, "ID;Descricao;Valor;Vencimento;Pagamento;Status\n");
    while (l_cp) {
        char* dt_pag = (strlen(l_cp->conteudo.data_pagamento) > 0) ? l_cp->conteudo.data_pagamento : "-";
        fprintf(f, "%d;%s;%.2f;%s;%s;%d\n", 
            l_cp->conteudo.id, l_cp->conteudo.descricao, l_cp->conteudo.valor_total, 
            l_cp->conteudo.data_vencimento, dt_pag, l_cp->conteudo.status);
        l_cp = l_cp->prox;
    }
    fclose(f);

    f = fopen("db_fin_receber.csv", "w");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    fprintf(f, "ID;ClienteID;EventoID;Descricao;Valor;Vencimento;Recebimento;Status\n");
    while (l_cr) {
        char* dt_rec = (strlen(l_cr->conteudo.data_recebimento) > 0) ? l_cr->conteudo.data_recebimento : "-";
        fprintf(f, "%d;%d;%d;%s;%.2f;%s;%s;%d\n", 
            l_cr->conteudo.id, l_cr->conteudo.id_cliente, l_cr->conteudo.id_evento_origem,
            l_cr->conteudo.descricao, l_cr->conteudo.valor_total, 
            l_cr->conteudo.data_vencimento, dt_rec, l_cr->conteudo.status);
        l_cr = l_cr->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

// CORREÇÃO CRÍTICA AQUI: Usando strtok e string_para_float_universal
StatusOperacao carregar_financeiro_txt(ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp) {
    liberar_listas_financeiro(l_cx, l_cr, l_cp);
    id_seq_caixa = 1; id_seq_receber = 1; id_seq_pagar = 1;
    char buffer[1024];

    // 1. Carregar Caixa
    FILE* f = fopen("db_fin_caixa.csv", "r");
    if (f) {
        fgets(buffer, 1024, f); // Pula cabeçalho
        while (fgets(buffer, 1024, f)) {
            buffer[strcspn(buffer, "\n")] = 0;
            LancamentoCaixa c;
            
            char* t = strtok(buffer, ";"); if(!t) continue; c.id = atoi(t);
            t = strtok(NULL, ";"); if(t) strcpy(c.data, t);
            t = strtok(NULL, ";"); c.tipo = t ? atoi(t) : 0;
            t = strtok(NULL, ";"); 
            c.valor = t ? string_para_float_universal(t) : 0.0f; // Universal
            
            t = strtok(NULL, ";"); if(t) strcpy(c.descricao, t);
            
            inserir_caixa(l_cx, c);
        }
        fclose(f);
    }

    // 2. Carregar Pagar
    f = fopen("db_fin_pagar.csv", "r");
    if (f) {
        fgets(buffer, 1024, f); 
        while (fgets(buffer, 1024, f)) {
            buffer[strcspn(buffer, "\n")] = 0;
            ContaPagar p;
            
            char* t = strtok(buffer, ";"); if(!t) continue; p.id = atoi(t);
            t = strtok(NULL, ";"); if(t) strcpy(p.descricao, t);
            t = strtok(NULL, ";"); 
            p.valor_total = t ? string_para_float_universal(t) : 0.0f; // Universal
            
            t = strtok(NULL, ";"); if(t) strcpy(p.data_vencimento, t);
            t = strtok(NULL, ";"); if(t) strcpy(p.data_pagamento, t);
            t = strtok(NULL, ";"); p.status = t ? atoi(t) : 0;

            if (strcmp(p.data_pagamento, "-") == 0) strcpy(p.data_pagamento, "");
            
            inserir_conta_pagar(l_cp, p);
        }
        fclose(f);
    }

    // 3. Carregar Receber 
    f = fopen("db_fin_receber.csv", "r");
    if (f) {
        fgets(buffer, 1024, f);
        while (fgets(buffer, 1024, f)) {
            buffer[strcspn(buffer, "\n")] = 0;
            ContaReceber r;
            
            char* t = strtok(buffer, ";"); if(!t) continue; r.id = atoi(t);
            t = strtok(NULL, ";"); r.id_cliente = t ? atoi(t) : 0;
            t = strtok(NULL, ";"); r.id_evento_origem = t ? atoi(t) : 0;
            t = strtok(NULL, ";"); if(t) strcpy(r.descricao, t);
            t = strtok(NULL, ";"); 
            r.valor_total = t ? string_para_float_universal(t) : 0.0f; // Universal
            
            t = strtok(NULL, ";"); if(t) strcpy(r.data_vencimento, t);
            t = strtok(NULL, ";"); if(t) strcpy(r.data_recebimento, t);
            t = strtok(NULL, ";"); r.status = t ? atoi(t) : 0;

            if (strcmp(r.data_recebimento, "-") == 0) strcpy(r.data_recebimento, "");

            inserir_conta_receber(l_cr, r);
        }
        fclose(f);
    }

    return OPERACAO_SUCESSO;
}