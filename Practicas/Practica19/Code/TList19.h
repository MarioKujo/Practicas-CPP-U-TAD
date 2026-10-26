/*
Implementar una lista con la misma funcionalidad que TList, pero que pueda almacenar cualquier tipo de
elementos mediante templates.

Un template es una "receta" con huecos para tipos: T es el hueco, y al escribir TList<int> o TList<float>
el compilador genera una clase completa con T sustituido. Por eso TODO el código va en el .h y no hay .cpp:
el compilador necesita ver la implementación entera en el momento de generar cada versión.
*/
#pragma once
namespace Practica19
{
	// Declaraciones adelantadas: avisan de que estas plantillas existen, porque el "friend" de más abajo
	// necesita nombrarlas antes de que estén definidas.
	template <typename T> class TList;
	template <typename T> TList<T> GetReverseList(TList<T>& _lstSrc);

	template<typename T>
	class TList
	{
	public:
		TList() = default; // Usa los valores por defecto de los atributos (punteros a nullptr, tamaño a 0)

		TList(const TList& _lstOther)
		{
			CopyFrom(_lstOther);
		}

		TList& operator=(const TList& _lstOther)
		{
			if (this != &_lstOther) // Evita borrar la lista al asignarla a sí misma
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

		int Size() const
		{
			return m_iSize;
		}

		// Añade una copia del elemento al final. Retorna el nº de elementos tras añadirlo.
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
			return ++m_iSize;
		}

		// Igual, pero al principio
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

		// Retorna un puntero al primer elemento (o nullptr si está vacía) y deja preparado el recorrido.
		// Devuelve la dirección del dato DENTRO de la lista, así que se puede modificar desde fuera.
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

		// Quita el primer elemento y lo copia en _outData (parámetro de salida: por ser referencia, escribe en la
		// variable original). Retorna false si la lista estaba vacía. Como la lista guarda copias y no punteros,
		// aquí no hay que hacer delete de nada fuera.
		bool Pop(T& _outData)
		{
			if (m_pFirst == nullptr)
			{
				return false;
			}
			TListNode* pRemovedNode = m_pFirst;
			_outData = pRemovedNode->m_data;
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
			delete pRemovedNode;
			return true;
		}

		void Reset()
		{
			while (m_pFirst)
			{
				TListNode* pNextNode = m_pFirst->m_pNext; // Guardamos el siguiente antes de borrar, si no lo perderíamos
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
			// explicit: impide que un T se convierta en nodo "a escondidas"
			explicit TListNode(const T& _data) : m_data(_data) {}
			// "= delete": prohíbe copiar un nodo; copiarlo rompería los enlaces de la lista
			TListNode(const TListNode&) = delete;
			T m_data; // Sin prefijo de tipo, porque no sabemos qué será T (int, float, SPunto...)
			TListNode* m_pNext = nullptr;
		};

		// Función auxiliar compartida por el constructor de copia y operator=
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

		// friend: esta función externa puede acceder a los miembros privados. El <T> indica que solo es amiga
		// la versión generada para el mismo T que esta lista.
		friend TList GetReverseList<T>(TList& _lstSrc);
	};

	// Retorna una lista nueva con los elementos de _lstSrc en orden inverso
	template<typename T>
	TList<T> GetReverseList(TList<T>& _lstSrc)
	{
		TList<T> lstReversed;
		// typename: dentro de una plantilla el compilador no sabe todavía si TListNode es un tipo o un valor
		// (depende de T), así que hay que decírselo.
		for (const typename TList<T>::TListNode* pNode = _lstSrc.m_pFirst; pNode != nullptr; pNode = pNode->m_pNext)
		{
			lstReversed.PushFront(pNode->m_data);
		}
		return lstReversed;
	}
}