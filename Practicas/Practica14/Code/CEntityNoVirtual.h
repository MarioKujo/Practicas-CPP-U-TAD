#pragma once
#include <iostream>
class CEntityNoVirtual
{
public:
    int m_iX, m_iY;         // posición
    int m_iDX, m_iDY;       // dirección de movimiento (-1, 0 o 1)
    int m_iWidth, m_iHeight;

    CEntityNoVirtual(int _iX, int _iY, int _iDX = 0, int _iDY = 0, int _iWidth = 1, int _iHeight = 1)
    {
        m_iX = _iX;   m_iY = _iY;
        m_iDX = _iDX; m_iDY = _iDY;
        m_iWidth = _iWidth;
        m_iHeight = _iHeight;
    }

    // Destructor NO virtual a propósito: esta clase solo existe para comparar con la versión virtual.
    // El problema: si borráramos un objeto hijo a través de un puntero a esta clase, solo se ejecutaría
    // este destructor y no el de la hija (se quedaría sin destruir bien).
    ~CEntityNoVirtual() {}

    // Funciones normales (sin virtual): la llamada se decide al compilar
    void Move();
    void Draw();
};