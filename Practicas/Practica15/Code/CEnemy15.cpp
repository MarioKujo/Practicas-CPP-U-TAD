#include "CEnemy15.h"
namespace Practica15
{
	CEnemy::CEnemy(const char* _nombre, int _iX, int _iY, int _iDamage, unsigned int _uVida) :CEntity(_nombre, _iX, _iY, _uVida), iDamage(_iDamage)
	{
	}

	CEnemy::~CEnemy()
	{
	}

	void CEnemy::SetTarget(CEntity* other)
	{
		target = other;
	}

	void CEnemy::Update()
	{
		Move(iX - 1, 0);
		Attack(*target);
	}

	void CEnemy::Print() const
	{
		printf("%s en (%d, %d) con %u de vida, damage %d\n", nombre, iX, iY, uVida, iDamage);
	}

	void CEnemy::Attack(CEntity& other)
	{
		other.TakeDamage(iDamage);
	}
}