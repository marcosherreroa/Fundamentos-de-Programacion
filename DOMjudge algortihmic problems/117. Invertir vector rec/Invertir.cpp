// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>


// función que resuelve el problema
void invertir(std::vector<int> & v, int ini, int fin) {
	if (ini < fin) {
		std::swap(v[ini], v[fin - 1]);
		invertir(v, ini + 1, fin - 1);
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int n;
	std::cin >> n;

    if (! std::cin)
        return false;

	std::vector<int> v (n);
	for (int i = 0; i < n; ++i) std::cin >> v[i];

	invertir(v, 0, n);

    // escribir sol
	for (int i = 0; i < n; ++i) std::cout << v[i]<<' ';
	std::cout << '\n';

    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
    // std::ifstream in("datos1.txt");
     //auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     //std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}