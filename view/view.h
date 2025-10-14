

#ifndef VIEW_H
#define VIEW_H

#include "cliente.h" 

// funções são responsáveis por MOSTRAR informações ao usuário.

void view_exibir_menu();
void view_imprimir_lista(ListaCliente* lista);
void view_imprimir_cliente_unico(ListaCliente* no_cliente);
void view_exibir_mensagem(const char* mensagem);

// Estas funções são responsáveis por LER dados do teclado do usuário.

int view_ler_opcao();
void view_ler_dados_cliente(Cliente* cliente);

#endif // Fim do Header Guard