

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orcamento_controller.h"

#include "../view/menus.h"
#include "../view/mostrar_dados.h"
#include "../view/receber_dados.h"

long calcular_data_int(int d, int m, int a) {
    return (a * 10000) + (m * 100) + d;
}

// Função INTELIGENTE para somar meses a uma data (aceita / ou espaco)
void somar_meses_data_orc(char* data_original, int meses, char* destino) {
    int d, m, a;
    // Tenta ler com barras
    if (sscanf(data_original, "%d/%d/%d", &d, &m, &a) != 3) {
        // Se falhar, tenta ler com espaços
        if (sscanf(data_original, "%d %d %d", &d, &m, &a) != 3) {
            strcpy(destino, data_original); // Falhou tudo, mantem original
            return;
        }
    }
    
    m += meses;
    while (m > 12) {
        m -= 12;
        a++;
    }
    // Formata padronizado com barras para salvar
    sprintf(destino, "%02d/%02d/%04d", d, m, a);
}

int verifica_colisao_datas(Orcamento* o1, Orcamento* o2) {
    long inicio1 = calcular_data_int(o1->dia_inicio, o1->mes_inicio, o1->ano_inicio);
    long fim1    = calcular_data_int(o1->dia_fim, o1->mes_fim, o1->ano_fim);
    long inicio2 = calcular_data_int(o2->dia_inicio, o2->mes_inicio, o2->ano_inicio);
    long fim2    = calcular_data_int(o2->dia_fim, o2->mes_fim, o2->ano_fim);
    return (inicio1 <= fim2 && inicio2 <= fim1);
}

int item_ja_existe(Orcamento* o, int id_item, int tipo) {
    if (tipo == 1) {
        for(int i=0; i < o->qtd_recursos_selecionados; i++) 
            if(o->lista_recursos[i].id_recurso == id_item) return 1;
    } else if (tipo == 2) {
        for(int i=0; i < o->qtd_servicos_selecionados; i++) 
            if(o->lista_servicos[i].id_fornecedor == id_item) return 1;
    } else if (tipo == 3) {
        for(int i=0; i < o->qtd_equipe_selecionada; i++) 
            if(o->lista_equipe[i].id_membro_equipe == id_item) return 1;
    }
    return 0;
}

int calcular_estoque_ocupado(ListaOrcamento* lista_orcamentos, int id_recurso, Orcamento* orcamento_atual) {
    int quantidade_ocupada = 0;
    ListaOrcamento* atual = lista_orcamentos;
    while (atual != NULL) {
        if (atual->conteudo.status == STATUS_APROVADO) {
            if (verifica_colisao_datas(&atual->conteudo, orcamento_atual)) {
                for (int i = 0; i < atual->conteudo.qtd_recursos_selecionados; i++) {
                    if (atual->conteudo.lista_recursos[i].id_recurso == id_recurso) {
                        quantidade_ocupada += atual->conteudo.lista_recursos[i].quantidade;
                    }
                }
            }
        }
        atual = atual->prox;
    }
    return quantidade_ocupada;
}

int obter_qtd_no_orcamento_atual(Orcamento* o, int id_rec) {
    for(int i=0; i < o->qtd_recursos_selecionados; i++) 
        if(o->lista_recursos[i].id_recurso == id_rec) return o->lista_recursos[i].quantidade;
    return 0;
}

