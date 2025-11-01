#ifndef MOSTRAR_DADOS_H
#define MOSTRAR_DADOS_H


#include "../model/produtora.h"
#include "../model/cliente.h"
#include "../model/equipe.h"
#include "../model/recurso.h"
#include "../model/fornecedor.h"
#include "../model/produtora.h"
#include "../model/operador.h"

void view_exibir_mensagem(const char* mensagem);
void view_imprimir_lista(ListaCliente* lista);
void view_imprimir_cliente_unico(ListaCliente* no_cliente);

void view_imprimir_lista_equipe(Listaequipe* lista);


void view_imprimir_fornecedor_unico(Listafornecedor* no_fornecedor);
void view_imprimir_lista_fornecedor(Listafornecedor* lista);

void view_imprimir_produtora_unico(Listaprodutora* no_produtora);
void view_imprimir_lista_produtora(Listaprodutora* lista);




#endif // MOSTRAR_DADOS