#include <stdio.h>
#include <string.h>
#include "mostrar_dados.h"
#include "formatacao.h"

void view_exibir_mensagem(const char* mensagem) {
    printf(">> %s\n", mensagem);
}




void view_imprimir_lista_produtora(Listaprodutora* lista) {
    if (lista == NULL) {
        printf("\n>> A lista de produtoras esta vazia.\n");
        return;
    }
    printf("\n--- Lista de Produtoras Cadastradas ---\n");
    for (Listaprodutora* aux = lista; aux != NULL; aux = aux->prox) {
        view_imprimir_produtora_unico(aux);
    }
}

void view_imprimir_produtora_unico(Listaprodutora* no_produtora) {
    if (no_produtora == NULL) return;

    printf("----------------------------------------\n");
    printf("\n   |Codigo                 | :  %d ", no_produtora->conteudo.id);
    printf("\n   |Nome Fantasia          | :  %s ", no_produtora->conteudo.nome_fantasia);
    printf("\n   |Razao Social           | :  %s ", no_produtora->conteudo.razao_social);
    printf("\n   |Inscricao Est          | :  %s ", no_produtora->conteudo.inscricao_estadual);
    printf("\n   |CNPJ                   | :  ");
    imprimir_cnpj_formatado(no_produtora->conteudo.cnpj);
    printf("\n   |Endereco               | :  %s ", no_produtora->conteudo.endereco_completo);
    printf("\n   |Telefone               | :  ");
    imprimir_telefone_formatado(no_produtora->conteudo.telefone);
    printf("\n   |Email                  | :  %s ", no_produtora->conteudo.email);
    printf("\n   |Nome do responsavel    | :  %s ", no_produtora->conteudo.nome_responsavel);
    printf("\n   |telefone do responsavel| :  %s ", no_produtora->conteudo.telefone_responsavel);
    printf("\n   |Status                 | :  %s ", no_produtora->conteudo.ativo ? "Ativo" : "Inativo");
}


void view_imprimir_lista(ListaCliente* lista) {
    if (lista == NULL) {
        printf("\n>> A lista de clientes esta vazia.\n");
        return;
    }
    printf("\n--- Lista de Clientes Cadastrados ---\n");
    for (ListaCliente* aux = lista; aux != NULL; aux = aux->prox) {
        view_imprimir_cliente_unico(aux);
    }
}

void view_imprimir_cliente_unico(ListaCliente* no_cliente) {
    if (no_cliente == NULL) return;
    printf("\n----------------------------------------\n");
    printf("\n  |Codigo      | : %d ", no_cliente->conteudo.id);
    if (no_cliente->conteudo.tipo == PESSOA_FISICA) {
    printf("\n  |Nome        | : %s ", no_cliente->conteudo.doc.pf.nome);
    printf("\n  |CPF         | : ");
    imprimir_cpf_formatado(no_cliente->conteudo.doc.pf.cpf);
    } else {
    printf("\n  |Razao Social| : %s ", no_cliente->conteudo.doc.pj.razao_social);
    printf("\n  |CNPJ        | : ");
    imprimir_cnpj_formatado(no_cliente->conteudo.doc.pj.cnpj);
    }
    printf("\n  |Endereco    | : %s ", no_cliente->conteudo.endereco_completo);
    printf("\n  |Telefone    | : ");
    imprimir_telefone_formatado(no_cliente->conteudo.telefone);
    printf("\n  |Email       | : %s ", no_cliente->conteudo.email);
    printf("\n  |Contato     | : %s ", no_cliente->conteudo.nome_contato);
    printf("\n  |Status      | : %s ", no_cliente->conteudo.ativo ? "Ativo" : "Inativo");

}


void view_imprimir_lista_equipe(Listaequipe* lista) {
    if (lista == NULL) {
        printf("\n>> A lista de membros da equipe esta vazia.\n");
        return;
    }
    printf("\n--- Lista de Membros da Equipe ---\n");
    for (Listaequipe* aux = lista; aux != NULL; aux = aux->prox) {
        view_imprimir_equipe_unico(aux);
    }
}

