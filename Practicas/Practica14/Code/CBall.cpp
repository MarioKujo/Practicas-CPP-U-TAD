#include "CBall.h"
#include "Constants.h"
#include "consola.h"
void CBall::Move()
{
    m_iX += m_iDX;
    if (m_iX <= 1 || m_iX >= WORLD_WIDTH - 2)
        m_iDX = -m_iDX;               // en el borde, cambia de sentido
}

void CBall::Draw()
{
    int iColor = (rand() % 256);
    gotoxy(m_iX, m_iY);
    // \033[38;5;Nm es un código ANSI que pone el color N (0-255) al texto; \033[0m lo restaura
    printf("\033[38;5;%dmO\033[0m", iColor);
}