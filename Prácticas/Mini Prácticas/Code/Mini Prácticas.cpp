#include <iostream>
#include <cmath>
#define PRINT_SIZE(tipo) printf("sizeof(" #tipo ") = %zu\n", sizeof(tipo))
// Escribir un programa que pida dos números e imprima su suma.
int Suma(int i1, int i2)
{
	return i1 + i2;
}

// ¿Para qué se usa // o /* */?
// Para agregar comentarios de código

// Imprimir por pantalla el tamaño de todas las combinaciones de modificador y tipo (unsigned, short, long... con char, int, float, double...).
void ImprimirSize()
{
	PRINT_SIZE(bool);
	PRINT_SIZE(char);
	PRINT_SIZE(signed char);
	PRINT_SIZE(unsigned char);
	PRINT_SIZE(short);
	PRINT_SIZE(unsigned short);
	PRINT_SIZE(int);
	PRINT_SIZE(unsigned int);
	PRINT_SIZE(long);
	PRINT_SIZE(unsigned long);
	PRINT_SIZE(long long);
	PRINT_SIZE(unsigned long long);
	PRINT_SIZE(float);
	PRINT_SIZE(double);
	PRINT_SIZE(long double);
}

// Asignar un int a un bool (¿qué valores son true y cuáles false?)
// Todo lo distinto de 0 es true

bool BoolToInt(int bValue)
{
	return bValue;
}

// y un float a un int.
int FloatToInt(float iValue)
{
	return iValue; // Saca warning, esperado
}

// Sumar un unsigned y un signed

unsigned int SumaUnsignedSigned(unsigned int uValue, int iValue)
{
	return uValue + iValue;
}

// restar dos unsigned.

unsigned int RestaUnsigned(unsigned int u1, unsigned int u2)
{
	return u1 - u2;
}

unsigned int RestaUnsignedSigned(unsigned int u1, int i1)
{
	return u1 - i1;
}

unsigned int RestaSignedUnsigned(int i1, unsigned int u1)
{
	return i1 - u1;
}

// Dividir dos int

int Division(int i1, int i2)
{
	return i1 / i2;
}

// dividir un float por un int

float DivisionFloat(float f1, int i1)
{
	return f1 / i1;
}

// y un int por un float.

float DivisionIntFloat(int i1, float f1)
{
	return i1 / f1;
}

// Forzar un NaN en una variable.
float ForzarNaN()
{
	float fCero = 0;
	return 0.0f / fCero;
}

// ¿Qué pasa si usamos ese NaN sobre cualquier otra variable, por ejemplo multiplicándolo?
// NaN se propaga

void MultiplicarNaN(float f1)
{
	printf("%f (float) * NaN = %f (float)\n\n", f1, ForzarNaN() * f1);
}
// ¿Cómo detectamos que un valor es NaN?
// Con la función isnan(n)

// Declarar una variable global llamada iPrueba y una variable local con el mismo nombre. ¿Qué ocurre?
// Se usa la local
int iPrueba = 0;

// ¿Qué pasa si no damos un valor a una variable? ¿Qué valor tiene?
// Que no se puede usar. En Debug y por ser Visual Studio, siempre inicializan con valor hexadecimal 0xcccccccc

/*
// ¿Qué líneas compilan y cuáles no ? ¿Por qué ?
// No compilan: enum stoplight (redefine red/yellow/green de color),
//   color eyes = green (green queda en conflicto por esa redefinición),
//   peppers p = green (green no pertenece a peppers; es enum class, requiere peppers::).
// Compilan: color hair = color::red; peppers p2 = peppers::red;
enum color { red, yellow, green };
enum stoplight { red, yellow, green };
enum class peppers { red, yellow, green };
color eyes = green;
peppers p = green;
color hair = color::red;
peppers p2 = peppers::red;
*/

// Escribir una función que reciba X números, los sume y devuelva el valor de la suma.

template<size_t N>
int Suma(const int(&numeros)[N])
{
	int suma = 0;
	for (size_t i = 0; i < N; i++)
	{
		suma += numeros[i];
	}
	return suma;
}

/*
Hacer un bucle que recorra la tabla sText y la imprima en la consola.
char sText[] = "Hola";
*/

void ImprimirTabla()
{
	char sText[] = "Hola";

	size_t uSize = strlen(sText);
	
	unsigned int uIndex = 0;
	while (sText[uIndex] != '\0')
	{
		printf("%c", sText[uIndex]);
		++uIndex;
	}
	/*for (unsigned int uIndex = 0; uIndex < uSize; ++uIndex)
	{
		printf("%c", sText[uIndex]);
	}*/
	printf("\n\n");
}
/*
1 Declarar una referencia a una variable y cambiarle el valor.

2 ¿Qué pasa si no inicializamos una referencia?

3 ¿Qué significa esta expresión? int &r = i, r2 = i2;
*/

