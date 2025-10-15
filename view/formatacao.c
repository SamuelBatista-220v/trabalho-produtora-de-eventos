#include <stdio.h>
#include <string.h>
#include <stddef.h> // Para size_t
#include "formatacao.h"

// Função movida de view.c
void imprimir_cpf_formatado(const char* cpf) {
    if (cpf != NULL && strlen(cpf) == 11) {
        printf("%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
    } else {
        printf("%s", cpf);
    }
}

// Função movida de view.c
void imprimir_cnpj_formatado(const char* cnpj) {
    if (cnpj != NULL && strlen(cnpj) == 14) {
        printf("%.2s.%.3s.%.3s/%.4s-%.2s", cnpj, cnpj + 2, cnpj + 5, cnpj + 8, cnpj + 12);
    } else {
        printf("%s", cnpj);
    }
}

// Função movida de view.c
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