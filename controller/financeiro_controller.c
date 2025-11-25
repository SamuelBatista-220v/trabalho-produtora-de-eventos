
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "financeiro_controller.h"
#include "../view/view.h"
#include "../view/receber_dados.h"
#include "../view/mostrar_dados.h"

float arredondar_duas_casas(float valor) { // funçao basica de arrendondamento 
    return (float)((int)(valor * 100 + 0.5)) / 100.0;
}

// Função INTELIGENTE para datas (aceita / ou espaco)
void somar_meses_financeiro(char* data_original, int meses, char* destino) {
    int d, m, a;
    // Tenta ler com barras
    if (sscanf(data_original, "%d/%d/%d", &d, &m, &a) != 3) { //sscanf tentar ler tudo seguindo a data_original
        // Se falhar, tenta ler com espaços
        if (sscanf(data_original, "%d %d %d", &d, &m, &a) != 3) {
            strcpy(destino, data_original); // Falhou, entao copia da data original para o destino 
            return;
        }
    }
    
    m += meses;
    while (m > 12) { //se for maior que doze entao começa do 1
        m -= 12;
        a++;
    }
    // Formata padronizado com barras
    sprintf(destino, "%02d/%02d/%04d", d, m, a); //formata a data no destino
}



// remove permaneentemente uma conta da memoria (e bom fazer uma confirmaçao)
void remover_conta_pagar_memoria(ListaContaPagar** lista, int id) {
    ListaContaPagar* atual = *lista; //inicia o ponteiro atual no inicio da lista
    ListaContaPagar* ant = NULL;  //aponta para o primiro no que nao tem ninguem antes dele
    while (atual != NULL) {
        if (atual->conteudo.id == id) {
            if (ant == NULL) *lista = atual->prox;
            else ant->prox = atual->prox;
            free(atual);
            return;
        }
        ant = atual;
        atual = atual->prox;
    }
}
// a mesma coisa so que da lista de contas a receber
void remover_conta_receber_memoria(ListaContaReceber** lista, int id) {
    ListaContaReceber* atual = *lista;
    ListaContaReceber* ant = NULL;
    while (atual != NULL) {
        if (atual->conteudo.id == id) {
            if (ant == NULL) *lista = atual->prox;
            else ant->prox = atual->prox;
            free(atual);
            return;
        }
        ant = atual;
        atual = atual->prox;
    }
}
// Função principal para processar a entrada de uma nota fiscal
void processar_entrada_nota_fiscal(Listarecurso* lista_recursos, ListaContaPagar** lista_pagar, Listaprodutora* lista_produtora, ListaCaixa** lista_caixa) {
    // 1. verificaçao para ver se existe a lista produtora e lista de recrusos. caso nao a retorna erro
    if (lista_produtora == NULL) { view_exibir_mensagem(">> ERRO: Cadastre a Produtora."); return; }
    if (lista_recursos == NULL) { view_exibir_mensagem(">> ERRO: Nenhum recurso cadastrado."); return; }

    float margem_lucro = lista_produtora->conteudo.margem_lucro_padrao;
    if (margem_lucro < 0 || margem_lucro > 1000) margem_lucro = 0; //se for negativo ou muito grande ele zera

    // 2. Leitura Totais  (v de valor)
    float v_prod=0, v_frete=0, v_imp=0;
    view_ler_totais_nota_fiscal(&v_prod, &v_frete, &v_imp);

    // carrinho temporario de itens tipo um buffer 
    ItemCompraTemp itens[100];
    int n_itens = 0;
    int qtd_total_pecas = 0;
    char resumo_desc[300] = "";
     // pq temporario? pq assim o codigo nao sera corrompido se abortar a compra no meio do caminho
    // 3. Loop de Itens
    while (1) {
        printf("\n--- SELECIONAR ITENS DA NOTA ---\n");
        view_imprimir_lista_recurso(lista_recursos);
        
        int id, qtd; float custo;
        if (view_ler_item_nota_fiscal(&id, &qtd, &custo) == 0)  break; //saida do loop

        Listarecurso* rec = buscar_recurso_por_id(lista_recursos, id);
        if (rec) {
            if (qtd <= 0) { view_exibir_mensagem(">> Qtd invalida."); continue; } // se digitar 0 ou numero negativo da erro
            
            itens[n_itens].id = id;
            itens[n_itens].qtd = qtd;
            itens[n_itens].custo = custo;
            strcpy(itens[n_itens].nome, rec->conteudo.descricao); //o buffer temporario citado acima
            
            // Resumo Descricao
            if (strlen(resumo_desc) < 250) {
                strcat(resumo_desc, rec->conteudo.descricao);
                strcat(resumo_desc, ", ");
            }
            //soma de tudo para o frete
            qtd_total_pecas += qtd;
            n_itens++;
            view_exibir_mensagem(">> Item adicionado a lista temporaria.");
        } else view_exibir_mensagem(">> ID nao encontrado.");
    }

    if (n_itens == 0) return;// se sair do loop com zero da erro
    
    // Remove última vírgula
    int len = strlen(resumo_desc); 
    if (len > 2) resumo_desc[len-2] = '\0';

    // CORREÇÃO VISUAL)
    view_imprimir_nota_fiscal_detalhada(itens, n_itens, v_prod, v_frete, v_imp);

    printf("\nConfirma a entrada desta Nota Fiscal? (1-Sim / 0-Cancelar): ");
    if (view_ler_opcao() != 1) return;

    //  Cálculos e Atualização de Estoque
    float frete_un = (qtd_total_pecas > 0) ? v_frete / qtd_total_pecas : 0;
    float imp_un = (qtd_total_pecas > 0) ? v_imp / qtd_total_pecas : 0;
    float total_nota = v_prod + v_frete + v_imp;
// ? e como se fosse um if simplificado
    printf("\n>> Atualizando Estoque e Precos...\n");
    for (int i = 0; i < n_itens; i++) {
        Listarecurso* r = buscar_recurso_por_id(lista_recursos, itens[i].id);
        // r de recruso
        int est_antigo = r->conteudo.quantidade;
        r->conteudo.quantidade += itens[i].qtd;
        r->conteudo.preco_de_custo = itens[i].custo;
        
        float lucro = r->conteudo.preco_de_custo * (margem_lucro / 100.0);
        float novo_preco = r->conteudo.preco_de_custo + frete_un + imp_un + lucro;
        r->conteudo.valor_da_locacao = arredondar_duas_casas(novo_preco);
        
        printf("   [%s] Estoque: %d->%d | Novo Aluguel: R$ %.2f\n", 
               r->conteudo.descricao, est_antigo, r->conteudo.quantidade, r->conteudo.valor_da_locacao);
    }

    // Pagamento (Mantido igual, pois já estava correto com parcelas)
    int forma; char dt_venc[20]; float entrada = 0; int parcelas = 1;
    view_ler_dados_pagamento(&forma, dt_venc, &entrada, &parcelas);

    if (forma == 1) {
        LancamentoCaixa l; l.id=0; l.tipo=2; l.valor=total_nota;
        snprintf(l.descricao, 300, "Compra A VISTA: %s", resumo_desc); // Use snprintf para segurança
        strcpy(l.data, dt_venc);
        inserir_caixa(lista_caixa, l);
        view_exibir_mensagem(">> Pago a vista (Caixa).");
    } else {
        if (entrada > 0) {
            LancamentoCaixa l; l.id=0; l.tipo=2; l.valor=entrada;
            snprintf(l.descricao, 300, "Entrada NF: %s", resumo_desc);
            strcpy(l.data, dt_venc);
            inserir_caixa(lista_caixa, l);
        }

        float restante = total_nota - entrada;
        if (restante > 0) {
            float val_parc = arredondar_duas_casas(restante / parcelas);
            float diferenca = restante - (val_parc * parcelas);

            for (int i = 1; i <= parcelas; i++) {
                ContaPagar cp; 
                cp.id=0; cp.status=0; cp.id_fornecedor=0; strcpy(cp.data_pagamento, "");
                cp.valor_total = (i == parcelas) ? val_parc + diferenca : val_parc;
                
                snprintf(cp.descricao, 300, "Parc %d/%d (%s)", i, parcelas, resumo_desc);
                
                char dt_parc[20];
                somar_meses_financeiro(dt_venc, i-1, dt_parc); // Usa a função corrigida de data
                strcpy(cp.data_vencimento, dt_parc);

                inserir_conta_pagar(lista_pagar, cp);
                printf(" -> Parcela %d: R$ %.2f (Venc: %s)\n", i, cp.valor_total, cp.data_vencimento);
            }
        }
    }
}

