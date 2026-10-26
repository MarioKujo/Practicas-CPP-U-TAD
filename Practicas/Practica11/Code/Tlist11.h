/*
1 Realizar un constructor de copia para la lista enlazada de la práctica 9.

2 Realizar una función que reciba una lista y retorne otra con los elementos invertidos: TList GetReverseList(TList
lstSrc);

3 Contar las llamadas al constructor de copia (un printf dentro) y rediseñar la función, cambiando su prototipo, para
maximizar su rendimiento. Pista: referencias. ¿Por qué no puede ser const TList&?

- GetReverseList no podrá recibir const TList& si usa First()/Next()/Pop() sobre la lista de entrada, porque esos
métodos no son const. Si quisiéramos const TList&, tendríamos que hacerlos const (o recorrer los nodos por otro camino).

// Práctica 12 <-- OJO, AQUÍ ESTÁ LA PRÁCTICA 12
// ▸ Además: añadir operator= a la TList de la práctica 11 (regla de tres).
*/

// Es la TList de la práctica 9 con añadidos. Si tienes dudas de cómo funciona algo que no esté comentado aquí,
// lee los comentarios de TList09.h y TList09.cpp

#pragma once
namespace Practica11
{

	class TList
	{
	public:
		TList();

		// Regla de tres: si una clase reserva memoria con new, necesita las TRES cosas a la vez:
		// constructor de copia, operator= y destructor. Si falta alguna, copiar la lista haría que dos listas
		// compartieran los mismos nodos y los dos destructores los liberasen (el problema de TFile en la práctica 8).

		// 1 Constructor de copia: se ejecuta con TList oB(oA); o TList oB = oA;
		// Hace una copia PROFUNDA: crea nodos nuevos, así cada lista tiene los suyos.
		TList(const TList& oOther);

		// Se ejecuta con oB = oA; cuando oB ya existe (por eso primero tiene que vaciarse)
		TList& operator=(const TList& oOther);

		~TList();

		int Size() const;
		int Push(const char* psz);

		// NUEVO: añade la cadena AL PRINCIPIO de la lista (se añadió para poder invertir). Retorna el nuevo tamaño.
		int PushFront(const char* psz);

		const char* First();
		const char* Next();
		const char* Pop();
		void Reset();

	private:
		class TListNode // Igual que en la práctica 9
		{
		public:
			TListNode(const char* _pszText = nullptr);
			TListNode(const TListNode&) = delete;
			TListNode& operator=(const TListNode&) = delete;
			~TListNode();
			const char* m_pszCadena = nullptr;
			TListNode* m_pNext = nullptr;
		};

		TListNode* m_pFirst = nullptr;
		TListNode* m_pIter = nullptr;
		TListNode* m_pLast = nullptr;
		const char* m_pszLastPopped = nullptr;
		unsigned int m_uSize = 0;

		// NUEVO: GetReverseList no es un método de la clase, pero con "friend" se le permite ver la parte privada
		// (aquí, recorrer los nodos directamente)
		friend TList GetReverseList(const TList& lstSrc);

	};

	// 2 Devuelve otra lista con los elementos en orden inverso
	TList GetReverseList(const TList& lstSrc);
}