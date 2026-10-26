#pragma once
#include "CEntityVirtual.h"
#include <iostream>

// Pelota horizontal de la práctica 4 (MoveHorizontal + DrawBall), ahora como clase hija
class CBall : public CEntityVirtual
{
public:
  // Lo que va después de ":" llama al constructor de la base, fijando ancho y alto a 1
  CBall(int _iX, int _iY, int _iDX = 0, int _iDY = 0)
    : CEntityVirtual(_iX, _iY, _iDX, _iDY, 1, 1)
  {
  }

  // override: indica que sustituye a la función virtual de la base. Si la firma no coincide,
  // el compilador da error en vez de crear una función distinta sin avisar
  virtual void Move() override;
  virtual void Draw()  const override;
};