#ifndef STATUS_H
#define STATUS_H

// ENUM para padronizar os retornos das funções de manipulação de dados.
typedef enum {
    // --- Sucesso ---
    OPERACAO_SUCESSO,

    // --- Erros Gerais de Dados ---
    ERRO_NAO_ENCONTRADO,
    ERRO_JA_ATIVO,
    ERRO_JA_INATIVO,

    // --- Erros de Sistema / Memória ---
    ERRO_ALOCACAO_MEMORIA,

    // --- Erros de Persistência (Ficheiros) ---
    ERRO_ABRIR_ARQUIVO,
    ERRO_ESCREVER_ARQUIVO,
    ERRO_LER_ARQUIVO

} StatusOperacao;

#endif // STATUS_H

