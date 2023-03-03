#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

int main() {
	char otra;
	do{
		int n;

        cout << "Introduce cuantas iteraciones de la serie de Fibonacci quieres hacer entre [0/46]: ";

        do {
            cin >> n;
            if (n < 0 || n > 46) {
                cout << "Numero de iteracion invalido, vuelve a introducirlo: ";
            }
        } while (n < 0 || n > 46);


		long result;
		auto tInic = std::chrono::high_resolution_clock::now();
        __asm {
            mov ecx, n; carga n en ecx
            mov eax, 1; F0 = 1
           
            cmp ecx, 1; verifica si n es 1
            je done; si es 1, salta a done

            mov eax, 0; F0 = 0

            cmp ecx, 0; verifica si n es 0
            je done; si es 0, salta a done

            mov ebx, 1; F1 = 1

            loop_start :
                add eax, ebx; F_n = F_(n - 1) + F_(n - 2)
                xchg eax, ebx; intercambia eax y ebx
                loop loop_start; repite hasta que n sea 0

            done:
                mov result, eax; guarda el resultado en la variable result
        }

		auto tEnd = std::chrono::high_resolution_clock::now();

        auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(tEnd - tInic);

        cout << endl << "Restultado de la serie de Fibonacci con " << n << " iteraciones: " << result << endl;
        cout << "Tiempo de ejecución: " << time.count() << " nanosegundos" << endl << endl;

		cout << "Indica si quieres realizar otro calculo(s/n): ";

		cin >> otra;

	}while(otra != 'n');


	return 0;
}