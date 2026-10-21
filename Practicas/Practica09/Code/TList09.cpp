#include "TList09.h"
#include <cstring>
#include <cstdio>

TList::TList()
{
}

TList::~TList()
{
	Reset();
}

int TList::Size()
{
	return m_iSize;
}

int TList::Push(const char* psz)
{
	TListNode* pNewNode = new TListNode(psz);

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

const char* TList::First()
{
	m_pIter = m_pFirst;
	if (m_pIter)
	{
		return m_pIter->m_sCadena;
	}
	return nullptr;
}

const char* TList::Next()
{
	if (m_pIter)
	{
		m_pIter = m_pIter->m_pNext;
	}
	if (m_pIter)
	{
		return m_pIter->m_sCadena;
	}
	return nullptr;
}

// El puntero que devuelve Pop es válido hasta la siguiente llamada a Pop o hasta destruir la lista o hasta Reset.
const char* TList::Pop()
{
	if (m_pFirst == nullptr)
	{
		m_pLast = nullptr;
		return nullptr;
	}

	delete[]m_pLastPopped;
	m_pLastPopped = nullptr;

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

	m_pLastPopped = pRemoved->m_sCadena;
	pRemoved->m_sCadena = nullptr;
	delete pRemoved;

	return m_pLastPopped;
}

void TList::Reset()
{
	TListNode* pTmp(m_pFirst);
	while (pTmp)
	{
		TListNode* pToDelete(pTmp);
		pTmp = pTmp->m_pNext;
		delete pToDelete;
	}
	m_pFirst = nullptr;
	m_pLast = nullptr;
	m_iSize = 0;
	m_pIter = nullptr;

	delete[] m_pLastPopped;
	m_pLastPopped = nullptr;
	/*
	delete m_pFirst;
	m_pFirst = nullptr; // Más elegante pero más peligroso
	*/
}
TListNode::TListNode(const char* _sText)
{
	if (_sText)
	{
		unsigned int uLen(static_cast<unsigned int>(strlen(_sText)));
		char*pCopy = new char[uLen + 1];
		strcpy_s(pCopy, uLen + 1, _sText);
		m_sCadena = pCopy;
	}
}
TListNode::~TListNode()
{
	if (m_sCadena)
	{
		delete[] m_sCadena;
		m_sCadena = nullptr;
	}
	/*if (m_pNext)
	{
		delete m_pNext;
		m_pNext = nullptr;
	}*/
}