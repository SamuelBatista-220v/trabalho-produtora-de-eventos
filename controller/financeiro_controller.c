
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>
// #include "financeiro_controller.h"
// #include "../view/view.h"
// #include "../view/receber_dados.h"
// #include "../view/mostrar_dados.h"

// // --- FUNÇÕES AUXILIARES ---

// float arredondar_duas_casas(float valor) {
//     return (float)((int)(valor * 100 + 0.5)) / 100.0;
// }

// // Função simples para somar meses a uma data DD/MM/AAAA
// void adicionar_meses_data(char* data_original, int meses_a_somar, char* data_destino) {
//     int d, m, a;
//     if (sscanf(data_original, "%d/%d/%d", &d, &m, &a) != 3) {
//         strcpy(data_destino, data_original); // Erro, mantem original
//         return;
//     }
    
//     m += meses_a_somar;
//     while (m > 12) {
//         m -= 12;
//         a++;
//     }
//     sprintf(data_destino, "%02d/%02d/%04d", d, m, a);
// }



// void processar_entrada_nota_fiscal(Listarecurso* lista_recursos, ListaContaPagar** lista_pagar, Listaprodutora* lista_produtora, ListaCaixa** lista_caixa) {
//     if (lista_produtora == NULL) {
//         view_exibir_mensagem(">> ERRO: Cadastre a Produtora primeiro.");
//         return;
//     }
//     if (lista_recursos == NULL) {
//         view_exibir_mensagem(">> ERRO: Nenhum recurso cadastrado.");
//         return;
//     }

//     float margem_lucro_percentual = lista_produtora->conteudo.margem_lucro_padrao;
//     // Proteção contra lixo de memória: Se a margem for negativa ou absurda, zera.
//     if (margem_lucro_percentual < 0 || margem_lucro_percentual > 1000) margem_lucro_percentual = 0;

//     view_exibir_mensagem("\n=== ENTRADA DE NOTA FISCAL ===");
    
//     float valor_total_produtos = 0, valor_frete = 0, valor_impostos = 0;
//     char buffer[50];

//     printf("Valor Total dos Produtos (R$): "); fgets(buffer, 50, stdin); valor_total_produtos = atof(buffer);
//     printf("Valor Total do Frete (R$): "); fgets(buffer, 50, stdin); valor_frete = atof(buffer);
//     printf("Valor Total de Impostos (R$): "); fgets(buffer, 50, stdin); valor_impostos = atof(buffer);

//     // Inicializa struct com zeros para evitar lixo de memória
//     struct { int id_rec; int qtd; float custo_unitario; char nome[100]; } itens_nota[100];
//     memset(itens_nota, 0, sizeof(itens_nota));

//     int qtd_itens_distintos = 0;
//     int soma_quantidade_total_unidades = 0;
//     char resumo_itens[250] = ""; // String para guardar nomes dos produtos

//     while (1) {
//         printf("\n--- RECURSOS DISPONIVEIS ---\n");
//         view_imprimir_lista_recurso(lista_recursos);
        
//         printf("\nDigite o ID do Recurso (0 para encerrar): ");
//         int id = view_ler_opcao();
//         if (id == 0) break;

//         Listarecurso* rec = buscar_recurso_por_id(lista_recursos, id);
//         if (rec) {
//             printf("Quantidade: "); int qtd = view_ler_opcao();
//             if (qtd <= 0) continue;

//             printf("Preco de Custo Unitario (R$): "); fgets(buffer, 50, stdin); float custo = atof(buffer);

//             itens_nota[qtd_itens_distintos].id_rec = id;
//             itens_nota[qtd_itens_distintos].qtd = qtd;
//             itens_nota[qtd_itens_distintos].custo_unitario = custo;
//             strcpy(itens_nota[qtd_itens_distintos].nome, rec->conteudo.descricao);
            
//             // Concatena nome para a descrição da conta (Ex: "Som, Luz")
//             if (strlen(resumo_itens) < 200) { // Proteção de tamanho
//                 strcat(resumo_itens, rec->conteudo.descricao);
//                 strcat(resumo_itens, ", ");
//             }

//             soma_quantidade_total_unidades += qtd;
//             qtd_itens_distintos++;
//         } else {
//             view_exibir_mensagem(">> Recurso nao encontrado!");
//         }
//     }

//     if (qtd_itens_distintos == 0) return;

