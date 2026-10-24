/*
Macros de depuración. Crear un fichero “Debug.h” con estas dos macros:
a. LOG(...): funciona como printf, pero delante escribe el fichero y la línea desde donde se llama
(__FILE__, __LINE__ y __VA_ARGS__). Por ejemplo, LOG("vida = %d", iVida);
muestra main.cpp(12): vida = 100.
b. ASSERT(cond): si la condición es falsa, muestra la condición como texto (operador #), el fichero
y la línea, y para el programa (con abort()). Por ejemplo, ASSERT(iVida > 200);
muestra ASSERT fallido: iVida > 200 y main.cpp(16).
c. Las dos macros solo hacen algo en Debug. En Release (cuando no está definida _DEBUG, que
Visual Studio define en la configuración Debug) no hacen nada. Comprobarlo compilando en las dos
configuraciones.
d. Probar ASSERT(++iIntentos < 3); en Debug y en Release: ¿cuánto vale iIntentos después en cada caso?
¿Por qué? ¿Qué regla sacamos para lo que se escribe dentro de un ASSERT?

- Debug: iIntentos = 1, porque ASSERT evalúa la condición y el ++ se ejecuta.
- Release: iIntentos = 0, porque ASSERT se expande a do { } while (0) y la condición ni se compila.
- Regla: dentro de un ASSERT solo van condiciones que lean, sin efectos secundarios (++, --, asignaciones, llamadas que modifiquen
estado). Si no, el bug aparece solo en Release, que es donde peor se depura. Lo correcto es separar: ++iIntentos;
ASSERT(iIntentos < 3);.

e. Pista: para que las macros funcionen bien dentro de un if sin llaves, envolverlas en do { ... }
while (0).
*/
#pragma once
#include <cstdio>
#include <cstdlib>

#ifdef _DEBUG
// __VA_ARGS__ Es lo que sustituye a ... en LOG(...), o sea, si haces LOG("vida = %d", iVida); __VA_ARGS__ se sustituye por
// "vida = %d", iVida 
#define LOG(...)                                     \
do                                                   \
{                                                    \
	printf("%s(%d): ", __FILE__, __LINE__);          \
	printf(__VA_ARGS__);                             \
	printf("\n");                                    \
} while (0)
// __FILE__ es el archivo (Practica18.h) y __LINE__ es la línea de la izquierda (como esta, que es la línea 30)
#define ASSERT(cond)                                 \
do                                                   \
{                                                    \
	if(!(cond))                                      \
	{                                                \
		printf("ASSERT fallido: %s\n%s(%d)\n",       \
		#cond, __FILE__, __LINE__);                  \
		abort();                                     \
	}\
} while (0)

#else

#define LOG(...)     do { } while (0)
#define ASSERT(cond) do { } while (0)

#endif