// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using tnum = unsigned long long int;
// función que resuelve el problema
std::vector<tnum> resolver(std::vector<tnum>const& conj1, std::vector<tnum> const& conj2 ) {
	std::vector<tnum> sol;

	tnum i = 0, j = 0;
	while (i < conj1.size() && j < conj2.size()){
		if (conj1[i] == conj2[j]){
			sol.push_back(conj1[i]);
			++i; ++j;
		}
		else if (conj1[i] < conj2[j]) ++i;
		else ++j;
	}
	return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	std::vector<tnum> conj1, conj2;
	tnum elemento = 0;

	std::cin>> elemento;

	while (elemento != 0){
		conj1.push_back(elemento);
		std::cin >> elemento;
	}

	std::cin >> elemento;

	while (elemento != 0){
		conj2.push_back(elemento);
		std::cin >> elemento;
	}

	sort(conj1.begin(), conj1.end());
	sort(conj2.begin(), conj2.end());

    std::vector<tnum> sol= resolver(conj1, conj2);
    // escribir sol

	if (sol.size() != 0)std::cout << sol[0];

	for (tnum i = 1; i < sol.size(); ++i) std::cout <<' '<< sol[i];
	
	std::cout << '\n';
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
//     std::ifstream in("datos1.txt");
//     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
//     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}