//     // Remove a última vírgula da string de resumo
//     int len = strlen(resumo_itens);
//     if (len > 2) resumo_itens[len-2] = '\0';

//     // CÁLCULOS
//     float valor_total_nota = valor_total_produtos + valor_frete + valor_impostos;
//     float frete_por_unidade = (soma_quantidade_total_unidades > 0) ? valor_frete / soma_quantidade_total_unidades : 0;
//     float imposto_por_unidade = (soma_quantidade_total_unidades > 0) ? valor_impostos / soma_quantidade_total_unidades : 0;

//     for (int i = 0; i < qtd_itens_distintos; i++) {
//         Listarecurso* rec = buscar_recurso_por_id(lista_recursos, itens_nota[i].id_rec);
        
//         rec->conteudo.quantidade += itens_nota[i].qtd;
//         rec->conteudo.preco_de_custo = itens_nota[i].custo_unitario;

//         float valor_lucro = rec->conteudo.preco_de_custo * (margem_lucro_percentual / 100.0);
//         float novo_preco_locacao = rec->conteudo.preco_de_custo + frete_por_unidade + imposto_por_unidade + valor_lucro;
        
//         rec->conteudo.valor_da_locacao = arredondar_duas_casas(novo_preco_locacao);
        
//         printf("   [ID %d] %s: Estoque %d -> %d | Novo Aluguel: R$ %.2f\n", 
//                rec->conteudo.id, rec->conteudo.descricao, 
//                rec->conteudo.quantidade - itens_nota[i].qtd, rec->conteudo.quantidade, 
//                rec->conteudo.valor_da_locacao);
//     }

//     // PAGAMENTO
//     printf("\n1. A Vista | 2. A Prazo: ");
//     int forma = view_ler_opcao();
    
//     printf("Data base (DD/MM/AAAA): ");
//     char data_venc[20]; fgets(data_venc, 20, stdin); data_venc[strcspn(data_venc, "\n")] = 0;

//     if (forma == 1) {
//         LancamentoCaixa lanc;
//         lanc.id = 0; lanc.tipo = 2; lanc.valor = valor_total_nota;
//         sprintf(lanc.descricao, "Compra: %s", resumo_itens); // <--- DESCRIÇÃO DETALHADA
//         strcpy(lanc.data, data_venc);
//         inserir_caixa(lista_caixa, lanc);
//         view_exibir_mensagem(">> Pago a vista.");
//     } else {
//         // A PRAZO (Simplificado: 1 parcela no vencimento)
//         ContaPagar cp;
//         cp.id = 0; cp.status = 0; cp.id_fornecedor = 0; strcpy(cp.data_pagamento, "");
//         cp.valor_total = valor_total_nota;
//         strcpy(cp.data_vencimento, data_venc);
        
//         // CRIA A DESCRIÇÃO DETALHADA NA CONTA
//         sprintf(cp.descricao, "NF (%s)", resumo_itens); 
        
//         inserir_conta_pagar(lista_pagar, cp);
//         printf(">> Conta a Pagar gerada: %s | R$ %.2f\n", cp.descricao, cp.valor_total);
//     }
// }


// void listar_contas_financeiras(ListaContaPagar* l_cp, ListaContaReceber* l_cr) {
//     printf("\n=== RELATORIO FINANCEIRO ===\n");
//     printf("\n--- CONTAS A PAGAR ---\n");
//     while(l_cp) {
//         printf(" ID: %d | Desc: %-20s | Valor: R$ %8.2f | Venc: %s | %s\n", 
//                l_cp->conteudo.id, l_cp->conteudo.descricao, l_cp->conteudo.valor_total, l_cp->conteudo.data_vencimento, l_cp->conteudo.status ? "[PAGO]" : "[PENDENTE]");
//         l_cp = l_cp->prox;
//     }
//     printf("\n--- CONTAS A RECEBER ---\n");
//     while(l_cr) {
//         printf(" ID: %d | Desc: %-20s | Valor: R$ %8.2f | Venc: %s | %s\n", 
//                l_cr->conteudo.id, l_cr->conteudo.descricao, l_cr->conteudo.valor_total, l_cr->conteudo.data_vencimento, l_cr->conteudo.status ? "[RECEBIDO]" : "[PENDENTE]");
//         l_cr = l_cr->prox;
//     }
// }

