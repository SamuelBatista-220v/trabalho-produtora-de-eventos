
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "orcamento_controller.h"

// #include "../view/view.h"
// #include "../view/menus.h"
// #include "../view/mostrar_dados.h"
// #include "../view/receber_dados.h"

// // --- FUNÇÕES AUXILIARES PRIVADAS ---

// long calcular_data_int(int d, int m, int a) {
//     return (a * 10000) + (m * 100) + d;
// }

// int verifica_colisao_datas(Orcamento* o1, Orcamento* o2) {
//     long inicio1 = calcular_data_int(o1->dia_inicio, o1->mes_inicio, o1->ano_inicio);
//     long fim1    = calcular_data_int(o1->dia_fim, o1->mes_fim, o1->ano_fim);
//     long inicio2 = calcular_data_int(o2->dia_inicio, o2->mes_inicio, o2->ano_inicio);
//     long fim2    = calcular_data_int(o2->dia_fim, o2->mes_fim, o2->ano_fim);
//     return (inicio1 <= fim2 && inicio2 <= fim1);
// }

// int calcular_estoque_ocupado(ListaOrcamento* lista_orcamentos, int id_recurso, Orcamento* orcamento_atual) {
//     int quantidade_ocupada = 0;
//     ListaOrcamento* atual = lista_orcamentos;
//     while (atual != NULL) {
//         if (atual->conteudo.status == STATUS_APROVADO) {
//             if (verifica_colisao_datas(&atual->conteudo, orcamento_atual)) {
//                 for (int i = 0; i < atual->conteudo.qtd_recursos_selecionados; i++) {
//                     if (atual->conteudo.lista_recursos[i].id_recurso == id_recurso) {
//                         quantidade_ocupada += atual->conteudo.lista_recursos[i].quantidade;
//                     }
//                 }
//             }
//         }
//         atual = atual->prox;
//     }
//     return quantidade_ocupada;
// }

// // --- FUNÇÕES PRINCIPAIS ---

// void criar_novo_orcamento(ListaOrcamento** lista_orc, ListaCliente* l_cli, Listarecurso* l_rec, Listafornecedor* l_for) {
//     if (l_cli == NULL || l_rec == NULL) {
//         view_exibir_mensagem(">> ERRO: Necessario ter Clientes e Recursos cadastrados.");
//         return;
//     }

//     Orcamento novo;
//     memset(&novo, 0, sizeof(Orcamento)); 
//     novo.ativo = 1;
//     novo.status = STATUS_EM_ANALISE;

//     // 1. Selecionar Cliente
//     view_imprimir_lista(l_cli);
//     view_exibir_mensagem("Digite o ID do Cliente:");
//     int id_cli = view_ler_opcao();
//     if (buscar_cliente_por_id(l_cli, id_cli) == NULL) {
//         view_exibir_mensagem(">> Cliente nao encontrado.");
//         return;
//     }
//     novo.id_cliente = id_cli;

//     // 2. Dados do Evento e Datas (USANDO A NOVA VIEW)
//     view_ler_dados_base_orcamento(&novo);

//     // Calcula dias
//     novo.qtd_dias = (novo.dia_fim - novo.dia_inicio) + 1; 
//     if (novo.qtd_dias < 1) novo.qtd_dias = 1;

//     // 3. Adicionar Recursos
//     int continuar = 1;
//     while (continuar) {
//         view_imprimir_lista_recurso(l_rec);
//         view_exibir_mensagem("\nDigite o ID do Recurso para adicionar (0 para parar):");
//         int id_rec = view_ler_opcao();
        
//         if (id_rec == 0) break;

//         Listarecurso* no_rec = buscar_recurso_por_id(l_rec, id_rec);
//         if (no_rec != NULL) {
//             int estoque_total = no_rec->conteudo.quantidade;
//             int estoque_usado = calcular_estoque_ocupado(*lista_orc, id_rec, &novo);
//             int disponivel = estoque_total - estoque_usado;

//             printf(">> Estoque Disponivel para esta data: %d (Total: %d)\n", disponivel, estoque_total);

//             if (disponivel <= 0) {
//                 view_exibir_mensagem(">> Indisponivel nas datas selecionadas!");
//             } else {
//                 printf("Quantidade: ");
//                 int qtd = view_ler_opcao();
                
