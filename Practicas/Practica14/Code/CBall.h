#pragma once
#include "CEntityVirtual.h"
#include <iostream>
class CBall : public CEntityVirtual
{
public:
    CBall(int x, int y, int dx = 0, int dy = 0) : CEntityVirtual(x, y, dx, dy, 1, 1) {}

    void Move() override;

    void Draw() override;
};
