#include <iostream>
#include "TList16.h"
#include <crtdbg.h>
class CText : public Practica16::IListItem // <-- Es una interfaz, así que siempre tiene que heredar alguien
{
public:
	virtual void Print() const override
	{
		printf("%s\n", sText);
	}
	virtual Practica16::IListItem* Clone() const override
	{
		return new CText(*this); // <-- new, te jodes
	}
	const char* sText = "";
};

class CNumber : public Practica16::IListItem
{
public:
	virtual void Print() const override
	{
		printf("%d\n", iValue);
	}
	virtual Practica16::IListItem* Clone() const override
	{
		return new CNumber(*this); // <-- new, te jodes
	}
	int iValue = 0;
};
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	CText oText1;
	oText1.sText = "uno";
	CText oText2;
	oText2.sText = "dos";
	CText oText3;
	oText3.sText = "tres";
	CText oText4;
	oText4.sText = "cuatro";
	CText oText5;
	oText5.sText = "cinco";

	CNumber oNumber1;
	oNumber1.iValue = 1;
	CNumber oNumber2;
	oNumber2.iValue = 2;
	CNumber oNumber3;
	oNumber3.iValue = 3;
	CNumber oNumber4;
	oNumber4.iValue = 4;
	CNumber oNumber5;
	oNumber5.iValue = 5;
	Practica16::TList lNumeros;
	lNumeros.Push(&oText1);
	lNumeros.Push(&oNumber1);
	lNumeros.Push(&oText2);
	lNumeros.Push(&oNumber2);
	lNumeros.Push(&oText3);
	lNumeros.Push(&oNumber3);
	lNumeros.Push(&oText4);
	lNumeros.Push(&oNumber4);
	lNumeros.Push(&oText5);
	lNumeros.Push(&oNumber5);
	printf("Numeros leidos (%d):\n", lNumeros.Size());
	for (Practica16::IListItem* p = lNumeros.First(); p != nullptr; p = lNumeros.Next())
	{
		p->Print();
	}
	printf("\n");
	Practica16::TList lNumeros2(lNumeros);
	printf("Numeros leidos (copia) (%d):\n", lNumeros2.Size());
	for (Practica16::IListItem* p = lNumeros2.First(); p != nullptr; p = lNumeros2.Next())
	{
		p->Print();
	}
	printf("\n");
	Practica16::TList lNumeros3(GetReverseList(lNumeros));
	printf("Numeros leidos (invertido) (%d):\n", lNumeros3.Size());
	for (Practica16::IListItem* p = lNumeros3.First(); p != nullptr; p = lNumeros3.Next())
	{
		p->Print();
	}
	printf("\n");
	Practica16::TList lNumeros4;
	lNumeros4 = lNumeros3;
	printf("Numeros leidos (operator=) (%d):\n", lNumeros4.Size());
	for (Practica16::IListItem* p = lNumeros4.First(); p != nullptr; p = lNumeros4.Next())
	{
		p->Print();
	}
	printf("\n");
	return 0;
}