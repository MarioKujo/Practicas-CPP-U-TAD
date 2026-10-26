/*
1 Crear una clase que contenga la definición de un enumerado y ofrezca:
const char* AsStr(Enum _eEnum);
Enum AsEnum(const char* _sEnum);

Prefijos nuevos: e = enumerado, apsz = array de punteros a texto.
*/
#pragma once

class CEnum
{
public:
	// "enum class": los valores se escriben siempre con el nombre delante (EColor::Rojo) y no se convierten
	// solos en int. Por debajo cada valor es un número que empieza en 0: Rojo = 0, Azul = 1, Verde = 2...
	enum class EColor
	{
		Rojo,
		Azul,
		Verde,
		Amarillo,
		Invalido // Valor "de error": lo devuelve AsEnum cuando el texto no corresponde a ningún color
	};
	static const char* AsStr(EColor _eColor);       // Enumerado -> texto
	static EColor AsEnum(const char* _pszNombre);   // Texto -> enumerado
};