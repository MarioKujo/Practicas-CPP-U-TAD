#pragma once
#include <iostream>
class CEntityNoVirtual
{
public:
    int m_ix, m_iy;    // posición
    int m_idx, m_idy;   // dirección de movimiento (-1, 0 o 1)
    int m_iWidth, m_iHeight;

    CEntityNoVirtual(int x, int y, int dx = 0, int dy = 0, int width = 1, int height = 1)
    {
        m_ix = x;   m_iy = y;
        m_idx = dx; m_idy = dy;
        m_iWidth = width;
        m_iHeight = height;
    }

    // Destructor
    ~CEntityNoVirtual() {} // Esta clase es solo para esto en específico, el destructor no virtual y los problemas que
    // causa

    // Funciones
    void Move();
    void Draw();
};
