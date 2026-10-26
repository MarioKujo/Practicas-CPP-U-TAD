#pragma once
#include <iostream>
// Convención de nombres: m_ = atributo de la clase, _ = parámetro que llega de fuera,
// i = int. Así _iX (parámetro) y m_iX (atributo) no se confunden.
class CEntityVirtual
{
public:
    int m_iX, m_iY;         // posición
    int m_iDX, m_iDY;       // dirección de movimiento (-1, 0 o 1)
    int m_iWidth, m_iHeight;

    CEntityVirtual(int _iX, int _iY, int _iDX = 0, int _iDY = 0, int _iWidth = 1, int _iHeight = 1)
    {
        //Move(); // Pregunta 3: descomentar para probar a llamar a una virtual desde el constructor
        m_iX = _iX;   m_iY = _iY;
        m_iDX = _iDX; m_iDY = _iDY;
        m_iWidth = _iWidth;
        m_iHeight = _iHeight;
    }

    // Destructor virtual: así, si hacemos delete a través de un puntero a la base,
    // también se ejecuta el destructor de la clase hija y se destruye todo bien.
    virtual ~CEntityVirtual()
    {
        //Move(); // Pregunta 3: descomentar para probar a llamar a una virtual desde el destructor
    }

    // Funciones virtuales (sustituyen a la tabla m_funcs[] de punteros a función).
    // "= 0" las hace virtuales puras: no tienen cuerpo, las hijas están obligadas a implementarlas
    // y por eso no se pueden crear objetos de CEntityVirtual directamente (es una clase abstracta).
    virtual void Move() = 0;
    virtual void Draw() = 0;
};