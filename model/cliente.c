// Arquivo: cliente.c (Refatorado para ser um Model "puro")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

//variável estática que rastreia qual será o próximo ID único a ser atribuído a um novo cliente. Começa em 1.
//Garante que cada cliente inserido na lista tenha um ID único
static int proximo_id = 1;

//StatusOperacao informa se a operação foi bem sucedida ou se ocorreu algum erro
//o proposito: inserir um novo_cliente no final da lista encadeada
//A função malloc é para alocar dinamicamente memória suficiente para armazenar um novo nó da lista
StatusOperacao inserir_cliente(ListaCliente** lista, Cliente novo_cliente) {
    ListaCliente* novo_no = (ListaCliente*) malloc(sizeof(ListaCliente));
    if (novo_no == NULL) {
        
        // Se a alocação falhar o sistema não tem memória livre, malloc retorna NULL
        //bloco if checa e retorna status de erro
        return ERRO_ALOCACAO_MEMORIA;
    }
    //id unico atribui valor do próximo_id ao campo id do cliente em seguida incrementa proximo_id++ para próximo cliente
    //conteúdo copia todos os dados do cliente para o campo conteúdo dentro do novo nó
    //ponteiro prox define o ponteiro prox do novo nó como NULL de canto que ele é o último nó da lista por enquanto
    novo_cliente.id = proximo_id++;
    novo_no->conteudo = novo_cliente;
    novo_no->prox = NULL;
    //verifica se o ponteiro de início da lista é NULL, se for, significa que a lista está vazia
    //o novo nó se torna o primeiro nó e o novo nó é atribuido ao ponteiro de início da lista
    if (*lista == NULL) {
        *lista = novo_no;
    } else {
        ListaCliente* atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_no;
    }
    //retorna operacao_sucesso quando o cliente for inserido com êxito.
    return OPERACAO_SUCESSO;
}

//essa função tem o objetivo de desalocar toda a memória utilizada pelos nós da lista encadeada previnindo vazamento de memória
void liberar_lista(ListaCliente** lista) {
    ListaCliente* atual = *lista;
    ListaCliente* proximo_no;
    while (atual != NULL) {
        proximo_no = atual->prox;
        free(atual); //desaloca memória ocupada pelo nó atual
        atual = proximo_no; //move o ponteiro atual para o endereço do próximo nó reiniciando o ciclo para liberar o próximo elemento
    }
    *lista = NULL; //aqui indica claramente que a lista está vazia
}


ListaCliente* buscar_cliente_por_id(ListaCliente* lista, int id_busca) {
    ListaCliente* atual = lista; //inicializa o ponteiro atual para começar a busca a partir do primeiro nó da lista
    while (atual != NULL) { //Continua enquanto não tiver chegado o final da lista
        if (atual->conteudo.id == id_busca) { //Compara o id armazenado do cliente do nó atual->conteudo.id com o id que está sendo procurado id_busca
            return atual; //caso a condição seja verdadeira, a função retorna o ponteiro para o nó onde o cliente foi encoontrado
        }
        atual = atual->prox; //move o ponteiro atual para o próximo nó da lista
    }
    return NULL; //se o loop terminar sem encontrar o id_busca, a função sai e retorna NULL
}


StatusOperacao atualizar_cliente_por_id(ListaCliente* lista, int id_busca, Cliente clienteAtualizado)  {
    // Variavel auxiliar para percorrer a lista
    ListaCliente *atual = lista;

    // Enquanto o nó atual não for nulo, avança
    while (atual != NULL) {
        // Se o id do conteudo atual for o id que eu quero, atualiza os dados
        if (atual->conteudo.id == id_busca) {
            atual->conteudo = clienteAtualizado;
            
            // Garante que o id não foi alterado acidentalmente
            atual->conteudo.id = id_busca; 
            
            return OPERACAO_SUCESSO; // Sucesso
        }
        atual = atual->prox;
    }

    // Se chegar aqui, não achou o cliente
    return ERRO_NAO_ENCONTRADO;
}



