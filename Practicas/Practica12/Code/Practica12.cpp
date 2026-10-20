#include <iostream>
#include "TVector2.h"

int main()
{
	TVector2 a(2.0f, 3.0f);
	TVector2 b(4.0f, -1.0f);

	printf("a = (%f, %f)\n", a.x, a.y);
	printf("b = (%f, %f)\n\n", b.x, b.y);

	TVector2 suma = a + b;
	printf("a + b = (%f, %f)\n", suma.x, suma.y);

	TVector2 resta = a - b;
	printf("a - b = (%f, %f)\n", resta.x, resta.y);

	TVector2 negA = -a;
	printf("-a = (%f, %f)\n", negA.x, negA.y);

	TVector2 negB = -b;
	printf("-b = (%f, %f)\n\n", negB.x, negB.y);

	TVector2 mul1 = a * 2.0f;
	printf("a * 2 = (%f, %f)\n", mul1.x, mul1.y);

	TVector2 mul2 = 2.0f * a;
	printf("2 * a = (%f, %f)\n", mul2.x, mul2.y);

	TVector2 mul3 = b * 3.0f;
	printf("b * 3 = (%f, %f)\n", mul3.x, mul3.y);

	TVector2 mul4 = 3.0f * b;
	printf("3 * b = (%f, %f)\n\n", mul4.x, mul4.y);

	printf("a == b : %s\n", (a == b) ? "true" : "false");
	printf("a != b : %s\n", (a != b) ? "true" : "false");

	TVector2 c(2.0f, 3.0f);
	printf("c = (%f, %f)\n", c.x, c.y);
	printf("a == c : %s\n", (a == c) ? "true" : "false");
	printf("a != c : %s\n", (a != c) ? "true" : "false");
	printf("Ahora los couts:\n");
	std::cout << a << '\n';
	std::cout << b << '\n';
	std::cout << a + b << '\n';
	std::cout << -a << '\n';
	std::cout << 2.0f * a << '\n';
}