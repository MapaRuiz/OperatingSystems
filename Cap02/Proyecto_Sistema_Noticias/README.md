# Proyecto Sistema de Noticias
Implementación de un sistema de noticias usando el patrón Publicador/Suscriptor en ANSI C.

## Estructura del Proyecto
- `src/`: Archivos fuente.
- `data/`: Archivos de noticias de prueba.
- `build/`: Objetos guardados al ejecutar make.

## Compilación y Ejecución
1. `make` para compilar los programas.
2. Ejecutar los procesos en diferentes terminales:

   - Sistema de Comunicación:
     ```bash
     ./sistema -p pipePSC -s pipeSSC -t 10
     ```

   - Publicador:
     ```bash
     ./publicador -p pipePSC -f data/noticias1.txt -t 2
     ```

   - Suscriptor:
     ```bash
     ./suscriptor -s pipeSSC
     ```

## Formato de las Noticias
Cada noticia debe tener el formato `[Tipo]:[Contenido]`.
Tipos válidos: A, P, E, C, S.
