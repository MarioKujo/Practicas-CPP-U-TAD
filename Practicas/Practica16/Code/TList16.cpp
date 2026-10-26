#include "TList16.h"
#include <cstring>
#include <cstdio>
namespace Practica16
{
	TList::TList()
		: m_pFirst(nullptr)
		, m_pIter(nullptr)
		, m_pLast(nullptr)
		, m_uSize(0)
	{
	}

	// Copiar, invertir y asignar funcionan igual que en la práctica 9: lo único que cambia es que
	// Push y PushFront ahora reciben el elemento (por referencia, de ahí el "*") y hacen su propio Clone().
	TList::TList(const TList& _lstOther)
	{
		printf("Constructor de copia de TList\n");
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

	TList GetReverseList(TList _lstSrc)
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

	int TList::Size()
	{
		return m_uSize;
	}

	int TList::Push(const IListItem& _oItem)
	{
		TListNode* pNewNode = new TListNode;
		pNewNode->m_pListItem = _oItem.Clone(); // Guardamos una copia propia, no el original
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
			m_pLast = nullptr; // La lista se ha vaciado: la cola ya no existe
		}
		if (m_pIter == pNodeQuitado)
		{
			m_pIter = nullptr;
		}
		// Hay que guardar el elemento antes de borrar el nodo; si no, perdemos su dirección y queda sin liberar.
		// Ya no es de la lista: quien llame a Pop() debe hacer delete.
		IListItem* pItemQuitado = pNodeQuitado->m_pListItem;
		delete pNodeQuitado;
		return pItemQuitado;
	}

	void TList::Reset()
	{
		TListNode* pNodeActual = m_pFirst;
		while (pNodeActual)
		{
			TListNode* pNodeABorrar = pNodeActual;
			pNodeActual = pNodeActual->m_pNext; // Avanzamos antes de borrar, si no perderíamos el resto de la lista
			delete pNodeABorrar->m_pListItem; // Aquí se libera la copia hecha con Clone()
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
			pNode->m_pListItem->Print();
		}
	}

	TList::TListNode::TListNode(IListItem* _pListItem)
	{
		m_pListItem = _pListItem;
	}

	// El destructor del nodo no borra nada a propósito: el delete de m_pListItem y de los nodos lo hace Reset()
	TList::TListNode::~TListNode()
	{
	}
}