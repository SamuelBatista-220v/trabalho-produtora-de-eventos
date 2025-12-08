
#ifndef MOSTRAR_DADOS_H
#define MOSTRAR_DADOS_H

#include "../model/produtora.h"
#include "../model/cliente.h"
#include "../model/equipe.h"
#include "../model/recurso.h"
#include "../model/fornecedor.h"
#include "../model/operador.h"
#include "../model/orcamento.h"
#include "../model/financeiro.h" 

// --- MENSAGENS GERAIS ---
void view_exibir_mensagem(const char* mensagem);
void view_exibir_msg_retornando();
void view_exibir_erro_busca_id(const char* entidade, int id);
void view_exibir_cabecalho_atualizacao(const char* entidade, int id);

// --- LISTAGENS ---
void view_imprimir_lista_produtora(Listaprodutora* lista);
void view_imprimir_produtora_unico(Listaprodutora* no_produtora);

void view_imprimir_lista(ListaCliente* lista);
void view_imprimir_cliente_unico(ListaCliente* no_cliente);

void view_imprimir_lista_equipe(Listaequipe* lista);
void view_imprimir_equipe_unico(Listaequipe* no_equipe);

void view_imprimir_lista_recurso(Listarecurso* lista);
void view_imprimir_recurso_unico(Listarecurso* no_recurso);

void view_imprimir_lista_fornecedor(Listafornecedor* lista);
void view_imprimir_fornecedor_unico(Listafornecedor* no_fornecedor);

void view_imprimir_lista_operador(Listaoperador* lista);
void view_imprimir_operador_unico(Listaoperador* no_operador);

// --- ORÇAMENTOS E EVENTOS ---
void view_imprimir_orcamento_unico(Orcamento* o, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq);
void view_imprimir_lista_orcamento(ListaOrcamento* lista, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq);
void view_imprimir_lista_orcamento_por_status(ListaOrcamento* lista, int status_filtro, Listarecurso* l_rec, Listafornecedor* l_for, Listaequipe* l_eq);
void view_exibir_ocupacao_recurso(int id_recurso, char* nome, int dia_i, int mes_i, int ano_i, int dia_f, int mes_f, int ano_f, int qtd);

// --- FINANCEIRO (RELATÓRIOS E NOTAS) ---
void view_imprimir_relatorio_financeiro(ListaContaPagar* l_cp, ListaContaReceber* l_cr);
void view_imprimir_extrato_caixa_detalhado(ListaCaixa* lista);
void view_imprimir_nota_fiscal_detalhada(void* lista_itens, int qtd_itens, float total_prod, float total_frete, float total_imp);

// --- NOVAS FUNÇÕES PARA LIMPAR O FINANCEIRO CONTROLLER ---
void view_exibir_cabecalho_nota_fiscal();
void view_exibir_item_adicionado_nota(); // Faltava esta
void view_exibir_atualizacao_estoque(const char* nome, int qtd_antiga, int qtd_nova, float novo_preco);
void view_exibir_confirmacao_entrada_nota(); // Faltava esta (O erro principal)
void view_exibir_pagamento_avista_sucesso(); // Faltava esta
void view_exibir_parcela_gerada(int num, int total, float valor, const char* vencto);
void view_exibir_confirmacao_pagamento(float valor);
void view_exibir_confirmacao_recebimento(float valor);
void view_exibir_sucesso_pagamento(); // Faltava esta
void view_exibir_sucesso_recebimento(); // Faltava esta

// ...
void view_ler_descricao_servico(char* destino);
void view_ler_valor_monetario(const char* mensagem, float* destino);
void view_ler_data_generica(const char* mensagem, char* destino);



// ... (Mantenha os includes e funções de listagem que já existem) ...

// --- FUNÇÕES GENÉRICAS INTELIGENTES (USE EM TODOS OS CONTROLLERS) ---
void view_exibir_titulo(const char* titulo);
void view_exibir_alerta(const char* tipo, const char* mensagem); // Tipo: "SUCESSO", "ERRO", "AVISO"
void view_exibir_linha_detalhe(const char* rotulo, const char* valor);
void view_exibir_confirmacao_acao(const char* acao, const char* objeto); // Ex: "EXCLUIR", "Evento X"

// --- FUNÇÕES ESPECÍFICAS (Não dá para ser genérico sem ficar feio) ---
// Mantemos apenas as que têm formatação muito complexa de tabela
void view_exibir_status_estoque(const char* nome, int total, int ocupado, int carrinho, int disponivel);
void view_exibir_item_carrinho_orcamento(const char* nome, int id, int qtd);

// Adicione esta linha no final do arquivo, antes do #endif
void view_exibir_detalhes_estoque(const char* nome, int total, int ocupado, int carrinho, int disponivel);

void view_exibir_msg_qtd_atualizada(int nova_qtd);

// Função genérica para qualquer pergunta de Sim/Nao envolvendo uma ação
void view_exibir_confirmacao_acao(const char* acao, const char* nome_objeto);


// ... código anterior ...

// --- FUNÇÕES ESPECÍFICAS PARA FINALIZAR EVENTO ---
void view_exibir_resumo_evento(const char* nome, float total);
void view_exibir_menu_pagamento_evento();
void view_exibir_prompt_data_simples();
void view_exibir_prompt_valor_entrada();
void view_exibir_prompt_data_vencimento();
void view_exibir_sucesso_entrada_caixa(float valor);
void view_exibir_prompt_parcelas(float restante);
void view_exibir_detalhe_fatura(int num, float valor, const char* venc);

// ...
void view_exibir_prompt_id_item_orcamento(const char* tipo_item);
void view_exibir_prompt_descricao_servico();
void view_exibir_prompt_valor_servico();
void view_exibir_sucesso_criacao_orcamento(float total);
void view_exibir_pergunta_adicionar_fornecedor();
void view_exibir_pergunta_adicionar_equipe();



void view_generico_imprimir_linha(const char* linha);

// Imprime um título padronizado
void view_generico_imprimir_titulo(const char* titulo);

// Imprime um rodapé com valor total (Genérico para qualquer soma monetária)
void view_generico_imprimir_total(double valor, const char* texto_descricao);

// Imprime o cabeçalho de uma tabela (colunas)
void view_relatorio_imprimir_cabecalho_tabela(const char* colunas);
#endif


