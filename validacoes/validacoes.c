#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Incluímos o nosso próprio cabeçalho para garantir que as
// declarações e implementações estão consistentes.
#include "validacoes.h"

/**
 * Valida se a string contém apenas letras e espaços.
 */
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

/**
 * Valida o campo 'cpf'.
 */
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

/**
 * Valida o campo 'cnpj'.
 */
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

/**
 * Valida o campo 'telefone'.
 */
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

/**
 * Valida o campo 'email'.
 */
int validar_email(const char* email) {
    if (email == NULL || email[0] == '\0') {
        return 0; // Email não pode ser vazio
    }
    if (strchr(email, '@') == NULL) {
        return 0; // Não encontrou o '@'
    }
    return 1; // Email parece válido
}





// #include <string.h>
// #include <ctype.h>
// #include "validacoes.h"

// int validar_cpf(const char* cpf) {
//     if (cpf == NULL || strlen(cpf) != 11) {
//         return 0; // Retorna falso se for nulo ou o tamanho estiver errado
//     }
//     for (int i = 0; cpf[i] != '\0'; i++) {
//         if (!isdigit((unsigned char)cpf[i])) {
//             return 0; // Retorna falso se encontrar algo que não é um dígito
//         }
//     }
//     return 1; // Retorna verdadeiro somente se passar em todas as verificações
// }

// // ... implemente as outras funções de validação aqui ...
// int validar_cnpj(const char* cnpj) { /* ... */ return 1; }
// int validar_apenas_letras(const char* str) { /* ... */ return 1; }
// int validar_telefone(const char* telefone) { /* ... */ return 1; }
// int validar_email(const char* email) { /* ... */ return 1; }

// #include <stdio.h>    // Necessário para printf (opcional, para debug)
// #include <string.h>   // Necessário para strlen e strchr
// #include <ctype.h>    // Necessário para isdigit, isalpha, isspace

// #include "validacoes.h" // Inclui as próprias declarações
// /**
//  * Valida se a string contém apenas letras e espaços.
//  * Perfeito para os campos 'nome' e 'nome_contato' da sua struct.
//  */
// int validar_apenas_letras(const char* str) {
//     if (str == NULL || str[0] == '\0') {
//         return 0; // Campo não pode ser vazio
//     }
//     for (int i = 0; str[i] != '\0'; i++) {
//         // Permite letras (isalpha) e espaços (isspace)
//         if (!isalpha((unsigned char)str[i]) && !isspace((unsigned char)str[i])) {
//             return 0; // Encontrou um caractere inválido
//         }
//     }
//     return 1; // String válida
// }

// /**
//  * Valida o campo 'cpf' da sua struct PessoaFisica.
//  */
// int validar_cpf(const char* cpf) {
//     if (cpf == NULL || strlen(cpf) != 11) {
//         return 0; // Tamanho incorreto
//     }
//     for (int i = 0; cpf[i] != '\0'; i++) {
//         if (!isdigit((unsigned char)cpf[i])) {
//             return 0; // Contém caracteres não numéricos
//         }
//     }
//     return 1; // CPF válido
// }

// /**
//  * Valida o campo 'cnpj' da sua struct PessoaJuridica.
//  */
// int validar_cnpj(const char* cnpj) {
//     if (cnpj == NULL || strlen(cnpj) != 14) {
//         return 0; // Tamanho incorreto
//     }
//     for (int i = 0; cnpj[i] != '\0'; i++) {
//         if (!isdigit((unsigned char)cnpj[i])) {
//             return 0; // Contém caracteres não numéricos
//         }
//     }
//     return 1; // CNPJ válido
// }

// /**
//  * Valida o campo 'telefone' da sua struct Cliente.
//  */
// int validar_telefone(const char* telefone) {
//     if (telefone == NULL) return 0;
    
//     size_t len = strlen(telefone);
//     if (len < 10 || len > 11) {
//         return 0; // Tamanho incorreto (deve ser 10 para fixo ou 11 para celular com DDD)
//     }

//     for (size_t i = 0; i < len; i++) {
//         if (!isdigit((unsigned char)telefone[i])) {
//             return 0; // Contém caracteres não numéricos
//         }
//     }
//     return 1; // Telefone válido
// }

// /**
//  * Valida o campo 'email' da sua struct Cliente.
//  */
// int validar_email(const char* email) {
//     if (email == NULL || email[0] == '\0') {
//         return 0; // Email não pode ser vazio
//     }
//     // Verificação simples: procura pela presença do caractere '@'.
//     // Uma validação completa de email é extremamente complexa, mas esta
//     // é suficiente para a maioria dos casos de cadastro.
//     if (strchr(email, '@') == NULL) {
//         return 0; // Não encontrou o '@'
//     }
//     return 1; // Email parece válido
// }
