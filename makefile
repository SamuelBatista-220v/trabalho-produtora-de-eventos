# =============================================================================
# Makefile para o projeto de Gestão de Clientes (VERSÃO CORRIGIDA)
# =============================================================================

# --- 1. CONFIGURAÇÕES E VARIÁVEIS ---
CC = gcc
TARGET = programa.exe
CFLAGS = -Wall -g -I. -Imodel -Iview -Icontroller -Ivalidacoes

# --- 2. DEFINIÇÃO DOS ARQUIVOS ---
VPATH = model:view:controller:validacoes

# CORREÇÃO: Adicionados todos os novos arquivos .c
SRCS =  main.c \
        model/cliente.c \
        model/equipe.c \
        view/view.c \
        controller/controller.c \
        controller/cliente_controller.c \
        controller/equipe_controller.c \
        validacoes/validacoes.c

OBJS = $(notdir $(SRCS:.c=.o))

# --- 3. REGRAS DE COMPILAÇÃO ---
all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "----------------------------------------"
	@echo ">> Linkando o programa: $(TARGET)"
	@echo "----------------------------------------"
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	@echo "Compilando $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

# --- 4. REGRAS AUXILIARES E DE ATALHO ---
run: $(TARGET)
	@echo "----------------------------------------"
	@echo ">> Executando o programa..."
	@echo "----------------------------------------"
	./$(TARGET)

clean:
	@echo "----------------------------------------"
	@echo ">> Limpando arquivos compilados..."
	@echo "----------------------------------------"
	del $(TARGET) $(OBJS)

.PHONY: all clean run