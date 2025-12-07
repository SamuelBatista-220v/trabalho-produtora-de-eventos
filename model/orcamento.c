// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "orcamento.h"

// static int proximo_id_orcamento = 1;



// StatusOperacao inserir_orcamento(ListaOrcamento** lista, Orcamento novo) {
//     ListaOrcamento* novo_no = (ListaOrcamento*) malloc(sizeof(ListaOrcamento));
//     if (!novo_no) return ERRO_ALOCACAO_MEMORIA;

//     if (novo.id <= 0) novo.id = proximo_id_orcamento++;
//     else if (novo.id >= proximo_id_orcamento) proximo_id_orcamento = novo.id + 1;

//     novo_no->conteudo = novo;
//     novo_no->prox = NULL;

//     if (*lista == NULL) {
//         *lista = novo_no;
//     } else {
//         ListaOrcamento* aux = *lista;
//         while (aux->prox) aux = aux->prox;
//         aux->prox = novo_no;
//     }
//     return OPERACAO_SUCESSO;
// }

// ListaOrcamento* buscar_orcamento_por_id(ListaOrcamento* lista, int id) {
//     while (lista) {
//         if (lista->conteudo.id == id) return lista;
//         lista = lista->prox;
//     }
//     return NULL;
// }

// void liberar_lista_orcamento(ListaOrcamento** lista) {
//     ListaOrcamento* atual = *lista;
//     while (atual) {
//         ListaOrcamento* prox = atual->prox;
//         free(atual);
//         atual = prox;
//     }
//     *lista = NULL;
// }



// StatusOperacao salvar_orcamento_bin(ListaOrcamento* lista, const char* nome_arquivo) {
//     FILE* f = fopen(nome_arquivo, "wb");
//     if (!f) return ERRO_ABRIR_ARQUIVO;
//     while (lista) {
//         fwrite(&lista->conteudo, sizeof(Orcamento), 1, f);
//         lista = lista->prox;
//     }
//     fclose(f);
//     return OPERACAO_SUCESSO;
// }

// StatusOperacao carregar_orcamento_bin(ListaOrcamento** lista, const char* nome_arquivo) {
//     FILE* f = fopen(nome_arquivo, "rb");
//     if (!f) return ERRO_ABRIR_ARQUIVO;
    
//     liberar_lista_orcamento(lista);
//     proximo_id_orcamento = 1;
    
//     Orcamento temp;
//     while (fread(&temp, sizeof(Orcamento), 1, f) == 1) {
//         inserir_orcamento(lista, temp);
//     }
//     fclose(f);
//     return OPERACAO_SUCESSO;
// }



// StatusOperacao remover_fisico_orcamento(ListaOrcamento** lista, int id) {
//     ListaOrcamento* atual = *lista;
//     ListaOrcamento* anterior = NULL;

//     // Procura o nó
//     while (atual != NULL && atual->conteudo.id != id) {
//         anterior = atual;
//         atual = atual->prox;
//     }

//     // Se não encontrou
//     if (atual == NULL) {
//         return ERRO_NAO_ENCONTRADO;
//     }

//     // Se for o primeiro da lista
//     if (anterior == NULL) {
//         *lista = atual->prox;
//     } else {
//         // Se for do meio ou fim
//         anterior->prox = atual->prox;
//     }

//     free(atual); // Libera a memória
//     return OPERACAO_SUCESSO;
// }

// // StatusOperacao salvar_orcamento_txt(ListaOrcamento* lista, const char* nome_arquivo) {
// //     FILE* f = fopen(nome_arquivo, "w");
// //     if (!f) return ERRO_ABRIR_ARQUIVO;
    
// //     // Cabeçalho Expandido
// //     fprintf(f, "ID;Cliente;Evento;Local;Inicio;Fim;Status;Total;ITENS_RECURSOS;ITENS_EQUIPE\n");