// --- FUNÇÕES DE LISTAGEM ---
void listar_contas_financeiras(ListaContaPagar* l_cp, ListaContaReceber* l_cr) {
    view_imprimir_relatorio_financeiro(l_cp, l_cr);
}

// PAGAMENTO DE CONTA remove da lista apos o pagamento
void realizar_pagamento_conta(ListaContaPagar** l_cp, ListaCaixa** l_cx) {
    view_exibir_mensagem("\n=== PAGAR CONTA ===");
    view_exibir_mensagem("ID da Conta:");
    int id = view_ler_opcao();
    
    ListaContaPagar* conta = buscar_conta_pagar_por_id(*l_cp, id);
    
    if (conta) {
        printf("Pagar R$ %.2f? (1-Sim): ", conta->conteudo.valor_total);
        if (view_ler_opcao() == 1) {
            // 1. Lança no Caixa (Histórico)
            LancamentoCaixa lanc; lanc.id=0; lanc.tipo=2; lanc.valor=conta->conteudo.valor_total;
            sprintf(lanc.descricao, "PGTO: %s", conta->conteudo.descricao);
            
            printf("Data (DD/MM/AAAA): "); 
            char buf[20]; fgets(buf, 20, stdin); buf[strcspn(buf, "\n")] = 0;
            strcpy(lanc.data, buf);
            
            inserir_caixa(l_cx, lanc);
            
            // 2. REMOVE DA LISTA DE PENDENTES (CORREÇÃO SOLICITADA)
            remover_conta_pagar_memoria(l_cp, id);
            
            view_exibir_mensagem(">> Pago e removido da lista de pendencias!");
        }
    } else view_exibir_mensagem(">> Conta nao encontrada.");
}

