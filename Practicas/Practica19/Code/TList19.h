/*
1 Implementar una lista con la misma funcionalidad que TList, pero que pueda almacenar cualquier tipo de elementos
mediante templates.
*/
#pragma once
namespace Practica19
{
    template <typename T> class TList;
    template <typename T> TList<T> GetReverseList(TList<T>& lstSrc);

    template<typename T>
    class TList
    {
    public:

        TList() = default;

        TList(const TList& other)
        {
            CopyFrom(other);
        }
        TList& operator=(const TList& other)
        {
            if (this != &other)
            {
                Reset();
                CopyFrom(other);
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

        int Push(const T& item)
        {
            TListNode* pNew = new TListNode(item);
            if (m_pFirst == nullptr)
            {
                m_pFirst = pNew;
            }
            else
            {
                m_pLast->m_pNext = pNew;
            }
            m_pLast = pNew;
            return ++m_iSize;
        }

        int PushFront(const T& item)
        {
            TListNode* pNew = new TListNode(item);
            pNew->m_pNext = m_pFirst;
            m_pFirst = pNew;
            if (m_pLast == nullptr)
            {
                m_pLast = pNew;
            }
            return ++m_iSize;
        }

        T* First()
        {
            m_pIter = m_pFirst;
            return m_pIter ? &m_pIter->m_data : nullptr;
        }

        T* Next()
        {
            if (m_pIter)
            {
                m_pIter = m_pIter->m_pNext;
            }
            return m_pIter ? &m_pIter->m_data : nullptr;
        }

        bool Pop(T& out_)
        {
            if (m_pFirst == nullptr)
            {
                return false;
            }
            TListNode* pRemoved = m_pFirst;
            out_ = pRemoved->m_data;
            m_pFirst = pRemoved->m_pNext;
            if (m_pFirst == nullptr)
            {
                m_pLast = nullptr;
            }
            if (m_pIter == pRemoved)
            {
                m_pIter = nullptr;
            }
            --m_iSize;
            delete pRemoved;
            return true;
        }

        void Reset()
        {
            while (m_pFirst)
            {
                TListNode* pNext = m_pFirst->m_pNext;
                delete m_pFirst;
                m_pFirst = pNext;
            }
            m_pLast = nullptr;
            m_pIter = nullptr;
            m_iSize = 0;
        }

    private:
        class TListNode
        {
        public:
            explicit TListNode(const T& data) : m_data(data) {}
            TListNode(const TListNode&) = delete;
            T m_data;
            TListNode* m_pNext = nullptr;
        };

        void CopyFrom(const TList& other)
        {
            for (const TListNode* p = other.m_pFirst; p != nullptr; p = p->m_pNext)
            {
                Push(p->m_data);
            }
        }

        TListNode* m_pFirst = nullptr;
        TListNode* m_pIter = nullptr;
        TListNode* m_pLast = nullptr;
        int m_iSize = 0;

        friend TList GetReverseList<T>(TList& lstSrc);

    };

    template<typename T>
    TList<T> GetReverseList(TList<T>& lstSrc)
    {
        TList<T> reversed;
        for (const typename TList<T>::TListNode* p = lstSrc.m_pFirst;p != nullptr; p = p->m_pNext)
        {
            reversed.PushFront(p->m_data);
        }
        return reversed;
    }
}