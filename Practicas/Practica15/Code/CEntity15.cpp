#include "CEntity15.h"
#include <cstdio>
namespace Practica15
{
	CEntity::CEntity(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida)
		: m_pszNombre(_pszNombre)
		, m_iX(_iX)
		, m_iY(_iY)
		, m_uVida(_uVida)
	{
	}

	CEntity::~CEntity()
	{
	}

	// Como Move sustituye la posición, las hijas pasan "m_iX + 1" o "m_iX - 1" para avanzar o retroceder
	void CEntity::Move(int _iNuevaX, int _iNuevaY)
	{
		m_iX = _iNuevaX;
		m_iY = _iNuevaY;
	}

	void CEntity::TakeDamage(int _iDamage)
	{
		// m_uVida es unsigned: restar de más no daría negativo sino un número enorme. Se comprueba antes
		// para que la vida no baje de 0 (ver práctica 13)
		if (static_cast<unsigned int>(_iDamage) >= m_uVida)
		{
			m_uVida = 0;
		}
		else
		{
			m_uVida -= _iDamage;
		}
	}

	bool CEntity::IsAlive() const
	{
		bool bVivo = m_uVida > 0;
		printf("%s %s vivo\n", m_pszNombre, bVivo ? "sigue" : "no sigue");
		return bVivo;
	}
}