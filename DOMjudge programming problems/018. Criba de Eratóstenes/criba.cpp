// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <math.h>


// función que resuelve el problema
std::vector<int> criba(int  n) {
	std::vector<int> primos;
	std::vector<bool> primoono(n+1, true);
	
	for (int i = 2; i <= sqrt(n); ++i){
		if (primoono[i]){
			for (int j = 2; i*j <= n; ++j){
				primoono[i*j] = false;
			}
		}
	}
	for (int i = 2; i <= n; ++i){
		if (primoono[i]) primos.push_back(i);
	}

	return primos;
}



int main() {
	int n = 0;
	std::cin >> n;

	std::vector<int>primos= criba(n);

	for (int i = 0; i < primos.size(); ++i){
		std::cout << primos[i] << '\n';
	}

	system("PAUSE");
    return 0;
}