// //     while (lista) {
// //         Orcamento* o = &lista->conteudo;
// //         fprintf(f, "%d;%d;%s;%s;%02d/%02d/%d;%02d/%02d/%d;%d;%.2f;",
// //             o->id, o->id_cliente, o->nome_evento, o->local,
// //             o->dia_inicio, o->mes_inicio, o->ano_inicio,
// //             o->dia_fim, o->mes_fim, o->ano_fim,
// //             o->status, o->valor_total_geral);

// //         // Salva Recursos: "ID:Qtd|ID:Qtd"
// //         if (o->qtd_recursos_selecionados == 0) fprintf(f, "NONE"); //none e para verifica se a erro tipo ;;
// //         else {
// //             for(int i=0; i<o->qtd_recursos_selecionados; i++) {
// //                 fprintf(f, "%d:%d|", o->lista_recursos[i].id_recurso, o->lista_recursos[i].quantidade);
// //             }
// //         }
// //         fprintf(f, ";");

// //         // Salva Equipe: "ID:Dias|ID:Dias"
// //         if (o->qtd_equipe_selecionada == 0) fprintf(f, "NONE");
// //         else {
// //             for(int i=0; i<o->qtd_equipe_selecionada; i++) {
// //                 fprintf(f, "%d:%d|", o->lista_equipe[i].id_membro_equipe, o->lista_equipe[i].dias_trabalhados);
// //             }
// //         }
// //         fprintf(f, "\n");

// //         lista = lista->prox;
// //     }
// //     fclose(f);
// //     return OPERACAO_SUCESSO;
// // }

// StatusOperacao salvar_orcamento_txt(ListaOrcamento* lista, const char* nome_arquivo) {
//     FILE* f = fopen(nome_arquivo, "w");
//     if (!f) return ERRO_ABRIR_ARQUIVO;
    
//     // 1. Cabeçalho atualizado (sem mudanças visuais, mas importante manter ordem)
//     fprintf(f, "ID;Cliente;Evento;Local;Inicio;Fim;Status;Total;ITENS_RECURSOS;ITENS_EQUIPE;ITENS_SERVICOS\n");

//     while (lista) {
//         Orcamento* o = &lista->conteudo;
        
//         // Salva dados básicos
//         fprintf(f, "%d;%d;%s;%s;%02d/%02d/%d;%02d/%02d/%d;%d;%.2f;",
//             o->id, o->id_cliente, o->nome_evento, o->local,
//             o->dia_inicio, o->mes_inicio, o->ano_inicio,
//             o->dia_fim, o->mes_fim, o->ano_fim,
//             o->status, o->valor_total_geral);

//         // --- SALVAR RECURSOS (Agora com PREÇO) ---
//         // Formato: ID:Qtd:Preco|
//         if (o->qtd_recursos_selecionados == 0) fprintf(f, "NONE");
//         else {
//             for(int i=0; i<o->qtd_recursos_selecionados; i++) {
//                 fprintf(f, "%d:%d:%.2f|", 
//                     o->lista_recursos[i].id_recurso, 
//                     o->lista_recursos[i].quantidade,
//                     o->lista_recursos[i].valor_unitario_momento); // <--- O SEGREDO ESTÁ AQUI
//             }
//         }
//         fprintf(f, ";");

//         // --- SALVAR EQUIPE (Agora com PREÇO DA DIÁRIA) ---
//         // Formato: ID:Dias:ValorDiaria|
//         if (o->qtd_equipe_selecionada == 0) fprintf(f, "NONE");
//         else {
//             for(int i=0; i<o->qtd_equipe_selecionada; i++) {
//                 fprintf(f, "%d:%d:%.2f|", 
//                     o->lista_equipe[i].id_membro_equipe, 
//                     o->lista_equipe[i].dias_trabalhados,
//                     o->lista_equipe[i].valor_diaria_momento); // <--- SALVANDO O VALOR
//             }
//         }
//         fprintf(f, ";");

