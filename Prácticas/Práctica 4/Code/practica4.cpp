// ***************************************************************************************
// PRÁCTICA 4 - Un mundo con entidades (punteros a función)
//
// Cada entidad guarda un puntero a una TABLA DE FUNCIONES de su tipo:
//
//     entidad ──► m_funcs ──► [ FUNC_MOVE ] ──► MoveHorizontal()
//                             [ FUNC_DRAW ] ──► DrawBall()
//
// El bucle principal no sabe de qué tipo es cada entidad: solo llama a
// m_funcs[FUNC_MOVE] y m_funcs[FUNC_DRAW]. Cada tipo decide qué hacer.
// (Es lo mismo que hace C++ con las funciones virtuales: lo veremos en la Sesión 9.)
//
// Busca los "TODO" para ver lo que tienes que completar.
// ***************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>      // _kbhit, _getch
#include <windows.h>    // Sleep
#include "consola.h"    // gotoxy, hidecursor, clear

// ---------------------------------------------------------------------------------------
// El mundo: un rectángulo de la consola con borde. Las entidades viven DENTRO del borde:
// x entre 1 y WORLD_WIDTH-2, y entre 1 y WORLD_HEIGHT-2.
// ---------------------------------------------------------------------------------------
const int WORLD_WIDTH  = 60;
const int WORLD_HEIGHT = 20;
const int FRAME_MS     = 100;   // milisegundos entre fotogramas

// ---------------------------------------------------------------------------------------
// La entidad y su tabla de funciones
// ---------------------------------------------------------------------------------------
struct TEntity;
typedef void (*funcEntity)(TEntity*);   // puntero a función que recibe una entidad

// Qué función hay en cada posición de la tabla
enum EFunc
{
    FUNC_MOVE = 0,   // m_funcs[FUNC_MOVE] -> mueve la entidad un paso
    FUNC_DRAW = 1,   // m_funcs[FUNC_DRAW] -> pinta la entidad
    FUNC_COUNT       // número de funciones de la tabla
};

struct TEntity
{
    int         m_ix,  m_iy;    // posición
    int         m_idx, m_idy;   // dirección de movimiento (-1, 0 o 1)
    int m_iWidth, m_iHeight;
    funcEntity m_funcs[FUNC_COUNT];        // tabla de FUNC_COUNT funciones de su tipo

    TEntity(funcEntity func_move, funcEntity func_draw, int x, int y, int dx = 0, int dy = 0, int width = 1, int height = 1)
    {
        m_funcs[FUNC_MOVE] = func_move;
        m_funcs[FUNC_DRAW] = func_draw;
        m_ix = x;   m_iy = y;
        m_idx = dx; m_idy = dy;
        m_iWidth = width;
        m_iHeight = height;
    }
};

// ***************************************************************************************
// EJEMPLO: tipo "pelota horizontal" (rebota de izquierda a derecha y se pinta como 'O')
// ***************************************************************************************
void MoveHorizontal(TEntity* e)
{
    e->m_ix += e->m_idx;
    if (e->m_ix <= 1 || e->m_ix >= WORLD_WIDTH - 2)
        e->m_idx = -e->m_idx;               // en el borde, cambia de sentido
}

void MoveVertical(TEntity* e)
{
    e->m_iy += e->m_idy;
    if (e->m_iy <= 1 || e->m_iy >= WORLD_HEIGHT - 2)
        e->m_idy = -e->m_idy;               // en el borde, cambia de sentido
}

void MoveDiagonal(TEntity* e)
{
    e->m_ix += e->m_idx;
    if (e->m_ix <= 1 || e->m_ix >= WORLD_WIDTH - 2)
        e->m_idx = -e->m_idx;               // en el borde, cambia de sentido

    e->m_iy += e->m_idy;
    if (e->m_iy <= 1 || e->m_iy >= WORLD_HEIGHT - 2)
        e->m_idy = -e->m_idy;               // en el borde, cambia de sentido
}

void MoveDiagonalDVD(TEntity* e)
{
    e->m_ix += e->m_idx;
    if (e->m_ix <= 1 || e->m_ix + e->m_iWidth - 1 >= WORLD_WIDTH - 2)
        e->m_idx = -e->m_idx;               // en el borde, cambia de sentido

    e->m_iy += e->m_idy;
    if (e->m_iy <= 1 || e->m_iy + e->m_iHeight - 1 >= WORLD_HEIGHT - 2)
        e->m_idy = -e->m_idy;               // en el borde, cambia de sentido
}

