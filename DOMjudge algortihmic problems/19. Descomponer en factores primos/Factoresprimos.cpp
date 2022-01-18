// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>


// función que resuelve el problema
std::vector<int> criba(int  n) {
	std::vector<int> primos;
	std::vector<bool> primoono(n + 1, true);

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
std::vector<int> factores(int numero, std::vector<int> const & primos) {
	std::vector<int> factores;
	for (int i = 0; i < numero; ++i){
		while (numero % primos[i] == 0){
			factores.push_back(primos[i]);
			numero /= primos[i];
		}
	}

	return factores;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso(std::vector<int> const & primos) {
    // leer los datos de la entrada
	int numero = 0;
	std::cin >> numero;
    
	if (numero == 0)
        return false;

    std::vector<int> sol = factores(numero, primos);
    // escribir sol

	std::cout << sol[0];
	for (int i = 1; i < sol.size(); ++i){
		std::cout <<' '<< sol[i];
	}
	std::cout << '\n';

	return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     //std::ifstream in("datos.txt");
     //auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
	std::vector<int>primos = criba(100000);
    
    while (resuelveCaso(primos))
        ;
	system("PAUSE");

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     //std::cin.rdbuf(cinbuf);
     #endif
    
    return 0;
}