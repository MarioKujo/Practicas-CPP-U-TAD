#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <list>
#include <cstdio>
#include "TEntity.h"

const int NUM_ENTITIES = 1000000;
const int FRAMES = 50;
float dt = 0.016f; // 60fps

void SimularConList()
{
	// std::list<TEntity>: primera forma de guardarlas
	std::list<TEntity> entities(NUM_ENTITIES);

	printf("Iniciando simulacion con std::list...\n");

	auto start = std::chrono::high_resolution_clock::now();

	for (int frame = 0; frame < FRAMES; ++frame)
	{
		for (auto& entity : entities)
		{
			entity.x += entity.vx * dt;
			entity.y += entity.vy * dt;
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;

	printf("std::list completada en %.3f ms.\n", elapsed.count());
}

void SimularConVectorPunterosDesordenado()
{
	// std::vector<TEntity*> desordenado con std::shuffle: segunda forma de guardarlas
	std::vector<TEntity*>entities(NUM_ENTITIES);

	for (int i = 0;i < NUM_ENTITIES;++i)
	{
		entities[i] = new TEntity();
	}

	std::random_device rd; // Generador de semillas
	std::mt19937 g(rd()); // Número aleatorio (necesario para shuffle)
	std::shuffle(entities.begin(), entities.end(), g); // Función shuffle barajea los punteros

	printf("Iniciando simulacion con std::vector<TEntity*> desordenado...\n");

	auto start = std::chrono::high_resolution_clock::now();

	for (int frame = 0;frame < FRAMES;++frame)
	{
		for (int i = 0;i < NUM_ENTITIES;++i)
		{
			entities[i]->x += entities[i]->vx * dt;
			entities[i]->y += entities[i]->vy * dt;
		}
	}

	for (int i = 0;i < NUM_ENTITIES;++i)
	{
		delete entities[i];
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;

	printf("std::vector<TEntity*> completado en %.3f ms.\n", elapsed.count());
}

void SimularConVectorContiguo()
{
	// std::vector<TEntity>: tercera forma de guardarlas
	std::vector<TEntity> entities(NUM_ENTITIES);

	printf("Iniciando simulacion con std::vector<TEntity> (AoA)...\n");

	auto start = std::chrono::high_resolution_clock::now();

	for (int frame = 0;frame < FRAMES;++frame)
	{
		for (int i = 0;i < NUM_ENTITIES;++i)
		{
			entities[i].x += entities[i].vx * dt;
			entities[i].y += entities[i].vy * dt;
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;

	printf("std::vector<TEntity> completado en %.3f ms.\n", elapsed.count());
}

void SimularConSoA()
{
	// SoA (un vector por campo: x, y, vx, vy): cuarta forma de guardarlas
	TEntityManagerSoA entities(NUM_ENTITIES);

	printf("Iniciando simulacion con SoA (Structure of Arrays)...\n");

	auto start = std::chrono::high_resolution_clock::now();

	for (int frame = 0;frame < FRAMES;++frame)
	{
		for (int i = 0;i < NUM_ENTITIES;++i)
		{
			entities.x[i] += entities.vx[i] * dt;
			entities.y[i] += entities.vy[i] * dt;
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;

	printf("SoA completado en %.3f ms.\n", elapsed.count());
}

void SumarMatriz()
{
	std::vector<std::vector<int>> matriz(4096, std::vector<int>(4096, 0));

	long long sumaFilas = 0;

	printf("Iniciando suma de matriz 4096 x 4096...\n");

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 4096; ++i)
	{
		for (int j = 0; j < 4096; ++j)
		{
			sumaFilas += matriz[i][j];
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;

	printf("Suma de matriz completada en %.3f ms. (Resultado: %lld)\n", elapsed.count(), sumaFilas);
}

int main()
{
	SimularConList();
	SimularConVectorPunterosDesordenado();
	SimularConVectorContiguo();
	SimularConSoA();
	SumarMatriz();
	return 0;
}