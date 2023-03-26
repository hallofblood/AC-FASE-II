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
	long fibonacciResult_C;			// Stores the resulting value from previous iteration
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
			mov ecx, fibonacciValue
			mov eax, 1				//current Fibonacci number

			cmp ecx, 1
			je done

			mov eax, 0

			cmp ecx, 0
			je done

			mov ebx, 1				//next fibonacciValue

			loop_start :
				add eax, ebx		//F_n = F_(n - 1) + F_(n - 2)
				xchg eax, ebx		//swap currentand next Fibonacci numbers
				loop loop_start		//if not 0, loop again

			done :
				mov fibonacciResult_x86, eax
		}
	}
	auto endTime = chrono::high_resolution_clock::now();

	auto totalTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
	totalTime /= 100000;
	return totalTime;
}

chrono::nanoseconds fibonacci_SSE(int fibonacciValue) {
	long fibonacciResult_SSE;
	std::chrono::high_resolution_clock::time_point startTime_SSE = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100000; i++) {
		__asm {
			// set up the initial values of the Fibonacci sequence
			mov ecx, fibonacciValue
			mov ebx, 0					//current Fibonacci number
			mov edx, 1					//next Fibonacci number

			movd xmm1, edx
			cmp ecx, 1
			je done

			movd xmm1, ebx

			cmp ecx, 0;
			je done

			//load the initial values into XMM0 and XMM1 registers

			movd xmm0, edx

			// generate the remaining Fibonacci numbers
			bucle :
				paddw xmm0, xmm1		//calculate the next Fibonacci number
				movd ebx, xmm0
				movd edx, xmm1
				xchg edx, ebx			//swap current and next Fibonacci numbers
				movd xmm0, ebx
				movd xmm1, edx
				sub ecx, 1				//decrement counter
				cmp ecx, 0
				jne bucle				//if not zero, loop again

			// Exit program
			done :
				movd fibonacciResult_SSE, xmm1
				emms
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
		<< "Byte Bandits - Arquitectura de los Computadores - Universidad de Alicante\n"
		<< "Curso 2022/23\n\n"
		<< "Pulse ENTER para cerrar\n"
		<< "> ";

	int fin = getchar(); //se guarda el valor en fin para evitar el warning "se ignora el valor devuelto"

	return 0;
}