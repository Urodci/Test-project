// RSASS.cpp: определяет точку входа для консольного приложения.
//:):(:/:\А (-_-(-_(-(O_o)-)_-)-_-)

#include "stdafx.h"
#include <iostream>
#include <string>
#include "math.h"
#include "time.h"

long int NOD(long int n1, long int n2)
{
	long int div;

	while (true)

	{
		if (n1 == n2)
			return n1;

		int d = n1 - n2;
		if (d < 0)
			d = -d;

		n1 = n2;
		n2 = d;
	}

	return div;
}


long int GetE(long int pfi) // Получаем открытую экспоненту (первое взаимнопростое от 2 до pfi-1)
{
	long int low, high, i, flag;
	low = 2;
	high = pfi;
	while (low < high) // Находим простые числа от low до high-1
	{
		flag = 0; // если 0, то оно простое

		for (i = 2; i <= low / 2; ++i) // Проверяем половину
		{
			if (low % i == 0) // Если нет остатка. то оно делится на что-то, а значет непростое
			{
				flag = 1;
				break;
			}
		}

		if (flag == 0) { // Если оно простое, то проверяем, что оно взаимнопростое с pfi
			if (NOD(pfi, low) == 1)
			{
				return low;
			}
		}

		++low;
	}

	return 1;
}

long int gcdex(long int a, long int b, long int &x, long int &y) { // Решаем Диофантово уравнение a*x + b*y = 1
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	long int x1, y1;
	long int d1 = gcdex(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return d1;
}

long int ReverseElement(long int a, long int N, long int &result) { // Находим обратный по модулю элемент в кольце вычетов
	long int x, y, d;
	d = gcdex(a, N, x, y);
	
	if (d != 1) 
	{
		return 1;
	}
	else
	{
		result = (x + N) % N; // Для кольца вычетов
		return 0;
	}
}

long int* getPrimeNumbers(long int low, long int high, long  int &count)
{
	
	long int *p = NULL;// = (int*)malloc(sizeof(int) * 0);
	long int i;
	count = 0;
	while (low < high)
	{
		bool isPrime = true;
		for (i = 2; i <= low / 2; ++i) // Проверяем половину
		{
			if (low % i == 0) 
			{
				isPrime = false;
				break;
			}
		}

		if (isPrime) {
			count++;
			p = (long int*)realloc(p, sizeof(long int)*count);
			p[count - 1] = low;
		}

		++low;
	}

	return p;
}

long int getFerma(long int max) {
	if (max > 65537)
	{
		return 65537;
	}
	else if (max > 257)
	{
		return 257;
	}
	else if (max > 5)
	{
		return 5;
	}
	else
		return 3;
}


int main()
{
	srand(time(NULL));
		
	long int countPrimeNumbers = 0;
	long int * primeNumbers = getPrimeNumbers(30000,40000, countPrimeNumbers);
	if (countPrimeNumbers < 2)
	{
		printf("Error. Wrong prime number interval");
	}

	long int p_ind = rand() % countPrimeNumbers;
	long int q_ind = 0;
	while ((q_ind = rand() % countPrimeNumbers) == p_ind);

	long int p = primeNumbers[p_ind];
	long int q = primeNumbers[q_ind];

	long int n = p*q;
	long int pfi = (p - 1)*(q - 1);

	printf("p=%ld \nq=%ld \nn=%ld \npfi=%ld\n countPrimeNumbers=%ld\n", p,q,n, pfi, countPrimeNumbers);

	//long int e = GetE(pfi);
	long int e = getFerma(pfi);
	printf("Open key: {%ld, %ld}\n", e, n);

	long int d = 0;

	if (ReverseElement(e, pfi, d) == 0)
	{
		printf("Secret key: {%ld, %ld}\n", d, n);
	}
	
	getchar();;
	getchar();;
	return 0;
}

//самопроизвольная генерация простых чисел
//алгоритмы с большими простыми числами