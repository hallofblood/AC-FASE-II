#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iomanip> // necesario para setw() y setprecision()


using namespace std;

void printResults(int it, double time_C, double time_x86, double time_SSE) {
	
	cout << "|     " << "Prueba " << it+1 << "\t  |"<< setw(9) << time_C << "\t    |"<< setw(9) << time_x86 << "\t      |"<< setw(9) << time_SSE << "        |\n"
		<< "|-----------------|-----------------|-----------------|-----------------|\n";
}

chrono::nanoseconds fibonacci_C(int fibonacciValue) {
	int fibonacciResult_C;			// Stores the resulting value from previous iteration
	int nextValue;					// Stores the next value
	int currentValue;				// Stores the current value
	int sequenceValue;				// Stores the number of Fibonacci numbers to generate

	
	//Bucle que realiza la serie de fibonacci
	auto startTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100000; i++) {
		sequenceValue = fibonacciValue;
		fibonacciResult_C = 0;
		nextValue = 1;
		while (sequenceValue > 0) {
			currentValue = nextValue;
			nextValue = fibonacciResult_C + nextValue;
			fibonacciResult_C = currentValue;
			sequenceValue--;
		}
	}
	auto endTime = std::chrono::high_resolution_clock::now();
	auto totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
	totalTime /= 100000;
	return totalTime;
}

chrono::nanoseconds fibonacci_x86(int fibonacciValue) {
	long fibonacciResult_x86;
	auto startTime = chrono::high_resolution_clock::now();
	for (int i = 0; i < 100000; i++) {
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
	}
	auto endTime = chrono::high_resolution_clock::now();

	auto totalTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
	totalTime /= 100000;
	return totalTime;
}

chrono::nanoseconds fibonacci_SSE(int fibonacciValue) {
	
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

	
	long fibonacciResult_SSE;
	std::chrono::high_resolution_clock::time_point startTime_SSE = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100000; i++) {
		__asm {
			// set up the initial values of the Fibonacci sequence
			mov ecx, fibonacciValue; number of Fibonacci numbers to generate
			mov ebx, 0; current Fibonacci number
			mov edx, 1; next Fibonacci number

			movd xmm1, edx; move from edx to xmm1
			cmp ecx, 1;
			je done; ends program when fibonacciValue equals 1

				movd xmm1, ebx; move from ebx to xmm1 

				cmp ecx, 0;
			je done; ends program when fibonacciValue equals 0

				//load the initial values into XMM0 and XMM1 registers

				movd xmm0, edx; move from edx to xmm0

				// generate the remaining Fibonacci numbers
				bucle :
				paddw xmm0, xmm1; calculate the next Fibonacci number
				movd ebx, xmm0; move from xmm1 to eax, to get the next value
				movd edx, xmm1; move from xmm0 to edx, to get the current value
				xchg edx, ebx; swap current and next Fibonacci numbers
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

	auto totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime_SSE - startTime_SSE);
	totalTime /= 100000;
	return totalTime;
}


int main() {
	int benchmarkOption;
	char repeatBenchmark;

	cout << "#######################################################################\n"
		<< "#           Benchmark reducido - Calculadora de Fibonacci             #\n"
		<< "#######################################################################\n"
		<< ">>Se va a ejecutar el benchmark 3 veces. A continuacion, se mostrara\n"
		<< "una tabla con los resultados obtenidos. Espere a que termine...\n\n"
		<< ">>Los tiempos de la tabla se expresan en nanosegundos (ns)\n\n";

	int fibonacciValue = 24;

	cout << "|#################|#################|#################|#################|\n"
		<< "|   Num. prueba   |   Tiempo C++    |   Tiempo x86    |   Tiempo SSE    |\n"
		<< "|#################|#################|#################|#################|\n";

	//Variables para almacenar los valores de los 3 tiempos y calcular una media para cada lenguaje
	double contador_C = 0;
	double contador_x86 = 0;
	double contador_SSE = 0;

	for (int i = 0; i < 3; i++) {
		double* time_C = new double;
		double* time_x86 = new double;
		double* time_SSE = new double;

		*time_C = fibonacci_C(fibonacciValue).count();
		*time_x86 = fibonacci_x86(fibonacciValue).count();
		*time_SSE = fibonacci_SSE(fibonacciValue).count();
		printResults(i, *time_C, *time_x86, *time_SSE);
			
		contador_C += *time_C;
		contador_x86 += *time_x86;
		contador_SSE += *time_SSE;

		delete(time_C);
		delete(time_x86);
		delete(time_SSE);

	}

	contador_C = contador_C / 3;
	contador_x86 = contador_x86 / 3;
	contador_SSE = contador_SSE / 3;

	cout << "|#################|#################|#################|#################|\n"
		<< "|     " << "Media" << "\t  |"
		<< setw(10) << contador_C << "       |"
		<< setw(10) << contador_x86 << "       |"
		<< setw(10) << contador_SSE << "       |\n"
		<< "|-----------------|-----------------|-----------------|-----------------|\n\n";
	
	cout << ">>En cada prueba para cada lenguaje se realiza 100.000 veces fibonacci y\n"
		<< "se divide el resultado entre 100.000 para mayor precision\n\n"
		<< "Pulse ENTER para cerrar\n"
		<< "> ";

	int fin = getchar(); //se guarda el valor en fin para evitar el warning "se ignora el valor devuelto"

	return 0;
}