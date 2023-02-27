#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main() {
	char otra;
	do{
		int n;

		cout << "Introduce cuantas iteraciones de la serie de Fibonacci quieres hacer: ";
		cin >> n;

		long result;
		auto tInic = clock();
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

		auto tEnd = clock();

		cout << (tEnd - tInic)*1000 << ", " << result << endl;

		cout << "Indica si quieres realizar otro calculo(s/n): ";

		cin >> otra;

	}while(otra != 'n');


	return 0;
}