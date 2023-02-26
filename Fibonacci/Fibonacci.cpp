#include <iostream>
#include <time.h>
using namespace std;
int main() {
	char opcion;
	do {
		long iteracionActual = 0;
		long siguiente = 1;
		long aux;

		long iteraciones;

		bool valido = false;
		while (valido == false) {
			cout << "Introduce cuantas iteraciones de la serie de fibonacci quieres realizar: ";
			cin >> iteraciones;
			if (iteraciones <= 0) {
				cout << "Numero de iteraciones no valido" << endl;
			}
			else {
				valido = true;
			}
		}
		auto tiempoInicial = clock();
		while (iteraciones > 0) {
			aux = siguiente;
			siguiente = iteracionActual + siguiente;
			iteracionActual = aux;
			iteraciones--;
		}
		auto tiempoFinal = clock();
		cout << iteracionActual <<endl;
		cout << tiempoFinal  << endl;

		cout << "Quiere continuar? (s/n): ";
		cin >> opcion;
	} while (opcion != 'n');
	return 0;
}