void view_imprimir_equipe_unico(Listaequipe* no_equipe) {
    if (no_equipe == NULL) {
         return;
    }
    printf("\n--- Lista de Membros da Equipe ---\n");

        printf("\n----------------------------------------\n");
        printf("\n |Codigo      | : %d ", no_equipe->conteudo.id);
        printf("\n |Nome        | : %s ", no_equipe->conteudo.nome);
        printf("\n |CPF         | : ");
        imprimir_cpf_formatado(no_equipe->conteudo.cpf);
        printf("\n");
        printf("\n |Funcao      | : %s ", no_equipe->conteudo.funcao);
        printf("\n |Valor Diaria| : R$ %.2f ", no_equipe->conteudo.valor_diaria);
        printf("\n |Status      | : %s ", no_equipe->conteudo.ativo ? "Ativo" : "Inativo");

}





void view_imprimir_lista_recurso(Listarecurso* lista) {
    if (lista == NULL) {
        printf("\n>> A lista de recursos esta vazia.\n");
        return;
    }
    printf("\n--- Lista de Recursos Cadastrados ---\n");
    for (Listarecurso* aux = lista; aux != NULL; aux = aux->prox) {
        view_imprimir_recurso_unico(aux);
    }
}

void view_imprimir_recurso_unico(Listarecurso* no_recurso) {
    if (no_recurso == NULL) return;

    printf("\n----------------------------------------\n");
    printf("\n |Codigo               | : %d ", no_recurso->conteudo.id);
    printf("\n |Descricao            | : %s ", no_recurso->conteudo.descricao);
    printf("\n |Categoria            | : %s ", no_recurso->conteudo.categoria);
    printf("\n |Quantidade em estoque| : %d ", no_recurso->conteudo.quantidade);
    printf("\n |Preco de Custo       | : R$ %.2f ", no_recurso->conteudo.preco_de_custo);
    printf("\n |Valor da Locacao     | : R$ %.2f ", no_recurso->conteudo.valor_da_locacao);
    printf("\n |Status               | : %s ", no_recurso->conteudo.ativo ? "Ativo" : "Inativo");
}




void view_imprimir_lista_fornecedor(Listafornecedor* lista) {
    if (lista == NULL) {
        printf("\n>> A lista de fornecedores esta vazia.\n");
        return;
    }
    printf("\n--- Lista de Fornecedores Cadastrados ---\n");
    for (Listafornecedor* aux = lista; aux != NULL; aux = aux->prox) {
        view_imprimir_fornecedor_unico(aux);
    }
}

void view_imprimir_fornecedor_unico(Listafornecedor* no_fornecedor) {
    if (no_fornecedor == NULL) return;

    printf("\n----------------------------------------\n");
    printf("\n |Codigo         | : %d ", no_fornecedor->conteudo.id);
    printf("\n |Nome Fantasia  | : %s ", no_fornecedor->conteudo.nome_fantasia);
    printf("\n |Razao Social   | : %s ", no_fornecedor->conteudo.razao_social);
      if (no_fornecedor->conteudo.tipoF == PESSOA_FISICA_FOR) {
    printf("\n |CPF            | : ");
        imprimir_cpf_formatado(no_fornecedor->conteudo.docfornecedor.pf.cpf);
    } else {
    printf("\n |CNPJ           | : ");
        imprimir_cnpj_formatado(no_fornecedor->conteudo.docfornecedor.pj.cnpj);
    }
    printf("\n |Endereco       | : %s ", no_fornecedor->conteudo.endereco_completo);
    printf("\n |Telefone       | : "); imprimir_telefone_formatado(no_fornecedor->conteudo.telefone);
    printf("\n |tipo de Servico| : %s ", no_fornecedor->conteudo.tipo_servico);
    printf("\n |Status         | : %s ", no_fornecedor->conteudo.ativo ? "Ativo" : "Inativo");
}



void view_imprimir_lista_operador(Listaoperador* lista) {
    if (lista == NULL) {
        printf("\n>> A lista de operadores esta vazia.\n");
        return;
    }
    printf("\n--- Lista de Operadores Cadastrados ---\n");
    for (Listaoperador* aux = lista; aux != NULL; aux = aux->prox) {
        view_imprimir_operador_unico(aux);
    }
}

void view_imprimir_operador_unico(Listaoperador* no_operador) {
    if (no_operador == NULL) return;

    printf("\n----------------------------------------------");
    printf("\n |Codigo      | : %d ", no_operador->conteudo.id);
    printf("\n |Nome        | : %s ", no_operador->conteudo.nome);
    printf("\n |Usuario     | : %s ", no_operador->conteudo.usuario);
    printf("\n |Senha       | : ******** ");
    printf("\n |Status      | : %s ", no_operador->conteudo.ativo ? "Ativo" : "Inativo");
}


