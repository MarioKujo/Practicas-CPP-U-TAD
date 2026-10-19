#include "TList.h"
#include <cstring>
#include <cstdio>

TList::TList()
{
}

TList::~TList()
{
}

int TList::Size()
{
	if (m_pFirst == nullptr)
	{
		return 0;
	}
	else
	{
		int iSize = 1;
		TListNode* pTmp(m_pFirst);
		while (pTmp->m_pNext)
		{
			pTmp = pTmp->m_pNext;
			iSize++;
		}
		return iSize;
	}
}

int TList::Push(const char* psz)
{
	TListNode* pNewNode = new TListNode(psz);
	pNewNode->m_sCadena = psz;

	if (m_pFirst == nullptr)
	{
		m_pFirst = pNewNode;
	}
	else
	{
		TListNode* pTmp(m_pFirst);
		while (pTmp->m_pNext)
		{
			pTmp = pTmp->m_pNext;
		}
	}
	return 0;
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

const char* TList::Pop()
{
	return nullptr;
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

	/*
	delete m_pFirst;
	m_pFirst = nullptr; // Más elegante pero más peligroso
	*/
}
TListNode::TListNode(const char* _sText)
{
	/*if (_sText)
	{
		unsigned int uLen(strlen(_sText));
		m_sCadena = new char[uLen + 1];
		strcpy_s(m_sCadena, uLen + 1, _sText);
	}*/
}
TListNode::~TListNode()
{
	/*if (m_sCadena)
	{
		delete[]m_sCadena;
		m_sCadena = nullptr;
	}*/
	if (m_pNext)
	{
		delete m_pNext;
		m_pNext = nullptr;
	}
}