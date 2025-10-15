#include <stdio.h>
#include "mostrar_dados.h"
#include "formatacao.h" // Importante: incluir o novo header de formatação!

void view_exibir_mensagem(const char* mensagem) {
    printf(">> %s\n", mensagem);
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

void view_imprimir_lista_equipe(ListaEquipe* lista) {
    if (lista == NULL) {
        printf("\n>> Nenhum membro de equipe cadastrado.\n");
        return;
    }
    printf("\n--- Lista de Membros da Equipe ---\n");
    for (ListaEquipe* aux = lista; aux != NULL; aux = aux->prox) {
        printf("----------------------------------------\n");
        printf("Codigo      : %d\n", aux->conteudo.id);
        printf("Nome        : %s\n", aux->conteudo.nome);
        printf("CPF         : ");
        imprimir_cpf_formatado(aux->conteudo.cpf);
        printf("\n");
        printf("Funcao      : %s\n", aux->conteudo.funcao);
        printf("Valor Diaria: R$ %.2f\n", aux->conteudo.valor_diaria);
        printf("Status      : %s\n", aux->conteudo.ativo ? "Ativo" : "Inativo");
    }
}