// --- ORÇAMENTOS DETALHADOS ---

void view_imprimir_orcamento_unico(Orcamento* o, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq) {
    if (o == NULL) return;

    printf("\n=========================================================================\n");
    printf(" ORCAMENTO #%d | STATUS: ", o->id);
    
    switch(o->status) {
        case STATUS_EM_ANALISE: printf("EM ANALISE"); break;
        case STATUS_APROVADO: printf("APROVADO (Reservado)"); break;
        case STATUS_FINALIZADO: printf("FINALIZADO"); break;
        case STATUS_CANCELADO: printf("CANCELADO"); break;
        default: printf("DESCONHECIDO");
    }
    printf("\n=========================================================================\n");
    printf(" Novo Evento  : %s\n", o->nome_evento);
    printf(" ID Cliente  : %d\n", o->id_cliente);
    printf(" Local       : %s\n", o->local);
    printf(" Periodo     : %02d/%02d/%d ate %02d/%02d/%d (%d dias)\n", 
           o->dia_inicio, o->mes_inicio, o->ano_inicio, 
           o->dia_fim, o->mes_fim, o->ano_fim, o->qtd_dias);
    
    printf("\n-------------------------------------------------------------------------\n");
    printf(" [ITENS DO ORCAMENTO]\n");

    // 1. LISTA OS RECURSOS
    if (o->qtd_recursos_selecionados > 0) {
        printf("\n > Equipamentos/Recursos:\n");
        for (int i = 0; i < o->qtd_recursos_selecionados; i++) {
            int id = o->lista_recursos[i].id_recurso;
            int qtd = o->lista_recursos[i].quantidade;
            float val_un = o->lista_recursos[i].valor_unitario_momento;
            float subtotal = val_un * qtd * o->qtd_dias; // Valor x Qtd x Dias

            // Busca o nome se a lista foi fornecida
            char nome_rec[100] = "Item nao encontrado";
            if (l_rec != NULL) {
                Listarecurso* no = buscar_recurso_por_id(l_rec, id);
                if (no) strcpy(nome_rec, no->conteudo.descricao);
            }

            printf("   - %dx %-20s (R$ %.2f/dia) = R$ %.2f\n", qtd, nome_rec, val_un, subtotal);
        }
        printf("   Subtotal Equipamentos: R$ %.2f\n", o->valor_total_recursos);
    }

    // 2. LISTAR SERVIÇOS
    if (o->qtd_servicos_selecionados > 0) {
        printf("\n > Servicos Terceirizados:\n");
        for (int i = 0; i < o->qtd_servicos_selecionados; i++) {
            int id = o->lista_servicos[i].id_fornecedor;
            float val = o->lista_servicos[i].valor_combinado;
            char* desc = o->lista_servicos[i].descricao_servico;

            char nome_for[100] = "Desconhecido";
            if (l_for != NULL) {
                Listafornecedor* no = buscar_fornecedor_por_id(l_for, id);
                if (no) strcpy(nome_for, no->conteudo.nome_fantasia);
            }

            printf("   - [%s] %s = R$ %.2f\n", nome_for, desc, val);
        }
        printf("   Subtotal Servicos: R$ %.2f\n", o->valor_total_servicos);
    }

    // LISTAR EQUIPE
    if (o->qtd_equipe_selecionada > 0) {
        printf("\n > Equipe Interna:\n");
        for (int i = 0; i < o->qtd_equipe_selecionada; i++) {
            int id = o->lista_equipe[i].id_membro_equipe;
            float val = o->lista_equipe[i].valor_diaria_momento;
            int dias = o->lista_equipe[i].dias_trabalhados;
            float subtotal = val * dias;

            char nome_eq[100] = "Desconhecido";
            if (l_eq != NULL) {
                Listaequipe* no = buscar_equipe_por_id(l_eq, id);
                if (no) strcpy(nome_eq, no->conteudo.nome);
            }

            printf("   - %s (%d dias x R$ %.2f) = R$ %.2f\n", nome_eq, dias, val, subtotal);
        }
        printf("   Subtotal Equipe: R$ %.2f\n", o->valor_total_equipe);
    }

    printf("-------------------------------------------------------------------------\n");
    printf(" (=) TOTAL GERAL            : R$ %.2f\n", o->valor_total_geral);
    printf("=========================================================================\n");
}

