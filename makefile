# =============================================================================
# Makefile para o projeto de Gestão de Eventos
# =============================================================================

# --- 1. CONFIGURAÇÕES E VARIÁVEIS ---
CC = gcc
TARGET = produtora.exe
CFLAGS = -Wall -g -I. -Imodel -Iview -Icontroller -Ivalidacoes

# --- 2. DEFINIÇÃO DOS ARQUIVOS ---
VPATH = model:view:controller:validacoes

# CORREÇÃO: Lista completa de todos os arquivos .c do projeto
SRCS =  main.c \
		model/produtora.c \
		model/recurso.c \
		model/operador.c \
        model/cliente.c \
        model/equipe.c \
        model/fornecedor.c \
        view/formatacao.c \
        view/menus.c \
        view/mostrar_dados.c \
        view/receber_dados.c \
		controller/produtora_controller.c \
		controller/recurso_controller.c \
		controller/operador_controller.c \
        controller/cliente_controller.c \
        controller/equipe_controller.c \
        controller/fornecedor_controller.c \
        controller/controller.c \
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


# # =============================================================================
# # Makefile para o projeto (Focado APENAS no módulo de Fornecedores)
# # =============================================================================

# # --- 1. CONFIGURAÇÕES E VARIÁVEIS ---
# CC = gcc
# TARGET = produtora.exe
# CFLAGS = -Wall -g -I. -Imodel -Iview -Icontroller -Ivalidacoes

# # --- 2. DEFINIÇÃO DOS ARQUIVOS ---
# VPATH = model:view:controller:validacoes

# # Lista de arquivos .c ESSENCIAIS para o módulo de fornecedores funcionar
# SRCS =  main.c \
#         model/fornecedor.c \
#         view/formatacao.c \
#         view/menus.c \
#         view/mostrar_dados.c \
#         view/receber_dados.c \
#         controller/fornecedor_controller.c \
#         controller/controller.c \
#         validacoes/validacoes.c

# OBJS = $(notdir $(SRCS:.c=.o))

# # --- 3. REGRAS DE COMPILAÇÃO ---
# all: $(TARGET)

# $(TARGET): $(OBJS)
# 	@echo "----------------------------------------"
# 	@echo ">> Linkando o programa: $(TARGET)"
# 	@echo "----------------------------------------"
# 	$(CC) $(OBJS) -o $(TARGET)

# %.o: %.c
# 	@echo "Compilando $< -> $@"
# 	$(CC) $(CFLAGS) -c $< -o $@

# # --- 4. REGRAS AUXILIARES E DE ATALHO ---
# run: $(TARGET)
# 	@echo "----------------------------------------"
# 	@echo ">> Executando o programa..."
# 	@echo "----------------------------------------"
# 	./$(TARGET)

# clean:
# 	@echo "----------------------------------------"
# 	@echo ">> Limpando arquivos compilados..."
# 	@echo "----------------------------------------"
# 	rm -f $(TARGET) $(OBJS)

# .PHONY: all clean run






# # =============================================================================
# # Makefile para o projeto de Gestão de Clientes (VERSÃO CORRIGIDA)
# # =============================================================================

# # --- 1. CONFIGURAÇÕES E VARIÁVEIS ---
# CC = gcc
# TARGET = programa.exe
# CFLAGS = -Wall -g -I. -Imodel -Iview -Icontroller -Ivalidacoes


# # --- 2. DEFINIÇÃO DOS ARQUIVOS controller/cliente_controller.c //model/equipe.c \ \ ---

# //model/equipe.c \
# SRCS =  main.c \
# 		model/fornecedor.c \
#         view/menus.c \
#         view/mostrar_dados.c \
#         view/receber_dados.c \
#         view/formatacao.c \
#         controller/controller.c \
#         controller/equipe_controller.c \
# 		controller/fornecedor_controller.c \
#         validacoes/validacoes.c

# OBJS = $(notdir $(SRCS:.c=.o))
# # CORREÇÃO: Adicionados todos os novos arquivos .c
# # SRCS =  main.c \
# #         model/cliente.c \
# #         model/equipe.c \
# #         view/view.c \
# #         controller/controller.c \
# #         controller/cliente_controller.c \
# #         controller/equipe_controller.c \
# #         validacoes/validacoes.c

# # OBJS = $(notdir $(SRCS:.c=.o))

# # --- 3. REGRAS DE COMPILAÇÃO ---
# all: $(TARGET)

# $(TARGET): $(OBJS)
# 	@echo "----------------------------------------"
# 	@echo ">> Linkando o programa: $(TARGET)"
# 	@echo "----------------------------------------"
# 	$(CC) $(OBJS) -o $(TARGET)

# %.o: %.c
# 	@echo "Compilando $< -> $@"
# 	$(CC) $(CFLAGS) -c $< -o $@

# # --- 4. REGRAS AUXILIARES E DE ATALHO ---
# run: $(TARGET)
# 	@echo "----------------------------------------"
# 	@echo ">> Executando o programa..."
# 	@echo "----------------------------------------"
# 	./$(TARGET)

# clean:
# 	@echo "----------------------------------------"
# 	@echo ">> Limpando arquivos compilados..."
# 	@echo "----------------------------------------"
# 	del $(TARGET) $(OBJS)

# .PHONY: all clean run