#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

int main() {
	char option;
	do{
		int fibonacciValue;

        cout << "Introduce cuantas iteraciones de la serie de Fibonacci quieres hacer entre [0/24]: ";

        do {
            cin >> fibonacciValue;
            if (fibonacciValue < 0 || fibonacciValue > 46) {
                cout << "Numero de iteracion invalido, vuelve a introducirlo: ";
            }
        } while (fibonacciValue < 0 || fibonacciValue > 46);


		long fibonacciResult;
		auto timeStart = std::chrono::high_resolution_clock::now();

        __asm {
            // set up the initial values of the Fibonacci sequence
            mov ecx, fibonacciValue; number of Fibonacci numbers to generate
            mov ebx, 0; current Fibonacci number
            mov edx, 1; next Fibonacci number

            movd xmm1, edx; from edx to xmm1
            cmp ecx, 1; 
            je done; ends program when fibonacciValue equals 1

            movd xmm1, ebx; move from edx to xmm1
            
            cmp ecx, 0;  
            je done; ends program when fibonacciValue equals 0

            //load the initial values into XMM0 and XMM1 registers

            movd xmm0, edx; move from edx to xmm0
            
            // generate the remaining Fibonacci numbers
            bucle:
                paddw xmm0, xmm1; calculate the next Fibonacci number
                movd ebx, xmm0; move from xmm1 to eax, to get the next value
                movd edx, xmm1; move from xmm0 to edx, to get the current value
                xchg edx, ebx; swap current and next Fibonacci numbers
                movd xmm0, ebx; move from eax to xmm1, to update the next value
                movd xmm1, edx; move from eax to xmm1, to update the next value
                sub ecx, 1; decrement counter
                cmp ecx, 0; compare counter with zero
                jne bucle; if not zero, loop again

            //exit program
            done:
                movd fibonacciResult, xmm1;
                emms; clear MMX registers
        }

		auto timeEnd = std::chrono::high_resolution_clock::now();

        auto timeTotal = std::chrono::duration_cast<std::chrono::nanoseconds>(timeEnd - timeStart);

        cout << endl << "Restultado de la serie de Fibonacci con " << fibonacciValue << " iteraciones: " << fibonacciResult << endl;
        cout << "Tiempo de ejecucion: " << timeTotal.count() << " nanosegundos" << endl << endl;

        cout << "Indica si quieres realizar otro calculo(s/n): ";

        do {
            cin >> option;

            if (option != 's' && option != 'n') {
                cout << "Opcion no valida, vuelve a introducirlo: ";
            }

        } while (option != 's' && option != 'n');

	}while(option != 'n');


	return 0;
}