void listar_cronograma_recurso(ListaOrcamento* lista, Listarecurso* l_rec) {
    view_imprimir_lista_recurso(l_rec);
    view_exibir_mensagem("\nDigite o ID do Recurso:");
    int id = view_ler_opcao();
    Listarecurso* r = buscar_recurso_por_id(l_rec, id);
    if (r == NULL) { view_exibir_mensagem(">> Recurso nao encontrado."); return; }

    printf("\n=== CRONOGRAMA: %s ===\n", r->conteudo.descricao);
    int encontrou = 0;
    while (lista != NULL) {
        if (lista->conteudo.status == STATUS_APROVADO) {
            for(int i=0; i < lista->conteudo.qtd_recursos_selecionados; i++) {
                if (lista->conteudo.lista_recursos[i].id_recurso == id) {
                    view_exibir_ocupacao_recurso(id, r->conteudo.descricao, 
                        lista->conteudo.dia_inicio, lista->conteudo.mes_inicio, lista->conteudo.ano_inicio,
                        lista->conteudo.dia_fim, lista->conteudo.mes_fim, lista->conteudo.ano_fim,
                        lista->conteudo.lista_recursos[i].quantidade);
                    encontrou = 1;
                }
            }
        }
        lista = lista->prox;
    }
    if (!encontrou) printf(">> Livre.\n");
}

