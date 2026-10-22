#include "CTurret.h"
namespace Practica15
{
    CTurret::CTurret(const char* _nombre, int _iX, int _iY, int _iDamage, unsigned int _uVida):CEnemy(_nombre, _iX, _iY, _iDamage, _uVida)
    {
    }

    CTurret::~CTurret()
    {
    }

    void CTurret::Update()
    {
        Attack(*target);
    }
}