void view_imprimir_lista_orcamento(ListaOrcamento* lista, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq) {
    if (lista == NULL) {
        view_exibir_mensagem("\n>> Nenhum orcamento cadastrado.");
        return;
    }
    printf("\n=== LISTA DE ORCAMENTOS ===\n");
    while (lista != NULL) {
        view_imprimir_orcamento_unico(&lista->conteudo, l_rec, l_for, l_eq);
        lista = lista->prox;
    }
}

void view_imprimir_lista_orcamento_por_status(ListaOrcamento* lista, int status_filtro, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq) {
    int encontrou = 0;
    if (lista == NULL) {
        printf("\n>> Nenhum orcamento cadastrado no sistema.\n");
        return;
    }
    
    char* titulo;
    if (status_filtro == 0) titulo = "EM ANALISE (Orcamentos)";
    else if (status_filtro == 1) titulo = "APROVADOS (Eventos Futuros)";
    else if (status_filtro == 2) titulo = "FINALIZADOS (Historico)";
    else titulo = "CANCELADOS";

    printf("\n=== LISTA: %s ===\n", titulo);
    while (lista != NULL) {
        if (lista->conteudo.status == status_filtro) {
            view_imprimir_orcamento_unico(&lista->conteudo, l_rec, l_for, l_eq);
            encontrou = 1;
        }
        lista = lista->prox;
    }
    if (!encontrou) printf(">> Nenhum registro encontrado com este status.\n");
}



void view_exibir_ocupacao_recurso(int id_recurso, char* nome, int dia_i, int mes_i, int ano_i, int dia_f, int mes_f, int ano_f, int qtd) {
    printf(">> RESERVADO: %s | Qtd: %d | Periodo: %02d/%02d/%d a %02d/%02d/%d\n", 
           nome, qtd, dia_i, mes_i, ano_i, dia_f, mes_f, ano_f);
}

// --- RELATÓRIOS FINANCEIROS ---

void view_imprimir_relatorio_financeiro(ListaContaPagar* l_cp, ListaContaReceber* l_cr) {
    printf("\n=== RELATORIO DE CONTAS ===\n");
    
    printf("\n--- CONTAS A PAGAR (Saidas Previstas) ---\n");
    if (l_cp == NULL) printf("   (Nenhuma conta pendente)\n");
    while(l_cp) {
        printf(" ID: %d | Desc: %-20s | Valor: R$ %8.2f | Venc: %s | Status: %s\n", 
               l_cp->conteudo.id, 
               l_cp->conteudo.descricao, 
               l_cp->conteudo.valor_total, 
               l_cp->conteudo.data_vencimento, 
               l_cp->conteudo.status ? "[PAGO]" : "[PENDENTE]");
        l_cp = l_cp->prox;
    }

    printf("\n--- CONTAS A RECEBER (Entradas Previstas) ---\n");
    if (l_cr == NULL) printf("   (Nenhuma fatura a receber)\n");
    while(l_cr) {
        printf(" ID: %d | Desc: %-20s | Valor: R$ %8.2f | Venc: %s | Status: %s\n", 
               l_cr->conteudo.id, 
               l_cr->conteudo.descricao, 
               l_cr->conteudo.valor_total, 
               l_cr->conteudo.data_vencimento, 
               l_cr->conteudo.status ? "[RECEBIDO]" : "[PENDENTE]");
        l_cr = l_cr->prox;
    }
    printf("=========================================================================\n");
}

void view_imprimir_extrato_caixa_detalhado(ListaCaixa* lista) {
    float saldo = 0;
    printf("\n=== EXTRATO DE CAIXA (Fluxo) ===\n");
    
    if (lista == NULL) printf("   (Caixa sem movimentacoes)\n");

 //lista de caixa
    while (lista) {
        char* tipo = (lista->conteudo.tipo == 1) ? "ENTRADA (+)" : "SAIDA   (-)";
        float val = lista->conteudo.valor;
        
        // Atualiza saldo total
        if (lista->conteudo.tipo == 1) saldo += val;
        else saldo -= val;

        printf("[%s] %s R$ %8.2f | Ref: %s\n", 
               lista->conteudo.data, tipo, val, lista->conteudo.descricao);
        
        lista = lista->prox;
    }
    printf("=========================================================================\n");
    printf("SALDO ATUAL DO CAIXA: R$ %.2f\n", saldo);
    printf("=========================================================================\n");
}



