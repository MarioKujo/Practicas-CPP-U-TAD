#include "CEntity13.h"
#include <cstdio>
namespace Practica13
{
	// Lo que va después de ":" es la lista de inicialización: da valor a los miembros en el momento
	// de crear el objeto, antes de ejecutar el cuerpo del constructor
	CEntity::CEntity(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida)
		: m_pszNombre(_pszNombre)
		, m_iX(_iX)
		, m_iY(_iY)
		, m_uVida(_uVida)
	{
		printf("Constructor de CEntity\n");
	}

	CEntity::~CEntity()
	{
		printf("Destructor de CEntity\n");
	}

	void CEntity::Move(int _iNuevaX, int _iNuevaY)
	{
		m_iX = _iNuevaX;
		m_iY = _iNuevaY;
		printf("%s se ha movido a (%d, %d)\n", m_pszNombre, m_iX, m_iY); // %s = texto, %d = entero
	}

	void CEntity::TakeDamage(int _iDamage)
	{
		printf("%s ha recibido %d de damage.\n", m_pszNombre, _iDamage);
		// m_uVida es unsigned: si se restara más de lo que hay, no saldría un negativo sino un número
		// enorme (0 - 1 = 4.294.967.295). Por eso se comprueba antes, para que la vida no baje de 0
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

		printf("%s %s vivo\n", m_pszNombre, bVivo ? "sigue" : "no sigue"); // ?: elige entre los dos textos
		return bVivo;
	}

	void CEntity::Print() const
	{
		printf("%s en (%d, %d) con %u de vida\n", m_pszNombre, m_iX, m_iY, m_uVida); // %u = entero sin signo
	}
}