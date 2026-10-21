#include "CBall.h"
#include "Constants.h"
#include "consola.h"
void CBall::Move()
{
    m_ix += m_idx;
    if (m_ix <= 1 || m_ix >= WORLD_WIDTH - 2)
        m_idx = -m_idx;               // en el borde, cambia de sentido
}

void CBall::Draw()
{
    int color = (rand() % 256);
    gotoxy(m_ix, m_iy);
    printf("\033[38;5;%dmO\033[0m", color);
}