//         // --- SALVAR SERVIÇOS ---
//         // Formato: ID:ValorCombinado|
//         if (o->qtd_servicos_selecionados == 0) fprintf(f, "NONE");
//         else {
//             for(int i=0; i<o->qtd_servicos_selecionados; i++) {
//                 fprintf(f, "%d:%.2f|", 
//                     o->lista_servicos[i].id_fornecedor, 
//                     o->lista_servicos[i].valor_combinado);
//             }
//         }
//         fprintf(f, "\n");

//         lista = lista->prox;
//     }
//     fclose(f);
//     return OPERACAO_SUCESSO;
// }



// StatusOperacao carregar_orcamento_txt(ListaOrcamento** lista, const char* nome_arquivo) {
//     FILE* f = fopen(nome_arquivo, "r");
//     if (!f) return ERRO_ABRIR_ARQUIVO;
    
//     liberar_lista_orcamento(lista);
//     char buffer[4096];
    
//     if (!fgets(buffer, sizeof(buffer), f)) { fclose(f); return OPERACAO_SUCESSO; }

//     while (fgets(buffer, sizeof(buffer), f)) {
//         buffer[strcspn(buffer, "\n")] = 0;
//         Orcamento o;
//         memset(&o, 0, sizeof(Orcamento)); 

//         // --- Leitura Básica ---
//         char* token = strtok(buffer, ";"); if(!token) continue; o.id = atoi(token);
//         token = strtok(NULL, ";"); o.id_cliente = token ? atoi(token) : 0;
//         token = strtok(NULL, ";"); if(token) strcpy(o.nome_evento, token);
//         token = strtok(NULL, ";"); if(token) strcpy(o.local, token);
//         token = strtok(NULL, ";"); if(token) sscanf(token, "%d/%d/%d", &o.dia_inicio, &o.mes_inicio, &o.ano_inicio);
//         token = strtok(NULL, ";"); if(token) sscanf(token, "%d/%d/%d", &o.dia_fim, &o.mes_fim, &o.ano_fim);
//         token = strtok(NULL, ";"); if(token) o.status = atoi(token);
//         token = strtok(NULL, ";"); if(token) o.valor_total_geral = atof(token);

//         // --- LER RECURSOS (COM PREÇO) ---
//         char* strRecursos = strtok(NULL, ";");
//         if (strRecursos && strcmp(strRecursos, "NONE") != 0) {
//             char* ptr = strRecursos;
//             int id, qtd, n;
//             float valor;

//             // Tenta ler 3 itens: ID, QTD e VALOR
//             while (1) {
//                 // Tenta ler formato NOVO (com preço)
//                 if (sscanf(ptr, "%d:%d:%f|%n", &id, &qtd, &valor, &n) == 3) {
//                     int i = o.qtd_recursos_selecionados;
//                     o.lista_recursos[i].id_recurso = id;
//                     o.lista_recursos[i].quantidade = qtd;
//                     o.lista_recursos[i].valor_unitario_momento = valor; // Recupera o preço!
//                     o.qtd_recursos_selecionados++;
//                     ptr += n;
//                 }
//                 // Tenta ler formato ANTIGO (sem preço, para não quebrar arquivos velhos)
//                 else if (sscanf(ptr, "%d:%d|%n", &id, &qtd, &n) == 2) {
//                     int i = o.qtd_recursos_selecionados;
//                     o.lista_recursos[i].id_recurso = id;
//                     o.lista_recursos[i].quantidade = qtd;
//                     o.lista_recursos[i].valor_unitario_momento = 0.0f; // Infelizmente é zero
//                     o.qtd_recursos_selecionados++;
//                     ptr += n;
//                 } 
//                 else break; // Acabou a string
                
//                 if (o.qtd_recursos_selecionados >= MAX_ITENS_ORCAMENTO) break;
//             }
//         }

//         // --- LER EQUIPE (COM PREÇO) ---
//         char* strEquipe = strtok(NULL, ";");
//         if (strEquipe && strcmp(strEquipe, "NONE") != 0) {
//             char* ptr = strEquipe;
//             int id, dias, n;
//             float valor;