void criar_novo_orcamento(ListaOrcamento** lista_orc, ListaCliente* l_cli, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq) {
    if (!l_cli || !l_rec) { view_exibir_mensagem(">> Cadastre Clientes e Recursos."); return; }
    Orcamento novo; memset(&novo, 0, sizeof(Orcamento)); novo.ativo=1; novo.status=STATUS_EM_ANALISE;
    
    view_imprimir_lista(l_cli);
    view_exibir_mensagem("ID do Cliente:"); novo.id_cliente = view_ler_opcao();
    if (!buscar_cliente_por_id(l_cli, novo.id_cliente)) { view_exibir_mensagem(">> Invalido."); return; }

    view_ler_dados_base_orcamento(&novo);
    novo.qtd_dias = (novo.dia_fim - novo.dia_inicio) + 1; if(novo.qtd_dias < 1) novo.qtd_dias = 1;
while (1) {
        printf("\n--- ADICIONAR RECURSOS ---\n");
        view_imprimir_lista_recurso(l_rec);
        
        // MOSTRA O QUE JÁ ESTÁ NO CARRINHO (Para o utilizador saber)
        if (novo.qtd_recursos_selecionados > 0) {
            printf("\n[ITENS JA SELECIONADOS NESTE ORCAMENTO]:\n");
            for(int i=0; i<novo.qtd_recursos_selecionados; i++) {
                // Busca o nome para mostrar (opcional, fica mais bonito)
                Listarecurso* temp = buscar_recurso_por_id(l_rec, novo.lista_recursos[i].id_recurso);
                char* nome_item = temp ? temp->conteudo.descricao : "Item";
                
                printf(" - %s (ID %d): %d unidades\n", 
                       nome_item,
                       novo.lista_recursos[i].id_recurso, 
                       novo.lista_recursos[i].quantidade);
            }
        }

        view_exibir_mensagem("\nDigite o ID do Recurso para adicionar (0 para parar):");
        int id_rec = view_ler_opcao(); // <--- A LEITURA DO ID TEM DE ESTAR AQUI
        
        if (id_rec == 0) break;

        Listarecurso* no_rec = buscar_recurso_por_id(l_rec, id_rec);
        if (no_rec) {
            int estoque_total = no_rec->conteudo.quantidade;
            // Verifica ocupação em outros eventos
            int ocupado_outros = calcular_estoque_ocupado(*lista_orc, id_rec, &novo);
            // Verifica o que já pus no meu carrinho agora
            int ja_no_carrinho = obter_qtd_no_orcamento_atual(&novo, id_rec);
            
            // Cálculo Real: Total - Outros - MeuCarrinho
            int disponivel_real = estoque_total - ocupado_outros - ja_no_carrinho;

            printf("\n>> Item: %s\n", no_rec->conteudo.descricao);
            printf("   Estoque Total: %d | Ocupado (Outros Eventos): %d\n", estoque_total, ocupado_outros);
            printf("   Ja neste orcamento: %d\n", ja_no_carrinho);
            printf("   >> DISPONIVEL PARA ADICIONAR: %d\n", disponivel_real);

            if (disponivel_real <= 0) {
                view_exibir_mensagem(">> ALERTA: Nao ha mais unidades disponiveis para esta data.");
                continue;
            }

            printf("Quantidade a adicionar: ");
            int qtd = view_ler_opcao();
            
            if (qtd > disponivel_real) {
                view_exibir_mensagem(">> Quantidade indisponivel (maior que o saldo).");
            } else {
                // Verifica se já existe para SOMAR
                int encontrado = 0;
                for(int i=0; i < novo.qtd_recursos_selecionados; i++) {
                    if(novo.lista_recursos[i].id_recurso == id_rec) {
                        novo.lista_recursos[i].quantidade += qtd;
                        novo.valor_total_recursos += (no_rec->conteudo.valor_da_locacao * qtd * novo.qtd_dias);
                        printf(">> Quantidade atualizada para %d!\n", novo.lista_recursos[i].quantidade);
                        encontrado = 1;
                        break;
                    }
                }

                // Se não existe, cria novo item na lista
                if (!encontrado) {
                    int idx = novo.qtd_recursos_selecionados;
                    if (idx < MAX_ITENS_ORCAMENTO) {
                        novo.lista_recursos[idx].id_recurso = id_rec;
                        novo.lista_recursos[idx].quantidade = qtd;
                        novo.lista_recursos[idx].valor_unitario_momento = no_rec->conteudo.valor_da_locacao;
                        novo.qtd_recursos_selecionados++;
                        
                        novo.valor_total_recursos += (no_rec->conteudo.valor_da_locacao * qtd * novo.qtd_dias);
                        printf(">> Item adicionado com sucesso!\n");
                    } else {
                        view_exibir_mensagem(">> Limite de itens no orcamento atingido.");
                    }
                }
            }
        } else {
            view_exibir_mensagem(">> Recurso nao encontrado.");
        }
    }
   
    if (l_for) {
        view_exibir_mensagem("\nFornecedores? (1-Sim)");
        if (view_ler_opcao() == 1) {
            while(1) {
                view_imprimir_lista_fornecedor(l_for);
                printf("ID (0 fim): "); int id = view_ler_opcao();
                if(id==0) break;
                if(item_ja_existe(&novo, id, 2)) continue;
                if(buscar_fornecedor_por_id(l_for, id)) {
                    int idx = novo.qtd_servicos_selecionados;
                    novo.lista_servicos[idx].id_fornecedor = id;
                    printf("Desc: "); char d[100]; fgets(d, 100, stdin); d[strcspn(d, "\n")]=0; strcpy(novo.lista_servicos[idx].descricao_servico, d);
                    printf("Valor: "); char v[20]; fgets(v, 20, stdin); novo.lista_servicos[idx].valor_combinado = atof(v);
                    novo.valor_total_servicos += novo.lista_servicos[idx].valor_combinado;
                    novo.qtd_servicos_selecionados++;
                }
            }
        }
    }
    if (l_eq) {
        view_exibir_mensagem("\nEquipe? (1-Sim) (0-Nao)");
        if (view_ler_opcao() == 1) {
            while(1) {
                view_imprimir_lista_equipe(l_eq);
                printf("ID (0 fim): "); int id = view_ler_opcao();
                if(id==0) break;
                if(item_ja_existe(&novo, id, 3)) continue;
                Listaequipe* eq = buscar_equipe_por_id(l_eq, id);
                if(eq) {
                    int idx = novo.qtd_equipe_selecionada;
                    novo.lista_equipe[idx].id_membro_equipe = id;
                    novo.lista_equipe[idx].valor_diaria_momento = eq->conteudo.valor_diaria;
                    novo.lista_equipe[idx].dias_trabalhados = novo.qtd_dias;
                    float custo = eq->conteudo.valor_diaria * novo.qtd_dias;
                    novo.valor_total_equipe += custo;
                    novo.qtd_equipe_selecionada++;
                }
            }
        }
    }

    novo.valor_total_geral = novo.valor_total_recursos + novo.valor_total_servicos + novo.valor_total_equipe;
    inserir_orcamento(lista_orc, novo);
    printf(">> CRIADO! Total: R$ %.2f\n", novo.valor_total_geral);
}

