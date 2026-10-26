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
#include <crtdbg.h> // Solo existe en Visual Studio (Windows): sirve para detectar fugas de memoria


// ---------------------------------------------------------------------------------------
// El mundo: un rectángulo de la consola con borde. Las entidades viven DENTRO del borde:
// x entre 1 y WORLD_WIDTH-2, y entre 1 y WORLD_HEIGHT-2.
// ---------------------------------------------------------------------------------------
const int WORLD_WIDTH = 60;
const int WORLD_HEIGHT = 20;
const int FRAME_MS = 100;   // milisegundos entre fotogramas

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
	int         m_ix, m_iy;    // posición
	int         m_idx, m_idy;   // dirección de movimiento (-1, 0 o 1)
	int m_iWidth, m_iHeight;    // tamaño en caracteres (para entidades de más de 1 carácter, como el logo DVD)
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

// Igual que MoveHorizontal, pero en vertical: solo cambia la fila (y) y rebota arriba y abajo
void MoveVertical(TEntity* e)
{
	// "e" es un puntero a una entidad, y la flecha -> sirve para llegar a un campo de lo que apunta.
	// e->m_iy es la fila de ESA entidad; sumarle m_idy la mueve una fila hacia abajo (1) o hacia arriba (-1)
	e->m_iy += e->m_idy;
	if (e->m_iy <= 1 || e->m_iy >= WORLD_HEIGHT - 2)
		e->m_idy = -e->m_idy;               // cambiar el signo invierte el sentido: 1 pasa a -1 y al revés
}

// Mezcla las dos anteriores: se mueve en x e y a la vez, así que rebota en las 4 paredes
void MoveDiagonal(TEntity* e)
{
	e->m_ix += e->m_idx;
	if (e->m_ix <= 1 || e->m_ix >= WORLD_WIDTH - 2)
		e->m_idx = -e->m_idx;

	e->m_iy += e->m_idy;
	if (e->m_iy <= 1 || e->m_iy >= WORLD_HEIGHT - 2)
		e->m_idy = -e->m_idy;
}

// Igual que MoveDiagonal, pero para entidades de más de 1 carácter.
// (m_ix, m_iy) es la esquina superior izquierda, así que el lado derecho está en m_ix + ancho - 1
// (un logo de ancho 5 que empieza en la columna 10 ocupa de la 10 a la 14, no hasta la 15).
// Con el alto pasa lo mismo: el lado de abajo está en m_iy + alto - 1.
void MoveDiagonalDVD(TEntity* e)
{
	e->m_ix += e->m_idx;
	if (e->m_ix <= 1 || e->m_ix + e->m_iWidth - 1 >= WORLD_WIDTH - 2)
		e->m_idx = -e->m_idx;

	e->m_iy += e->m_idy;
	if (e->m_iy <= 1 || e->m_iy + e->m_iHeight - 1 >= WORLD_HEIGHT - 2)
		e->m_idy = -e->m_idy;
}

// Movimiento aleatorio. Cada fotograma se mueve -1, 0 o 1 en cada eje (ignora m_idx y m_idy).
void MoveRandom(TEntity* e)
{
	// rand() % 3 da 0, 1 o 2; restándole 1 queda -1, 0 o 1
	e->m_ix += rand() % 3 - 1;
	e->m_iy += rand() % 3 - 1;

	// Como no hay un sentido que invertir, si se sale del mundo lo devolvemos al borde interior
	if (e->m_ix < 1)                  e->m_ix = 1;
	if (e->m_ix > WORLD_WIDTH - 2)    e->m_ix = WORLD_WIDTH - 2;
	if (e->m_iy < 1)                  e->m_iy = 1;
	if (e->m_iy > WORLD_HEIGHT - 2)   e->m_iy = WORLD_HEIGHT - 2;
}

// Devuelve un número aleatorio de 0 a 255 (rand() % 256 es el resto de dividir entre 256).
// Se usa como índice de la paleta de 256 colores de la consola
int RandomColor()
{
	int color = (rand() % 256);

	return color;
}

void DrawBall(TEntity* e)
{
	const int color = RandomColor();
	gotoxy(e->m_ix, e->m_iy);   // Coloca el cursor donde está la entidad: lo siguiente que se imprima irá ahí
	// \033[38;5;Nm: 38 = color de texto extendido, 5 = modo paleta de 256 colores, N = índice (0-255).
	// \033[0m restaura el color por defecto para que el resto de cosas después de esto se impriman en blanco.
	printf("\033[38;5;%dm0\033[0m", color);
}

// Mismo mecanismo que DrawBall (color aleatorio entre los códigos de color), pero pinta una 'A'
void DrawLegs(TEntity* e)
{
	const int color = RandomColor();
	gotoxy(e->m_ix, e->m_iy);
	printf("\033[38;5;%dmA\033[0m", color);
}

// Igual que DrawBall, pero pinta un '*'
void DrawAsteroid(TEntity* e)
{
	const int color = RandomColor();
	gotoxy(e->m_ix, e->m_iy);
	printf("\033[38;5;%dm*\033[0m", color);
}

