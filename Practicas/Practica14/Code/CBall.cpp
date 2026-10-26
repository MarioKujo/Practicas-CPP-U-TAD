#include "CBall.h"
#include "Constants.h"
#include "consola.h"
#include <cstdio>
#include <cstdlib>

// Mismo código que MoveHorizontal y DrawBall de la práctica 4 (ver sus comentarios);
// ahora m_iX, m_iDX... son atributos de la propia clase, y no hace falta recibir la entidad como parámetro
void CBall::Move()
{
  m_iX += m_iDX;
  if (m_iX <= 1 || m_iX >= WORLD_WIDTH - 2)
    m_iDX = -m_iDX;
}

void CBall::Draw() const
{
  int iColor = (rand() % 256);
  gotoxy(m_iX, m_iY);
  printf("\033[38;5;%dmO\033[0m", iColor);
}