void view_imprimir_nota_fiscal_detalhada(void* lista_itens, int qtd_itens, float total_prod, float total_frete, float total_imp) {
    ItemCompraTemp* itens = (ItemCompraTemp*) lista_itens;
    
    printf("\n=========================================================================\n");
    printf("          PREVIA DA NOTA FISCAL (COMPRA)                                  \n");
    printf("==========================================================================\n");
    printf(" ITEM                          | QTD | UNITARIO | SUBTOTAL                \n");
    printf("--------------------------------------------------------------------------\n");

    float soma_itens = 0;
    for (int i = 0; i < qtd_itens; i++) {
        float subtotal = itens[i].qtd * itens[i].custo;
        soma_itens += subtotal;
        
        // Formatação bonita com espaçamento fixo
        printf(" %-29s | %3d | R$ %6.2f | R$ %6.2f\n", 
               itens[i].nome, itens[i].qtd, itens[i].custo, subtotal);
    }
    
    printf("--------------------------------------------------------------------------\n");
    printf(" (+) Total Produtos : R$ %.2f\n", total_prod);
    printf(" (+) Frete Total    : R$ %.2f\n", total_frete);
    printf(" (+) Impostos Totais: R$ %.2f\n", total_imp);
    printf("==========================================================================\n");
    printf(" (=) TOTAL A PAGAR  : R$ %.2f\n", total_prod + total_frete + total_imp);
    printf("==========================================================================\n");
}


//implementaçoes nao tao genericas mas funcionam bem


void view_exibir_cabecalho_atualizacao(const char* entidade, int id) {
    printf("\n--- Digite os NOVOS dados para %s (ID: %d) ---\n", entidade, id);
}

void view_exibir_erro_busca_id(const char* entidade, int id) {
    printf("\n>> AVISO: %s com Codigo %d nao encontrado.\n", entidade, id);
}

void view_exibir_msg_retornando() {
    printf("\n>> Retornando ao menu principal...\n");
}


// --- IMPLEMENTAÇÕES NOVAS DO FINANCEIRO 

void view_exibir_cabecalho_nota_fiscal() {
    printf("\n--- SELECIONAR ITENS DA NOTA ---\n");
}

void view_exibir_item_adicionado_nota() {
    printf(">> Item adicionado a lista temporaria.\n");
}

void view_exibir_atualizacao_estoque(const char* nome, int qtd_antiga, int qtd_nova, float novo_preco) {
    printf("   [%s] Estoque: %d->%d | Novo Aluguel: R$ %.2f\n", nome, qtd_antiga, qtd_nova, novo_preco);
}

void view_exibir_confirmacao_entrada_nota() {
    printf("\nConfirma a entrada desta Nota Fiscal? (1-Sim / 0-Cancelar): ");
}

void view_exibir_pagamento_avista_sucesso() {
    printf(">> Pago a vista (Caixa).\n");
}

void view_exibir_parcela_gerada(int num, int total, float valor, const char* vencto) {
    printf(" -> Parcela %d/%d: R$ %.2f (Venc: %s)\n", num, total, valor, vencto);
}

void view_exibir_confirmacao_pagamento(float valor) {
    printf("Pagar R$ %.2f? (1-Sim / 0-Nao): ", valor);
}

void view_exibir_confirmacao_recebimento(float valor) {
    printf("Receber R$ %.2f? (1-Sim / 0-Nao): ", valor);
}

void view_exibir_sucesso_pagamento() {
    printf(">> Pago e removido da lista de pendencias!\n");
}

void view_exibir_sucesso_recebimento() {
    printf(">> Recebido e removido da lista!\n");
}




// --- IMPLEMENTAÇÃO GENÉRICA INTELIGENTE ---

void view_exibir_titulo(const char* titulo) {
    printf("\n=== %s ===\n", titulo);
}

void view_exibir_alerta(const char* tipo, const char* mensagem) {
    // Ex: ">> ERRO: Recurso nao encontrado."
    printf(">> %s: %s\n", tipo, mensagem);
}

