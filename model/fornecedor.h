#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#include "status.h" // Inclui o enum StatusOperacao

typedef enum {PESSOA_FISICA_FOR, PESSOA_JURIDICA_FOR} TipoFornecedor;

typedef union 
{
     struct { char cpf[12]; } pf; 
    struct {  char cnpj[15]; } pj;
    
} DocumentoFornecedor;



// Estrutura principal com todos os dados de um fornecedor (agora apenas PJ)
typedef struct {
    int id;
    TipoFornecedor tipoF;
    DocumentoFornecedor docfornecedor;
    char nome_fantasia[100];
    char razao_social[100];
    char endereco_completo[150];
    char telefone[12];
    char tipo_servico[50];
    int ativo; // 1 para ativo, 0 para inativo
} fornecedor;

// Estrutura do nó da lista ligada de fornecedores
typedef struct no_fornecedor Listafornecedor;

struct no_fornecedor {
    fornecedor conteudo;
    Listafornecedor* prox;
};


// --- DECLARAÇÃO DAS FUNÇÕES (PROTÓTIPOS) ---

// Funções para manipulação da lista (CRUD)
StatusOperacao inserir_fornecedor(Listafornecedor** lista, fornecedor novo_fornecedor);
Listafornecedor* buscar_fornecedor_por_id(Listafornecedor* lista, int id_busca);
StatusOperacao atualizar_fornecedor_por_id(Listafornecedor* lista, int id_busca, fornecedor fornecedor_atualizado);
StatusOperacao desativar_fornecedor_por_id(Listafornecedor* lista, int id_busca);
StatusOperacao ativar_fornecedor_por_id(Listafornecedor* lista, int id_busca);
StatusOperacao remover_fisico_fornecedor_por_id(Listafornecedor** lista, int id_busca);
void liberar_lista_fornecedor(Listafornecedor** lista);

// (Opcional) Funções de Persistência
// StatusOperacao salvar_fornecedores(ListaFornecedor* lista, const char* nome_arquivo);
// StatusOperacao carregar_fornecedores(ListaFornecedor** lista, const char* nome_arquivo);
// ... (código anterior) ...

// Funções de Persistência
StatusOperacao salvar_fornecedor_txt(Listafornecedor* lista, const char* nome_arquivo);
StatusOperacao carregar_fornecedor_txt(Listafornecedor** lista, const char* nome_arquivo);
StatusOperacao salvar_fornecedor_bin(Listafornecedor* lista, const char* nome_arquivo);
StatusOperacao carregar_fornecedor_bin(Listafornecedor** lista, const char* nome_arquivo);

#endif // FORNECEDOR_H







// #define FORNECEDOR_H

// #include "status.h"



// typedef union {
//     struct { char nome[100]; char cpf[12]; } pf;
//     struct { char razao_social[100]; char cnpj[15]; } pj;
// } DocumentoFornecedores;

// typedef struct {
//     int id;
//     char nome_fantasia[100];
//     char razao_social[100];
//     char inscricao_estadual[50];
//     char cnpj[15]; // Sempre PJ
//     char endereco_completo[150];
//     char telefone[12];
//     char email[100];
//     char nome_responsavel[100];
//     char telefone_responsavel[12];
//     float margem_lucro;
//     int ativo; 
// } Fornecedores;

// // As funções de
// // typedef struct {
// //     int id;
// //     char nome_fantasia[100];
// //     TipoPessoaFornecedores tipo;
// //     DocumentoFornecedores doc;
// //     char endereco_completo[150];
// //     char telefone[12];
// //     char tipo_servico[100];
// //     int ativo;
// // } Fornecedores;

// typedef struct no_Fornecedores ListaFornecedores;
// struct no_Fornecedores {
//     Fornecedores conteudo;
//     ListaFornecedores* prox;
// };

// // --- Funções CRUD ---
// StatusOperacao inserir_Fornecedores(ListaFornecedores** lista, Fornecedores novo_Fornecedores);
// ListaFornecedores* buscar_Fornecedores_por_id(ListaFornecedores* lista, int id_busca);
// StatusOperacao atualizar_Fornecedores_por_id(ListaFornecedores* lista, int id_busca, Fornecedores Fornecedores_atualizado);
// StatusOperacao desativar_Fornecedores_por_id(ListaFornecedores* lista, int id_busca);
// StatusOperacao ativar_Fornecedores_por_id(ListaFornecedores* lista, int id_busca);
// StatusOperacao remover_fisico_Fornecedores_por_id(ListaFornecedores** lista, int id_busca);
// void liberar_lista_Fornecedores(ListaFornecedores** lista);

// // --- Funções de Persistência ---
// StatusOperacao salvar_Fornecedoreses(ListaFornecedores* lista, const char* nome_arquivo);
// StatusOperacao carregar_Fornecedoreses(ListaFornecedores** lista, const char* nome_arquivo);

// #endif // Fornecedores_H

