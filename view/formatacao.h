#ifndef FORMATACAO_H
#define FORMATACAO_H

void imprimir_cpf_formatado(const char* cpf);
void imprimir_cnpj_formatado(const char* cnpj);
void imprimir_telefone_formatado(const char* telefone);

// --- NOVA FUNÇÃO BLINDADA ---
float string_para_float_universal(char* str);

#endif 