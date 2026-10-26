/*
Práctica 21 - Memoria y caché
(compilar en Release x64; en Debug las medidas no sirven)

a. Crear una struct TEntity con datos que se usan al moverse (float x, y, vx, vy) y datos que no (nombre de 32
caracteres, vida, equipo y 8 floats de estadísticas). Mover 1.000.000 de entidades durante 50 fotogramas
(x += vx * dt; y += vy * dt;).

b. Hacerlo con cuatro formas de guardarlas: std::list<TEntity>, std::vector<TEntity*> desordenado con
std::shuffle, std::vector<TEntity> y SoA (un vector por campo: x, y, vx, vy).

c. Sumar una matriz de 4096 x 4096 enteros recorriéndola por filas y por columnas.

d. Medir cada versión con std::chrono y explicar las diferencias: ¿cuántos bytes útiles trae cada línea de
caché (64 bytes) en cada versión?

Pista: usar el resultado de los cálculos (por ejemplo, imprimirlo): si no, el optimizador puede eliminar los
bucles y las medidas saldrán a 0. Por eso se imprime un checksum (suma de todas las x).

RESULTADOS MEDIDOS (Release x64, AMD Ryzen 9 3900X, mejor de 5 medidas):
std::list<TEntity>      1662 ms
vector<TEntity*>         558 ms
vector<TEntity> (AoS)    348 ms
SoA                       41 ms
Matriz 4096x4096: por filas 8,4 ms | por columnas 88,9 ms (~11x más lenta)

BYTES ÚTILES POR LÍNEA DE CACHÉ (línea = 64 bytes; el movimiento solo necesita x, y, vx, vy = 16 bytes)

1. SoA: 64 de 64 bytes (100%). Tiene los mismos campos que TEntity, pero cada uno en su vector, así que el
bucle de movimiento solo trae floats que va a usar, y los datos fríos (nombre, vida, equipo, stats) no se tocan.
2. vector<TEntity> (AoS): 16 de 64 bytes (25%). Cada entidad mide 88 bytes y solo se usan 16; el resto viaja a
la caché sin hacer falta. Al menos están seguidas, y la CPU adivina lo siguiente (prefetcher).
3. vector<TEntity*> desordenado: 16 de 64 bytes (25%) como mucho. Al estar barajado, casi cada entidad es un
fallo de caché y la CPU no puede adivinar cuál toca después.
4. std::list<TEntity>: 16 de 64 bytes (25%) como mucho. Cada nodo mide 104 bytes (88 de la entidad + 16 de los
punteros anterior/siguiente) y están repartidos por el heap.
5. Matriz por filas: 64 de 64 bytes (se usan los 16 ints de la línea). Por columnas: 4 de 64 bytes, porque
cada acceso salta a otra fila y solo se usa 1 int de cada línea.

Prefijos: v = vector, a = array, sz = texto acabado en cero, i = int, f = float, t = tiempo, d = double,
lst = lista, p = puntero, o = objeto.
*/
#pragma once
#include <vector>
#include <array> // Para guardar el nombre y las estadísticas de cada entidad en un bloque de tamaño fijo

// AoS (Array of Structures): cada entidad es una struct con todo junto, y las entidades van una detrás de otra
struct TEntity
{
	// Datos "calientes": se usan en cada fotograma
	float x = 0.0f, y = 0.0f;
	float vx = 1.0f, vy = 1.0f; // Velocidad a 1 para que el resultado no sea 0
	// Datos "fríos": casi nunca se usan al moverse, pero ocupan sitio y viajan a la caché igualmente.
	// En total una entidad ocupa 88 bytes: 16 calientes y 72 fríos
	char szName[32] = "";
	int iLife = 100;
	int iTeam = 0;
	float aStats[8] = {};
};

// SoA (Structure of Arrays): un vector por campo, que guarda los datos de TODAS las entidades. Los de la
// primera son vX[0], vY[0], vVX[0]...; los de la segunda, vX[1]... Tiene los mismos campos que TEntity, pero
// los calientes (vX, vY, vVX, vVY) quedan en bloques de floats seguidos y los fríos aparte, sin estorbar
struct TEntities
{
	// Datos "calientes": se usan en cada fotograma
	std::vector<float> vX, vY;
	std::vector<float> vVX, vVY;
	// Datos "fríos": existen, pero el bucle de movimiento no los toca
	std::vector<std::array<char, 32>> vName;
	std::vector<int> vLife;
	std::vector<int> vTeam;
	std::vector<std::array<float, 8>> vStats;

	explicit TEntities(size_t _uCount)
		: vX(_uCount, 0.0f) // Un vector con _uCount elementos, todos con el mismo valor
		, vY(_uCount, 0.0f)
		, vVX(_uCount, 1.0f)
		, vVY(_uCount, 1.0f)
		, vName(_uCount) // Sin valor: se rellenan con ceros (nombre vacío)
		, vLife(_uCount, 100)
		, vTeam(_uCount, 0)
		, vStats(_uCount) // Sin valor: las 8 estadísticas de cada entidad empiezan en 0
	{
	}
};