#pragma once
#include "CEntityVirtual.h"
#include <iostream>
class CBall : public CEntityVirtual
{
public:
    // Después de los ":" llamamos al constructor de la clase base (ancho y alto fijos a 1)
    CBall(int _iX, int _iY, int _iDX = 0, int _iDY = 0) : CEntityVirtual(_iX, _iY, _iDX, _iDY, 1, 1) {}

    // override: indica que sustituye a la función virtual de la base (si la firma no coincide, el compilador avisa)
    void Move() override;

    void Draw() override;
};