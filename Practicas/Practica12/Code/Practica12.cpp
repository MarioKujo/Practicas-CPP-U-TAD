#include <cstdio>
#include <iostream>
#include "TVector2.h"

int main()
{
	const TVector2 vA(2.0f, 3.0f);
	const TVector2 vB(4.0f, -1.0f);

	printf("a = (%f, %f)\n", vA.x, vA.y);
	printf("b = (%f, %f)\n\n", vB.x, vB.y);

	const TVector2 vSuma = vA + vB; // Llama a operator+
	printf("a + b = (%f, %f)\n", vSuma.x, vSuma.y);

	const TVector2 vResta = vA - vB;
	printf("a - b = (%f, %f)\n", vResta.x, vResta.y);

	const TVector2 vNegA = -vA; // Llama al operator- de un solo parámetro
	printf("-a = (%f, %f)\n", vNegA.x, vNegA.y);

	const TVector2 vNegB = -vB;
	printf("-b = (%f, %f)\n\n", vNegB.x, vNegB.y);

	// Multiplicación por un float en los dos órdenes
	const TVector2 vMul1 = vA * 2.0f;
	printf("a * 2 = (%f, %f)\n", vMul1.x, vMul1.y);

	const TVector2 vMul2 = 2.0f * vA;
	printf("2 * a = (%f, %f)\n", vMul2.x, vMul2.y);

	const TVector2 vMul3 = vB * 3.0f;
	printf("b * 3 = (%f, %f)\n", vMul3.x, vMul3.y);

	const TVector2 vMul4 = 3.0f * vB;
	printf("3 * b = (%f, %f)\n\n", vMul4.x, vMul4.y);

	// Comparaciones: vA y vB son distintos
	printf("a == b : %s\n", (vA == vB) ? "true" : "false");
	printf("a != b : %s\n\n", (vA != vB) ? "true" : "false");

	// vC tiene los mismos valores que vA, así que aquí el resultado es el contrario
	const TVector2 vC(2.0f, 3.0f);
	printf("c = (%f, %f)\n", vC.x, vC.y);
	printf("a == c : %s\n", (vA == vC) ? "true" : "false");
	printf("a != c : %s\n\n", (vA != vC) ? "true" : "false");

	// Con operator<< el vector se imprime directamente, sin acceder a .x y .y
	printf("Ahora los couts:\n");
	std::cout << vA << '\n';
	std::cout << vB << '\n';
	std::cout << vA + vB << '\n';
	std::cout << -vA << '\n';
	std::cout << 2.0f * vA << '\n';
}