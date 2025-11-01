#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Incluímos o nosso próprio cabeçalho para garantir que as
// declarações e implementações estão consistentes.
#include "validacoes.h"


int validar_apenas_letras(const char* str) {
    if (str == NULL || str[0] == '\0') {
        return 0; // Campo não pode ser vazio
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha((unsigned char)str[i]) && !isspace((unsigned char)str[i])) {
            return 0; // Encontrou um caractere inválido
        }
    }
    return 1; // String válida
}


int validar_cpf(const char* cpf) {
    if (cpf == NULL || strlen(cpf) != 11) {
        return 0; // Tamanho incorreto
    }
    for (int i = 0; cpf[i] != '\0'; i++) {
        if (!isdigit((unsigned char)cpf[i])) {
            return 0; // Contém caracteres não numéricos
        }
    }
    return 1; // CPF válido
}


int validar_cnpj(const char* cnpj) {
    if (cnpj == NULL || strlen(cnpj) != 14) {
        return 0; // Tamanho incorreto
    }
    for (int i = 0; cnpj[i] != '\0'; i++) {
        if (!isdigit((unsigned char)cnpj[i])) {
            return 0; // Contém caracteres não numéricos
        }
    }
    return 1; // CNPJ válido
}


int validar_telefone(const char* telefone) {
    if (telefone == NULL) return 0;
    
    size_t len = strlen(telefone);
    if (len < 10 || len > 11) {
        return 0; // Tamanho incorreto
    }

    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)telefone[i])) {
            return 0; // Contém caracteres não numéricos
        }
    }
    return 1; // Telefone válido
}


int validar_email(const char* email) {
    if (email == NULL || email[0] == '\0') {
        return 0; // Email não pode ser vazio
    }
    if (strchr(email, '@') == NULL) {
        return 0; // Não encontrou o '@'
    }
    return 1; // Email parece válido
}




