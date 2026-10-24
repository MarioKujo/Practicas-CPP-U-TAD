/*
(compilar en Release x64; en Debug las medidas no sirven)

a. Crear una struct TEntity con datos que se usan al moverse (float x, y, vx, vy) y datos que no (nombre de 32
caracteres, vida, equipo y 8 floats de estadísticas). Mover 1.000.000 de entidades durante 50 fotogramas
(x += vx * dt; y += vy * dt;).

b. Hacerlo con cuatro formas de guardarlas: std::list<TEntity>, std::vector<TEntity*> desordenado con std::shuffle,
std::vector<TEntity> y SoA (un vector por campo: x, y, vx, vy).

c. Sumar una matriz de 4096 × 4096 enteros recorriéndola por filas y por columnas.

d. Medir cada versión con std::chrono y explicar las diferencias: ¿cuántos bytes útiles trae cada línea de caché
(64 bytes) en cada versión?

 =====================================================================================
 ANÁLISIS DE EFICIENCIA DE CACHÉ (Línea de caché = 64 bytes | Datos útiles = 16 bytes: x, y, vx, vy)
 =====================================================================================

 1. SoA (Structure of Arrays):
    > 100% útil (64/64 bytes). Vectores separados de floats puros. Cero desperdicio de caché.

 2. Vector Contiguo (AoA - std::vector<TEntity>):
    > ~25% útil (16/64 bytes). Entidades de 88 bytes cargan datos muertos (nombre, vida, stats).

 3. Vector Punteros Desordenado (std::vector<TEntity*>):
    > Eficiencia pésima. Saltos aleatorios masivos en el Heap que destruyen la caché (cache misses).

 4. Lista Enlazada (std::list<TEntity>):
    > Eficiencia muy baja. Nodos dispersos en memoria con sobrecarga extra de punteros (next/prev).
 =====================================================================================

Aunque el SoA maximiza la eficiencia de caché al 100% al evitar datos muertos, en modo Release el AoA se vio
beneficiado por la capacidad de auto-vectorización (SIMD) del compilador al empaquetar los structs contiguos de forma
óptima en los registros de la CPU.

Pista:
 Usar el resultado de los cálculos (por ejemplo, imprimirlo): si no, el optimizador puede eliminar los bucles y las
medidas saldrán a 0.
*/
#pragma once
#include <vector>
enum class EEquipo
{
	Neutral,
	Player,
	Enemy
};

struct TEntity
{
	float x, y, vx, vy;
	char nombre[32]; // nombre de 32 caracteres
	unsigned int vida;
	EEquipo equipo;
	float stats[8];
	TEntity()
		:x(0.0f)
		, y(0.0f)
		, vx(0.0f)
		, vy(0.0f)
		, vida(100)
		, equipo(EEquipo::Neutral)
		, nombre('\0')
	{
		for (int i = 0;i < 8;i++)
		{
			stats[i] = 0.0f;
		}
	}
};

struct TEntityManagerSoA
{
	std::vector<float> x;
	std::vector<float> y;
	std::vector<float> vx;
	std::vector<float> vy;

	TEntityManagerSoA(size_t size) // En vez de un struct por entidad, un único struct que guarda todos los valores de
		// todas las entidades. Entonces, los valores de la primera entidad serán x[0], y[0], vx[0], vy[0]
		:x(size, 0.0f)
		, y(size, 0.0f)
		, vx(size, 0.0f)
		, vy(size, 0.0f)
	{
	}
};