#include <iostream>

using namespace std;
int main() {
	int iteracionActual = 0;
	int siguiente = 1;
	int iteraciones;

	cout << "Introduce cuantas iteraciones de la serie de fibonacci quieres realizar: ";
	cin >> iteraciones;

	while (iteraciones > 0) {
		int aux = siguiente;
		siguiente = iteracionActual + siguiente;
		iteracionActual = aux;
		iteraciones--;
	}
	cout << iteracionActual;
	return 0;
}