StatusOperacao desativar_cliente_por_id(ListaCliente* lista, int id_busca) {
    ListaCliente* no_cliente = buscar_cliente_por_id(lista, id_busca);
    if (no_cliente == NULL) {
        return ERRO_NAO_ENCONTRADO;
        //se a busca retornar NULL, o cliente não está na lista, e a função retorna o erro
    }
    if (no_cliente->conteudo.ativo == 0) {
        return ERRO_JA_INATIVO; //verifica se o cliente já está inativo
    }
    no_cliente->conteudo.ativo = 0;
    return OPERACAO_SUCESSO; //muda o valor do campo ativo dentro da estrutura Cliente para 0(falso)
}

// Função alterada para retornar StatusOperacao
StatusOperacao remover_fisico_cliente_por_id(ListaCliente** lista, int id_busca) {
    ListaCliente* atual = *lista; //ponteiro que percorre a lista
    ListaCliente* anterior = NULL; //ponteiro que rastreia o nó imediatamente antes do nó atual

    while (atual != NULL && atual->conteudo.id != id_busca) {
        anterior = atual;
        atual = atual->prox; //O loop avança, mas antes de atyal ir para o próximo,
        //o anterior é atualizado para o nó que o atual está prestes a deixar.
    }

    if (atual == NULL) {
        return ERRO_NAO_ENCONTRADO; //Se o loop terminou e atual é NULL, o cliente não foi encontrado
    }

    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox; //primeiro caso: se o anterior for NULL, significa que o nó a ser removido é o primeiro nó.
        //Segundo caso: o ponteiro prox do nó anterior é alterado para apontar para o nó que vinha depois do nó atual(atual->prox),
        //ignorando o nó atual.
    }

    free(atual);
    return OPERACAO_SUCESSO;
    //a função free(atual) libera a memória que estava sendo usada pelo nó que foi removido da cadeia.
}

//Chama a função buscar_cliente_por_id para localizar o nó do cliente na lista com base no id fornecido
StatusOperacao ativar_cliente_por_id(ListaCliente* lista, int id_busca) {
    ListaCliente* no_cliente = buscar_cliente_por_id(lista, id_busca);
    if (no_cliente == NULL) {
        return ERRO_NAO_ENCONTRADO;
        //verifica se o ponteiro retornado pela busca é NULL. Se for, significa que não há cliente com o id especificado
    }
    if (no_cliente->conteudo.ativo == 1) {
        return ERRO_JA_ATIVO;
        //Verifica se o cliente já tem o campo ativo igual a 1(verdadeiro/ativo)
    }
    no_cliente->conteudo.ativo = 1;
    return OPERACAO_SUCESSO;
    //Acessa a estrutura Cliente dentro do nó (no_cliente->conteudo) e define o campo ativo como 1.
}

//
StatusOperacao salvar_clientes_txt(ListaCliente* lista, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) return ERRO_ABRIR_ARQUIVO;
    //tenta abrir pou criar o arquivo especificado em modo de escrita("w"). O modo "w" significa "write" e,
    //se o arquivo já existir, ele será removido para começar a gravação do zero

    //inicia a travessia da lista a partir do primeiro nó
    ListaCliente* atual = lista;
    while (atual != NULL) {
        //o loop percorre cada nó da lista encadeada
        Cliente* c = &atual->conteudo; //cria um ponteiro para auxiliar (c) para estrutura Cliente dentro do nó atual. 
        //gravação dos dados
        fprintf(arquivo, "%d;%d;%d;%s;%s;%s;%s;", 
                c->id, c->ativo, (int)c->tipo, 
                c->endereco_completo, c->telefone, c->email, c->nome_contato);
                //fprint: é a função para escrever dados formatados em um arquivo. Ela funciona de
                //maneira semelhante ao 'printf', mas direciona a saída para o FILE* arquivo.
                //(int)c->tipo: O campo tipo provavelmente é um enum (como PESSOA_FISICA ou PESSOA_JURIDICA).
                //Ele é explicitamente convertido para int para que o printf possa gravá-lo como um número no arquivo.

        if (c->tipo == PESSOA_FISICA) {
            fprintf(arquivo, "%s;%s\n", c->doc.pf.nome, c->doc.pf.cpf);
        } else {
            fprintf(arquivo, "%s;%s\n", c->doc.pj.razao_social, c->doc.pj.cnpj); //Esta parte lida com os dados que estão armazenados
            //em uma union ou em campos específicos por tipo de pessoa
        }

        atual = atual->prox;
    }
    fclose(arquivo);
    return OPERACAO_SUCESSO; //Fecha o arquivo de maneira correta 
}