//             while (1) {
//                 if (sscanf(ptr, "%d:%d:%f|%n", &id, &dias, &valor, &n) == 3) {
//                     int i = o.qtd_equipe_selecionada;
//                     o.lista_equipe[i].id_membro_equipe = id;
//                     o.lista_equipe[i].dias_trabalhados = dias;
//                     o.lista_equipe[i].valor_diaria_momento = valor; // Recupera a diária!
//                     o.qtd_equipe_selecionada++;
//                     ptr += n;
//                 }
//                 else if (sscanf(ptr, "%d:%d|%n", &id, &dias, &n) == 2) {
//                     int i = o.qtd_equipe_selecionada;
//                     o.lista_equipe[i].id_membro_equipe = id;
//                     o.lista_equipe[i].dias_trabalhados = dias;
//                     o.lista_equipe[i].valor_diaria_momento = 0.0f;
//                     o.qtd_equipe_selecionada++;
//                     ptr += n;
//                 }
//                 else break;

//                 if (o.qtd_equipe_selecionada >= MAX_ITENS_ORCAMENTO) break;
//             }
//         }

//         // --- LER SERVIÇOS ---
//         char* strServicos = strtok(NULL, ";");
//         if (strServicos && strcmp(strServicos, "NONE") != 0) {
//             char* ptr = strServicos;
//             int id, n;
//             float valor;
//             while (sscanf(ptr, "%d:%f|%n", &id, &valor, &n) == 2) {
//                 int i = o.qtd_servicos_selecionados;
//                 o.lista_servicos[i].id_fornecedor = id;
//                 o.lista_servicos[i].valor_combinado = valor;
//                 o.qtd_servicos_selecionados++;
//                 ptr += n;
//                 if (o.qtd_servicos_selecionados >= MAX_ITENS_ORCAMENTO) break;
//             }
//         }

//         o.qtd_dias = (o.dia_fim - o.dia_inicio) + 1;
//         if(o.qtd_dias < 1) o.qtd_dias = 1;
//         o.valor_total_recursos = 0; // Recalcular se necessário na exibição
//         o.ativo = 1;
//         inserir_orcamento(lista, o);
//     }
//     fclose(f);
//     return OPERACAO_SUCESSO;
// }


// // Função auxiliar segura para adicionar recurso
// int adicionar_recurso_ao_orcamento(Orcamento* orc, int id_recurso, int quantidade, float preco_total_item) {
//     if (orc->qtd_recursos_selecionados >= MAX_ITENS_ORCAMENTO) {
//         printf("Erro: Limite de itens no orçamento atingido!\n");
//         return 0; // Falha
//     }

//     int i = orc->qtd_recursos_selecionados;
    
//     // 1. Salva os dados
//     orc->lista_recursos[i].id_recurso = id_recurso;
//     orc->lista_recursos[i].quantidade = quantidade;
    
//     // 2. Atualiza o preço
//     orc->valor_total_recursos += preco_total_item;
//     orc->valor_total_geral += preco_total_item;

//     // 3. O PASSO CRUCIAL (Sem isso, ele salva como NONE no arquivo!)
//     orc->qtd_recursos_selecionados++; 
    
//     return 1; // Sucesso
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> // Importante para corrigir o erro de Ponto/Virgula
#include "orcamento.h"

static int proximo_id_orcamento = 1;

// --- FUNÇÃO AUXILIAR PARA BLINDAR A LEITURA DE FLOAT ---
// Converte string para float independente se o PC usa ponto ou virgula
float string_para_float_universal(char* str) {
    if (!str || strlen(str) == 0) return 0.0f;
    
    char buffer[50];
    strncpy(buffer, str, 49);
    buffer[49] = '\0';
    
    // Descobre qual o separador decimal do sistema (Ponto ou Virgula?)
    struct lconv * lc = localeconv();
    char sep_sistema = *lc->decimal_point; // Pega o separador atual
    
    // Varre a string e troca qualquer ponto ou virgula pelo separador do sistema
    for(int i=0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '.' || buffer[i] == ',') {
            buffer[i] = sep_sistema;
        }
    }
    
    return (float)atof(buffer);
}
// -------------------------------------------------------

