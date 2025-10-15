#ifndef RECEBER_DADOS_H
#define RECEBER_DADOS_H

#include "../model/cliente.h"
#include "../model/equipe.h"

int view_ler_opcao();
void view_ler_dados_cliente(Cliente* cliente);
void view_ler_dados_equipe(Equipe* equipe);

#endif // RECEBER_DADOS_H