void aprovar_orcamento_controller(ListaOrcamento* lista) {
    view_exibir_mensagem("ID:"); int id = view_ler_opcao();
    ListaOrcamento* no = buscar_orcamento_por_id(lista, id);
    if (no && no->conteudo.status == STATUS_EM_ANALISE) {
        no->conteudo.status = STATUS_APROVADO;
        view_exibir_mensagem(">> APROVADO!");
    } else view_exibir_mensagem(">> Erro.");
}

void excluir_orcamento_controller(ListaOrcamento** lista) {
    view_exibir_mensagem("\n=== EXCLUIR ORCAMENTO (APAGAR) ===");
    view_exibir_mensagem("Digite o ID do orcamento:");
    int id = view_ler_opcao();
    
    ListaOrcamento* no = buscar_orcamento_por_id(*lista, id);
    
    if (no) {
        // Aviso de segurança
        if (no->conteudo.status == STATUS_FINALIZADO) {
            view_exibir_mensagem(">> ATENCAO: Este evento ja foi FINALIZADO e gerou financeiro.");
            view_exibir_mensagem(">> Apaga-lo pode deixar os relatorios financeiros sem detalhes.");
        }

        printf("Tem a certeza que deseja APAGAR DEFINITIVAMENTE o evento '%s'? (1-Sim / 0-Nao): ", no->conteudo.nome_evento);
        if (view_ler_opcao() == 1) {
            // Chama a função do Model para remover da memória
            if (remover_fisico_orcamento(lista, id) == OPERACAO_SUCESSO) {
                view_exibir_mensagem(">> SUCESSO: Orcamento apagado do sistema.");
            } else {
                view_exibir_mensagem(">> Erro ao excluir.");
            }
        }
    } else {
        view_exibir_mensagem(">> Orcamento nao encontrado.");
    }
}