int RandomColor()
{
    int color = (rand() % 256);

    return color;
}

void DrawBall(TEntity* e)
{
    int color = RandomColor();
    gotoxy(e->m_ix, e->m_iy);
    printf("\033[38;5;%dm0\033[0m", color);
}

void DrawLegs(TEntity* e)
{
    int color = RandomColor();
    gotoxy(e->m_ix, e->m_iy);
    printf("\033[38;5;%dmA\033[0m", color);
}

void DrawAsteroid(TEntity* e)
{
    int color = RandomColor();
    gotoxy(e->m_ix, e->m_iy);
    printf("\033[38;5;%dm*\033[0m", color);
}

void DrawDVDLogo(TEntity* e)
{
    int color = RandomColor();
    gotoxy(e->m_ix, e->m_iy);
    printf("\033[38;5;%dm----\033[0m", color);
    gotoxy(e->m_ix, e->m_iy + 1);
    printf("\033[38;5;%dm|DVD|\033[0m", color);
    gotoxy(e->m_ix, e->m_iy + 2);
    printf("\033[38;5;%dm----\033[0m", color);
}

// ***************************************************************************************
// TODO: añade al menos 3 tipos más. Cada tipo = sus funciones + su tabla.
//   - Al menos dos tipos distintos deben COMPARTIR la función de pintar
//     (por ejemplo, una pelota vertical que también usa DrawBall).
//   - Ideas: vertical, diagonal (rebota en las 4 paredes), aleatorio (rand() % 3 - 1),
//     uno que parpadea (se pinta un fotograma sí y otro no)...
// ***************************************************************************************


// ---------------------------------------------------------------------------------------
// Pinta el borde del mundo
// ---------------------------------------------------------------------------------------
void DrawWorld()
{
    for (int x = 0; x < WORLD_WIDTH; ++x)
    {
        gotoxy(x, 0);                printf("-");
        gotoxy(x, WORLD_HEIGHT - 1); printf("-");
    }
    for (int y = 1; y < WORLD_HEIGHT - 1; ++y)
    {
        gotoxy(0, y);                printf("|");
        gotoxy(WORLD_WIDTH - 1, y);  printf("|");
    }
    gotoxy(2, WORLD_HEIGHT);
    printf("ESC para salir");
}

// ***************************************************************************************
// MAIN
// ***************************************************************************************
const int MAX_ENTITIES = 32;

int main()
{
    hidecursor();

    // 1. Crear las entidades con new y guardarlas en la tabla del mundo
    TEntity* entities[MAX_ENTITIES] = {};
    int numEntities = 0;

    entities[numEntities++] = new TEntity(&MoveHorizontal,&DrawBall, 5, 3, 1, 0);
    entities[numEntities++] = new TEntity(&MoveVertical, &DrawLegs, 40, 10, 0, 1);
    entities[numEntities++] = new TEntity(&MoveDiagonal, &DrawAsteroid, 35, 5, -1, 1);
    entities[numEntities++] = new TEntity(&MoveDiagonalDVD, &DrawDVDLogo, 48, 7, 2, 1, 5, 3);
    // TODO: crear varias entidades de cada uno de vuestros tipos

    // 2. Bucle del juego: se repite hasta pulsar ESC
    bool bExit = false;
    while (!bExit)
    {
        if (_kbhit() && _getch() == 27)     // 27 = tecla ESC
            bExit = true;

        // Mover todas: se llama a la función que hay en la posición FUNC_MOVE de su tabla
        for (int i = 0; i < numEntities; ++i)
            entities[i]->m_funcs[FUNC_MOVE](entities[i]);

        // Pintar: borrar la pantalla, pintar el mundo y luego todas las entidades
        clear();
        DrawWorld();
        // TODO: pintar todas las entidades llamando a la función FUNC_DRAW de su tabla
        for (int i = 0; i < numEntities; ++i)
            entities[i]->m_funcs[FUNC_DRAW](entities[i]);
        Sleep(10);
    }

    // 3. Liberar la memoria
    // TODO: delete de cada entidad creada con new
    for (int i = 0; i < numEntities; i++)
    {
        delete[]entities[i];
        entities[i] = nullptr;
    }
    clear();
    return 0;
}
