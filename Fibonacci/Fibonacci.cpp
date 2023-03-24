#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

void printResults(string language, int fibonacciValue, long fibonacciResult, chrono::nanoseconds totalTime) {
	cout << "Resultado de la serie de Fibonacci de " << fibonacciValue
		<< " iteraciones, utilizando el benchmark creado con " << language << ":\n" << fibonacciResult << endl
		<< "Tiempo de ejecucion (en nanosegundos): \n"
		<< totalTime.count() << endl << endl;
}

void fibonacci_C(int fibonacciValue) {
	int fibonacciResult_C = 0;		// Stores the resulting value from previous iteration
	int nextValue = 1;				// Stores the next value
	int currentValue;				// Stores the current value
	int sequenceValue;				// Stores the number of Fibonacci numbers to generate

	cout << "\n";
	sequenceValue = fibonacciValue;
	//Bucle que realiza la serie de fibonacci
	auto startTime = std::chrono::high_resolution_clock::now();
	while (sequenceValue > 0) {
		currentValue = nextValue;
		nextValue = fibonacciResult_C + nextValue;
		fibonacciResult_C = currentValue;
		sequenceValue--;
	}
	auto endTime = std::chrono::high_resolution_clock::now();
	auto totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
	printResults("C++", fibonacciValue, fibonacciResult_C, totalTime);
}

void fibonacci_x86(int fibonacciValue) {
	long fibonacciResult_x86;
	auto startTime = chrono::high_resolution_clock::now();
	__asm {
		mov ecx, fibonacciValue; number of Fibonacci numbers to generate
		mov eax, 1; current Fibonacci number

		cmp ecx, 1;
		je done; ends program when fibonacciValue equals 1

			mov eax, 0;

		cmp ecx, 0;
		je done; ends program when fibonacciValue equals 0

			mov ebx, 1; next fibonacciValue

			loop_start :
		add eax, ebx; F_n = F_(n - 1) + F_(n - 2)
			xchg eax, ebx; swap currentand next Fibonacci numbers
			loop loop_start; if not 0, loop again

			done :
		mov fibonacciResult_x86, eax; stores the Fibonacci result
	}

	auto endTime = chrono::high_resolution_clock::now();

	auto totalTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
	printResults("x86", fibonacciValue, fibonacciResult_x86, totalTime);
}

double fibonacci_SSE(int fibonacciValue) {

	/*
	float t1 = 0, t2 = 1, nextTerm = 0;
	float* t1Aux;
	float* t2Aux;
	float* nextTermAux;
	t1Aux = &t1;
	t2Aux = &t2;
	nextTermAux = &nextTerm;
	std::chrono::high_resolution_clock::time_point startTime_SSE = std::chrono::high_resolution_clock::now();
	for (int j = 0; j < 100000; j++) {
		float t1 = 0, t2 = 1, nextTerm = 0;
		for (int i = 1; i <= fibonacciValue; i++) {
			_asm {
				mov esi, t1Aux
				mov edi, t2Aux
				mov ebx, nextTermAux
				movss xmm0, [esi]
				movss xmm1, [edi]
				movss xmm2, [ebx]
				addss xmm2, xmm0
				addss xmm2, xmm1
				movss t1, xmm1
				movss t2, xmm2
			}
		}
	}
	*/


	std::chrono::high_resolution_clock::time_point startTime_SSE = std::chrono::high_resolution_clock::now();
	long fibonacciResult_SSE;
	for (int i = 0; i < 100000; i++) {

		__asm {
			// set up the initial values of the Fibonacci sequence
			mov ecx, fibonacciValue; number of Fibonacci numbers to generate
			mov ebx, 0; current Fibonacci number
			mov edx, 1; next Fibonacci number

			movd xmm1, edx; move from edx to xmm1
			cmp ecx, 1;
			je done; ends program when fibonacciValue equals 1

				movd xmm1, ebx; move from edx to xmm1

				cmp ecx, 0;
			je done; ends program when fibonacciValue equals 0

				//load the initial values into XMM0 and XMM1 registers

				movd xmm0, edx; move from ecx to xmm0

				// generate the remaining Fibonacci numbers
				bucle :
			paddw xmm0, xmm1; calculate the next Fibonacci number
				movd ebx, xmm0; move from xmm1 to eax, to get the next value
				movd edx, xmm1; move from xmm0 to edx, to get the current value
				xchg edx, ebx; swap currentand next Fibonacci numbers
				movd xmm0, ebx; move from eax to xmm1, to update the next value
				movd xmm1, edx; move from eax to xmm1, to update the next value
				sub ecx, 1; decrement counter
				cmp ecx, 0; compare counter with zero
				jne bucle; if not zero, loop again

				// Exit program
				done :
			movd fibonacciResult_SSE, xmm1; stores the Fibonacci result
				emms; clear MMX registers
		}
	}


	std::chrono::high_resolution_clock::time_point endTime_SSE = std::chrono::high_resolution_clock::now();

	auto totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>((endTime_SSE - startTime_SSE) / 100000);
	printResults("SSE", fibonacciValue, fibonacciResult_SSE, totalTime);
}


int main() {
	int benchmarkOption;
	char repeatBenchmark;

	cout << "Bienvenido a la calculadora de Fibonacci.\n"
		<< "1. Fibonacci en C++ \n"
		<< "2. Fibonacci en x86 \n"
		<< "3. Fibonacci en SSE \n"
		<< "4. Las tres versiones \n"
		<< "Seleccione una opcion: ";
	do {
		cin >> benchmarkOption;

		if (benchmarkOption < 1 || benchmarkOption > 4) {
			cout << "Opcion no valida, vuelve a introducirla: ";
		}

	} while (benchmarkOption < 1 || benchmarkOption > 4);
	do {
		int fibonacciValue;

		cout << "Introduce cuantas iteraciones de la serie de Fibonacci quieres hacer entre [0/24]: ";

		do {
			cin >> fibonacciValue;
			if (fibonacciValue < 0 || fibonacciValue > 24) {
				cout << "Numero de iteraciones invalido, vuelve a introducirlo: ";
			}
		} while (fibonacciValue < 0 || fibonacciValue > 24);


		switch (benchmarkOption) {
		case 1:
			fibonacci_C(fibonacciValue);
			break;

		case 2:
			fibonacci_x86(fibonacciValue);
			break;

		case 3:
			fibonacci_SSE(fibonacciValue);
			break;
		case 4:
			fibonacci_C(fibonacciValue);
			fibonacci_x86(fibonacciValue);
			fibonacci_SSE(fibonacciValue);
			break;
		}

		cout << "Indique si quiere probar con otro valor (s/n): ";

		do {
			cin >> repeatBenchmark;

			if (repeatBenchmark != 's' && repeatBenchmark != 'n') {
				cout << "Opcion no valida, vuelve a introducirla: ";
			}

		} while (repeatBenchmark != 's' && repeatBenchmark != 'n');

	} while (repeatBenchmark != 'n');

	return 0;
}