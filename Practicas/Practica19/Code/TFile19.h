/*
1 Implementar una lista con la misma funcionalidad que TList, pero que pueda almacenar cualquier tipo de elementos
mediante templates.
*/
#pragma once
namespace Practica19
{
    class TListNode
    {
    public:
        TListNode(const char* _sText = nullptr);
        TListNode(const TListNode&) = delete;
        ~TListNode();
        const char* m_sCadena = nullptr;
        TListNode* m_pNext = nullptr;
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
        int Push(const char* psz);

        int PushFront(const char* psz);

        // Retorna el primer elemento de la lista, o nullptr si está vacía.
        // Además, deja la lista preparada para que Next() devuelva el segundo.
        const char* First();

        // Retorna el elemento siguiente al último devuelto por First() o Next().
        // Retorna nullptr cuando ya no quedan más elementos (o si no se ha llamado a First()).
        const char* Next();

        // Quita el primer elemento de la lista y lo retorna.
        // Retorna nullptr si la lista está vacía.
        const char* Pop();

        // Elimina todos los elementos. La lista queda vacía (Size() == 0) y se puede seguir usando.
        void Reset();

    private:
        // TODO: los miembros privados los decidís vosotros.
        TListNode* m_pFirst = nullptr;

        TListNode* m_pIter = nullptr;

        const char* m_pLastPopped = nullptr;

        TListNode* m_pLast = nullptr;
        unsigned int m_iSize = 0;
        friend TList GetReverseList(TList lstSrc);

    };

    // 2 Realizar una función que reciba una lista y retorne otra con los elementos invertidos: TList GetReverseList
    // TList lstSrc);
    TList GetReverseList(TList lstSrc);
}