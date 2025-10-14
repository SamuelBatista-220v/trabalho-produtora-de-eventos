#ifndef CONTROLLER_H
#define CONTROLLER_H

// O controller precisa de saber as definições de dados do model.
#include "cliente.h"
void controller_iniciar_sistema();
// --- Declarações das Funções do Controller ---

// Funções principais de manipulação de dados
//StatusOperacao inserir_novo_cliente(ListaCliente** lista);
//StatusOperacao remover_cliente_por_id(ListaCliente** lista, int id_busca);
//StatusOperacao atualizar_cliente_por_id(ListaCliente* lista, int id_busca);
//StatusOperacao controller_atualizar_cliente(ListaCliente* lista);
StatusOperacao desativar_cliente_por_id(ListaCliente* lista, int id_busca);
StatusOperacao ativar_cliente_por_id(ListaCliente* lista, int id_busca);
ListaCliente* buscar_cliente_por_id(ListaCliente* lista, int id_busca);

// --- Funções Auxiliares ---
void limpar_buffer_teclado();

#endif // Fim de CONTROLLER_H




// // Arquivo: controller.h
// // Define a interface da camada de controle.

// #ifndef CONTROLLER_H
// #define CONTROLLER_H

// // A única função que o main precisa conhecer.
// // Ela é o ponto de entrada que inicia todo o fluxo da aplicação.
// void controller_iniciar_sistema();

// #endif // Fim do Header Guard