#include "TList09.h"
#include <cstring>
#include <cstdio>
namespace Practica09
{
	TList::TList()
		: m_pFirst(nullptr)
		, m_pIter(nullptr)
		, m_pLast(nullptr)
		, m_pLastPopped(nullptr)
		, m_iSize(0)
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
			m_pLast->m_pNext = pNewNode; // Se agrega a la derecha (el siguiente del último)
		}
		m_pLast = pNewNode; // El último ahora es el recién agregado
		++m_iSize; // Aumenta el tamaño en 1
		return m_iSize;
	}

	const char* TList::First()
	{
		m_pIter = m_pFirst;
		if (m_pIter)
		{
			return m_pIter->m_sCadena; // Creo que no hace falta decir nada
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
			return m_pIter->m_sCadena; // Creo que no hace falta decir nada
		}
		return nullptr;
	}

	// El puntero que devuelve Pop es válido hasta la siguiente llamada a Pop o hasta Reset.
	const char* TList::Pop()
	{
		if (m_pFirst == nullptr)
		{
			m_pLast = nullptr;
			return nullptr; // No hay lista
		}

		delete[]m_pLastPopped; // Antes de nada, porsiaca, se libera la memoria de pLastPopped
		m_pLastPopped = nullptr;

		TListNode* pRemoved = m_pFirst; // El que va a ser eliminado es el primero
		m_pFirst = pRemoved->m_pNext; // El primero se mueve uno a la derecha (si se elimina la posición 1, la posición
		// 2 pasa a ser la 1)
		--m_iSize; // Se resta 1 al tamaño
		if (m_pFirst == nullptr)
		{
			m_pLast = nullptr; // La lista se ha vaciado: la cola ya no existe
		}
		if (m_pIter == pRemoved) // Si el iterador está sobre el nodo eliminado, lo libera por completo antes de
			// olvidarse de él
		{
			m_pIter = nullptr;
		}

		m_pLastPopped = pRemoved->m_sCadena; // Se guarda la dirección de la cadena antes de ser eliminada
		pRemoved->m_sCadena = nullptr; // Primero la cadena se vuelve nullptr (antes de eliminar el nodo, si no hay
		// basura en memoria)
		delete pRemoved; // Ahora sí se elimina el nodo (pero el puntero a la cadena sigue existiendo por ahí)

		return m_pLastPopped;
	}

	void TList::Reset()
	{
		TListNode* pTmp(m_pFirst); // Constructor de copia para apuntar al primer elemento
		while (pTmp)
		{
			TListNode* pToDelete(pTmp);
			pTmp = pTmp->m_pNext;
			delete pToDelete; // Mientras que hayan elementos, pToDelete guarda el nodo x, pTmp pasa a x + 1 y pToDelete
			// libera x, a la siguiente pasada pToDelete guarda x + 1, pTmp pasa a apuntar a x + 2, y así borra todos
			// hasta que no haya ninguno
		}
		m_pFirst = nullptr;
		m_pLast = nullptr;
		m_iSize = 0;
		m_pIter = nullptr;

		delete[] m_pLastPopped; // IMPORTANTE NO OLVIDARSE DE QUE ESTABA COLGANDO M_SCADENA
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