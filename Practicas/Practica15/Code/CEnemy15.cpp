#include "CEnemy15.h"
#include <cstdio>
namespace Practica15
{
	CEnemy::CEnemy(const char* _pszNombre, int _iX, int _iY, int _iDamage, unsigned int _uVida)
		: CEntity(_pszNombre, _iX, _iY, _uVida)
		, m_iDamage(_iDamage)
	{
	}

	CEnemy::~CEnemy()
	{
	}

	void CEnemy::SetTarget(CEntity* _pObjetivo)
	{
		m_pObjetivo = _pObjetivo;
	}

	void CEnemy::Update()
	{
		Move(m_iX - 1, m_iY); // Una casilla a la izquierda, en la misma fila
		// m_pObjetivo es una dirección; el * de delante da el objeto al que apunta,
		// que es lo que espera Attack (una referencia a un objeto, no una dirección)
		if (m_pObjetivo != nullptr)
		{
			Attack(*m_pObjetivo);
		}
	}

	void CEnemy::Print() const
	{
		printf("%s en (%d, %d) con %u de vida, damage %d\n", m_pszNombre, m_iX, m_iY, m_uVida, m_iDamage);
	}

	// Ver práctica 13: se llama a TakeDamage y no se toca la vida del objetivo directamente
	void CEnemy::Attack(CEntity& _oObjetivo) const
	{
		_oObjetivo.TakeDamage(m_iDamage);
	}
}