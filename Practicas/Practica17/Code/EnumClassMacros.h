/*
2 Mediante macros, generalizar el código anterior para que sea más fácil crear enumerados con esa funcionalidad.

Técnica ("X-macro"): escribimos la lista de colores UNA sola vez y a partir de ella el preprocesador
genera el enum y la tabla de textos. Así nunca se desordenan y para añadir un color solo se toca un sitio.
Una macro es texto que el preprocesador sustituye por otro texto ANTES de compilar.
*/
#pragma once

/*
La lista de colores. Recibe como parámetro(X) OTRA macro y la llama una vez por cada color :
por sí sola no hace nada, solo dice "aplica X a Rojo, a Azul, a Verde y a Amarillo".
La "\" al final de cada línea significa "la macro sigue en la línea siguiente".
Para añadir un color, basta con otra línea X(NuevoColor) aquí.
*/

#define COLOR_LIST(X) \
X(Rojo)               \
X(Azul)               \
X(Verde)              \
X(Amarillo)           \
X(Morado)


class CEnumM
{
public:
// Macro auxiliar: deja el nombre seguido de una coma. AS_ENUMERATOR(Rojo) se convierte en: Rojo,
#define AS_ENUMERATOR(name) name,

enum class EColorM
{
	// COLOR_LIST(AS_ENUMERATOR) se expande a:
	//   AS_ENUMERATOR(Rojo) AS_ENUMERATOR(Azul) ... AS_ENUMERATOR(Morado)
	// y cada una a su vez a "Rojo," "Azul," ..., o sea, el contenido normal de un enum.
	COLOR_LIST(AS_ENUMERATOR)

	Invalido // Siempre el último y fuera de la lista
};
// Borramos la macro auxiliar: ya no hace falta y así no molesta al resto del código
// (además, en el .cpp volveremos a usar COLOR_LIST con otra macro distinta).
#undef AS_ENUMERATOR
	const char* AsStr(EColorM _eColor);
	EColorM AsEnum(const char* _pszNombre);
};