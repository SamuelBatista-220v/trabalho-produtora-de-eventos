
# # --- 1. CONFIGURAÇÕES E VARIÁVEIS ---
# CC = gcc
# TARGET = produtora.exe
# CFLAGS = -Wall -g -I. -Imodel -Iview -Icontroller -Ivalidacoes

# # --- 2. DEFINIÇÃO DOS ARQUIVOS ---
# VPATH = model:view:controller:validacoes

# # LISTA COMPLETA DE ARQUIVOS (Incluindo Financeiro e Orcamento)
# SRCS =  main.c \
#         model/produtora.c \
#         model/recurso.c \
#         model/operador.c \
#         model/cliente.c \
#         model/equipe.c \
#         model/fornecedor.c \
#         model/orcamento.c \
#         model/financeiro.c \
#         view/formatacao.c \
#         view/menus.c \
#         view/mostrar_dados.c \
#         view/receber_dados.c \
#         controller/produtora_controller.c \
#         controller/recurso_controller.c \
#         controller/operador_controller.c \
#         controller/cliente_controller.c \
#         controller/equipe_controller.c \
#         controller/fornecedor_controller.c \
#         controller/orcamento_controller.c \
#         controller/financeiro_controller.c \
#         controller/controller.c \
#         validacoes/validacoes.c

# # Gera a lista de objetos (.o) automaticamente
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

# # --- 4. REGRAS AUXILIARES ---
# run: $(TARGET)
# 	@echo ">> Executando..."
# 	./$(TARGET)

# clean:
# 	@echo ">> Limpando arquivos..."
# 	del $(TARGET) $(OBJS)

# .PHONY: all clean run7

# =============================================================================
# Makefile para o projeto de Gestão de Eventos
# =============================================================================

# --- 1. CONFIGURAÇÕES E VARIÁVEIS ---
CC = gcc
TARGET = produtora.exe
CFLAGS = -Wall -g -I. -Imodel -Iview -Icontroller -Ivalidacoes

# --- 2. DEFINIÇÃO DOS ARQUIVOS ---
# O VPATH diz ao make onde procurar os arquivos .c se não estiverem na raiz
VPATH = model:view:controller:validacoes

# LISTA COMPLETA DE ARQUIVOS (Incluindo Financeiro, Orcamento e Relatorios)
SRCS =  main.c \
        model/produtora.c \
        model/recurso.c \
        model/operador.c \
        model/cliente.c \
        model/equipe.c \
        model/fornecedor.c \
        model/orcamento.c \
        model/financeiro.c \
        view/formatacao.c \
        view/menus.c \
        view/mostrar_dados.c \
        view/receber_dados.c \
        view/relatorios_view.c \
        controller/produtora_controller.c \
        controller/recurso_controller.c \
        controller/operador_controller.c \
        controller/cliente_controller.c \
        controller/equipe_controller.c \
        controller/fornecedor_controller.c \
        controller/orcamento_controller.c \
        controller/financeiro_controller.c \
        controller/relatorios_controller.c \
        controller/xml_controller.c \
        controller/controller.c \
        validacoes/validacoes.c

# Gera a lista de objetos (.o) automaticamente retirando o caminho das pastas
OBJS = $(notdir $(SRCS:.c=.o))

# --- 3. REGRAS DE COMPILAÇÃO ---
all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "----------------------------------------"
	@echo ">> Linkando o programa: $(TARGET)"
	@echo "----------------------------------------"
	$(CC) $(OBJS) -o $(TARGET)

# Regra genérica para compilar qualquer .c em .o
%.o: %.c
	@echo "Compilando $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

# --- 4. REGRAS AUXILIARES ---
run: $(TARGET)
	@echo ">> Executando..."
	./$(TARGET)

clean:
	@echo ">> Limpando arquivos..."
	del $(TARGET) $(OBJS)

.PHONY: all clean run