//  RECEBIMENTO DE CONTA AGORA REMOVE DA LISTA
void realizar_recebimento_conta(ListaContaReceber** l_cr, ListaCaixa** l_cx) {
    view_exibir_mensagem("\n=== RECEBER FATURA ===");
    view_exibir_mensagem("ID da Fatura:");
    int id = view_ler_opcao();
    
    ListaContaReceber* conta = buscar_conta_receber_por_id(*l_cr, id);
    
    if (conta) {
        printf("Receber R$ %.2f? (1-Sim): ", conta->conteudo.valor_total);
        if (view_ler_opcao() == 1) {
            // 1. Lança no Caixa (Histórico)
            LancamentoCaixa lanc; lanc.id=0; lanc.tipo=1; lanc.valor=conta->conteudo.valor_total;
            sprintf(lanc.descricao, "RECTO: %s", conta->conteudo.descricao);
            
            printf("Data (DD/MM/AAAA): "); 
            char buf[20]; fgets(buf, 20, stdin); buf[strcspn(buf, "\n")] = 0;
            strcpy(lanc.data, buf);
            
            inserir_caixa(l_cx, lanc);
            
            // 2. REMOVE DA LISTA DE PENDENTES 
            remover_conta_receber_memoria(l_cr, id);
            
            view_exibir_mensagem(">> Recebido e removido da lista!");
        }
    } else view_exibir_mensagem(">> Fatura nao encontrada.");
}

void exibir_extrato_caixa(ListaCaixa* lista) {
    view_imprimir_extrato_caixa_detalhado(lista);
}


void controller_gerenciar_financeiro(ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp, Listarecurso* l_rec, Listaprodutora* l_prod) {
    int opcao = -1;
    do {
        printf("\n=== FINANCEIRO ===\n1. Nota Fiscal (Compra)\n2. Listar Contas Pendentes\n3. Pagar Conta\n4. Receber Fatura\n5. Extrato Caixa\n0. Voltar\nOpcao: ");
        opcao = view_ler_opcao();
        switch(opcao) {
            case 1: processar_entrada_nota_fiscal(l_rec, l_cp, l_prod, l_cx); break;
            case 2: listar_contas_financeiras(*l_cp, *l_cr); break;
            case 3: realizar_pagamento_conta(l_cp, l_cx); break; // Passa endereço da lista
            case 4: realizar_recebimento_conta(l_cr, l_cx); break; // Passa endereço da lista
            case 5: exibir_extrato_caixa(*l_cx); break;
        }
    } while(opcao != 0);
}