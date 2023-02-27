#include <iostream>
#include <time.h>
using namespace std;
int main() {
	char opcion;
	do {
		long long iteracionActual = 0;		//Almacena el valor en la primera iteracion con el valor anterior
		long long siguiente = 1;				//Almacena el valor de la siguiente operacion de sumar los valores n + (n-1)
		long long aux;					//Auxiliar para intercambiar los valores de iteración actual y siguiente
		long long iteraciones;		//Iteraciones a realizar
		clock_t tiempoInicial = 0;	//Almaceno el tiempo inicial antes de ejecutar el algoritmo
		clock_t tiempoFinal = 0;		//Almacenan el tiempo final de ejecutar mi algoritmo
		
		//Compruebo si el numero de iteraciones es valido
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

		//Bucle que realiza la serie de fibonacci
		tiempoInicial = clock();
		while (iteraciones > 0) {
			aux = siguiente;
			siguiente = iteracionActual + siguiente;
			iteracionActual = aux;
			iteraciones--;
		}
		tiempoFinal = clock();

		cout << iteracionActual <<endl;
		cout << 1000.0 * (tiempoFinal - tiempoInicial)/CLOCKS_PER_SEC << endl;
		cout << "Quiere continuar? (s/n): ";
		cin >> opcion;
	} while (opcion != 'n');
	return 0;
}