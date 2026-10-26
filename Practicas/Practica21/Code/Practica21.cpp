#include <chrono>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <cstdio>
#include "TEntity.h"

const int NUM_ENTITIES = 1000000;
const int FRAMES = 50;
const int REPETITIONS = 5; // Veces que se repite cada medida; nos quedamos con la mejor
const int N = 4096;        // Lado de la matriz
const float DT = 0.016f;   // Duración de un fotograma a 60 fps (aprox.)

// ---------------------------------------------------------------------------------------
// CRONÓMETRO
// ---------------------------------------------------------------------------------------
using Clock = std::chrono::high_resolution_clock;
using Ms = std::chrono::duration<double, std::milli>;

// Mide cuánto tarda en ejecutarse lo que le pasemos. Se le pasa una lambda: una función sin nombre escrita
// donde se necesita; los "[&]" significan que puede usar las variables de fuera.
template <typename TFunc>
double Measure(TFunc f)
{
	auto tStart = Clock::now();
	f();
	return Ms(Clock::now() - tStart).count();
}

// Repite la medida y devuelve la más baja, que es la menos afectada por "ruido" del sistema
template <typename TFunc>
double MeasureBest(TFunc f)
{
	double tBest = Measure(f);
	for (int iRepeticion = 1; iRepeticion < REPETITIONS; ++iRepeticion)
	{
		double tMs = Measure(f);
		if (tMs < tBest)
		{
			tBest = tMs;
		}
	}
	return tBest;
}

void PrintResult(const char* pszTitulo, double tMs, double dChecksum)
{
	printf("%-24s %9.3f ms (checksum: %.2f)\n", pszTitulo, tMs, dChecksum);
}

// ---------------------------------------------------------------------------------------
// UN FOTOGRAMA DE CADA VERSIÓN: mueve todas las entidades una vez (x += vx * dt; y += vy * dt)
// ---------------------------------------------------------------------------------------
void UpdateList(std::list<TEntity>& lEntities, float dt)
{
	for (TEntity& oEntity : lEntities)
	{
		oEntity.x += oEntity.vx * dt;
		oEntity.y += oEntity.vy * dt;
	}
}

void UpdatePointers(std::vector<TEntity*>& vEntities, float dt)
{
	for (TEntity* pEntity : vEntities) // pEntity es una dirección; con "->" accedemos a la entidad a la que apunta
	{
		pEntity->x += pEntity->vx * dt;
		pEntity->y += pEntity->vy * dt;
	}
}

void UpdateAoS(std::vector<TEntity>& vEntities, float dt)
{
	for (TEntity& oEntity : vEntities)
	{
		oEntity.x += oEntity.vx * dt;
		oEntity.y += oEntity.vy * dt;
	}
}

void UpdateSoA(TEntities& oEntities, float dt)
{
	// Punteros locales a cada array: así el compilador sabe dónde están los datos durante todo el bucle
	// y no tiene que volver a leerlos de oEntities en cada vuelta.
	float* pX = oEntities.vX.data();
	float* pY = oEntities.vY.data();
	const float* pVX = oEntities.vVX.data();
	const float* pVY = oEntities.vVY.data();
	const int iCount = static_cast<int>(oEntities.vX.size());

	for (int iIndice = 0; iIndice < iCount; ++iIndice)
	{
		pX[iIndice] += pVX[iIndice] * dt;
		pY[iIndice] += pVY[iIndice] * dt;
	}
}

// ---------------------------------------------------------------------------------------
// MEDICIONES (el checksum se calcula DESPUÉS de medir, así que no cuenta en el tiempo)
// ---------------------------------------------------------------------------------------
void MedirList()
{
	// Lista enlazada: cada nodo está en su propia reserva de memoria, repartidos por el heap
	std::list<TEntity> lEntities(NUM_ENTITIES);

	double tMs = MeasureBest([&]
		{
			for (int iFrame = 0; iFrame < FRAMES; ++iFrame)
			{
				UpdateList(lEntities, DT);
			}
		});

	double dChecksum = 0.0;
	for (const TEntity& oEntity : lEntities)
	{
		dChecksum += oEntity.x;
	}
	PrintResult("std::list<TEntity>", tMs, dChecksum);
}