StatusOperacao carregar_clientes_txt(ListaCliente** lista, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r"); //Abre o arquivo em modo de leitura ("r"). Se o arquivo não existir ou não puder ser aberto, retorna o erro.
    if (arquivo == NULL) return ERRO_ABRIR_ARQUIVO;

    liberar_lista(lista); //desaloca qualquer lista de clientes que possa estar carregada na memória antes de iniciar o carregamento
    proximo_id = 1; //Reinicia o contador de id

    Cliente temp; //cria uma estrutura temporária para armazenar os dados lidos antes de inseri-los na lista.
    // Loop de leitura
    while (fscanf(arquivo, "%d;%d;%d;%[^;];%[^;];%[^;];%[^;];", //este é o coração da leitura
        //fscanf: lê dados formatados do arquivo
                  &temp.id, &temp.ativo, (int*)&temp.tipo, 
                  temp.endereco_completo, temp.telefone, temp.email, temp.nome_contato) == 7) {
                    //O loop continua enquanto o fscanf  conseguir ler com sucesso 7 itens(os 7 campos comuns).

        
        if (temp.tipo == PESSOA_FISICA) {
            fscanf(arquivo, "%[^;];%[^\n]\n", temp.doc.pf.nome, temp.doc.pf.cpf);
        } else {
            fscanf(arquivo, "%[^;];%[^\n]\n", temp.doc.pj.razao_social, temp.doc.pj.cnpj); //baseado no valor lido para temp.tipo(etapa 2),
            //a função sabe qual formato de dados esperar em seguifda (pessoa física ou jurídica).
        }

        inserir_cliente(lista, temp); //após todos os campos do cliente terem sido lidos na estrutura temp,
        //a função inserir_cliente é chamada para criar um novo nó da lista encadeada e copiar os dados para lá.
    }

    fclose(arquivo); //fecha o arquivo, liberando o recurso
    return OPERACAO_SUCESSO; //retorna o status de sucesso
}

StatusOperacao salvar_clientes_bin(ListaCliente* lista, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "wb"); //tenta abrir ou criar o arquivo
    if (arquivo == NULL) return ERRO_ABRIR_ARQUIVO;

    ListaCliente* atual = lista; //inicia o ponteiro da travessia na cabeça da lista
    while (atual != NULL) {
        fwrite(&atual->conteudo, sizeof(Cliente), 1, arquivo); //Esta é a função central para I/O(Input/Output) binário em C.
        atual = atual->prox;
    }
    
    fclose(arquivo); //fecha o arquivo corretamente.
    return OPERACAO_SUCESSO; //retorna operacao_sucesso
}

StatusOperacao carregar_clientes_bin(ListaCliente** lista, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "rb"); //abre o arquivo em modo de leitura binária("rb").
    if (arquivo == NULL) return ERRO_ABRIR_ARQUIVO;

    liberar_lista(lista); //limpa qualquer lista existente na memória, prevenindo duplicação de dados.
    proximo_id = 1; //reinicia o contador de id para manter a consistência com o estado inicial da aplicação.

    Cliente temp; //croa uma variável temporária na pilha para receber os dados lidos do arquivo.
    while (fread(&temp, sizeof(Cliente), 1, arquivo) == 1) { //este é o loop de leitura binária.
        inserir_cliente(lista, temp); //para cada cliente armazenado na variável temp, ele é inserido na lista encadeada usando a variável que já analisou.
    }

    fclose(arquivo); //fecha o arquivo, finalizando a operação de leitura e liberando recursos do sistema.
    return OPERACAO_SUCESSO;
}

