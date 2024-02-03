#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;

//Vamos a ver que hace si lo edito.
int main() {
	char opcion;
	do {
		int iteracionActual = 0;		//Almacena el valor en la primera iteracion con el valor anterior
		int siguiente = 1;				//Almacena el valor de la siguiente operacion de sumar los valores n + (n-1)
		int aux;					//Auxiliar para intercambiar los valores de iteraci�n actual y siguiente
		int iteraciones;		//Iteraciones a realizar
		int numIteraciones;

		//Compruebo si el numero de iteraciones es valido
		cout << "Introduce cuantas iteraciones de la serie de Fibonacci quieres hacer [0/46]: ";
		do {
			cin >> iteraciones;
			if (iteraciones < 0 || iteraciones > 46) {
				cout << "Numero de iteracion invalido, vuelve a introducirlo: ";
			}
		} while (iteraciones < 0 || iteraciones > 46);

		cout << "\n";
		numIteraciones = iteraciones;
		//Bucle que realiza la serie de fibonacci
		auto tiempoInicial = std::chrono::high_resolution_clock::now();
		while (iteraciones > 0) {
			aux = siguiente;
			siguiente = iteracionActual + siguiente;
			iteracionActual = aux;
			iteraciones--;
		}
		auto tiempoFinal = std::chrono::high_resolution_clock::now();
		cout << "Resultado de la serie de Fibonacci con "<<numIteraciones<<" iteraciones: " << iteracionActual << endl;
		auto duracion = std::chrono::duration_cast<std::chrono::nanoseconds>(tiempoFinal - tiempoInicial);
		cout <<"Tiempo de ejecucion: " << duracion.count() <<" nanosegundos" << endl<<endl;
		do {
			cout << "Indica si quieres realizar otro calculo(s/n): ";
			cin >> opcion;
			if (opcion != 'n' && opcion != 's') {
				cout << "Opcion no valida" << endl;
			}
		} while (opcion != 'n' && opcion != 's');
	} while (opcion != 'n');
	return 0;
}