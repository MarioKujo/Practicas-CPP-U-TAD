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
			Push(p->pListItem);
		}
	}

	TList& TList::operator=(const TList& other)
	{
		if (this != &other)
		{
			Reset();
			for (const TListNode* p = other.m_pFirst; p != nullptr; p = p->m_pNext)
			{
				Push(p->pListItem);
			}
		}
		return *this;
	}

	TList GetReverseList(TList lstSrc)
	{
		TList reversed;
		for (const TList::TListNode* p = lstSrc.m_pFirst; p != nullptr; p = p->m_pNext)
		{
			reversed.PushFront(p->pListItem);
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
		pNewNode->pListItem = psz->Clone();
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
		IListItem* pRet = pRemoved->pListItem;
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
			delete pToDelete->pListItem;
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