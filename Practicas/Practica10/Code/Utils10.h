/*
1 Añadir al namespace de utilidades de la práctica 7 una función que retorne una
lista de cadenas (TList) con los números separados por comas presentes en un
fichero. Diseñar la declaración de la función.
2 Sacar por consola los números leídos.
*/
#pragma once
#include "TList09.h"
#include <iostream>
namespace Utils
{
	bool ReadNumbers(const char* pszFileName, Practica09::TList& tList);
}