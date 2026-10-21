#pragma once
#include <iostream>
class CEntityVirtual
{
public:
    int m_ix, m_iy;    // posición
    int m_idx, m_idy;   // dirección de movimiento (-1, 0 o 1)
    int m_iWidth, m_iHeight;

    CEntityVirtual(int x, int y, int dx = 0, int dy = 0, int width = 1, int height = 1)
    {
        //Move();
        m_ix = x;   m_iy = y;
        m_idx = dx; m_idy = dy;
        m_iWidth = width;
        m_iHeight = height;
    }

    // Destructor virtual para asegurar que se destruyen bien las clases derivadas
    virtual ~CEntityVirtual()
    {
        //Move();
    }

    // Funciones virtuales (sustituyen a la tabla m_funcs[] de punteros a función)
    virtual void Move() = 0;
    virtual void Draw() = 0;
};
