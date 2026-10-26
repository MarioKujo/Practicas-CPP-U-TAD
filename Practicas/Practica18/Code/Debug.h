/*
Macros de depuración
Crear un fichero "Debug.h" con estas dos macros:
a. LOG(...): funciona como printf, pero delante escribe el fichero y la línea desde donde se llama
(__FILE__, __LINE__ y __VA_ARGS__). Por ejemplo, LOG("vida = %d", iVida); muestra main.cpp(12): vida = 100.
b. ASSERT(cond): si la condición es falsa, muestra la condición como texto (operador #), el fichero
y la línea, y para el programa (con abort()). Por ejemplo, ASSERT(iVida > 200); muestra
ASSERT fallido: iVida > 200 y main.cpp(16).
c. Las dos macros solo hacen algo en Debug. En Release (cuando no está definida _DEBUG, que
Visual Studio define en la configuración Debug) no hacen nada. Comprobarlo compilando en las dos configuraciones.
d. Probar ASSERT(++iIntentos < 3); en Debug y en Release: ¿cuánto vale iIntentos después en cada caso?
¿Por qué? ¿Qué regla sacamos para lo que se escribe dentro de un ASSERT?

- Debug: iIntentos = 1, porque ASSERT evalúa la condición y el ++ se ejecuta.
- Release: iIntentos = 0, porque ASSERT se expande a do { } while (0) y la condición ni se compila.
- Regla: dentro de un ASSERT solo van condiciones que lean, sin efectos secundarios (++, --, asignaciones,
llamadas que modifiquen estado). Si no, el bug aparece solo en Release, que es donde peor se depura.
Lo correcto es separar: ++iIntentos; ASSERT(iIntentos < 3);

e. Pista: para que las macros funcionen bien dentro de un if sin llaves, envolverlas en do { ... } while (0).
*/
#pragma once
#include <cstdio>
#include <cstdlib>

/*
Una macro es texto que el preprocesador sustituye por otro ANTES de compilar (no es una función).
#ifdef significa "si está definido": lo que hay hasta el #else solo se compila si existe _DEBUG,
que Visual Studio define solo en la configuración Debug. En Release se compila la parte del #else
*/

#ifdef _DEBUG

/*
Los "..." significan "cualquier cantidad de argumentos", y __VA_ARGS__ es donde se pegan tal cual:
LOG("vida = %d", iVida); convierte __VA_ARGS__ en  "vida = %d", iVida
__FILE__ y __LINE__ los rellena el preprocesador con el fichero y la línea donde se ESCRIBE la llamada a LOG
(por eso es una macro y no una función: una función daría siempre el fichero y la línea de su propia definición).
La "\" tiene que ser lo último de cada línea: significa "la macro sigue en la línea siguiente".
do { ... } while (0) se ejecuta una sola vez y hace que la macro cuente como UNA sola instrucción.
Sin él, en un if sin llaves solo la primera línea de la macro quedaría dentro del if
*/

#define LOG(...)                                          \
do                                                        \
{                                                         \
	printf("%s(%d): ", __FILE__, __LINE__);                 \
	printf(__VA_ARGS__);                                    \
	printf("\n");                                           \
} while (0)

// El operador # delante de un parámetro de macro lo convierte en texto entre comillas:
// con ASSERT(iVida > 200), #condicion es "iVida > 200", y así se puede mostrar la condición tal cual está escrita.
// Los paréntesis de (condicion) evitan problemas de prioridad de operadores al negarla con !.
// abort() detiene el programa de golpe
#define ASSERT(condicion)                                 \
do                                                        \
{                                                         \
	if (!(condicion))                                       \
	{                                                       \
		fprintf(stderr, "ASSERT fallido: %s\n%s(%d)\n",       \
		#condicion, __FILE__, __LINE__);                      \
		abort();                                              \
	}                                                       \
} while (0)

#else

// En Release las macros se expanden a "nada": lo que se escriba entre paréntesis ni se compila.
// Por eso un ++ dentro de un ASSERT desaparece en Release (pregunta d)
#define LOG(...)             do { } while (0)
#define ASSERT(condicion)    do { } while (0)

#endif