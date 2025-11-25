
#ifndef CLIENTE_CONTROLLER_H
#define CLIENTE_CONTROLLER_H

#include "../model/cliente.h" // Precisa da definição de ListaCliente

// Função que será chamada pelo controller principal para gerenciar os clientes.
void controller_gerenciar_clientes(ListaCliente** lista_de_clientes);

#endif // CLIENTE_CONTROLLER_H