#include "TList11.h"
#include <cstring>
#include <cstdio>

// Si tienes dudas de cómo funciona algo, lee los comentarios de la práctica 9

namespace Practica11
{
	TList::TList()
	{

	}

	TList::TList(const TList& other)
	{
		printf("Constructor de copia de TList\n");
		for (const TListNode* p = other.m_pFirst; p != nullptr; p = p->m_pNext)
		{
			Push(p->m_sCadena); // Hace push a la lista vacía por cada nodo que tiene la otra lista de la que se copia.
		}
	}

	TList& TList::operator=(const TList& other)
	{
		if (this != &other) // Si no es él mismo (porque sería una gilipollez lista1 = lista1)
		{
			Reset(); // En esto se diferencia con el constructor de copia, que el objeto ya está creado. El resto es
			// igual
			for (const TListNode* p = other.m_pFirst; p != nullptr; p = p->m_pNext)
			{
				Push(p->m_sCadena);
			}
		}
		return *this;
	}

	TList GetReverseList(TList lstSrc)
	{
		TList reversed;
		for (const TList::TListNode* p = lstSrc.m_pFirst; p != nullptr; p = p->m_pNext)
		{
			reversed.PushFront(p->m_sCadena);
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
	// Nueva función que me he tenido que inventar para invertir la cadena: un push que mete los nuevos nodos hacia la
	// izquierda
	int TList::PushFront(const char* psz) 
	{
		TListNode* pNewNode = new TListNode(psz);

		pNewNode->m_pNext = m_pFirst; // Esto hace que por ejemplo m_pNext sea la posición 2 y pNewNode sea la 1)
		m_pFirst = pNewNode; // El primero se mueve hacia la izquierda (PushFront(3);PushFront(2);PushFront(1); quedaría
		// 1, 2, 3)

		if (m_pLast == nullptr)
		{
			m_pLast = pNewNode; // Este solo se cambia con el primer nodo que entra (la última posición no se mueve)
		}

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
	TList::TListNode::TListNode(const char* _sText)
	{
		if (_sText)
		{
			unsigned int uLen(static_cast<unsigned int>(strlen(_sText)));
			char* pCopy = new char[uLen + 1];
			strcpy_s(pCopy, uLen + 1, _sText);
			m_sCadena = pCopy;
		}
	}
	TList::TListNode::~TListNode()
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
}