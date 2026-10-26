#pragma once
#include <iostream>

// Copia de CEntityVirtual sin nada virtual. Solo existe para comparar (sizeof, desensamblado)
class CEntityNoVirtual
{
public:
  int m_iX, m_iY;
  int m_iDX, m_iDY;
  int m_iWidth, m_iHeight;

  CEntityNoVirtual(int _iX, int _iY, int _iDX = 0, int _iDY = 0, int _iWidth = 1, int _iHeight = 1)
  {
    m_iX = _iX;   m_iY = _iY;
    m_iDX = _iDX; m_iDY = _iDY;
    m_iWidth = _iWidth;
    m_iHeight = _iHeight;
  }

  // Sin virtual a propósito: si se borrara un objeto hijo a través de un puntero a esta clase, solo se
  // ejecutaría este destructor y el de la hija no (la hija quedaría mal destruida)
  ~CEntityNoVirtual() {}

  // Sin virtual, el compilador decide a qué función llamar al compilar. Aquí solo se declaran (sin cuerpo)
  void Move();
  void Draw() const;
};