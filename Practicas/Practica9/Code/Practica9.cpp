#include <iostream>
#include "TList.h"

void Prueba(TList& tList_)
{
	char sText[] = "cadena temporal";
	tList_.Push(sText);
}

int main()
{
	TList tList;

	tList.Push("primero");
	printf("Size = %d\n", tList.Size());
	tList.Push("segundo");
	printf("Size = %d\n", tList.Size());
	tList.Push("tercero");
	printf("Size = %d\n", tList.Size());
	{
		char sText[] = "cuarto";
		tList.Push(sText);
	}

	Prueba(tList);

	for (const char* p = tList.First(); p != nullptr; p = tList.Next())
	{
		printf("%s\n", p);
	}
	printf("\n");
}