//                 if (qtd > disponivel) {
//                     view_exibir_mensagem(">> Quantidade indisponivel.");
//                 } else {
//                     int idx = novo.qtd_recursos_selecionados;
//                     if (idx < MAX_ITENS_ORCAMENTO) {
//                         novo.lista_recursos[idx].id_recurso = id_rec;
//                         novo.lista_recursos[idx].quantidade = qtd;
//                         novo.lista_recursos[idx].valor_unitario_momento = no_rec->conteudo.valor_da_locacao;
//                         novo.qtd_recursos_selecionados++;
                        
//                         novo.valor_total_recursos += (no_rec->conteudo.valor_da_locacao * qtd * novo.qtd_dias);
//                         view_exibir_mensagem(">> Recurso adicionado!");
//                     }
//                 }
//             }
//         } else {
//             view_exibir_mensagem(">> Recurso nao encontrado.");
//         }
//     }

//     // 4. Adicionar Serviços
//     view_exibir_mensagem("\nAdicionar servicos terceirizados? (1-Sim / 0-Nao)");
//     if (view_ler_opcao() == 1 && l_for != NULL) {
//         while (1) {
//             view_imprimir_lista_fornecedor(l_for);
//             view_exibir_mensagem("ID do Fornecedor (0 para parar):");
//             int id_for = view_ler_opcao();
//             if (id_for == 0) break;

//             if (buscar_fornecedor_por_id(l_for, id_for)) {
//                 int idx = novo.qtd_servicos_selecionados;
//                 novo.lista_servicos[idx].id_fornecedor = id_for;
                
//                 printf("Descricao do servico: ");
//                 char desc[100];
//                 fgets(desc, 100, stdin); desc[strcspn(desc, "\n")] = 0;
//                 strcpy(novo.lista_servicos[idx].descricao_servico, desc);

//                 printf("Valor combinado: ");
//                 char val[20]; fgets(val, 20, stdin);
//                 novo.lista_servicos[idx].valor_combinado = atof(val);

//                 novo.valor_total_servicos += novo.lista_servicos[idx].valor_combinado;
//                 novo.qtd_servicos_selecionados++;
//             }
//         }
//     }

//     novo.valor_total_geral = novo.valor_total_recursos + novo.valor_total_servicos;
//     inserir_orcamento(lista_orc, novo);
    
//     char msg[100];
//     sprintf(msg, ">> ORCAMENTO CRIADO! Total: R$ %.2f", novo.valor_total_geral);
//     view_exibir_mensagem(msg);
// }

// void aprovar_orcamento_controller(ListaOrcamento* lista) {
//     view_exibir_mensagem("Digite o ID do orcamento para APROVAR:");
//     int id = view_ler_opcao();
//     ListaOrcamento* no = buscar_orcamento_por_id(lista, id);
    
//     if (no) {
//         if (no->conteudo.status == STATUS_EM_ANALISE) {
//             no->conteudo.status = STATUS_APROVADO;
//             view_exibir_mensagem(">> SUCESSO: Orcamento Aprovado!");
//         } else {
//             view_exibir_mensagem(">> Erro: Orcamento nao esta em analise.");
//         }
//     } else {
//         view_exibir_mensagem(">> Nao encontrado.");
//     }
// }

// void controller_gerenciar_orcamentos(ListaOrcamento** lista_orcamentos, ListaCliente* lista_clientes, Listarecurso* lista_recursos, Listafornecedor* lista_fornecedores) {
//     int opcao = -1;
//     do {
//         printf("\n=== GESTAO DE ORCAMENTOS ===\n");
//         printf("1. Criar Novo Orcamento\n");
//         printf("2. Listar Orcamentos\n");
//         printf("3. Aprovar Orcamento\n");
//         printf("0. Voltar\n");
//         opcao = view_ler_opcao();

//         switch (opcao) {
//             case 1: 
//                 criar_novo_orcamento(lista_orcamentos, lista_clientes, lista_recursos, lista_fornecedores);
//                 break;
//             case 2:
//                 view_imprimir_lista_orcamento(*lista_orcamentos); // USANDO A NOVA VIEW
//                 break;
//             case 3:
//                 aprovar_orcamento_controller(*lista_orcamentos);
//                 break;
//         }
//     } while (opcao != 0);
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orcamento_controller.h"

#include "../view/view.h"
#include "../view/menus.h"
#include "../view/mostrar_dados.h"
#include "../view/receber_dados.h"

// --- FUNÇÕES AUXILIARES PRIVADAS ---

long calcular_data_int(int d, int m, int a) {
    return (a * 10000) + (m * 100) + d;
}

