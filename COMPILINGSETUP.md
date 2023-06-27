# Configuración rápida

Si se desea compilar el archivo por cuenta propia, es necesario instalar opencv y cmake, y añadir ciertos directorios al path (reemplazando cuando sea necesario).

## Añadir a path del sistema

```
C:\tools\opencv\build\x64\vc16\bin
```

```
C:\Program Files\CMake\bin
```

```
C:\tools\opencv\build\x64\vc16\lib
```

## Añadir a path del usuario

```
C:\Program Files\CMake\bin
```

# Extras

Se recomienda añadir el directorio del build de OpenCV a usar a los ajustes de Intellisense (vscode):
```
".../build/include/opencv2/**"
```

Donde '**' indica búsqueda recursiva.

Ejemplo:
```
"C:\tools\opencv\build\include\opencv2/**"
```

El compilador utilizado fue Visual Studio Community 20XX Release - amd64.