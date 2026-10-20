/*
1 int CountOccurrences(const char* pszFileName, const char* pszText): veces que aparece el texto (-1 si no se abre). Distingue mayúsculas y cuenta las solapadas: "aa" en "aaaa" → 3.

2 bool SumNumbers(const char* pszFileName, int& iSum_): suma de los enteros separados por comas (puede haber negativos, espacios y saltos de línea).

3 Declarar en Utils.h, definir en Utils.cpp y leer con las funciones de la práctica 5, por bloques de 16 caracteres.

4 Probar con texto.txt y numeros.txt: "enemigo" → 3, "Enemigo" → 1, "aa" → 3, "xyz" → 0; la suma es 13245.
*/
#pragma once
#include "TList.h"
#include <iostream>
namespace Utils
{
	int CountOccurrences(const char* pszFileName, const char* pszText);
	bool SumNumbers(const char* pszFileName, int& iSum_);
	/*
	Práctica 10:
	1 Añadir al namespace de utilidades de la práctica 7 una función que retorne una lista de cadenas (TList) con los
	números separados por comas presentes en un fichero. Diseñar la declaración de la función.
	*/
	bool ReadNumbers(const char* pszFileName, TList& tList);
}