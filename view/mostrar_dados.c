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
    printf("Codigo       : %d\n", no_produtora->conteudo.id);
    printf("Nome Fantasia: %s\n", no_produtora->conteudo.nome_fantasia);
    printf("Razao Social : %s\n", no_produtora->conteudo.razao_social);
    printf("Inscricao Est: %s\n", no_produtora->conteudo.inscricao_estadual);
    printf("CNPJ         : ");
    imprimir_cnpj_formatado(no_produtora->conteudo.cnpj);
    printf("\nEndereco     : %s\n", no_produtora->conteudo.endereco_completo);
    printf("Telefone     : ");
    imprimir_telefone_formatado(no_produtora->conteudo.telefone);
    printf("\nEmail        : %s\n", no_produtora->conteudo.email);
    printf("Nome fo responsavel.   : %s\n", no_produtora->conteudo.nome_responsavel);
    printf("telefone do responsavel: %s\n", no_produtora->conteudo.telefone_responsavel);
    printf("Status       : %s\n", no_produtora->conteudo.ativo ? "Ativo" : "Inativo");
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
    printf("Codigo : %d\n", no_cliente->conteudo.id);
    if (no_cliente->conteudo.tipo == PESSOA_FISICA) {
        printf("Nome   : %s\n", no_cliente->conteudo.doc.pf.nome);
        printf("CPF    : ");
        imprimir_cpf_formatado(no_cliente->conteudo.doc.pf.cpf);
    } else {
        printf("Razao Social: %s\n", no_cliente->conteudo.doc.pj.razao_social);
        printf("CNPJ        : ");
        imprimir_cnpj_formatado(no_cliente->conteudo.doc.pj.cnpj);
    }
    printf("\nEndereco: %s\n", no_cliente->conteudo.endereco_completo);
    printf("Telefone: ");
    imprimir_telefone_formatado(no_cliente->conteudo.telefone);
    printf("\nEmail   : %s\n", no_cliente->conteudo.email);
    printf("Contato : %s\n", no_cliente->conteudo.nome_contato);
    printf("Status  : %s\n", no_cliente->conteudo.ativo ? "Ativo" : "Inativo");
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
    if (no_equipe == NULL) { return;
    printf("\n--- Lista de Membros da Equipe ---\n");

        printf("----------------------------------------\n");
        printf("Codigo      : %d\n", no_equipe->conteudo.id);
        printf("Nome        : %s\n", no_equipe->conteudo.nome);
        printf("CPF         : ");
        imprimir_cpf_formatado(no_equipe->conteudo.cpf);
        printf("\n");
        printf("Funcao      : %s\n", no_equipe->conteudo.funcao);
        printf("Valor Diaria: R$ %.2f\n", no_equipe->conteudo.valor_diaria);
        printf("Status      : %s\n", no_equipe->conteudo.ativo ? "Ativo" : "Inativo");

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
    printf("Codigo       : %d\n", no_recurso->conteudo.id);
    printf("Descricao   : %s\n", no_recurso->conteudo.descricao);
    printf("Categoria   : %s\n", no_recurso->conteudo.categoria);
    printf("Quantidade em estoque: %d\n", no_recurso->conteudo.quantidade);
    printf("Preco de Custo: R$ %.2f\n", no_recurso->conteudo.preco_de_custo);
    printf("Valor da Locacao: R$ %.2f\n", no_recurso->conteudo.valor_da_locacao);
    printf("Status       : %s\n", no_recurso->conteudo.ativo ? "Ativo" : "Inativo");
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
    printf("Nome Fantasia: %s\n", no_fornecedor->conteudo.nome_fantasia);
    printf("Razao Social : %s\n", no_fornecedor->conteudo.razao_social);
      if (no_fornecedor->conteudo.tipoF == PESSOA_FISICA) {
        printf("CPF    : ");
        imprimir_cpf_formatado(no_fornecedor->conteudo.docfornecedor.pf.cpf);
    } else {
        printf("CNPJ        : ");
        imprimir_cnpj_formatado(no_fornecedor->conteudo.docfornecedor.pj.cnpj);
    }
    printf("\nEndereco     : %s\n", no_fornecedor->conteudo.endereco_completo);
    printf("Telefone     : "); imprimir_telefone_formatado(no_fornecedor->conteudo.telefone);
    printf("\ntipo de Servico      : %s\n", no_fornecedor->conteudo.tipo_servico);
    printf("Status       : %s\n", no_fornecedor->conteudo.ativo ? "Ativo" : "Inativo");
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
    printf("Codigo       : %d\n", no_operador->conteudo.id);
    printf("Nome         : %s\n", no_operador->conteudo.nome);
    printf("Usuario      : %s\n", no_operador->conteudo.usuario);
    printf("Senha        : ********\n");
    printf("Status       : %s\n", no_operador->conteudo.ativo ? "Ativo" : "Inativo");
}