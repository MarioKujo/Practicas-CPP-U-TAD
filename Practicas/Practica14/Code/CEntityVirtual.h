#pragma once
#include <iostream>

// Convención de nombres: m_ = atributo de la clase, _ = parámetro que llega de fuera, i = int.
// Así _iX (parámetro) y m_iX (atributo) no se confunden.

// Es la TEntity de la práctica 4, pero con funciones virtuales en vez de la tabla m_funcs[] de punteros a función
// (el propio enunciado de la práctica 4 ya lo anunciaba). Los campos son los mismos
class CEntityVirtual
{
public:
  int m_iX, m_iY;
  int m_iDX, m_iDY;
  int m_iWidth, m_iHeight;

  CEntityVirtual(int _iX, int _iY, int _iDX = 0, int _iDY = 0, int _iWidth = 1, int _iHeight = 1)
    : m_iX(_iX)
    , m_iY(_iY)
    , m_iDX(_iDX)
    , m_iDY(_iDY)
    , m_iWidth(_iWidth)
    , m_iHeight(_iHeight)
  {
    // Move(); // Pregunta 3: descomentar para probar una llamada virtual desde el constructor
  }

  // virtual: al hacer delete a través de un puntero a la base (CEntityVirtual*), se ejecuta primero el
  // destructor de la clase hija y después este. Sin virtual, solo se ejecutaría este
  virtual ~CEntityVirtual()
  {
    // Move(); // Pregunta 3: descomentar para probar una llamada virtual desde el destructor
  }

  // "= 0" las hace virtuales PURAS: no tienen cuerpo y cada hija está obligada a escribir el suyo.
  // Una clase con alguna función pura es abstracta: no se pueden crear objetos de ella, solo de sus hijas
  virtual void Move() = 0;
  virtual void Draw() const = 0;
};