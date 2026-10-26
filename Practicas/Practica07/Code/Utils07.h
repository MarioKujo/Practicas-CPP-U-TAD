// 2 Organizar el código de la práctica 6 usando un namespace.
#pragma once
#include <iostream>

namespace Utils
{
	int CountOccurrences(const char* pszFileName, const char* pszText); // Devuelve -1 si no se puede abrir el archivo
	bool SumNumbers(const char* pszFileName, int& iSum_); // iSum_ es parámetro de salida. Devuelve false si no se puede
	// abrir
}