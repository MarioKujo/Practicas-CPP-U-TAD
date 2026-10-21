/*
1 Con código documentado que lo demuestre, en Visual Studio x64: ¿cuánto ocupa la vtable? ¿Dónde está? (Pista: compara su dirección, en los primeros 8 bytes del objeto, con una global, una local y una de new.)

- La vtable ocupa 32 bits, y está en la memoria estática.

2 ¿Cuánto ocupa de más un objeto por tener funciones virtuales? (Compara el sizeof con y sin virtual.)

- Exactamente 8 bytes, justo lo que ocupa el puntero a la vtable

3 ¿Qué pasa si llamo a un método virtual desde el constructor? ¿Y desde el destructor?

- En el constructor: El polimorfismo está desactivado porque el objeto aún no es de la clase derivada. Al ser una
función virtual pura ('= 0') sin cuerpo, provoca un error crítico en ejecución (pure virtual function call).

- En el destructor: La parte derivada ya ha sido destruida, por lo que el objeto ha retrocedido a ser de la clase base y
se llamaría a su versión (si es pura sin cuerpo, también peta).

4 Virtual vs no virtual: ¿cuántos pasos más hacen falta? (Pista: Depurar → Ventanas → Desensamblado.)

- Hacen falta 3 pasos más para la clase virtual, donde tiene que cargar el puntero, buscar en la tabla y hacer la
llamada indirecta a ese registro

*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>      // _kbhit, _getch
#include <windows.h>    // Sleep
#include "consola.h"    // gotoxy, hidecursor, clear

// ---------------------------------------------------------------------------------------
// El mundo: un rectángulo de la consola con borde.
// ---------------------------------------------------------------------------------------
const int WORLD_WIDTH = 60;
const int WORLD_HEIGHT = 20;
const int FRAME_MS = 100;

// ---------------------------------------------------------------------------------------
// CEntity: Clase base con funciones virtuales (aquí se genera la vtable automáticamente)
// ---------------------------------------------------------------------------------------
class CEntityVirtual
{
public:
    int m_ix, m_iy;    // posición
    int m_idx, m_idy;   // dirección de movimiento (-1, 0 o 1)
    int m_iWidth, m_iHeight;

    CEntityVirtual(int x, int y, int dx = 0, int dy = 0, int width = 1, int height = 1)
    {
        //Move();
        m_ix = x;   m_iy = y;
        m_idx = dx; m_idy = dy;
        m_iWidth = width;
        m_iHeight = height;
    }

    // Destructor virtual para asegurar que se destruyen bien las clases derivadas
    virtual ~CEntityVirtual()
    {
        //Move();
    }

    // Funciones virtuales (sustituyen a la tabla m_funcs[] de punteros a función)
    virtual void Move() = 0;
    virtual void Draw() = 0;
};

class CEntityNoVirtual
{
public:
    int m_ix, m_iy;    // posición
    int m_idx, m_idy;   // dirección de movimiento (-1, 0 o 1)
    int m_iWidth, m_iHeight;

    CEntityNoVirtual(int x, int y, int dx = 0, int dy = 0, int width = 1, int height = 1)
    {
        m_ix = x;   m_iy = y;
        m_idx = dx; m_idy = dy;
        m_iWidth = width;
        m_iHeight = height;
    }

    // Destructor
    ~CEntityNoVirtual() {}

    // Funciones
    void Move();
    void Draw();
};

// ***************************************************************************************
// Clase derivada "CBall" (reemplaza a MoveHorizontal y DrawBall)
// ***************************************************************************************
class CBall : public CEntityVirtual
{
public:
    CBall(int x, int y, int dx = 0, int dy = 0) : CEntityVirtual(x, y, dx, dy, 1, 1) {}

    void Move() override
    {
        m_ix += m_idx;
        if (m_ix <= 1 || m_ix >= WORLD_WIDTH - 2)
            m_idx = -m_idx;               // en el borde, cambia de sentido
    }

    void Draw() override
    {
        int color = (rand() % 256);
        gotoxy(m_ix, m_iy);
        printf("\033[38;5;%dmO\033[0m", color);
    }
};

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

// ---------------------------------------------------------------------------------------
// MAIN
// ---------------------------------------------------------------------------------------
const int MAX_ENTITIES = 32;

// 1. Una variable global para comparar
int g_variableGlobal = 10;

int main()
{
    // 2. Una variable local para comparar
    int l_variableLocal = 20;

    // 3. Una variable creada con new para comparar
    int* h_variableNew = new int(30);

    // Creamos una pelota
    CBall* cBall = new CBall(5, 3, 1, 0);

    // CÓMO OBTENER LA DIRECCIÓN DE LA VTABLE:
    // 'cBall' es un CBall*. Si lo convertimos a void** (puntero a puntero) 
    // y lo desreferenciamos con un *, leemos los primeros 8 bytes del objeto (el vptr).
    void* direccionVTable = *(void**)cBall;

    // Imprimimos todas las direcciones en hexadecimal (%p) usando punteros void*
    printf("--------------------------------------------------\n");
    printf("Direccion de la VTABLE:    %p\n", direccionVTable);
    printf("Direccion variable GLOBAL: %p\n", (void*)&g_variableGlobal);
    printf("Direccion variable LOCAL:  %p\n", (void*)&l_variableLocal);
    printf("Direccion variable NEW:    %p\n\n", (void*)h_variableNew);
    printf("sizeof(CEntityVirutal) = %zu\n", sizeof(CEntityVirtual));
    printf("sizeof(CEntityNoVirutal) = %zu\n", sizeof(CEntityNoVirtual));
    printf("--------------------------------------------------\n");

    // Limpieza de memoria
    delete h_variableNew;
    delete cBall;

    return 0;
}