void view_exibir_linha_detalhe(const char* rotulo, const char* valor) {
    printf(" - %-20s: %s\n", rotulo, valor);
}


// --- ESPECÍFICAS NECESSÁRIAS ---

void view_exibir_status_estoque(const char* nome, int total, int ocupado, int carrinho, int disponivel) {
    printf("\n>> Item: %s\n", nome);
    printf("   Estoque Total: %d | Ocupado (Outros): %d | No Carrinho: %d\n", total, ocupado, carrinho);
    printf("   >> DISPONIVEL AGORA: %d\n", disponivel);
}

void view_exibir_item_carrinho_orcamento(const char* nome, int id, int qtd) {
    printf(" - [ID %d] %s: %d unidades\n", id, nome, qtd);
}

void view_exibir_detalhes_estoque(const char* nome, int total, int ocupado, int carrinho, int disponivel) {
    printf("\n>> Item: %s\n", nome);
    printf("   Estoque Total: %d | Ocupado (Outros Eventos): %d\n", total, ocupado);
    printf("   Ja neste orcamento: %d\n", carrinho);
    printf("   >> DISPONIVEL PARA ADICIONAR: %d\n", disponivel);
}

void view_exibir_msg_qtd_atualizada(int nova_qtd) {
    printf(">> Quantidade atualizada para %d!\n", nova_qtd);
}

void view_exibir_confirmacao_acao(const char* acao, const char* nome_objeto) {
    // Exemplo de resultado: "Tem certeza que deseja APAGAR o evento 'Festa da Firma'? ..."
    printf("\nTem a certeza que deseja %s '%s'? (1-Sim / 0-Nao): ", acao, nome_objeto);
}


void view_exibir_resumo_evento(const char* nome, float total) {
    printf("\n--- RESUMO: %s ---\nTOTAL: R$ %.2f\n", nome, total);
}

void view_exibir_menu_pagamento_evento() {
    printf("\nPagamento:\n1. A Vista (Caixa)\n2. Credito Parcelado (Entrada + Parcelas)\nOpcao: ");
}

void view_exibir_prompt_data_simples() {
    printf("Data: ");
}

void view_exibir_prompt_valor_entrada() {
    printf("Valor de Entrada (0 se nao houver): ");
}

void view_exibir_prompt_data_vencimento() {
    printf("Data do Recebimento da Entrada /  Vencimento: ");
}

void view_exibir_sucesso_entrada_caixa(float valor) {
    printf(">> Entrada de R$ %.2f lancada no Caixa.\n", valor);
}

void view_exibir_prompt_parcelas(float restante) {
    printf("Numero de parcelas (R$ %.2f): ", restante);
}

void view_exibir_detalhe_fatura(int num, float valor, const char* venc) {
    printf(" -> Fatura %d: R$ %.2f (Venc: %s)\n", num, valor, venc);
}




// ...
void view_exibir_pergunta_adicionar_fornecedor() {
    printf("\nFornecedores? (1-Sim) (0-Nao): ");
}

void view_exibir_pergunta_adicionar_equipe() {
    printf("\nEquipe? (1-Sim) (0-Nao): ");
}

void view_exibir_prompt_id_item_orcamento(const char* tipo_item) {
    printf("ID do %s (0 fim): ", tipo_item);
}

void view_exibir_prompt_descricao_servico() {
    printf("Descricao: ");
}

void view_exibir_prompt_valor_servico() {
    printf("Valor: ");
}

void view_exibir_sucesso_criacao_orcamento(float total) {
    printf(">> CRIADO! Total: R$ %.2f\n", total);
}

void view_generico_imprimir_linha(const char* linha) {
    printf("%s\n", linha);
}

void view_generico_imprimir_titulo(const char* titulo) {
    printf("\n========================================\n");
    printf(" RELATORIO: %s\n", titulo);
    printf("========================================\n");
}

void view_generico_imprimir_total(double valor, const char* texto_descricao) {
    printf("----------------------------------------\n");
    printf(" %s: R$ %.2f\n", texto_descricao, valor);
    printf("----------------------------------------\n");
}

void view_relatorio_imprimir_cabecalho_tabela(const char* colunas) {
    printf("-------------------------------------------------------------------------\n");
    printf(" %s\n", colunas);
    printf("-------------------------------------------------------------------------\n");
}