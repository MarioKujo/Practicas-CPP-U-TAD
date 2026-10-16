/*
1 Al menos 4 tipos de entidad (la pelota de ejemplo cuenta). Cada tipo: sus funciones + su tabla.

2 Al menos dos tipos comparten la función de pintar, pero se mueven distinto.

3 Varias entidades de cada tipo, creadas con new y guardadas en la tabla entities.

4 Mover y pintar siempre a través de m_funcs: nada de if ni switch según el tipo.

5 No se salen del mundo y, al pulsar ESC, se hace delete de todas antes de salir.
*/
#include <iostream>

struct TEntity;
typedef void (*funcEntity)(TEntity*);
enum EFunc
{
	FUNC_MOVE = 0,
	FUNC_DRAW = 1,
	FUNC_COUNT
};

struct TEntity
{
	int m_ix, m_iy; // Posición
	int m_idx, m_idy; // Dirección
	funcEntity* m_funcs; // Tabla del tipo
};

void MoveHorizontal(TEntity* e)
{
	e->m_ix += e->m_idx;
	if (e->m_ix <= 1 || e->m_ix >= WORLD_WIDTH - 2)
	{
		e->m_idx = -e->m_idx; // Rebota
	}
}

void DrawBall(TEntity* e)
{
	gotoxy(e->m_ix, e->m_iy);
	printf("0");
}

funcEntity g_HorizontalBall[FUNC_COUNT] = { MoveHorizontal, DrawBall };

while(!bExit)
{

}

int main()
{
	return 0;
}