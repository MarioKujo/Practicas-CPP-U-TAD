#include "TList09.h"
#include <cstring>
#include <cstdio>

// Lo nuevo respecto a otras prácticas: "TList::" delante del nombre indica que es un método de TList,
// y "TList::TListNode::" que es de la clase anidada TListNode.
namespace Practica09
{
	TList::TList()
		: m_pFirst(nullptr)
		, m_pIter(nullptr)
		, m_pLast(nullptr)
		, m_pszLastPopped(nullptr)
		, m_uSize(0)
	{
	}

	TList::~TList()
	{
		Reset(); // Libera todos los nodos y la última cadena de Pop
	}

	int TList::Size()
	{
		return m_uSize;
	}

	int TList::Push(const char* psz)
	{
		TListNode* pNewNode = new TListNode(psz);

		if (m_pFirst == nullptr)
		{
			m_pFirst = pNewNode; // Lista vacía: el nuevo nodo es también el primero
		}
		else
		{
			m_pLast->m_pNext = pNewNode; // El que era último ahora apunta al nuevo
		}
		m_pLast = pNewNode; // El último ahora es el recién añadido
		++m_uSize;
		return m_uSize;
	}

	const char* TList::First()
	{
		m_pIter = m_pFirst; // El recorrido empieza en el primer nodo
		if (m_pIter)
		{
			return m_pIter->m_pszCadena;
		}
		return nullptr; // Lista vacía
	}

	const char* TList::Next()
	{
		if (m_pIter == nullptr) // Nunca se llamó a First(), o ya se acabó la lista
		{
			return nullptr;
		}
		m_pIter = m_pIter->m_pNext; // Avanza un nodo
		return m_pIter ? m_pIter->m_pszCadena : nullptr; // Si era el último, m_pIter ahora es nullptr
	}

	// El puntero que devuelve Pop es válido hasta la siguiente llamada a Pop o hasta Reset.
	const char* TList::Pop()
	{
		if (m_pFirst == nullptr)
		{
			m_pLast = nullptr;
			return nullptr; // No hay nada que sacar
		}

		// La cadena del Pop anterior ya no se necesita (por eso el puntero solo vale hasta el siguiente Pop)
		delete[] m_pszLastPopped;
		m_pszLastPopped = nullptr;

		TListNode* pRemoved = m_pFirst; // El que se va a quitar es el primero
		m_pFirst = pRemoved->m_pNext; // El segundo pasa a ser el primero
		--m_uSize;
		if (m_pFirst == nullptr)
		{
			m_pLast = nullptr; // La lista se ha vaciado: ya no hay último
		}
		if (m_pIter == pRemoved) // Si el recorrido estaba sobre este nodo, se invalida para no apuntar a un nodo borrado
		{
			m_pIter = nullptr;
		}

		// "Robamos" la cadena del nodo y dejamos su puntero a nullptr. Si no, el destructor del nodo la liberaría
		// (delete[]) y devolveríamos una dirección que ya no es válida
		m_pszLastPopped = pRemoved->m_pszCadena;
		pRemoved->m_pszCadena = nullptr;
		delete pRemoved; // Se borra solo el nodo; la cadena sigue viva en m_pszLastPopped

		return m_pszLastPopped;
	}

	void TList::Reset()
	{
		TListNode* pTmp = m_pFirst;
		while (pTmp)
		{
			// Se guarda el nodo actual para borrarlo, y antes de borrarlo se avanza al siguiente.
			// Si no, al borrar el nodo se perdería la dirección del siguiente
			TListNode* pToDelete = pTmp;
			pTmp = pTmp->m_pNext;
			delete pToDelete;
		}
		m_pFirst = nullptr;
		m_pLast = nullptr;
		m_uSize = 0;
		m_pIter = nullptr;

		delete[] m_pszLastPopped; // También hay que liberar la última cadena que sacó Pop
		m_pszLastPopped = nullptr;
	}

	// Cada nodo hace su propia copia de la cadena: así no depende de que el original siga existiendo
	TList::TListNode::TListNode(const char* _pszText)
	{
		if (_pszText)
		{
			unsigned int uLen = static_cast<unsigned int>(strlen(_pszText));
			char* pcCopia = new char[uLen + 1]; // +1 para el '\0'
			strcpy_s(pcCopia, uLen + 1, _pszText);
			m_pszCadena = pcCopia;
		}
	}

	// Solo libera SU cadena. No borra el nodo siguiente: de recorrer la lista se encarga TList::Reset
	TList::TListNode::~TListNode()
	{
		if (m_pszCadena)
		{
			delete[] m_pszCadena;
			m_pszCadena = nullptr;
		}
	}
}