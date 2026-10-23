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
e. Pista: para que las macros funcionen bien dentro de un if sin llaves, envolverlas en do { ... }
while (0).
*/
#pragma once
