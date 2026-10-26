// ***************************************************************************************
// TList.h - Práctica 9: lista enlazada de cadenas
//
// La interfaz pública está fijada: no cambiéis los nombres ni los parámetros, porque las
// prácticas 10, 11, 16 y 19 parten de ella.
// La parte privada (cómo se guardan los elementos) la decidís vosotros.
//
// Ejemplo de uso:
//
//     TList lista;
//     lista.Push("uno");
//     lista.Push("dos");
//     lista.Push("tres");                    // lista: uno, dos, tres  -> Size() == 3
//
//     for (const char* p = lista.First(); p != nullptr; p = lista.Next())
//         printf("%s\n", p);                 // uno, dos, tres
//
//     const char* pPrimero = lista.Pop();    // "uno"  -> lista: dos, tres
//     lista.Reset();                         // lista vacía -> Size() == 0
// ***************************************************************************************
#pragma once
namespace Practica09
{

    class TList
    {
    public:
        // Crea una lista vacía.
        TList();

        // Libera toda la memoria que haya reservado la lista.
        ~TList();

        // Número de elementos de la lista (0 si está vacía).
        int Size();

        // Añade la cadena AL FINAL de la lista.
        // Retorna el número de elementos que tiene la lista después de añadirla.
        int Push(const char* psz);

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
        // Una lista enlazada es una cadena de "nodos": cada nodo guarda una cadena y la dirección del
        // siguiente nodo. El último apunta a nullptr. Así la lista crece sin tener que reservar un array grande.
        //
        //   m_pFirst ──► [ "uno" | ●──]──► [ "dos" | ●──]──► [ "tres" | nullptr ] ◄── m_pLast
        class TListNode // Clase anidada: vive dentro de TList y solo se puede usar desde ella
        {
        public:
            TListNode(const char* _pszText); // Hace una COPIA propia de la cadena
            ~TListNode(); // Libera esa copia
            const char* m_pszCadena = nullptr; // La copia de la cadena (el nodo es su dueño)
            TListNode* m_pNext = nullptr; // Siguiente nodo (nullptr si es el último)
        };

        TListNode* m_pFirst = nullptr; // Primer nodo de la lista
        TListNode* m_pIter = nullptr; // Nodo por el que va el recorrido de First()/Next()
        TListNode* m_pLast = nullptr; // Último nodo: así Push añade al final sin recorrer toda la lista

        // Pop saca la cadena del nodo y borra el nodo, pero la cadena tiene que seguir viva para que el
        // llamador la lea. Se guarda aquí, y se libera en el siguiente Pop o en Reset
        const char* m_pszLastPopped = nullptr;

        unsigned int m_uSize = 0; // Número de elementos

    };
}