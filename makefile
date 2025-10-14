# =============================================================================
# Makefile para o projeto de Gestão de Clientes
# Este arquivo automatiza a compilação e execução do projeto.
#
# Comandos úteis:
#   make        - Compila o projeto.
#   make run    - Compila (se necessário) e executa o programa.
#   make clean  - Apaga os arquivos compilados.
# =============================================================================

# --- 1. CONFIGURAÇÕES E VARIÁVEIS ---

# Nome do compilador C que será usado
CC = gcc

# Nome do arquivo executável que será gerado
TARGET = programa.exe

# Flags (opções) para o compilador
CFLAGS = -Wall -g -I. -Imodel -Iview -Icontroller -Ivalidacoes

# --- 2. DEFINIÇÃO DOS ARQUIVOS ---

# Adiciona os diretórios dos fontes ao caminho de busca do make (VPATH).
# CORRIGIDO: Adicionada a pasta 'validacoes'
VPATH = model:view:controller:validacoes

# Lista de todos os arquivos de código-fonte (.c) do projeto.
SRCS =  main.c \
        model/cliente.c \
        view/view.c \
        controller/controller.c \
        validacoes/validacoes.c

# Gera a lista de arquivos objeto (.o), removendo os caminhos das pastas.
OBJS = $(notdir $(SRCS:.c=.o))


# --- 3. REGRAS DE COMPILAÇÃO ---

# A regra padrão 'make' apenas compila o programa.
all: $(TARGET)

# Regra para "linkar" o programa (juntar tudo no executável final).
$(TARGET): $(OBJS)
	@echo "----------------------------------------"
	@echo ">> Linkando o programa: $(TARGET)"
	@echo "----------------------------------------"
	$(CC) $(OBJS) -o $(TARGET)

# Regra genérica para compilar qualquer arquivo .c em um arquivo .o
%.o: %.c
	@echo "Compilando $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@


# --- 4. REGRAS AUXILIARES E DE ATALHO ---

# Regra para compilar (se necessário) e executar o programa.
run: $(TARGET)
	@echo "----------------------------------------"
	@echo ">> Executando o programa..."
	@echo "----------------------------------------"
	./$(TARGET)

# Regra para limpar o projeto (apagar arquivos compilados).
clean:
	@echo "----------------------------------------"
	@echo ">> Limpando arquivos compilados..."
	@echo "----------------------------------------"
	del $(TARGET) $(OBJS)

# Declara que 'all', 'clean', e 'run' não são nomes de arquivos reais.
.PHONY: all clean run






# # Define o compilador a ser usado.
# CC = gcc
# # Define as flags de compilação.
# # -Wall: Habilita todos os avisos (warnings) comuns.
# # -Wextra: Habilita avisos extras.
# # -g: Inclui informações de debug no executável (útil para o GDB).
# CFLAGS = -Wall -Wextra -g
# # Define o nome do arquivo executável final.
# TARGET = programa.exe

# # Define a lista de todos os arquivos objeto (.o) que o projeto precisa.
# # Cada arquivo .c será compilado em um arquivo .o correspondente.
# OBJECTS = main.o cliente.o view.o controller.o

# # --- Regras de Compilação ---

# # A regra padrão, executada quando você digita apenas 'make'.
# # Ela depende de todos os arquivos objeto listados em $(OBJECTS).
# all: $(TARGET)

# # Regra de linkagem: Junta todos os arquivos objeto para criar o executável final.
# # Esta regra é acionada depois que todos os arquivos .o foram criados.
# $(TARGET): $(OBJECTS)
# 	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# # Regra de compilação para main.o.
# # Ele depende de main.c e controller.h. Se algum deles mudar, main.o será recompilado.
# main.o: main.c controller.h
# 	$(CC) $(CFLAGS) -c main.c -o main.o

# # Regra de compilação para controller.o.
# # Depende dos seus próprios fontes e dos headers que ele inclui.
# controller.o: controller.c controller.h view.h cliente.h
# 	$(CC) $(CFLAGS) -c controller.c -o controller.o

# # Regra de compilação para view.o.
# view.o: view.c view.h cliente.h
# 	$(CC) $(CFLAGS) -c view.c -o view.o

# # Regra de compilação para cliente.o.
# cliente.o: cliente.c cliente.h
# 	$(CC) $(CFLAGS) -c cliente.c -o cliente.o

# # Regra de limpeza: Remove os arquivos gerados pela compilação.
# # Executada com o comando 'make clean'.
# clean:
# 	# Comando para deletar no Windows.
# 	del /f /q $(TARGET) $(OBJECTS) 2>nul || (exit 0)
# 	# O '2>nul || (exit 0)' evita erros caso os arquivos não existam.