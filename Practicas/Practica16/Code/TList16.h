/*
Interfaces: una lista de IListItem

▸ Una lista con la funcionalidad de TList que guarde cualquier objeto que implemente IListItem.
▸ Push recibe un const IListItem& y guarda una copia hecha con Clone(). First, Next y Pop retornan IListItem*; quien
recibe el de Pop lo borra.
▸ Al menos dos clases que implementen la interfaz (un número, un texto...), mezcladas en la misma lista.
▸ Un método Print() de la lista que muestre todos sus elementos.
*/
#pragma once
namespace Practica16
{
	class IListItem
	{
	public:
		virtual ~IListItem() {}
		virtual IListItem* Clone() const = 0; // copia
		virtual void Print() const = 0; // consola
	};

    

    class TList
    {
    public:
        // Crea una lista vacía.
        TList();
        // 1 Realizar un constructor de copia para la lista enlazada de la práctica 9.
        TList(const TList& other);
        TList& operator=(const TList& other);
        // Libera toda la memoria que haya reservado la lista.
        ~TList();

        // Número de elementos de la lista (0 si está vacía).
        int Size();

        // Añade la cadena AL FINAL de la lista.
        // Retorna el número de elementos que tiene la lista después de añadirla.
        int Push(IListItem* psz);

        int PushFront(IListItem* psz);

        // Retorna el primer elemento de la lista, o nullptr si está vacía.
        // Además, deja la lista preparada para que Next() devuelva el segundo.
        IListItem* First();

        // Retorna el elemento siguiente al último devuelto por First() o Next().
        // Retorna nullptr cuando ya no quedan más elementos (o si no se ha llamado a First()).
        IListItem* Next();

        // Quita el primer elemento de la lista y lo retorna.
        // Retorna nullptr si la lista está vacía.
        IListItem* Pop();

        // Elimina todos los elementos. La lista queda vacía (Size() == 0) y se puede seguir usando.
        void Reset();

    private:

        class TListNode
        {
        public:
            TListNode(IListItem* _iListItem = nullptr);
            ~TListNode();
            IListItem* pListItem = nullptr;
            TListNode* m_pNext = nullptr;
        };
        // TODO: los miembros privados los decidís vosotros.
        TListNode* m_pFirst = nullptr;

        TListNode* m_pIter = nullptr;

        TListNode* m_pLast = nullptr;
        unsigned int m_iSize = 0;
        friend TList GetReverseList(TList lstSrc);

    };

    // 2 Realizar una función que reciba una lista y retorne otra con los elementos invertidos: TList GetReverseList
    // TList lstSrc);
    TList GetReverseList(TList lstSrc);
}