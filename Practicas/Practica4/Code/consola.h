// ***************************************************************************************
// consola.h - Funciones auxiliares para pintar en la consola de Windows
// ***************************************************************************************
#pragma once

// Sitúa el cursor en la columna x, fila y (0,0 es la esquina superior izquierda).
// El siguiente printf escribirá a partir de ahí.
void gotoxy(int x, int y);

// Esconde el cursor parpadeante de la consola.
void hidecursor();

// Borra toda la pantalla y deja el cursor en (0,0).
void clear();
