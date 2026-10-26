/*
Práctica 16 - Interfaces: una lista de IListItem

1 Una lista con la funcionalidad de TList que guarde cualquier objeto que implemente IListItem.

2 Push recibe un const IListItem& y guarda una copia hecha con Clone(). First, Next y Pop retornan IListItem*;
quien recibe el de Pop lo borra.

3 Al menos dos clases que implementen la interfaz (un número, un texto...), mezcladas en la misma lista.

4 Un método Print() de la lista que muestre todos sus elementos.
*/

// Es la TList de las prácticas 9 y 11, pero en vez de cadenas guarda objetos IListItem.
// Si tienes dudas de cómo funciona la lista, lee los comentarios de TList09.h y TList11.h
#pragma once
namespace Practica16
{
	// Una interfaz es una clase sin atributos ni código, solo funciones virtuales puras (= 0). Es un "contrato":
	// cualquier clase que la herede se compromete a escribir Clone y Print. Así la lista puede guardar objetos
	// de tipos distintos (texto, número...) sin saber cuál es cuál: solo sabe que cumplen el contrato
	class IListItem
	{
	public:
		virtual ~IListItem() {} // Virtual: si no, delete sobre un IListItem* no destruiría bien al objeto hijo

		// Devuelve una copia del objeto, creada con new. La lista guarda esa copia y no el original: si dos
		// sitios apuntaran al mismo objeto, el delete de uno dejaría al otro apuntando a memoria liberada
		// (es lo mismo que hacía TList09 al copiar cada cadena con new char[])
		virtual IListItem* Clone() const = 0;
		virtual void Print() const = 0;
	};

	class TList
	{
	public:
		TList();
		TList(const TList& _lstOther); // Regla de tres, igual que en la práctica 11
		TList& operator=(const TList& _lstOther);
		~TList();

		int Size() const;

		// Añaden una COPIA del elemento (hecha con Clone) al final / al principio. Retornan el nuevo tamaño
		int Push(const IListItem& _oItem);
		int PushFront(const IListItem& _oItem);

		// Igual que en la práctica 9, pero devuelven el elemento (IListItem*) en vez de una cadena
		IListItem* First();
		IListItem* Next();

		// Quita el primer elemento y lo retorna (nullptr si está vacía). A diferencia de TList09, el elemento
		// ya NO pertenece a la lista: quien lo recibe es responsable de hacer delete
		IListItem* Pop();

		void Reset();

		// Llama a Print() de cada elemento, en orden
		void Print() const;

	private:
		class TListNode
		{
		public:
			TListNode(IListItem* _pListItem = nullptr);
			TListNode(const TListNode&) = delete;
			TListNode& operator=(const TListNode&) = delete;
			~TListNode();
			IListItem* m_pListItem = nullptr; // La copia hecha con Clone (antes era el const char*)
			TListNode* m_pNext = nullptr;
		};

		TListNode* m_pFirst = nullptr;
		TListNode* m_pIter = nullptr;
		TListNode* m_pLast = nullptr;
		unsigned int m_uSize = 0;

		friend TList GetReverseList(const TList& _lstSrc); // Ver práctica 11
	};

	TList GetReverseList(const TList& _lstSrc); // Retorna una lista nueva con los elementos en orden inverso
}