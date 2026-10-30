#pragma once

template < class T >
class ISingleton
{
  static T *m_singleton;

public:
  inline static bool HasInstance()
  {
    return m_singleton != nullptr;
  }

  inline static T &GetInstance() 
  {
    CreateSingleton();
    return *m_singleton; 
  }

  static void DestroySingleton() 
  { 
    if (m_singleton) 
    {
      delete m_singleton;
      m_singleton = nullptr; 
    }
  }

  static T &CreateSingleton()
  {
    if ( !m_singleton )
    {
      m_singleton = new T();
    }
    return *m_singleton; 
  }
};

//Singleton 
template < class T >
T *ISingleton<T>::m_singleton = nullptr;

