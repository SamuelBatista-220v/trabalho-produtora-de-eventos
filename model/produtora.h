#ifndef PRODUTORA_H
#define PRODUTORA_H

#include "status.h" // Inclui o enum StatusOperacao

// Estrutura principal com todos os dados de um produtora (agora apenas PJ)
typedef struct {
    int id;
    char nome_fantasia[100];
    char razao_social[100]; 
    char inscricao_estadual[15]; 
    char cnpj[15];          // Campo direto na struct
    char endereco_completo[150];
    char telefone[12];
    char email[100];
    char nome_responsavel[100];
    char telefone_responsavel[12];
    float margem_lucro_padrao;  

    int ativo; // 1 para ativo, 0 para inativo
} produtora;

// ➢ Nome Fantasia
// ➢ Razão Social
// ➢ Inscrição Estadual
// ➢ CNPJ
// ➢ Endereço completo
// ➢ Telefone
// ➢ E-mail
// ➢ Nome do responsável
// ➢ Telefone do responsável
// ➢ Margem de lucro padrão
// Estrutura do nó da lista ligada de produtoraes
typedef struct no_produtora Listaprodutora;

struct no_produtora {
    produtora conteudo;
    Listaprodutora* prox;
};


// --- DECLARAÇÃO DAS FUNÇÕES (PROTÓTIPOS) ---

// Funções para manipulação da lista (CRUD)
StatusOperacao inserir_produtora(Listaprodutora** lista, produtora novo_produtora);
Listaprodutora* buscar_produtora_por_id(Listaprodutora* lista, int id_busca);
StatusOperacao atualizar_produtora_por_id(Listaprodutora* lista, int id_busca, produtora produtora_atualizado);
StatusOperacao desativar_produtora_por_id(Listaprodutora* lista, int id_busca);
StatusOperacao ativar_produtora_por_id(Listaprodutora* lista, int id_busca);
StatusOperacao remover_fisico_produtora_por_id(Listaprodutora** lista, int id_busca);
void liberar_lista_produtora(Listaprodutora** lista);

// (Opcional) Funções de Persistência
// StatusOperacao salvar_produtoraes(Listaprodutora* lista, const char* nome_arquivo);
// StatusOperacao carregar_produtoraes(Listaprodutora** lista, const char* nome_arquivo);

#endif // produtora_H


