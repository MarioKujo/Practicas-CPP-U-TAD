/*
Práctica 16 - Interfaces: una lista de IListItem

1 Una lista con la funcionalidad de TList que guarde cualquier objeto que implemente IListItem.

2 Push recibe un const IListItem& y guarda una copia hecha con Clone(). First, Next y Pop retornan IListItem*;
quien recibe el de Pop lo borra.

3 Al menos dos clases que implementen la interfaz (un número, un texto...), mezcladas en la misma lista.

4 Un método Print() de la lista que muestre todos sus elementos.
*/
#pragma once
namespace Practica16
{
	// Interfaz: clase sin atributos ni código, solo funciones virtuales puras. Es un "contrato": cualquier clase
	// que la herede se compromete a implementar Clone y Print. Así la lista guarda objetos de tipos distintos
	// (texto, número...) sin saber cuál es cuál. Todo lo que antes era const char* ahora es IListItem.
	class IListItem
	{
	public:
		virtual ~IListItem() {} // Virtual para que el delete a través de un IListItem* destruya bien al objeto hijo

		// Devuelve una copia del objeto creada con new. La lista guarda esa copia y no el original: si dos sitios
		// apuntaran al mismo objeto, el delete de uno dejaría al otro apuntando a memoria ya liberada.
		virtual IListItem* Clone() const = 0;
		virtual void Print() const = 0;
	};

	class TList
	{
	public:
		TList();
		TList(const TList& _lstOther);
		TList& operator=(const TList& _lstOther);
		~TList();

		int Size();

		// Añade una copia del elemento AL FINAL de la lista. Retorna el nº de elementos tras añadirlo.
		int Push(const IListItem& _oItem);

		// Igual, pero AL PRINCIPIO de la lista.
		int PushFront(const IListItem& _oItem);

		// Retorna el primer elemento (o nullptr si está vacía) y deja la lista preparada para que Next() devuelva el
		// segundo.
		IListItem* First();

		// Retorna el siguiente al último devuelto por First() o Next(), o nullptr cuando no quedan más.
		IListItem* Next();

		// Quita el primer elemento y lo retorna (nullptr si está vacía). Quien lo recibe es responsable de hacer delete.
		IListItem* Pop();

		// Elimina todos los elementos; la lista queda vacía pero se puede seguir usando.
		void Reset();

		// Llama a Print() de cada elemento, en orden.
		void Print() const;

	private:
		class TListNode
		{
		public:
			TListNode(IListItem* _pListItem = nullptr);
			~TListNode();
			IListItem* m_pListItem = nullptr; // Antes era el const char*; ahora es el elemento clonado
			TListNode* m_pNext = nullptr;
		};

		TListNode* m_pFirst = nullptr;
		TListNode* m_pIter = nullptr; // Por dónde va el recorrido con First/Next
		TListNode* m_pLast = nullptr;
		unsigned int m_uSize = 0;

		// friend: esta función externa puede acceder a los miembros privados de la lista
		friend TList GetReverseList(TList _lstSrc);
	};

	// Retorna una lista nueva con los elementos de _lstSrc en orden inverso
	TList GetReverseList(TList _lstSrc);
}