// void realizar_pagamento_conta(ListaContaPagar* l_cp, ListaCaixa** l_cx) {
//     view_exibir_mensagem("\n=== PAGAR CONTA (SAIDA) ===");
//     view_exibir_mensagem("Digite o ID da Conta a Pagar:");
//     int id = view_ler_opcao();
    
//     ListaContaPagar* conta = buscar_conta_pagar_por_id(l_cp, id);
    
//     if (conta) {
//         if (conta->conteudo.status == 1) {
//             view_exibir_mensagem(">> Erro: Esta conta ja foi paga.");
//             return;
//         }

//         printf("Pagar R$ %.2f referente a '%s'? (1-Sim/0-Nao): ", conta->conteudo.valor_total, conta->conteudo.descricao);
//         if (view_ler_opcao() == 1) {
//             conta->conteudo.status = 1; 
//             LancamentoCaixa lanc;
//             lanc.id = 0; lanc.tipo = 2; // Saída
//             lanc.valor = conta->conteudo.valor_total;
//             sprintf(lanc.descricao, "PGTO Conta #%d (%s)", id, conta->conteudo.descricao);
            
//             printf("Data do Pagamento (DD/MM/AAAA): ");
//             char buffer[20]; fgets(buffer, 20, stdin); buffer[strcspn(buffer, "\n")] = 0;
//             strcpy(lanc.data, buffer);
//             strcpy(conta->conteudo.data_pagamento, buffer);

//             inserir_caixa(l_cx, lanc);
//             view_exibir_mensagem(">> SUCESSO: Pagamento registrado no Caixa.");
//         }
//     } else {
//         view_exibir_mensagem(">> Conta nao encontrada.");
//     }
// }

// void realizar_recebimento_conta(ListaContaReceber* l_cr, ListaCaixa** l_cx) {
//     view_exibir_mensagem("\n=== RECEBER DE CLIENTE (ENTRADA) ===");
//     view_exibir_mensagem("Digite o ID da Fatura/Conta a Receber:");
//     int id = view_ler_opcao();
    
//     ListaContaReceber* conta = buscar_conta_receber_por_id(l_cr, id);
    
//     if (conta) {
//         if (conta->conteudo.status == 1) {
//             view_exibir_mensagem(">> Erro: Esta conta ja foi recebida.");
//             return;
//         }

//         printf("Receber R$ %.2f referente a '%s'? (1-Sim/0-Nao): ", conta->conteudo.valor_total, conta->conteudo.descricao);
//         if (view_ler_opcao() == 1) {
//             conta->conteudo.status = 1; // Pago
//             LancamentoCaixa lanc;
//             lanc.id = 0; lanc.tipo = 1; // Entrada
//             lanc.valor = conta->conteudo.valor_total;
//             sprintf(lanc.descricao, "RECTO Fatura #%d (%s)", id, conta->conteudo.descricao);
            
//             printf("Data do Recebimento (DD/MM/AAAA): ");
//             char buffer[20]; fgets(buffer, 20, stdin); buffer[strcspn(buffer, "\n")] = 0;
//             strcpy(lanc.data, buffer);
//             strcpy(conta->conteudo.data_recebimento, buffer);

//             inserir_caixa(l_cx, lanc);
//             view_exibir_mensagem(">> SUCESSO: Recebimento registrado no Caixa.");
//         }
//     } else {
//         view_exibir_mensagem(">> Conta nao encontrada.");
//     }
// }

// void exibir_extrato_caixa(ListaCaixa* lista) {
//     float saldo = 0;
//     printf("\n=== EXTRATO DE CAIXA ===\n");
//     if (lista == NULL) printf("   (Nenhuma movimentacao registrada)\n");

//     while (lista) {
//         char* tipo = (lista->conteudo.tipo == 1) ? "ENTRADA (+)" : "SAIDA   (-)";
//         float val = lista->conteudo.valor;
//         if (lista->conteudo.tipo == 1) saldo += val; else saldo -= val;

//         printf("[%s] %s R$ %8.2f | %s\n", 
//                lista->conteudo.data, tipo, val, lista->conteudo.descricao);
//         lista = lista->prox;
//     }
//     printf("--------------------------------\n");
//     printf("SALDO ATUAL: R$ %.2f\n", saldo);
//     printf("================================\n");
// }

