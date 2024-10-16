# Nombre del ejecutable
EXEC = parcial

# Archivos fuente
SRC = Parcial2.c

# Compilador
CC = gcc

# Flags de compilación
CFLAGS = -Wall -Wextra -Werror

# Valores de ejemplo para los argumentos de entrada
N1 = 5
N2 = 4
ARCHIVO00 = archivo00.txt
ARCHIVO01 = archivo01.txt

# Regla principal
all: $(EXEC)

# Regla para compilar el ejecutable
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

# Regla para ejecutar el programa con los argumentos de ejemplo
run: $(EXEC)
	./$(EXEC) $(N1) $(ARCHIVO00) $(N2) $(ARCHIVO01)

# Regla para limpiar archivos objeto y ejecutables generados
clean:
	rm -f $(EXEC)

# Regla para recompilar desde cero
rebuild: clean all

# Indicar que estas reglas no corresponden a archivos
.PHONY: all clean rebuild run
