#include <chrono>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <cstdio>
#include "TEntity.h"

constexpr int NUM_ENTITIES = 1000000;
constexpr int FRAMES = 50;
constexpr int REPETITIONS = 5; // Veces que se repite cada medida; nos quedamos con la mejor
constexpr int N = 4096;        // Lado de la matriz
constexpr float DT = 0.016f;   // Duración de un fotograma a 60 fps (aprox.)

/*
---------------------------------------------------------------------------------------
CRONÓMETRO
---------------------------------------------------------------------------------------
*/

using Clock = std::chrono::high_resolution_clock;
using Ms = std::chrono::duration<double, std::milli>; // Duración medida en milisegundos, con decimales

// Mide cuánto tarda en ejecutarse lo que se le pase (una lambda, como en la práctica 19; los [&] dejan
// que use las variables de fuera)
template <typename TFunc>
double Measure(const TFunc& _fnFunc)
{
	const auto tStart = Clock::now();
	_fnFunc();
	return Ms(Clock::now() - tStart).count();
}

// Repite la medida y devuelve la más baja, que es la menos afectada por "ruido" del sistema.
// Ojo: cada repetición sigue moviendo las MISMAS entidades, así que el checksum final corresponde a
// FRAMES * REPETITIONS fotogramas. No afecta al tiempo, solo al valor que se imprime
template <typename TFunc>
double MeasureBest(const TFunc& _fnFunc)
{
	double tBest = Measure(_fnFunc);
	for (int iRepeticion = 1; iRepeticion < REPETITIONS; ++iRepeticion)
	{
		double tMs = Measure(_fnFunc);
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

/*
---------------------------------------------------------------------------------------
UN FOTOGRAMA DE CADA VERSIÓN: mueve todas las entidades una vez (x += vx * dt; y += vy * dt).
La cuenta es la misma en las cuatro; lo único que cambia es cómo están guardados los datos
---------------------------------------------------------------------------------------
*/

void UpdateList(std::list<TEntity>& lstEntities, float _fDt)
{
	for (TEntity& oEntity : lstEntities)
	{
		oEntity.x += oEntity.vx * _fDt;
		oEntity.y += oEntity.vy * _fDt;
	}
}

void UpdatePointers(std::vector<TEntity*>& vEntities, float _fDt)
{
	for (TEntity* pEntity : vEntities) // pEntity es una dirección; con -> se accede a la entidad a la que apunta
	{
		pEntity->x += pEntity->vx * _fDt;
		pEntity->y += pEntity->vy * _fDt;
	}
}

void UpdateAoS(std::vector<TEntity>& vEntities, float _fDt)
{
	for (TEntity& oEntity : vEntities)
	{
		oEntity.x += oEntity.vx * _fDt;
		oEntity.y += oEntity.vy * _fDt;
	}
}

void UpdateSoA(TEntities& oEntities, float _fDt)
{
	// Punteros locales a cada array: así el compilador sabe dónde están los datos durante todo el bucle
	// y no tiene que volver a leerlos de oEntities en cada vuelta
	float* pX = oEntities.vX.data();
	float* pY = oEntities.vY.data();
	const float* pVX = oEntities.vVX.data();
	const float* pVY = oEntities.vVY.data();
	const int iCount = static_cast<int>(oEntities.vX.size());

	for (int iIndice = 0; iIndice < iCount; ++iIndice)
	{
		pX[iIndice] += pVX[iIndice] * _fDt;
		pY[iIndice] += pVY[iIndice] * _fDt;
	}
}

/*
---------------------------------------------------------------------------------------
MEDICIONES (el checksum se calcula DESPUÉS de medir, así que no cuenta en el tiempo)
---------------------------------------------------------------------------------------
*/

void MedirList()
{
	// Lista enlazada: cada nodo es una reserva de memoria aparte, repartidos por el heap
	std::list<TEntity> lstEntities(NUM_ENTITIES);

	const double tMs = MeasureBest([&]
		{
			for (int iFrame = 0; iFrame < FRAMES; ++iFrame)
			{
				UpdateList(lstEntities, DT);
			}
		});

	double dChecksum = 0.0;
	for (const TEntity& oEntity : lstEntities)
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

	// Se barajan las direcciones: ahora recorrer el vector es saltar por el heap sin ningún orden
	std::random_device oRandomDevice;
	std::mt19937 oGenerator(oRandomDevice());
	std::shuffle(vEntities.begin(), vEntities.end(), oGenerator);

	const double tMs = MeasureBest([&]
		{
			for (int iFrame = 0; iFrame < FRAMES; ++iFrame)
			{
				UpdatePointers(vEntities, DT);
			}
		});

	double dChecksum = 0.0;
	for (const TEntity* const pEntity : vEntities)
	{
		dChecksum += pEntity->x;
	}
	PrintResult("vector<TEntity*>", tMs, dChecksum);

	// Todo lo creado con new se libera con delete (después de medir, para que no cuente en el tiempo)
	for (const TEntity* const pEntity : vEntities)
	{
		delete pEntity;
	}
}

void MedirVectorContiguo()
{
	// Las entidades enteras, una detrás de otra, en un único bloque de memoria
	std::vector<TEntity> vEntities(NUM_ENTITIES);

	const double tMs = MeasureBest([&]
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

	const double tMs = MeasureBest([&]
		{
			for (int iFrame = 0; iFrame < FRAMES; ++iFrame)
			{
				UpdateSoA(oEntities, DT);
			}
		});

	double dChecksum = 0.0;
	for (const float fX : oEntities.vX)
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
	const double tFilas = MeasureBest([&]
		{
			iSumFilas = 0;
			for (int iFila = 0; iFila < N; ++iFila)
			{
				for (int iColumna = 0; iColumna < N; ++iColumna)
				{
					iSumFilas += vviMatriz[iFila][iColumna];
				}
			}
		});

	// Por columnas: mismos datos con los bucles intercambiados; cada acceso salta a otra fila
	int iSumColumnas = 0;
	const double tColumnas = MeasureBest([&]
		{
			iSumColumnas = 0;
			for (int iColumna = 0; iColumna < N; ++iColumna)
			{
				for (int iFila = 0; iFila < N; ++iFila)
				{
					iSumColumnas += vviMatriz[iFila][iColumna];
				}
			}
		});

	// Imprimir las sumas también evita que el optimizador elimine los bucles
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