// 2 Organizar el código de la práctica 6 usando un namespace.
#pragma once
#include <iostream>
namespace Utils
{
	int CountOccurrences(const char* pszFileName, const char* pszText);
	bool SumNumbers(const char* pszFileName, int& iSum_);
}