#include "TList16.h"
#include <cstring>
#include <cstdio>
namespace Practica16
{
	TList::TList()
		: m_pFirst(nullptr)
		, m_pIter(nullptr)
		, m_pLast(nullptr)
		, m_iSize(0)
	{
	}

	TList::TList(const TList& other)
	{
		printf("Constructor de copia de TList\n");
		for (const TListNode* p = other.m_pFirst; p != nullptr; p = p->m_pNext)
		{
			Push(p->pListItem); // <-- Estas se mantienen exactamente igual porque se basan en TListNode* no en el
			// const char* ni en qué tiene TListNode* por dentro
		}
	}

	TList& TList::operator=(const TList& other)
	{
		if (this != &other)
		{
			Reset();
			for (const TListNode* p = other.m_pFirst; p != nullptr; p = p->m_pNext)
			{
				Push(p->pListItem);// <-- Estas se mantienen exactamente igual porque se basan en TListNode* no en el
			// const char* ni en qué tiene TListNode* por dentro
			}
		}
		return *this;
	}

	TList GetReverseList(TList lstSrc)
	{
		TList reversed;
		for (const TList::TListNode* p = lstSrc.m_pFirst; p != nullptr; p = p->m_pNext)
		{
			reversed.PushFront(p->pListItem);// <-- Estas se mantienen exactamente igual porque se basan en TListNode*
			// no en el const char* ni en qué tiene TListNode* por dentro
		}
		return reversed;
	}

	TList::~TList()
	{
		Reset();
	}

	int TList::Size()
	{
		return m_iSize;
	}

	int TList::Push(IListItem* psz)
	{
		TListNode* pNewNode = new TListNode;
		pNewNode->pListItem = psz->Clone(); // pListItem era m_sCadena antes, y psz->Clone() hace lo que digo en el .h,
		// para que no apunte al mismo puntero y no haga delete múltiple (el resto del código es igual, es sólo esto)
		if (m_pFirst == nullptr)
		{
			m_pFirst = pNewNode;
		}
		else
		{
			m_pLast->m_pNext = pNewNode;
		}
		m_pLast = pNewNode;
		++m_iSize;
		return m_iSize;
	}

	int TList::PushFront(IListItem* psz)
	{
		TListNode* pNewNode = new TListNode;
		pNewNode->pListItem = psz->Clone();
		pNewNode->m_pNext = m_pFirst;
		m_pFirst = pNewNode;

		if (m_pLast == nullptr)
		{
			m_pLast = pNewNode;
		}

		++m_iSize;
		return m_iSize;
	}

	IListItem* TList::First()
	{
		m_pIter = m_pFirst;
		if (m_pIter)
		{
			return m_pIter->pListItem;
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
			return m_pIter->pListItem;
		}
		return nullptr;
	}

	// El puntero que devuelve Pop es válido hasta la siguiente llamada a Pop o hasta destruir la lista o hasta Reset.
	IListItem* TList::Pop()
	{
		if (m_pFirst == nullptr)
		{
			m_pLast = nullptr;
			return nullptr;
		}

		TListNode* pRemoved = m_pFirst;
		m_pFirst = pRemoved->m_pNext;
		--m_iSize;
		if (m_pFirst == nullptr)
		{
			m_pLast = nullptr; // La lista se ha vaciado: la cola ya no existe
		}
		if (m_pIter == pRemoved)
		{
			m_pIter = nullptr;
		}
		IListItem* pRet = pRemoved->pListItem; // Se tiene que guardar antes de que se elimine el nodo para poder
		// liberar la memoria correctamente porque si no se pierde el puntero y hay memory leak
		delete pRemoved;
		return pRet;
	}

	void TList::Reset()
	{
		TListNode* pTmp(m_pFirst);
		while (pTmp)
		{
			TListNode* pToDelete(pTmp);
			pTmp = pTmp->m_pNext;
			delete pToDelete->pListItem; // <-- Aquí se hace el delete de IListItem
			delete pToDelete;
		}
		m_pFirst = nullptr;
		m_pLast = nullptr;
		m_iSize = 0;
		m_pIter = nullptr;
		/*
		delete m_pFirst;
		m_pFirst = nullptr; // Más elegante pero más peligroso
		*/
	}
	TList::TListNode::TListNode(IListItem* _iListItem)
	{
			pListItem = _iListItem;
	}
	TList::TListNode::~TListNode()
	{
		//if (pListItem)
		//{
		//	delete pListItem;
		//	pListItem = nullptr;
		//}
		/*if (m_pNext)
		{
			delete m_pNext;
			m_pNext = nullptr;
		}*/
	}
}