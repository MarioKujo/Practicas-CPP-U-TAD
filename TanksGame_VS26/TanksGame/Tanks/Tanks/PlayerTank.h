#pragma once

#include "Tank.h"

class CPlayerTank : public CTank
{
public:
  CPlayerTank(int _iX, int _iY, int _iColor);

  virtual void Update() override;
};