void MedirVectorPunteros()
{
	// El vector guarda solo direcciones; cada TEntity vive aparte en el heap (creado con new)
	std::vector<TEntity*> vEntities(NUM_ENTITIES);
	for (TEntity*& pEntity : vEntities)
	{
		pEntity = new TEntity();
	}

	// Barajamos las direcciones: ahora recorrer el vector es saltar por el heap sin ningún orden
	std::random_device oRandomDevice;
	std::mt19937 oGenerator(oRandomDevice());
	std::shuffle(vEntities.begin(), vEntities.end(), oGenerator);

	double tMs = MeasureBest([&]
		{
			for (int iFrame = 0; iFrame < FRAMES; ++iFrame)
			{
				UpdatePointers(vEntities, DT);
			}
		});

	double dChecksum = 0.0;
	for (const TEntity* pEntity : vEntities)
	{
		dChecksum += pEntity->x;
	}
	PrintResult("vector<TEntity*>", tMs, dChecksum);

	// Todo lo creado con new se libera con delete (después de medir, para que no cuente en el tiempo)
	for (TEntity* pEntity : vEntities)
	{
		delete pEntity;
	}
}

void MedirVectorContiguo()
{
	// Las entidades enteras, una detrás de otra, en un único bloque de memoria
	std::vector<TEntity> vEntities(NUM_ENTITIES);

	double tMs = MeasureBest([&]
		{
			for (int iFrame = 0; iFrame < FRAMES; ++iFrame)
			{
				UpdateAoS(vEntities, DT);
			}
		});

	double dChecksum = 0.0;
	for (const TEntity& oEntity : vEntities)
	{
		dChecksum += oEntity.x;
	}
	PrintResult("vector<TEntity> (AoS)", tMs, dChecksum);
}

void MedirSoA()
{
	TEntities oEntities(NUM_ENTITIES);

	double tMs = MeasureBest([&]
		{
			for (int iFrame = 0; iFrame < FRAMES; ++iFrame)
			{
				UpdateSoA(oEntities, DT);
			}
		});

	double dChecksum = 0.0;
	for (float fX : oEntities.vX)
	{
		dChecksum += fX;
	}
	PrintResult("SoA", tMs, dChecksum);
}

void MedirMatriz()
{
	// Matriz de N x N ints, todos a 1: el resultado correcto de la suma es N * N = 16777216
	std::vector<std::vector<int>> vviMatriz(N, std::vector<int>(N, 1));

	// Por filas: el bucle interno recorre elementos vecinos en memoria (lo que más le gusta a la caché)
	int iSumFilas = 0;
	double tFilas = MeasureBest([&]
		{
			iSumFilas = 0;
			for (int r = 0; r < N; ++r)
			{
				for (int c = 0; c < N; ++c)
				{
					iSumFilas += vviMatriz[r][c];
				}
			}
		});

	// Por columnas: mismos datos con los bucles intercambiados; cada acceso salta a otra fila
	int iSumColumnas = 0;
	double tColumnas = MeasureBest([&]
		{
			iSumColumnas = 0;
			for (int c = 0; c < N; ++c)
			{
				for (int r = 0; r < N; ++r)
				{
					iSumColumnas += vviMatriz[r][c];
				}
			}
		});

	printf("Matriz por filas:        %9.3f ms (suma: %d)\n", tFilas, iSumFilas);
	printf("Matriz por columnas:     %9.3f ms (suma: %d)\n", tColumnas, iSumColumnas);
}

int main()
{
	printf("Moviendo %d entidades durante %d fotogramas (mejor de %d medidas):\n\n", NUM_ENTITIES, FRAMES, REPETITIONS);
	MedirList();
	MedirVectorPunteros();
	MedirVectorContiguo();
	MedirSoA();
	printf("\n");
	MedirMatriz();
	return 0;
}