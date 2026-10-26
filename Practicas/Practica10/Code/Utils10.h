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
	// En vez de "retornar" la lista, la función la rellena: oLista_ es una referencia, así que lo que se haga
	// dentro se ve en la variable que se pase desde fuera (el _ final indica que es un parámetro de salida).
	// El bool dice si se pudo abrir el archivo: false = error, true = todo bien
	bool ReadNumbers(const char* pszFileName, Practica09::TList& oLista_);
}