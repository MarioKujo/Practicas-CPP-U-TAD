#pragma once

#include "Tank.h"

class CRandTank : public CTank
{
public:
  CRandTank(int _iX, int _iY, int _iColor);

  virtual void Update() override;
};
