#include <stdio.h>
#include "mostrar_dados.h"
#include "formatacao.h" // Importante: incluir o novo header de formatação!

void view_exibir_mensagem(const char* mensagem) {
    printf(">> %s\n", mensagem);
}
/////////////////////////////////////////////////////



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
    printf("----------------------------------------\n");
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

        printf("----------------------------------------\n");
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

    printf("----------------------------------------\n");
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

    printf("----------------------------------------\n");
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

    printf("----------------------------------------\n");
    printf("\n |Codigo      | : %d ", no_operador->conteudo.id);
    printf("\n |Nome        | : %s ", no_operador->conteudo.nome);
    printf("\n |Usuario     | : %s ", no_operador->conteudo.usuario);
    printf("\n |Senha       | : ******** ");
    printf("\n |Status      | : %s ", no_operador->conteudo.ativo ? "Ativo" : "Inativo");
}