// --- FUNÇÃO CORRIGIDA COM ENTRADA + PARCELAS PARA CLIENTE ---
void finalizar_evento_controller(ListaOrcamento* lista, ListaContaReceber** lista_receber, ListaCaixa** lista_caixa) {
    view_exibir_mensagem("\n=== FINALIZAR EVENTO ===");
    view_exibir_mensagem("Digite o ID do Evento (Deve estar APROVADO):");
    int id = view_ler_opcao();
    
    ListaOrcamento* no = buscar_orcamento_por_id(lista, id);

    if (no && no->conteudo.status == STATUS_APROVADO) {
        Orcamento* o = &no->conteudo;
        printf("\n--- RESUMO: %s ---\nTOTAL: R$ %.2f\n", o->nome_evento, o->valor_total_geral);
        
        printf("\nPagamento:\n1. A Vista (Caixa)\n2. Credito Parcelado (Entrada + Parcelas)\nOpcao: ");
        int op = view_ler_opcao();

        if (op == 1) {
            LancamentoCaixa lanc; lanc.id=0; lanc.tipo=1; lanc.valor=o->valor_total_geral;
            sprintf(lanc.descricao, "Evento #%d: %s (A Vista)", o->id, o->nome_evento);
            printf("Data: "); char buf[20]; fgets(buf, 20, stdin); buf[strcspn(buf, "\n")]=0; strcpy(lanc.data, buf);
            inserir_caixa(lista_caixa, lanc);
            o->status = STATUS_FINALIZADO;
            view_exibir_mensagem(">> Sucesso (Caixa)!");

        } else if (op == 2) {
            // AQUI ESTÁ A CORREÇÃO: OPÇÃO DE ENTRADA
            printf("Valor de Entrada (0 se nao houver): ");
            char buf_ent[20]; fgets(buf_ent, 20, stdin); float entrada = atof(buf_ent);
            
            printf("Data do Recebimento da Entrada /  Vencimento: ");
            char dt_base[20]; fgets(dt_base, 20, stdin); dt_base[strcspn(dt_base, "\n")]=0;

            if (entrada > 0) {
                LancamentoCaixa lanc; lanc.id=0; lanc.tipo=1; lanc.valor=entrada;
                sprintf(lanc.descricao, "Entrada Evt #%d: %s", o->id, o->nome_evento);
                strcpy(lanc.data, dt_base);
                inserir_caixa(lista_caixa, lanc);
                printf(">> Entrada de R$ %.2f lancada no Caixa.\n", entrada);
            }

            float restante = o->valor_total_geral - entrada;
            if (restante > 0) {
                printf("Numero de parcelas (R$ %.2f): ", restante);
                int parc = view_ler_opcao();
                if (parc < 1) parc = 1;

                float val_parc = (float)((int)((restante / parc)*100))/100.0;
                float diff = restante - (val_parc * parc);

                for (int i = 1; i <= parc; i++) {
                    ContaReceber cr; cr.id=0; cr.id_cliente=o->id_cliente; cr.id_evento_origem=o->id; cr.status=0; strcpy(cr.data_recebimento, "");
                    cr.valor_total = (i == parc) ? val_parc + diff : val_parc;
                    sprintf(cr.descricao, "Fatura Evt #%d (%d/%d)", o->id, i, parc);
                    
                    char dt_venc[20];
                    somar_meses_data_orc(dt_base, i, dt_venc); // Começa 1 mês depois da entrada/base
                    strcpy(cr.data_vencimento, dt_venc);

                    inserir_conta_receber(lista_receber, cr);
                    printf(" -> Fatura %d: R$ %.2f (Venc: %s)\n", i, cr.valor_total, cr.data_vencimento);
                }
            }
            o->status = STATUS_FINALIZADO;
            view_exibir_mensagem(">> Sucesso (Parcelas Geradas)!");
        }
    } else view_exibir_mensagem(">> Erro.");
}

void controller_gerenciar_orcamentos(ListaOrcamento** lista_orcamentos, ListaCliente* lista_clientes, Listarecurso* lista_recursos, Listafornecedor* lista_fornecedores, Listaequipe* lista_equipe, ListaContaReceber** lista_receber, ListaCaixa** lista_caixa) {
    int opcao = -1;
    do {
        printf("\n=== ORCAMENTOS ===\n1. Novo\n2. Listar (Analise)\n3. Listar (Aprovados)\n4. Historico\n5. Cronograma\n6. Aprovar\n7. Finalizar\n8. Excluir\n0. Voltar\nOpcao: ");
        opcao = view_ler_opcao();
        switch (opcao) {
            case 1: criar_novo_orcamento(lista_orcamentos, lista_clientes, lista_recursos, lista_fornecedores, lista_equipe); break;
            case 2: view_imprimir_lista_orcamento_por_status(*lista_orcamentos, STATUS_EM_ANALISE, lista_recursos, lista_fornecedores, lista_equipe); break;
            case 3: view_imprimir_lista_orcamento_por_status(*lista_orcamentos, STATUS_APROVADO, lista_recursos, lista_fornecedores, lista_equipe); break;
            case 4: view_imprimir_lista_orcamento_por_status(*lista_orcamentos, STATUS_FINALIZADO, lista_recursos, lista_fornecedores, lista_equipe); break;
            case 5: listar_cronograma_recurso(*lista_orcamentos, lista_recursos); break;
            case 6: aprovar_orcamento_controller(*lista_orcamentos); break;
            case 7: finalizar_evento_controller(*lista_orcamentos, lista_receber, lista_caixa); break;
            case 8: 
                // Agora chama a exclusão física
                
                excluir_orcamento_controller(lista_orcamentos); 
                break;
        }
    } while (opcao != 0);
}
