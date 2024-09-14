# Variables
GCC = gcc          # Compilador
CFLAGS = -Wall     # Flags de compilación
LIBS = Taller.o    # Librerías objeto a enlazar
TARGET = programa  # Nombre del ejecutable final

# Regla para compilar el programa principal
$(TARGET): Principal.o $(LIBS)
	$(GCC) -o $(TARGET) Principal.o $(LIBS)

# Regla para compilar el archivo Principal.c
Principal.o: Principal.c Taller.h
	$(GCC) $(CFLAGS) -c Principal.c

# Regla para compilar el archivo Taller.c (que contiene la implementación de la librería)
Taller.o: Taller.c Taller.h
	$(GCC) $(CFLAGS) -c Taller.c

# Limpiar archivos objeto y ejecutables
clean:
	rm -f *.o $(TARGET)
