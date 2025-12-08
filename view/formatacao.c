#include <stdio.h>
#include <string.h>
#include <stddef.h> // Para size_t
#include "formatacao.h"
#include <stdlib.h> // Necessário para atof
#include <locale.h> 


void imprimir_cpf_formatado(const char* cpf) {
    if (cpf != NULL && strlen(cpf) == 11) {
        printf("%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
    } else {
        printf("%s", cpf);
    }
}


void imprimir_cnpj_formatado(const char* cnpj) {
    if (cnpj != NULL && strlen(cnpj) == 14) {
        printf("%.2s.%.3s.%.3s/%.4s-%.2s", cnpj, cnpj + 2, cnpj + 5, cnpj + 8, cnpj + 12);
    } else {
        printf("%s", cnpj);
    }
}


void imprimir_telefone_formatado(const char* telefone) {
    if (telefone == NULL) return;
    size_t len = strlen(telefone);
    if (len == 11) {
        printf("(%.2s) %.1s %.4s-%.4s", telefone, telefone + 2, telefone + 3, telefone + 7);
    } else if (len == 10) {
        printf("(%.2s) %.4s-%.4s", telefone, telefone + 2, telefone + 6);
    } else {
        printf("%s", telefone);
    }
}

// Implementação centralizada da conversão segura
float string_para_float_universal(char* str) {
    if (!str || strlen(str) == 0) return 0.0f;
    
    char buffer[50];
    strncpy(buffer, str, 49);
    buffer[49] = '\0';
    
    struct lconv * lc = localeconv();
    char sep_sistema = *lc->decimal_point; 
    
    for(int i=0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '.' || buffer[i] == ',') {
            buffer[i] = sep_sistema;
        }
    }
    return (float)atof(buffer);
}