StatusOperacao inserir_orcamento(ListaOrcamento** lista, Orcamento novo) {
    ListaOrcamento* novo_no = (ListaOrcamento*) malloc(sizeof(ListaOrcamento));
    if (!novo_no) return ERRO_ALOCACAO_MEMORIA;

    if (novo.id <= 0) novo.id = proximo_id_orcamento++;
    else if (novo.id >= proximo_id_orcamento) proximo_id_orcamento = novo.id + 1;

    novo_no->conteudo = novo;
    novo_no->prox = NULL;

    if (*lista == NULL) {
        *lista = novo_no;
    } else {
        ListaOrcamento* aux = *lista;
        while (aux->prox) aux = aux->prox;
        aux->prox = novo_no;
    }
    return OPERACAO_SUCESSO;
}

ListaOrcamento* buscar_orcamento_por_id(ListaOrcamento* lista, int id) {
    while (lista) {
        if (lista->conteudo.id == id) return lista;
        lista = lista->prox;
    }
    return NULL;
}

void liberar_lista_orcamento(ListaOrcamento** lista) {
    ListaOrcamento* atual = *lista;
    while (atual) {
        ListaOrcamento* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    *lista = NULL;
}

StatusOperacao salvar_orcamento_bin(ListaOrcamento* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "wb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    while (lista) {
        fwrite(&lista->conteudo, sizeof(Orcamento), 1, f);
        lista = lista->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

StatusOperacao carregar_orcamento_bin(ListaOrcamento** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "rb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    
    liberar_lista_orcamento(lista);
    proximo_id_orcamento = 1;
    
    Orcamento temp;
    while (fread(&temp, sizeof(Orcamento), 1, f) == 1) {
        inserir_orcamento(lista, temp);
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

StatusOperacao remover_fisico_orcamento(ListaOrcamento** lista, int id) {
    ListaOrcamento* atual = *lista;
    ListaOrcamento* anterior = NULL;

    while (atual != NULL && atual->conteudo.id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return ERRO_NAO_ENCONTRADO;

    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    return OPERACAO_SUCESSO;
}

// === SALVAR TXT (CORRIGIDO PARA SALVAR PREÇOS) ===
StatusOperacao salvar_orcamento_txt(ListaOrcamento* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "w");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    
    fprintf(f, "ID;Cliente;Evento;Local;Inicio;Fim;Status;Total;ITENS_RECURSOS;ITENS_EQUIPE;ITENS_SERVICOS\n");

    while (lista) {
        Orcamento* o = &lista->conteudo;
        
        fprintf(f, "%d;%d;%s;%s;%02d/%02d/%d;%02d/%02d/%d;%d;%.2f;",
            o->id, o->id_cliente, o->nome_evento, o->local,
            o->dia_inicio, o->mes_inicio, o->ano_inicio,
            o->dia_fim, o->mes_fim, o->ano_fim,
            o->status, o->valor_total_geral);

        // --- SALVAR RECURSOS: ID:Qtd:Preco| ---
        if (o->qtd_recursos_selecionados == 0) fprintf(f, "NONE");
        else {
            for(int i=0; i<o->qtd_recursos_selecionados; i++) {
                // %.2f salva com ponto ou virgula dependendo do locale, 
                // mas nossa funcao de carregar agora entende os dois!
                fprintf(f, "%d:%d:%.2f|", 
                    o->lista_recursos[i].id_recurso, 
                    o->lista_recursos[i].quantidade,
                    o->lista_recursos[i].valor_unitario_momento); 
            }
        }
        fprintf(f, ";");

        // --- SALVAR EQUIPE: ID:Dias:ValorDiaria| ---
        if (o->qtd_equipe_selecionada == 0) fprintf(f, "NONE");
        else {
            for(int i=0; i<o->qtd_equipe_selecionada; i++) {
                fprintf(f, "%d:%d:%.2f|", 
                    o->lista_equipe[i].id_membro_equipe, 
                    o->lista_equipe[i].dias_trabalhados,
                    o->lista_equipe[i].valor_diaria_momento);
            }
        }
        fprintf(f, ";");

        // --- SALVAR SERVIÇOS: ID:Valor| ---
        if (o->qtd_servicos_selecionados == 0) fprintf(f, "NONE");
        else {
            for(int i=0; i<o->qtd_servicos_selecionados; i++) {
                fprintf(f, "%d:%.2f|", 
                    o->lista_servicos[i].id_fornecedor, 
                    o->lista_servicos[i].valor_combinado);
            }
        }
        fprintf(f, "\n");

        lista = lista->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

// === CARREGAR TXT (BLINDADO COM PARSER MANUAL) ===
StatusOperacao carregar_orcamento_txt(ListaOrcamento** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    
    liberar_lista_orcamento(lista);
    char buffer[4096];
    
    if (!fgets(buffer, sizeof(buffer), f)) { fclose(f); return OPERACAO_SUCESSO; }

    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = 0;
        Orcamento o;
        memset(&o, 0, sizeof(Orcamento)); 

        // Lê os campos básicos usando strtok
        char* token = strtok(buffer, ";"); if(!token) continue; o.id = atoi(token);
        token = strtok(NULL, ";"); o.id_cliente = token ? atoi(token) : 0;
        token = strtok(NULL, ";"); if(token) strcpy(o.nome_evento, token);
        token = strtok(NULL, ";"); if(token) strcpy(o.local, token);
        token = strtok(NULL, ";"); if(token) sscanf(token, "%d/%d/%d", &o.dia_inicio, &o.mes_inicio, &o.ano_inicio);
        token = strtok(NULL, ";"); if(token) sscanf(token, "%d/%d/%d", &o.dia_fim, &o.mes_fim, &o.ano_fim);
        token = strtok(NULL, ";"); if(token) o.status = atoi(token);
        
        // LEITURA SEGURA DO TOTAL GERAL
        token = strtok(NULL, ";"); 
        if(token) o.valor_total_geral = string_para_float_universal(token);

        // --- LER RECURSOS (PARSER MANUAL ROBUSTO) ---
        char* strRecursos = strtok(NULL, ";");
        if (strRecursos && strcmp(strRecursos, "NONE") != 0) {
            char* ptr = strRecursos;
            while (*ptr != '\0') {
                if (*ptr == '|') { ptr++; continue; } // Pula separador vazio
                
                // 1. Ler ID
                int id = (int)strtol(ptr, &ptr, 10);
                if (*ptr == ':') ptr++; 

                // 2. Ler Qtd
                int qtd = (int)strtol(ptr, &ptr, 10);
                if (*ptr == ':') ptr++; 

                // 3. Ler Preço (como string primeiro, depois converte)
                char precoStr[50]; int k=0;
                while (*ptr != '|' && *ptr != '\0' && k < 49) {
                    precoStr[k++] = *ptr++;
                }
                precoStr[k] = '\0';
                
                float valor = string_para_float_universal(precoStr); // MÁGICA ACONTECE AQUI
                
                // Adiciona na struct
                if (o.qtd_recursos_selecionados < MAX_ITENS_ORCAMENTO) {
                    int i = o.qtd_recursos_selecionados;
                    o.lista_recursos[i].id_recurso = id;
                    o.lista_recursos[i].quantidade = qtd;
                    o.lista_recursos[i].valor_unitario_momento = valor;
                    o.qtd_recursos_selecionados++;
                }
            }
        }

        // --- LER EQUIPE (PARSER MANUAL ROBUSTO) ---
        char* strEquipe = strtok(NULL, ";");
        if (strEquipe && strcmp(strEquipe, "NONE") != 0) {
            char* ptr = strEquipe;
            while (*ptr != '\0') {
                if (*ptr == '|') { ptr++; continue; }
                
                int id = (int)strtol(ptr, &ptr, 10);
                if (*ptr == ':') ptr++; 
                
                int dias = (int)strtol(ptr, &ptr, 10);
                if (*ptr == ':') ptr++; 
                
                char precoStr[50]; int k=0;
                while (*ptr != '|' && *ptr != '\0' && k < 49) {
                    precoStr[k++] = *ptr++;
                }
                precoStr[k] = '\0';
                
                float valor = string_para_float_universal(precoStr);
                
                if (o.qtd_equipe_selecionada < MAX_ITENS_ORCAMENTO) {
                    int i = o.qtd_equipe_selecionada;
                    o.lista_equipe[i].id_membro_equipe = id;
                    o.lista_equipe[i].dias_trabalhados = dias;
                    o.lista_equipe[i].valor_diaria_momento = valor;
                    o.qtd_equipe_selecionada++;
                }
            }
        }

        // --- LER SERVIÇOS (PARSER MANUAL ROBUSTO) ---
        char* strServicos = strtok(NULL, ";");
        if (strServicos && strcmp(strServicos, "NONE") != 0) {
            char* ptr = strServicos;
            while (*ptr != '\0') {
                if (*ptr == '|') { ptr++; continue; }
                
                int id = (int)strtol(ptr, &ptr, 10);
                if (*ptr == ':') ptr++; 
                
                char precoStr[50]; int k=0;
                while (*ptr != '|' && *ptr != '\0' && k < 49) {
                    precoStr[k++] = *ptr++;
                }
                precoStr[k] = '\0';
                
                float valor = string_para_float_universal(precoStr);
                
                if (o.qtd_servicos_selecionados < MAX_ITENS_ORCAMENTO) {
                    int i = o.qtd_servicos_selecionados;
                    o.lista_servicos[i].id_fornecedor = id;
                    o.lista_servicos[i].valor_combinado = valor;
                    strcpy(o.lista_servicos[i].descricao_servico, "Carregado");
                    o.qtd_servicos_selecionados++;
                }
            }
        }

        o.qtd_dias = (o.dia_fim - o.dia_inicio) + 1;
        if(o.qtd_dias < 1) o.qtd_dias = 1;
        
        // Recalcular parciais para consistência
        o.valor_total_recursos = 0;
        for(int i=0; i<o.qtd_recursos_selecionados; i++)
            o.valor_total_recursos += (o.lista_recursos[i].valor_unitario_momento * o.lista_recursos[i].quantidade * o.qtd_dias);
            
        o.valor_total_equipe = 0;
        for(int i=0; i<o.qtd_equipe_selecionada; i++)
            o.valor_total_equipe += (o.lista_equipe[i].valor_diaria_momento * o.lista_equipe[i].dias_trabalhados);
            
        o.valor_total_servicos = 0;
        for(int i=0; i<o.qtd_servicos_selecionados; i++)
            o.valor_total_servicos += o.lista_servicos[i].valor_combinado;

        o.ativo = 1;
        inserir_orcamento(lista, o);
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}

int adicionar_recurso_ao_orcamento(Orcamento* orc, int id_recurso, int quantidade, float preco_total_item) {
    if (orc->qtd_recursos_selecionados >= MAX_ITENS_ORCAMENTO) {
        printf("Erro: Limite de itens no orcamento atingido!\n");
        return 0;
    }
    int i = orc->qtd_recursos_selecionados;
    orc->lista_recursos[i].id_recurso = id_recurso;
    orc->lista_recursos[i].quantidade = quantidade;
    orc->valor_total_recursos += preco_total_item;
    orc->valor_total_geral += preco_total_item;
    orc->qtd_recursos_selecionados++; 
    return 1;
}