// void controller_gerenciar_financeiro(ListaCaixa** l_cx, ListaContaReceber** l_cr, ListaContaPagar** l_cp, Listarecurso* l_rec, Listaprodutora* l_prod) {
//     int opcao = -1;
//     do {
//         printf("\n=== MODULO FINANCEIRO & ESTOQUE ===\n");
//         printf("1. Entrada de Nota Fiscal (Compra de Estoque)\n");
//         printf("2. Listar Contas (Pagar/Receber)\n");
//         printf("3. Pagar Conta (Baixa de Divida)\n");
//         printf("4. Receber de Cliente (Baixa de Fatura)\n");
//         printf("5. Ver Extrato de Caixa\n");
//         printf("0. Voltar\n");
//         printf("Opcao: ");
//         opcao = view_ler_opcao();
//         switch(opcao) {
//             case 1: processar_entrada_nota_fiscal(l_rec, l_cp, l_prod, l_cx); break;
//             case 2: listar_contas_financeiras(*l_cp, *l_cr); break;
//             case 3: realizar_pagamento_conta(*l_cp, l_cx); break;
//             case 4: realizar_recebimento_conta(*l_cr, l_cx); break;
//             case 5: exibir_extrato_caixa(*l_cx); break;
//         }
//     } while(opcao != 0);
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "financeiro_controller.h"
#include "../view/view.h"
#include "../view/receber_dados.h"
#include "../view/mostrar_dados.h"

float arredondar_duas_casas(float valor) {
    return (float)((int)(valor * 100 + 0.5)) / 100.0;
}

// Função INTELIGENTE para datas (aceita / ou espaco)
// Ex: 10/01/2025 + 1 mês -> 10/02/2025
void somar_meses_financeiro(char* data_original, int meses, char* destino) {
    int d, m, a;
    // Tenta ler com barras
    if (sscanf(data_original, "%d/%d/%d", &d, &m, &a) != 3) {
        // Se falhar, tenta ler com espaços
        if (sscanf(data_original, "%d %d %d", &d, &m, &a) != 3) {
            strcpy(destino, data_original); // Falhou, mantem original
            return;
        }
    }
    
    m += meses;
    while (m > 12) {
        m -= 12;
        a++;
    }
    // Formata padronizado com barras
    sprintf(destino, "%02d/%02d/%04d", d, m, a);
}

