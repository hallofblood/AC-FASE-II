#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>


using namespace std;

void fibonacciC() {

}

void fibonaccix86() {

}

void fibonacciSSE() {

}


int main() {
	char seguir;
	do {

		int opc;
		cout << "Bienvenido a la calculadore de Fibonacci. \n"
			<< "1. Fibonacci en C++ \n"
			<< "2. Fibonacci en x86 \n"
			<< "3. Fibonacci en SSE \n"
			<< "Seleccione una opcion: ";
		do {
			cin >> opc;

			if (opc < 1 || opc > 3) {
				cout << "Opcion no valida, vuelve a introducirla: ";
			}

		} while (opc < 1 || opc > 3);

		switch (opc) {
		case 1: fibonacciC();
			break;

		case 2: fibonaccix86();
			break;

		case 3: fibonacciSSE();
		}

		cout << "Indique si quiere probar otra forma(s/n): ";

		do {
			cin >> seguir;

			if (seguir != 's' && seguir != 'n') {
				cout << "Opcion no valida, vuelve a introducirla: ";
			}

		} while (seguir != 's' && seguir != 'n');

	} while (seguir != 'n');

	return 0;
}