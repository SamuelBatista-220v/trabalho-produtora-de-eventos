#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fornecedor.h"

#include "status.h"

// Variável estática para controlar o próximo ID de fornecedor
static int proximo_id_fornecedor = 1;
//O uso de Listafornecedor** lista permite alterar a variável que aponta para o início da lista no programa principal.
StatusOperacao inserir_fornecedor(Listafornecedor** lista, fornecedor novo_fornecedor) {
    Listafornecedor* novo_no = (Listafornecedor*) malloc(sizeof(Listafornecedor));
    if (novo_no == NULL) {
        return ERRO_ALOCACAO_MEMORIA;
    }

    novo_fornecedor.id = proximo_id_fornecedor++; // Atribui e incrementa o ID global
    novo_no->conteudo = novo_fornecedor;
    novo_no->prox = NULL;
//Se a lista estiver vazia (*lista == NULL), o novo nó se torna a cabeça (*lista = novo_no
    if (*lista == NULL) {
        *lista = novo_no;
        //Caso contrário, percorre a lista até o final (while (atual->prox != NULL)) e anexa o novo nó.
    } else {
        Listafornecedor* atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_no;
    }
    return OPERACAO_SUCESSO;
}


Listafornecedor* buscar_fornecedor_por_id(Listafornecedor* lista, int id_busca) {
    Listafornecedor* atual = lista;
    while (atual != NULL) {//Implementa uma busca sequencial
        if (atual->conteudo.id == id_busca) {//compara o id busca com o id do conteúdo de cada nó atual->conteúdo.id
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

//busca o no pelo ID, se encontra preserva o status ativo, garante que o ID não seja sobrescrito e que o status ativo/inativo so possa ser mudado pelas funções especificas de ativação/desativação
StatusOperacao atualizar_fornecedor_por_id(Listafornecedor* lista, int id_busca, fornecedor fornecedor_atualizado) {
    Listafornecedor* no_fornecedor = buscar_fornecedor_por_id(lista, id_busca);
    if (no_fornecedor == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }

    // Preserva o ID original e o status de ativo, que não devem ser alterados aqui
    fornecedor_atualizado.id = no_fornecedor->conteudo.id;
    fornecedor_atualizado.ativo = no_fornecedor->conteudo.ativo;

    no_fornecedor->conteudo = fornecedor_atualizado;



    return OPERACAO_SUCESSO;
}

//Marcar um fornecedor como inativo
//Localiza o nó e altera o campo ativo para 0. Inclui validações para retornar ERRO_NAO_ENCONTRADO ou ERRO_JA_INATIVO
StatusOperacao desativar_fornecedor_por_id(Listafornecedor* lista, int id_busca) {
    Listafornecedor* no_fornecedor = buscar_fornecedor_por_id(lista, id_busca);
    if (no_fornecedor == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_fornecedor->conteudo.ativo == 0) {
        return ERRO_JA_INATIVO;
    }
    no_fornecedor->conteudo.ativo = 0;
    return OPERACAO_SUCESSO;
}

//Remover o nó da lista permanentemente e liberar sua memória.
StatusOperacao ativar_fornecedor_por_id(Listafornecedor* lista, int id_busca) {
    Listafornecedor* no_fornecedor = buscar_fornecedor_por_id(lista, id_busca);
    if (no_fornecedor == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (no_fornecedor->conteudo.ativo == 1) {
        return ERRO_JA_ATIVO;
    }
    no_fornecedor->conteudo.ativo = 1;
    return OPERACAO_SUCESSO;
}

//Remover o nó da lista permanentemente e liberar sua memória.
StatusOperacao remover_fisico_fornecedor_por_id(Listafornecedor** lista, int id_busca) {
    Listafornecedor* atual = *lista;
    Listafornecedor* anterior = NULL;
//Percorre a lista rastreando o nó anterior (anterior) e o nó atual (atual)
    while (atual != NULL && atual->conteudo.id != id_busca) {
        anterior = atual;
        atual = atual->prox;
    }
//se for encontrado ajusta ponteiro prox do nó anterior para que ele aponte para o nó que vinha depois de atual
    if (atual == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
//Se o nó removido for o primeiro, usa *lista= atua->prox
    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    return OPERACAO_SUCESSO;
}
//Desalocar toda a memória usada pela lista encadeada, prevenindo vazamento de memória.
void liberar_lista_fornecedor(Listafornecedor** lista) {
    //Percorre a lista nó por nó. Em cada etapa, salva o endereço do próximo nó
    Listafornecedor* atual = *lista;
    Listafornecedor* proximo_no;
    while (atual != NULL) {
        proximo_no = atual->prox;
        free(atual);
        atual = proximo_no;
    }
    *lista = NULL;
}

// estas funções são responsáveis por salvar e carregar os dados entre a memória RAM e o disco.

StatusOperacao salvar_fornecedor_txt(Listafornecedor* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "w");//Percorre a lista e escreve os campos separados por ;
    if (!f) return ERRO_ABRIR_ARQUIVO;
    
    Listafornecedor* atual = lista;
    while (atual) {
        fornecedor* fr = &atual->conteudo;
        // Salva campos comuns
        fprintf(f, "%d;%d;%s;%s;%s;%s;%s;%d;",
            fr->id, (int)fr->tipoF, fr->nome_fantasia, fr->razao_social,
            fr->endereco_completo, fr->telefone, fr->tipo_servico, fr->ativo);
        
        if (fr->tipoF == PESSOA_FISICA_FOR) {
            fprintf(f, "%s\n", fr->docfornecedor.pf.cpf);
        } else {
            fprintf(f, "%s\n", fr->docfornecedor.pj.cnpj);
        }
        
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}
//usa fscanf com expressões %[^;] e %[^\n] para ler os campos, e chama inserir_fornecedor para reconstruir a lista.
StatusOperacao carregar_fornecedor_txt(Listafornecedor** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");//Abre o arquivo em modo de leitura ("r").
    if (!f) return ERRO_ABRIR_ARQUIVO;
    
    liberar_lista_fornecedor(lista);//Libera qualquer lista existente na memória. Isso é crucial para começar a reconstrução do zero.
    proximo_id_fornecedor = 1;//Reinicia o contador para consistência.

    fornecedor fr;
    // %[^;]: Este formato é usado para ler strings (textos) e diz ao fscanf para ler todos os caracteres até encontrar o próximo ponto e vírgula (;). Isso garante que o campo seja lido corretamente, mesmo que contenha espaços.
    while (fscanf(f, "%d;%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;",//fscanf: Lê dados formatados do arquivo.
        &fr.id, (int*)&fr.tipoF, fr.nome_fantasia, fr.razao_social,
        fr.endereco_completo, fr.telefone, fr.tipo_servico, &fr.ativo) == 8) {//O loop continua enquanto 8 campos forem lidos com sucesso.
        
       //Pessoa Física ou Jurídica), a função sabe qual campo da union (docfornecedor) deve ser preenchido (CPF ou CNPJ). 
        if (fr.tipoF == PESSOA_FISICA_FOR) {
            fscanf(f, "%[^\n]\n", fr.docfornecedor.pf.cpf);//%[^\n]\n: Lê o restante da linha até o caractere de quebra de linha (\n) e consome esse \n, preparando o ponteiro do arquivo para o início da próxima linha.
        } else {
            fscanf(f, "%[^\n]\n", fr.docfornecedor.pj.cnpj);
        }
        
        inserir_fornecedor(lista, fr);
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}
//Usa fwrite para copiar os bytes brutos da estrutura fornecedor para o arquivo. Mais rápido e compacto que o TXT.
StatusOperacao salvar_fornecedor_bin(Listafornecedor* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "wb");
    if (!f) return ERRO_ABRIR_ARQUIVO;
    Listafornecedor* atual = lista;
    while (atual) {
        //fwrite(...): É a função para gravação binária. Ela copia blocos de bytes da memória para o arquivo.
        fwrite(&atual->conteudo, sizeof(fornecedor), 1, f);//sizeof(fornecedor): O tamanho exato em bytes da estrutura fornecedor.
        atual = atual->prox;
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}
//Limpa a lista e usa fread para ler blocos de dados do tamanho exato de uma estrutura fornecedor diretamente na memória
StatusOperacao carregar_fornecedor_bin(Listafornecedor** lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "rb");//Abre em modo de leitura binária ("rb").
    if (!f) return ERRO_ABRIR_ARQUIVO;
    liberar_lista_fornecedor(lista);
    proximo_id_fornecedor = 1;
    fornecedor fr;// O endereço da variável fr (o destino na memória).
    while (fread(&fr, sizeof(fornecedor), 1, f) == 1) {//O loop continua enquanto fread conseguir ler um item completo (uma estrutura fornecedor)
        inserir_fornecedor(lista, fr);
    }
    fclose(f);
    return OPERACAO_SUCESSO;
}
