#include <iostream>
#include "TList.h"
int main()
{
	TList tList;

	tList.Push("primero");
	printf("Size = %d\n", tList.Size());
	tList.Push("segundo");
	printf("Size = %d\n", tList.Size());
	tList.Push("tercero");
	printf("Size = %d\n", tList.Size());

	for (const char* p = tList.First(); p != nullptr; p = tList.Next())
	{
		printf("%s\n", p);
	}
	printf("\n");

	const char* pPrimero = tList.Pop();    // "uno"  -> lista: dos, tres

	for (const char* p = tList.First(); p != nullptr; p = tList.Next())
	{
		printf("%s\n", p);
	}
	tList.Reset();                         // lista vacía -> Size() == 0
	printf("\n");
	printf("Size = %d\n", tList.Size());
	printf("\n");
}