#include "CEnemy13.h"
#include <cstdio>

namespace Practica13
{
	// Primero se construye la parte CEntity (se llama a su constructor en la lista de inicialización)
	// y después el miembro propio, m_iDamage. Por eso el printf de CEntity sale antes que el de CEnemy
	CEnemy::CEnemy(const char* _pszNombre, int _iX, int _iY, int _iDamage, unsigned int _uVida)
		: CEntity(_pszNombre, _iX, _iY, _uVida)
		, m_iDamage(_iDamage)
	{
		printf("Constructor de CEnemy\n");
	}

	CEnemy::~CEnemy()
	{
		printf("Destructor de CEnemy\n"); // Al destruir pasa al revés: sale este y después el de CEntity
	}

	void CEnemy::Attack(CEntity& _oObjetivo) const
	{
		// _oObjetivo es otro nombre para el objeto original (un CPlayer u otro CEnemy), sin copiarlo.
		// No se puede tocar _oObjetivo.m_uVida directamente: una clase hija solo accede a los miembros
		// protected de sí misma, no a los de otro objeto declarado como CEntity. Por eso se llama a TakeDamage()
		_oObjetivo.TakeDamage(m_iDamage);
		printf("%s ha hecho %d de damage.\n", m_pszNombre, m_iDamage);
	}
}