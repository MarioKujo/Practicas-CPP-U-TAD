#include "TList16.h"
#include <cstdio>

// Es la TList de las prácticas 9 y 11; para lo que no esté comentado aquí, mira TList09.cpp y TList11.cpp.
// Lo único que cambia: Push y PushFront ahora reciben un elemento y hacen su propio Clone(), y como
// los nodos guardan punteros a objetos, hay que hacer delete de cada uno
namespace Practica16
{
	TList::TList()
		: m_pFirst(nullptr)
		, m_pIter(nullptr)
		, m_pLast(nullptr)
		, m_uSize(0)
	{
	}

	TList::TList(const TList& _lstOther)
	{
		printf("Constructor de copia de TList\n");
		// *pNode->m_pListItem: el * convierte el puntero en el objeto al que apunta, que es lo que espera Push
		for (const TListNode* pNode = _lstOther.m_pFirst; pNode != nullptr; pNode = pNode->m_pNext)
		{
			Push(*pNode->m_pListItem);
		}
	}

	TList& TList::operator=(const TList& _lstOther)
	{
		if (this != &_lstOther)
		{
			Reset();
			for (const TListNode* pNode = _lstOther.m_pFirst; pNode != nullptr; pNode = pNode->m_pNext)
			{
				Push(*pNode->m_pListItem);
			}
		}
		return *this;
	}

	TList GetReverseList(const TList& _lstSrc)
	{
		TList lstReversed;
		for (const TList::TListNode* pNode = _lstSrc.m_pFirst; pNode != nullptr; pNode = pNode->m_pNext)
		{
			lstReversed.PushFront(*pNode->m_pListItem);
		}
		return lstReversed;
	}

	TList::~TList()
	{
		Reset();
	}

	int TList::Size() const
	{
		return m_uSize;
	}

	int TList::Push(const IListItem& _oItem)
	{
		TListNode* pNewNode = new TListNode;
		// Clone() sabe crear la copia del tipo REAL del objeto (CText, CNumber...) aunque aquí solo se vea un IListItem
		pNewNode->m_pListItem = _oItem.Clone();
		if (m_pFirst == nullptr)
		{
			m_pFirst = pNewNode;
		}
		else
		{
			m_pLast->m_pNext = pNewNode;
		}
		m_pLast = pNewNode;
		++m_uSize;
		return m_uSize;
	}

	int TList::PushFront(const IListItem& _oItem)
	{
		TListNode* pNewNode = new TListNode;
		pNewNode->m_pListItem = _oItem.Clone();
		pNewNode->m_pNext = m_pFirst;
		m_pFirst = pNewNode;

		if (m_pLast == nullptr)
		{
			m_pLast = pNewNode;
		}

		++m_uSize;
		return m_uSize;
	}

	IListItem* TList::First()
	{
		m_pIter = m_pFirst;
		if (m_pIter)
		{
			return m_pIter->m_pListItem;
		}
		return nullptr;
	}

	IListItem* TList::Next()
	{
		if (m_pIter)
		{
			m_pIter = m_pIter->m_pNext;
		}
		if (m_pIter)
		{
			return m_pIter->m_pListItem;
		}
		return nullptr;
	}

	IListItem* TList::Pop()
	{
		if (m_pFirst == nullptr)
		{
			m_pLast = nullptr;
			return nullptr;
		}

		TListNode* pNodeQuitado = m_pFirst;
		m_pFirst = pNodeQuitado->m_pNext;
		--m_uSize;
		if (m_pFirst == nullptr)
		{
			m_pLast = nullptr;
		}
		if (m_pIter == pNodeQuitado)
		{
			m_pIter = nullptr;
		}
		// Se guarda el elemento antes de borrar el nodo, si no se perdería su dirección. Aquí no hace falta
		// el truco de m_pszLastPopped de la práctica 9: el elemento sigue vivo y se lo queda quien llame a Pop
		IListItem* pItemQuitado = pNodeQuitado->m_pListItem;
		delete pNodeQuitado; // Borra solo el nodo
		return pItemQuitado;
	}

	void TList::Reset()
	{
		TListNode* pNodeActual = m_pFirst;
		while (pNodeActual)
		{
			TListNode* pNodeABorrar = pNodeActual;
			pNodeActual = pNodeActual->m_pNext;
			delete pNodeABorrar->m_pListItem; // Libera la copia hecha con Clone()
			delete pNodeABorrar;
		}
		m_pFirst = nullptr;
		m_pLast = nullptr;
		m_uSize = 0;
		m_pIter = nullptr;
	}

	void TList::Print() const
	{
		// Recorre con su propio puntero para no alterar m_pIter (el recorrido de First/Next)
		for (const TListNode* pNode = m_pFirst; pNode != nullptr; pNode = pNode->m_pNext)
		{
			pNode->m_pListItem->Print(); // Polimorfismo: se ejecuta el Print de CText o de CNumber según el objeto
		}
	}

	TList::TListNode::TListNode(IListItem* _pListItem)
	{
		m_pListItem = _pListItem;
	}

	// No borra nada a propósito: de los elementos y de los nodos se encarga Reset(). Además, Pop borra
	// el nodo pero NO el elemento, porque se lo lleva quien llama
	TList::TListNode::~TListNode()
	{
	}
}