/*
1 Crear una clase que contenga la definición de un enumerado y ofrezca:
const char* AsStr(Enum _eEnum); Enum AsEnum(const char* _sEnum);
*/
#pragma once
enum class EColor
{
	Rojo,
	Azul,
	Verde,
	Amarillo,
	Invalido
};
class CEnum
{
public:
	const char* AsStr(EColor _eEnum);
	EColor AsEnum(const char* _sEnum);
};