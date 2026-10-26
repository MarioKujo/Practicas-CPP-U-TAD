// ***************************************************************************************
// consola.cpp - Funciones auxiliares para pintar en la consola de Windows
// ***************************************************************************************
#include <windows.h>
#include "consola.h"

void gotoxy(int x, int y)
{
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hidecursor()
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;       // hay que darle un valor válido (1..100) o la llamada falla
	info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void clear()
{
	// Rellena la pantalla con espacios. Es mucho más rápido que system("cls")
	// y parpadea menos al llamarlo en cada fotograma.
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hOut, &csbi))
		return;

	DWORD size = csbi.dwSize.X * csbi.dwSize.Y;
	DWORD written = 0;
	COORD origin = { 0, 0 };
	FillConsoleOutputCharacterA(hOut, ' ', size, origin, &written);
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, size, origin, &written);
	SetConsoleCursorPosition(hOut, origin);
}