// --- FUNÇÕES AUXILIARES DE REMOÇÃO (LOCAIS) ---
// Como não expusemos isso no model, vamos fazer a remoção manual aqui ou pedir para adicionar no model.
// Para ser rápido e não mexer em .h, vou implementar a lógica de remoção na lista aqui mesmo.
void remover_conta_pagar_memoria(ListaContaPagar** lista, int id) {
    ListaContaPagar* atual = *lista;
    ListaContaPagar* ant = NULL;
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

// --- LÓGICA DA NOTA FISCAL ---
// void processar_entrada_nota_fiscal(Listarecurso* lista_recursos, ListaContaPagar** lista_pagar, Listaprodutora* lista_produtora, ListaCaixa** lista_caixa) {
//     if (lista_produtora == NULL) { view_exibir_mensagem(">> ERRO: Cadastre a Produtora."); return; }
//     if (lista_recursos == NULL) { view_exibir_mensagem(">> ERRO: Sem recursos."); return; }

//     float margem_lucro = lista_produtora->conteudo.margem_lucro_padrao;
//     if (margem_lucro < 0 || margem_lucro > 1000) margem_lucro = 0;

//     // 1. LEITURA DOS TOTAIS (View)
//     float v_prod=0, v_frete=0, v_imp=0;
//     view_ler_totais_nota_fiscal(&v_prod, &v_frete, &v_imp);

//     struct { int id; int qtd; float custo; char nome[100]; } itens[100];
//     int n_itens = 0;
//     int qtd_total_pecas = 0;
//     char resumo_desc[250] = "";

//     // 2. LEITURA DOS ITENS (View)
//     while (1) {
//         printf("\n--- RECURSOS ---\n");
//         view_imprimir_lista_recurso(lista_recursos);
//         int id, qtd; float custo;
//         if (view_ler_item_nota_fiscal(&id, &qtd, &custo) == 0) break;

//         Listarecurso* rec = buscar_recurso_por_id(lista_recursos, id);
//         if (rec) {
//             if (qtd <= 0) { view_exibir_mensagem(">> Qtd invalida."); continue; }
//             itens[n_itens].id = id;
//             itens[n_itens].qtd = qtd;
//             itens[n_itens].custo = custo;
//             strcpy(itens[n_itens].nome, rec->conteudo.descricao);
//             if (strlen(resumo_desc) < 200) { strcat(resumo_desc, rec->conteudo.descricao); strcat(resumo_desc, ", "); }
//             qtd_total_pecas += qtd;
//             n_itens++;
//             view_exibir_mensagem(">> Item adicionado.");
//         } else view_exibir_mensagem(">> ID nao encontrado.");
//     }

//     if (n_itens == 0) return;
//     int len = strlen(resumo_desc);
//     if (len > 2) resumo_desc[len-2] = '\0';

//     float total_nota = v_prod + v_frete + v_imp;
//     printf("\nTotal a Pagar: R$ %.2f. Confirma? (1-Sim): ", total_nota);
//     if (view_ler_opcao() != 1) return;

//     // 3. CÁLCULOS DE ESTOQUE
//     float frete_un = (qtd_total_pecas > 0) ? v_frete / qtd_total_pecas : 0;
//     float imp_un = (qtd_total_pecas > 0) ? v_imp / qtd_total_pecas : 0;

//     for (int i = 0; i < n_itens; i++) {
//         Listarecurso* r = buscar_recurso_por_id(lista_recursos, itens[i].id);
//         r->conteudo.quantidade += itens[i].qtd;
//         r->conteudo.preco_de_custo = itens[i].custo;
        
//         float lucro = r->conteudo.preco_de_custo * (margem_lucro / 100.0);
//         float novo_preco = r->conteudo.preco_de_custo + frete_un + imp_un + lucro;
//         r->conteudo.valor_da_locacao = arredondar_duas_casas(novo_preco);
//         printf(">> %s: Novo Preco Locacao R$ %.2f\n", r->conteudo.descricao, r->conteudo.valor_da_locacao);
//     }

//     // 4. PAGAMENTO
//     int forma; char dt_venc[20]; float entrada = 0; int parcelas = 1;
//     view_ler_dados_pagamento(&forma, dt_venc, &entrada, &parcelas);

//     if (forma == 1) {
//         // A VISTA
//         LancamentoCaixa l; l.id=0; l.tipo=2; l.valor=total_nota;
//         sprintf(l.descricao, "Compra A VISTA: %s", resumo_desc);
//         strcpy(l.data, dt_venc);
//         inserir_caixa(lista_caixa, l);
//         view_exibir_mensagem(">> Pago a vista (Caixa).");
//     } else {
//         // A PRAZO
//         if (entrada > 0) {
//             LancamentoCaixa l; l.id=0; l.tipo=2; l.valor=entrada;
//             sprintf(l.descricao, "Entrada NF: %s", resumo_desc);
//             strcpy(l.data, dt_venc);
//             inserir_caixa(lista_caixa, l);
//         }

//         float restante = total_nota - entrada;
//         if (restante > 0 && parcelas >= 1) {
//             float val_parc = arredondar_duas_casas(restante / parcelas);
//             float diferenca = restante - (val_parc * parcelas);

//             for (int i = 1; i <= parcelas; i++) {
//                 ContaPagar cp; 
//                 cp.id=0; cp.status=0; cp.id_fornecedor=0; strcpy(cp.data_pagamento, "");
                
//                 cp.valor_total = (i == parcelas) ? val_parc + diferenca : val_parc;
//                 sprintf(cp.descricao, "Parc %d/%d (%s)", i, parcelas, resumo_desc);
                
//                 char dt_parc[20];
//                 // CORREÇÃO DO ERRO DE DATA: Usamos a função inteligente agora
//                 // Se i=1, soma 0 meses (data base). Se i=2, soma 1 mês.
//                 somar_meses_financeiro(dt_venc, i-1, dt_parc); 
//                 strcpy(cp.data_vencimento, dt_parc);

//                 inserir_conta_pagar(lista_pagar, cp);
//                 printf(" -> Parcela %d: R$ %.2f (Venc: %s)\n", i, cp.valor_total, cp.data_vencimento);
//             }
//             view_exibir_mensagem(">> Parcelas geradas.");
//         }
//     }
// }
// Em controller/financeiro_controller.c

void processar_entrada_nota_fiscal(Listarecurso* lista_recursos, ListaContaPagar** lista_pagar, Listaprodutora* lista_produtora, ListaCaixa** lista_caixa) {
    // 1. Validações
    if (lista_produtora == NULL) { view_exibir_mensagem(">> ERRO: Cadastre a Produtora."); return; }
    if (lista_recursos == NULL) { view_exibir_mensagem(">> ERRO: Nenhum recurso cadastrado."); return; }

    float margem_lucro = lista_produtora->conteudo.margem_lucro_padrao;
    if (margem_lucro < 0 || margem_lucro > 1000) margem_lucro = 0;

    // 2. Leitura Totais
    float v_prod=0, v_frete=0, v_imp=0;
    view_ler_totais_nota_fiscal(&v_prod, &v_frete, &v_imp);

    // USANDO A NOVA STRUCT DO MODEL
    ItemCompraTemp itens[100];
    int n_itens = 0;
    int qtd_total_pecas = 0;
    char resumo_desc[300] = "";

    // 3. Loop de Itens
    while (1) {
        printf("\n--- SELECIONAR ITENS DA NOTA ---\n");
        view_imprimir_lista_recurso(lista_recursos);
        
        int id, qtd; float custo;
        if (view_ler_item_nota_fiscal(&id, &qtd, &custo) == 0) break;

        Listarecurso* rec = buscar_recurso_por_id(lista_recursos, id);
        if (rec) {
            if (qtd <= 0) { view_exibir_mensagem(">> Qtd invalida."); continue; }
            
            itens[n_itens].id = id;
            itens[n_itens].qtd = qtd;
            itens[n_itens].custo = custo;
            strcpy(itens[n_itens].nome, rec->conteudo.descricao);
            
            // Concatena para a descrição da conta
            if (strlen(resumo_desc) < 250) {
                strcat(resumo_desc, rec->conteudo.descricao);
                strcat(resumo_desc, ", ");
            }
            
            qtd_total_pecas += qtd;
            n_itens++;
            view_exibir_mensagem(">> Item adicionado a lista temporaria.");
        } else view_exibir_mensagem(">> ID nao encontrado.");
    }

    if (n_itens == 0) return;
    
    // Remove última vírgula
    int len = strlen(resumo_desc); 
    if (len > 2) resumo_desc[len-2] = '\0';

    // 4. EXIBE A NOTA DETALHADA (AQUI ESTA A CORREÇÃO VISUAL)
    view_imprimir_nota_fiscal_detalhada(itens, n_itens, v_prod, v_frete, v_imp);

    printf("\nConfirma a entrada desta Nota Fiscal? (1-Sim / 0-Cancelar): ");
    if (view_ler_opcao() != 1) return;

    // 5. Cálculos e Atualização de Estoque
    float frete_un = (qtd_total_pecas > 0) ? v_frete / qtd_total_pecas : 0;
    float imp_un = (qtd_total_pecas > 0) ? v_imp / qtd_total_pecas : 0;
    float total_nota = v_prod + v_frete + v_imp;

    printf("\n>> Atualizando Estoque e Precos...\n");
    for (int i = 0; i < n_itens; i++) {
        Listarecurso* r = buscar_recurso_por_id(lista_recursos, itens[i].id);
        
        int est_antigo = r->conteudo.quantidade;
        r->conteudo.quantidade += itens[i].qtd;
        r->conteudo.preco_de_custo = itens[i].custo;
        
        float lucro = r->conteudo.preco_de_custo * (margem_lucro / 100.0);
        float novo_preco = r->conteudo.preco_de_custo + frete_un + imp_un + lucro;
        r->conteudo.valor_da_locacao = arredondar_duas_casas(novo_preco);
        
        printf("   [%s] Estoque: %d->%d | Novo Aluguel: R$ %.2f\n", 
               r->conteudo.descricao, est_antigo, r->conteudo.quantidade, r->conteudo.valor_da_locacao);
    }

    // 6. Pagamento (Mantido igual, pois já estava correto com parcelas)
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

// --- PAGAMENTO DE CONTA (AGORA REMOVE DA LISTA) ---
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

// --- RECEBIMENTO DE CONTA (AGORA REMOVE DA LISTA) ---
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
            
            // 2. REMOVE DA LISTA DE PENDENTES (CORREÇÃO SOLICITADA)
            remover_conta_receber_memoria(l_cr, id);
            
            view_exibir_mensagem(">> Recebido e removido da lista!");
        }
    } else view_exibir_mensagem(">> Fatura nao encontrada.");
}

void exibir_extrato_caixa(ListaCaixa* lista) {
    view_imprimir_extrato_caixa_detalhado(lista);
}

// ATENÇÃO: Alterei os parâmetros para ponteiro duplo (**) para poder remover
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