void Referencias()
{
	int i = 1;
	int i2 = 2;

	int& b = i;

	//int& b; // Error: tiene que tener una referencia a otra variable obligatoriamente

	int& r = i, r2 = i2; // r recibe una referencia de i, r2 recibe una copia del valor almacenado en i2
	printf("i = %d, i2 = %d, b = %d, r = %d, r2 = %d\n\n", i, i2, b, r, r2);
}

/*
// Escribir dos funciones distintas que provoquen que la pila se quede sin memoria.
void StackOverflow1(int n)
{
	char relleno[1024];
	relleno[0] = (char)n;          // evita que se optimice fuera
	printf("%d %d\n", n, relleno[0]);
	StackOverflow1(n + 1);
}

void StackOverflow2() // Este warning es exactamente lo que necesita para hacer stackoverflow
{
	char buffer[2 * 1024 * 1024];   // 2 MB en la pila
	buffer[0] = 1;
	printf("%d\n", buffer[0]);
}
*/

// ¿Hay algún problema en este código?
char* GetGreeting()
{
	char t[] = "Hola";
	return t; // Sólo vive en el frame de la función. Al devolverlo, apunta a basura
}

// Escribir una función que reciba una variable int y le asigne un valor.
void ChangeValueRef(int& rValue)
{
	rValue = 5;
}

// Lo mismo, pero recibiendo un puntero a un int.
void ChangeValuePointer(int* pValue)
{
	*pValue = 10;
}

// ¿Cómo haríamos para pasar un puntero y que nos lo rellenen con la dirección de una variable?
void FillPointer(int*& pointer, int& toPoint)
{
	pointer = &toPoint;
}

// ¿Qué dos opciones tenemos? (Opción 2)
void FillDoublePointer(int** pointer, int& toPoint)
{
	*pointer = &toPoint;
}



int main()
{
	printf("\n%d + %d = %d\n\n", 60, 7, Suma(60, 7));

	ImprimirSize();

	printf("\n%d a bool es = %s\n\n", 0, BoolToInt(0) ? "true" : "false");
	printf("%d a bool es = %s\n\n", 1, BoolToInt(1) ? "true" : "false");
	printf("%d a bool es = %s\n\n", 2, BoolToInt(2) ? "true" : "false");
	printf("%d a bool es = %s\n\n", 3, BoolToInt(3) ? "true" : "false");

	printf("%f a int es = %d\n\n", 8.008135f, FloatToInt(8.008135f));

	unsigned int u = 2147483650;
	unsigned int r = SumaUnsignedSigned(u, 17);

	printf("%u (unsigned) + %d (signed) = %u (unsigned)\n\n", u, 17, r);

	unsigned t = RestaUnsigned(r, u);

	printf("%u (unsigned) - %u (unsigned) = %u (unsigned)\n\n", r, u, t);

	printf("%d (int) / %d (int) = %d (int)\n\n", 3618, 54, Division(3618, 54));

	printf("%f (float) / %f (float) = %f (float)\n\n", 3690.7218f, 54.54f, DivisionFloat(3690.7218f, 54.54f));

	printf("%d (int) / %f (float) = %f (float)\n\n", 5, 1.5f, DivisionIntFloat(5, 1.5f));

	printf("%d (signed) - %u (unsigned) = %u (unsigned)\n\n", 10, 42, RestaSignedUnsigned(10, 42));
	printf("%u (unsigned) - %i (signed) = %u (unsigned)\n\n", 10, 42, RestaUnsignedSigned(10, 42));

	if (isnan(ForzarNaN()))
	{
		printf("0 / 0 = NaN\n\n");
	}

	MultiplicarNaN(5.0f);

	int iPrueba = 7;
	printf("iPrueba = %d\n\n", iPrueba);

	int n;








	ImprimirTabla();
	
	int numeros[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 1 };
	printf("La suma es: %d\n\n", Suma(numeros));
	
	Referencias();

	printf("%s (se supone que tiene que decir 'Hola')\n\n", GetGreeting());

	int a = 0;
	printf("Valor de a: %d\n\n", a);
	ChangeValueRef(a);
	printf("Valor de a (despues de cambiarlo por referencia): %d\n\n", a);
	ChangeValuePointer(&a);
	printf("Valor de a (despues de cambiarlo por puntero): %d\n\n", a);

	int* b = nullptr;

	printf("b ahora apunta a %p\n\n", (void*)b);
	FillPointer(b, a);
	printf("b ahora apunta a %p\n\n", (void*)b);
	int c = 750;
	FillDoublePointer(&b, c);
	printf("b ahora apunta a %p\n\n", (void*)b);
	// StackOverflow1(INT_MIN);
	// StackOverflow2();

	return 0;
}