int verifica_colisao_datas(Orcamento* o1, Orcamento* o2) {
    long inicio1 = calcular_data_int(o1->dia_inicio, o1->mes_inicio, o1->ano_inicio);
    long fim1    = calcular_data_int(o1->dia_fim, o1->mes_fim, o1->ano_fim);
    long inicio2 = calcular_data_int(o2->dia_inicio, o2->mes_inicio, o2->ano_inicio);
    long fim2    = calcular_data_int(o2->dia_fim, o2->mes_fim, o2->ano_fim);
    return (inicio1 <= fim2 && inicio2 <= fim1);
}

// Verifica duplicidade dentro do próprio orçamento que está sendo criado
int item_ja_existe(Orcamento* o, int id_item, int tipo) {
    // tipo: 1=Recurso, 2=Fornecedor, 3=Equipe
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
        // IMPORTANTE: Só orçamentos APROVADOS seguram estoque.
        // Finalizados já liberaram (evento passou), Cancelados também.
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

// --- FUNÇÕES DE LÓGICA ---

void listar_cronograma_recurso(ListaOrcamento* lista, Listarecurso* l_rec) {
    view_imprimir_lista_recurso(l_rec);
    view_exibir_mensagem("\nDigite o ID do Recurso para ver o CRONOGRAMA de uso:");
    int id = view_ler_opcao();
    Listarecurso* r = buscar_recurso_por_id(l_rec, id);
    
    if (r == NULL) {
        view_exibir_mensagem(">> Recurso nao encontrado.");
        return;
    }

    printf("\n=== CRONOGRAMA DE USO: %s (Total em Estoque: %d) ===\n", r->conteudo.descricao, r->conteudo.quantidade);
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
    if (!encontrou) printf(">> Este recurso esta livre em todos os periodos futuros.\n");
}

void criar_novo_orcamento(ListaOrcamento** lista_orc, ListaCliente* l_cli, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq) {
    if (!l_cli || !l_rec) {
        view_exibir_mensagem(">> ERRO: Cadastre Clientes e Recursos primeiro.");
        return;
    }

    Orcamento novo;
    memset(&novo, 0, sizeof(Orcamento)); 
    novo.ativo = 1;
    novo.status = STATUS_EM_ANALISE;

    // 1. Selecionar Cliente
    view_imprimir_lista(l_cli);
    view_exibir_mensagem("Digite o ID do Cliente:");
    int id_cli = view_ler_opcao();
    if (!buscar_cliente_por_id(l_cli, id_cli)) {
        view_exibir_mensagem(">> Cliente invalido.");
        return;
    }
    novo.id_cliente = id_cli;

    // 2. Dados Básicos
    view_ler_dados_base_orcamento(&novo);
    novo.qtd_dias = (novo.dia_fim - novo.dia_inicio) + 1;
    if (novo.qtd_dias < 1) novo.qtd_dias = 1;

    // 3. Adicionar Recursos
    while (1) {
        view_imprimir_lista_recurso(l_rec);
        view_exibir_mensagem("\nAdicionar Recurso (ID ou 0 para parar):");
        int id_rec = view_ler_opcao();
        if (id_rec == 0) break;

        // Verificação de Duplicidade
        if (item_ja_existe(&novo, id_rec, 1)) {
            view_exibir_mensagem(">> ERRO: Recurso ja adicionado! Remova ou edite (funcionalidade futura).");
            continue;
        }

        Listarecurso* no_rec = buscar_recurso_por_id(l_rec, id_rec);
        if (no_rec) {
            int disponivel = no_rec->conteudo.quantidade - calcular_estoque_ocupado(*lista_orc, id_rec, &novo);
            printf(">> Disponivel: %d\n", disponivel);

            if (disponivel <= 0) {
                view_exibir_mensagem(">> INDISPONIVEL nestas datas!");
            } else {
                printf("Quantidade: ");
                int qtd = view_ler_opcao();
                if (qtd > disponivel) {
                    view_exibir_mensagem(">> Quantidade insuficiente.");
                } else {
                    int idx = novo.qtd_recursos_selecionados;
                    novo.lista_recursos[idx].id_recurso = id_rec;
                    novo.lista_recursos[idx].quantidade = qtd;
                    novo.lista_recursos[idx].valor_unitario_momento = no_rec->conteudo.valor_da_locacao;
                    novo.qtd_recursos_selecionados++;
                    novo.valor_total_recursos += (no_rec->conteudo.valor_da_locacao * qtd * novo.qtd_dias);
                }
            }
        }
    }

    // 4. Adicionar Fornecedores
    if (l_for) {
        view_exibir_mensagem("\nAdicionar servicos de parceiros? (1-Sim / 0-Nao)");
        if (view_ler_opcao() == 1) {
            while (1) {
                view_imprimir_lista_fornecedor(l_for);
                view_exibir_mensagem("ID Fornecedor (0 para parar):");
                int id_for = view_ler_opcao();
                if (id_for == 0) break;

                if (item_ja_existe(&novo, id_for, 2)) {
                    view_exibir_mensagem(">> ERRO: Fornecedor ja esta na lista.");
                    continue;
                }

                if (buscar_fornecedor_por_id(l_for, id_for)) {
                    int idx = novo.qtd_servicos_selecionados;
                    novo.lista_servicos[idx].id_fornecedor = id_for;
                    
                    printf("Descricao do servico: ");
                    char desc[100]; fgets(desc, 100, stdin); desc[strcspn(desc, "\n")] = 0;
                    strcpy(novo.lista_servicos[idx].descricao_servico, desc);

                    printf("Custo Total do Servico: ");
                    char val[20]; fgets(val, 20, stdin);
                    novo.lista_servicos[idx].valor_combinado = atof(val);

                    novo.valor_total_servicos += novo.lista_servicos[idx].valor_combinado;
                    novo.qtd_servicos_selecionados++;
                }
            }
        }
    }

    // 5. Adicionar Equipe Interna
    if (l_eq) {
        view_exibir_mensagem("\nAlocar Equipe Interna? (1-Sim / 0-Nao)");
        if (view_ler_opcao() == 1) {
            while (1) {
                view_imprimir_lista_equipe(l_eq);
                view_exibir_mensagem("ID Membro Equipe (0 para parar):");
                int id_eq = view_ler_opcao();
                if (id_eq == 0) break;

                if (item_ja_existe(&novo, id_eq, 3)) {
                    view_exibir_mensagem(">> ERRO: Funcionario ja alocado.");
                    continue;
                }

                Listaequipe* no_eq = buscar_equipe_por_id(l_eq, id_eq);
                if (no_eq) {
                    int idx = novo.qtd_equipe_selecionada;
                    novo.lista_equipe[idx].id_membro_equipe = id_eq;
                    novo.lista_equipe[idx].valor_diaria_momento = no_eq->conteudo.valor_diaria;
                    novo.lista_equipe[idx].dias_trabalhados = novo.qtd_dias; // Padrão: trabalha todos os dias
                    
                    // Custo = Diaria * Dias
                    float custo_eq = no_eq->conteudo.valor_diaria * novo.qtd_dias;
                    novo.valor_total_equipe += custo_eq;
                    novo.qtd_equipe_selecionada++;
                    printf(">> %s alocado. Custo: R$ %.2f\n", no_eq->conteudo.nome, custo_eq);
                }
            }
        }
    }

    novo.valor_total_geral = novo.valor_total_recursos + novo.valor_total_servicos + novo.valor_total_equipe;
    inserir_orcamento(lista_orc, novo);
    printf(">> ORCAMENTO CRIADO! Total: R$ %.2f\n", novo.valor_total_geral);
}

void finalizar_evento_controller(ListaOrcamento* lista) {
    view_exibir_mensagem("=== FINALIZAR EVENTO E GERAR COBRANCA ===");
    view_exibir_mensagem("Digite o ID do Evento (Deve estar APROVADO):");
    int id = view_ler_opcao();
    ListaOrcamento* no = buscar_orcamento_por_id(lista, id);

    if (no && no->conteudo.status == STATUS_APROVADO) {
        Orcamento* o = &no->conteudo;
        
        // Consolidação
        printf("\n--- CONSOLIDACAO DE CUSTOS ---\n");
        printf("Equipamentos: R$ %.2f\n", o->valor_total_recursos);
        printf("Servicos:     R$ %.2f\n", o->valor_total_servicos);
        printf("Equipe:       R$ %.2f\n", o->valor_total_equipe);
        printf("--------------------------\n");
        printf("TOTAL FINAL:  R$ %.2f\n", o->valor_total_geral);
        
        view_exibir_mensagem("\nConfirma a finalizacao? O estoque sera liberado. (1-Sim / 0-Cancelar)");
        if (view_ler_opcao() == 1) {
            o->status = STATUS_FINALIZADO;
            // AQUI ENTRARIA A CRIAÇÃO DA "CONTA A RECEBER" NO MÓDULO FINANCEIRO
            // exemplo: criar_conta_receber(o->id_cliente, o->valor_total_geral, data_hoje);
            view_exibir_mensagem(">> SUCESSO: Evento finalizado! Valor enviado para faturamento.");
            view_exibir_mensagem(">> Recursos liberados no sistema.");
        }
    } else {
        view_exibir_mensagem(">> Erro: Evento nao encontrado ou nao esta APROVADO.");
    }
}

void aprovar_orcamento_controller(ListaOrcamento* lista) {
    view_exibir_mensagem("Digite o ID para APROVAR (Reservar):");
    int id = view_ler_opcao();
    ListaOrcamento* no = buscar_orcamento_por_id(lista, id);
    if (no && no->conteudo.status == STATUS_EM_ANALISE) {
        no->conteudo.status = STATUS_APROVADO;
        view_exibir_mensagem(">> APROVADO! Recursos reservados.");
    } else {
        view_exibir_mensagem(">> Erro: Status invalido para aprovacao.");
    }
}

// void controller_gerenciar_orcamentos(ListaOrcamento** lista_orcamentos, ListaCliente* lista_clientes, Listarecurso* lista_recursos, Listafornecedor* lista_fornecedores, Listaequipe* lista_equipe) {
//     int opcao = -1;
//     do {
//         printf("\n=== GESTAO DE ORCAMENTOS E EVENTOS ===\n");
//         printf("1. Criar Novo Orcamento\n");
//         printf("2. Listar Orcamentos (Em Analise)\n");
//         printf("3. Listar Eventos Aprovados (Futuros)\n");
//         printf("4. Listar Historico (Finalizados)\n");
//         printf("5. Ver Cronograma de Recurso (Disponibilidade)\n");
//         printf("6. Aprovar Orcamento\n");
//         printf("7. Finalizar Evento (Faturar e Liberar)\n");
//         printf("0. Voltar\n");
//         printf("Opcao: ");
//         opcao = view_ler_opcao();

//         switch (opcao) {
//             case 1: 
//                 criar_novo_orcamento(lista_orcamentos, lista_clientes, lista_recursos, lista_fornecedores, lista_equipe);
//                 break;
//             case 2: view_imprimir_lista_orcamento_por_status(*lista_orcamentos, STATUS_EM_ANALISE); break;
//             case 3: view_imprimir_lista_orcamento_por_status(*lista_orcamentos, STATUS_APROVADO); break;
//             case 4: view_imprimir_lista_orcamento_por_status(*lista_orcamentos, STATUS_FINALIZADO); break;
//             case 5: listar_cronograma_recurso(*lista_orcamentos, lista_recursos); break;
//             case 6: aprovar_orcamento_controller(*lista_orcamentos); break;
//             case 7: finalizar_evento_controller(*lista_orcamentos); break;
//         }
//     } while (opcao != 0);
// }

void controller_gerenciar_orcamentos(ListaOrcamento** lista_orcamentos, ListaCliente* lista_clientes, Listarecurso* lista_recursos, Listafornecedor* lista_fornecedores, Listaequipe* lista_equipe) {
    int opcao = -1;
    do {
        printf("\n=== GESTAO DE ORCAMENTOS E EVENTOS ===\n");
        printf("1. Criar Novo Orcamento\n");
        printf("2. Listar Orcamentos (Em Analise)\n");
        printf("3. Listar Eventos Aprovados (Futuros)\n");
        printf("4. Listar Historico (Finalizados)\n");
        printf("5. Ver Cronograma de Recurso (Disponibilidade)\n");
        printf("6. Aprovar Orcamento\n");
        printf("7. Finalizar Evento (Faturar e Liberar)\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        opcao = view_ler_opcao();

        switch (opcao) {
            case 1: 
                criar_novo_orcamento(lista_orcamentos, lista_clientes, lista_recursos, lista_fornecedores, lista_equipe);
                break;
            case 2: 
                // ATUALIZADO: Passando todas as listas para exibir nomes
                view_imprimir_lista_orcamento_por_status(*lista_orcamentos, STATUS_EM_ANALISE, lista_recursos, lista_fornecedores, lista_equipe); 
                break;
            case 3: 
                // ATUALIZADO
                view_imprimir_lista_orcamento_por_status(*lista_orcamentos, STATUS_APROVADO, lista_recursos, lista_fornecedores, lista_equipe); 
                break;
            case 4: 
                // ATUALIZADO
                view_imprimir_lista_orcamento_por_status(*lista_orcamentos, STATUS_FINALIZADO, lista_recursos, lista_fornecedores, lista_equipe); 
                break;
            case 5: 
                listar_cronograma_recurso(*lista_orcamentos, lista_recursos); 
                break;
            case 6: 
                aprovar_orcamento_controller(*lista_orcamentos); 
                break;
            case 7: 
                finalizar_evento_controller(*lista_orcamentos); 
                break;
        }
    } while (opcao != 0);
}