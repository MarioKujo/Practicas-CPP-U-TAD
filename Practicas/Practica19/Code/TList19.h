/*
Implementar una lista con la misma funcionalidad que TList, pero que pueda almacenar cualquier tipo de
elementos mediante templates.
*/

/*
Es la TList de las prácticas 9, 11 y 16. Para lo que no esté comentado aquí (nodos, Push, Pop, Reset...),
lee los comentarios de TList09 y TList11. Lo nuevo es el template.

Un template es una "receta" con huecos para tipos: T es el hueco, y al escribir TList<int> o TList<float>
el compilador genera una clase completa con T sustituido. Por eso TODO el código va en el .h y no hay .cpp:
el compilador necesita ver la implementación entera cuando genera cada versión.
*/
#pragma once
#include <utility>
namespace Practica19
{
	// Declaraciones adelantadas: avisan de que estas plantillas existen, porque el "friend" de más abajo
	// las nombra antes de que estén definidas
	template <typename T> class TList;
	template <typename T> TList<T> GetReverseList(const TList<T>& _lstSrc);

	template<typename T>
	class TList
	{
	public:
		TList() = default; // Usa los valores por defecto de los miembros (punteros a nullptr, tamaño a 0)

		// Regla de tres, igual que en la práctica 11. Los dos copian con la misma función auxiliar
		TList(const TList& _lstOther)
		{
			CopyFrom(_lstOther);
		}

		TList& operator=(const TList& _lstOther)
		{
			if (this != &_lstOther) // Evita borrar la lista antes de copiarla cuando se asigna a sí misma
			{
				Reset();
				CopyFrom(_lstOther);
			}
			return *this;
		}

		~TList()
		{
			Reset();
		}

		int Size() const // const: promete no modificar la lista, solo leerla
		{
			return m_iSize;
		}

		// Igual que en la práctica 16: la lista guarda COPIAS de los elementos (aquí con el constructor de
		// copia de T, ya no hace falta Clone)
		int Push(const T& _item)
		{
			TListNode* pNewNode = new TListNode(_item);
			if (m_pFirst == nullptr)
			{
				m_pFirst = pNewNode;
			}
			else
			{
				m_pLast->m_pNext = pNewNode;
			}
			m_pLast = pNewNode;
			return ++m_iSize; // ++ delante: primero suma y luego devuelve el valor ya sumado
		}

		int PushFront(const T& _item)
		{
			TListNode* pNewNode = new TListNode(_item);
			pNewNode->m_pNext = m_pFirst;
			m_pFirst = pNewNode;
			if (m_pLast == nullptr)
			{
				m_pLast = pNewNode;
			}
			return ++m_iSize;
		}

		// Devuelven la dirección del dato DENTRO de la lista (o nullptr), así que desde fuera se puede
		// modificar: *lstInts.First() = 999;. Dejan de ser válidas si se hace Pop de ese elemento o Reset
		T* First()
		{
			m_pIter = m_pFirst;
			return m_pIter ? &m_pIter->m_data : nullptr; // condición ? si_true : si_false
		}

		T* Next()
		{
			if (m_pIter)
			{
				m_pIter = m_pIter->m_pNext;
			}
			return m_pIter ? &m_pIter->m_data : nullptr;
		}

		/*
		Diferencia con la práctica 9: aquí Pop no devuelve el elemento, lo copia en data_ (parámetro de
		salida: al ser una referencia, escribe en la variable original). Devuelve false si la lista estaba vacía.
		Como la lista guarda copias y no punteros, no hay nada que borrar fuera ni que dure hasta el siguiente Pop
		*/

		bool Pop(T& data_)
		{
			if (m_pFirst == nullptr)
			{
				return false;
			}
			TListNode* pRemovedNode = m_pFirst;
			data_ = pRemovedNode->m_data;
			m_pFirst = pRemovedNode->m_pNext;
			if (m_pFirst == nullptr)
			{
				m_pLast = nullptr;
			}
			if (m_pIter == pRemovedNode)
			{
				m_pIter = nullptr;
			}
			--m_iSize;
			data_ = std::move(pRemovedNode->m_data); // el nodo se borra justo después: se mueve en vez de copiar. #include <utility>
			delete pRemovedNode;
			return true;
		}

		void Reset()
		{
			while (m_pFirst)
			{
				TListNode* pNextNode = m_pFirst->m_pNext; // Se guarda el siguiente antes de borrar, si no se perdería
				delete m_pFirst;
				m_pFirst = pNextNode;
			}
			m_pLast = nullptr;
			m_pIter = nullptr;
			m_iSize = 0;
		}

	private:
		class TListNode
		{
		public:
			// explicit: impide que un T se convierta en nodo "a escondidas" sin escribir TListNode(...)
			explicit TListNode(const T& _data)
				: m_data(_data)
			{
			}
			TListNode(const TListNode&) = delete; // Copiar un nodo suelto rompería los enlaces de la lista
			T m_data; // Sin prefijo de tipo porque no se sabe qué será T (int, float, SPunto...)
			TListNode* m_pNext = nullptr;
			// No hace falta destructor: el de T se ejecuta solo al borrar el nodo (en la práctica 9 sí hacía falta
			// porque la cadena se reservaba con new[])
		};
		TListNode& operator=(const TListNode&) = delete;
		// Función auxiliar que comparten el constructor de copia y operator=
		void CopyFrom(const TList& _lstOther)
		{
			for (const TListNode* pNode = _lstOther.m_pFirst; pNode != nullptr; pNode = pNode->m_pNext)
			{
				Push(pNode->m_data);
			}
		}

		TListNode* m_pFirst = nullptr;
		TListNode* m_pIter = nullptr;
		TListNode* m_pLast = nullptr;
		int m_iSize = 0;

		// friend, como en la práctica 11. El <T> indica que solo es amiga la versión de la función generada
		// para el mismo T que esta lista
		friend TList GetReverseList<T>(const TList& _lstSrc);
	};

	// Retorna una lista nueva con los elementos de _lstSrc en orden inverso. Recibe una referencia, no una copia:
	// es la solución del punto 3 de la práctica 11 (así no se llama al constructor de copia al entrar)
	template<typename T>
	TList<T> GetReverseList(const TList<T>& _lstSrc)
	{
		TList<T> lstReversed;
		// typename: dentro de una plantilla el compilador aún no sabe si TList<T>::TListNode es un tipo o un
		// valor (depende de T), así que hay que decírselo
		for (const typename TList<T>::TListNode* pNode = _lstSrc.m_pFirst; pNode != nullptr; pNode = pNode->m_pNext)
		{
			lstReversed.PushFront(pNode->m_data);
		}
		return lstReversed;
	}
}