// Pinta el logo en 3 filas. Se elige el color una sola vez para que las 3 filas salgan del mismo color
void DrawDVDLogo(TEntity* e)
{
	const int color = RandomColor();
	gotoxy(e->m_ix, e->m_iy);
	printf("\033[38;5;%dm----\033[0m", color);
	gotoxy(e->m_ix, e->m_iy + 1); // Misma columna, una fila más abajo
	printf("\033[38;5;%dm|DVD|\033[0m", color);
	gotoxy(e->m_ix, e->m_iy + 2); // Misma columna, dos filas más abajo
	printf("\033[38;5;%dm----\033[0m", color);
}
/*
Resultado final:
----
|DVD|
----
*/


// ***************************************************************************************
// TODO: añade al menos 3 tipos más. Cada tipo = sus funciones + su tabla.
//   - Al menos dos tipos distintos deben COMPARTIR la función de pintar
//     (por ejemplo, una pelota vertical que también usa DrawBall).
//   - Ideas: vertical, diagonal (rebota en las 4 paredes), aleatorio (rand() % 3 - 1),
//     uno que parpadea (se pinta un fotograma sí y otro no)...
//
// HECHO: los tipos nuevos son vertical, diagonal, diagonal DVD y aleatorio (las funciones están arriba).
// Un "tipo" es la combinación de una función de mover y una de pintar. Por eso se pueden compartir:
//   - Pelota horizontal  = MoveHorizontal + DrawBall
//   - Pelota vertical    = MoveVertical   + DrawBall   <-- comparte DrawBall con la horizontal
//   - Pelota diagonal    = MoveDiagonal   + DrawBall   <-- también
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
	// Al cerrar el programa, Visual Studio escribe en la ventana Salida si ha quedado memoria sin liberar
	// y dónde se reservó
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	hidecursor();

	// 1. Crear las entidades con new y guardarlas en la tabla del mundo
	TEntity* entities[MAX_ENTITIES] = {};
	int numEntities = 0;

	// Orden de los datos: función de mover, función de pintar, x, y, dirección x, dirección y, ancho, alto
	entities[numEntities++] = new TEntity(&MoveHorizontal, &DrawBall, 5, 3, 1, 0);
	entities[numEntities++] = new TEntity(&MoveVertical, &DrawLegs, 40, 10, 0, 1);        // Solo baja y sube (dx = 0)
	entities[numEntities++] = new TEntity(&MoveDiagonal, &DrawAsteroid, 35, 5, -1, 1);    // Empieza yendo a la
	// izquierda y hacia abajo
	entities[numEntities++] = new TEntity(&MoveDiagonalDVD, &DrawDVDLogo, 48, 7, 2, 1, 5, 3); // Se mueve 2 columnas
	// por fotograma; ocupa 5x3

	// Varias entidades de cada tipo, en posiciones y sentidos distintos para que no vayan todas juntas
	// Pelotas horizontales (la segunda empieza yendo hacia la izquierda)
	entities[numEntities++] = new TEntity(&MoveHorizontal, &DrawBall, 30, 8, -1, 0);
	entities[numEntities++] = new TEntity(&MoveHorizontal, &DrawBall, 15, 16, 1, 0);

	// Pelotas verticales: comparten DrawBall con las horizontales
	entities[numEntities++] = new TEntity(&MoveVertical, &DrawBall, 10, 5, 0, 1);
	entities[numEntities++] = new TEntity(&MoveVertical, &DrawBall, 55, 15, 0, -1);

	// Pelota diagonal: otro tipo que reutiliza DrawBall
	entities[numEntities++] = new TEntity(&MoveDiagonal, &DrawBall, 20, 4, 1, 1);

	// Piernas verticales y asteroides diagonales (más de uno de cada)
	entities[numEntities++] = new TEntity(&MoveVertical, &DrawLegs, 25, 12, 0, -1);
	entities[numEntities++] = new TEntity(&MoveDiagonal, &DrawAsteroid, 12, 14, 1, -1);

	// Entidades aleatorias: ignoran dx y dy, así que se pasa 0, 0. Una usa DrawAsteroid y otra DrawLegs
	entities[numEntities++] = new TEntity(&MoveRandom, &DrawAsteroid, 30, 10);
	entities[numEntities++] = new TEntity(&MoveRandom, &DrawLegs, 45, 12);

	// Segundo logo DVD, empezando arriba a la izquierda y yendo hacia la derecha y hacia arriba
	entities[numEntities++] = new TEntity(&MoveDiagonalDVD, &DrawDVDLogo, 10, 9, 2, -1, 5, 3);

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
		// Pintar todas las entidades llamando a la función FUNC_DRAW de su tabla
		for (int i = 0; i < numEntities; ++i)
			entities[i]->m_funcs[FUNC_DRAW](entities[i]);
		Sleep(10);
	}

	// 3. Liberar la memoria
	// Cada entidad se creó con new (un solo objeto), así que se libera con delete (delete[] es solo para arrays)
	for (int i = 0; i < numEntities; i++)
	{
		delete entities[i];
		entities[i] = nullptr;  // Así no queda un puntero apuntando a memoria que ya no es nuestra
	}
	clear();
	showcursor();
	return 0;
}