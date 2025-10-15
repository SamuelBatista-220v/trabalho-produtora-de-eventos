#ifndef MOSTRAR_DADOS_H
#define MOSTRAR_DADOS_H

#include "../model/cliente.h"
#include "../model/equipe.h"

void view_exibir_mensagem(const char* mensagem);
void view_imprimir_lista(ListaCliente* lista);
void view_imprimir_cliente_unico(ListaCliente* no_cliente);
void view_imprimir_lista_equipe(ListaEquipe* lista);

#endif // MOSTRAR_DADOS_H