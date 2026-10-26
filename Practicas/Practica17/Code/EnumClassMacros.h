/*
2 Mediante macros, generalizar el código anterior para que sea más fácil crear enumerados con esa funcionalidad.

Técnica "X-macro": la lista de colores se escribe UNA sola vez y el preprocesador genera a partir de ella el enum
y la tabla de textos, así nunca se desordenan. Una macro es texto que el preprocesador sustituye por otro texto
ANTES de compilar.
*/
#pragma once
/*
 La lista de colores. Recibe como parámetro (X) OTRA macro y la aplica a cada color: por sí sola no hace
 nada, solo dice "aplica X a Rojo, a Azul, a Verde...". Para añadir un color basta con otra línea X(...) aquí.
 La "\" tiene que ser lo ÚLTIMO de la línea (ni siquiera un espacio detrás): significa "sigue en la línea siguiente"
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
	// Macro auxiliar: AS_ENUMERATOR(Rojo) se convierte en "Rojo,"
#define AS_ENUMERATOR(name) name,

	enum class EColorM
	{
		// COLOR_LIST(AS_ENUMERATOR) se expande a "Rojo, Azul, Verde, Amarillo, Morado,", que es
		// justo el contenido normal de un enum
		COLOR_LIST(AS_ENUMERATOR)

		Invalido // Siempre el último y fuera de la lista
	};
	// Ya no hace falta: se borra para que no moleste (en el .cpp se usa COLOR_LIST con otra macro distinta)
#undef AS_ENUMERATOR

	static const char* AsStr(EColorM _eColor);
	static EColorM AsEnum(const char* _pszNombre);
};