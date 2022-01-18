// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


int pares1(std::vector<int> const & v, int ini, int fin) {
	if (ini >= fin) return 0;
	else if (v[ini] % 2 == 0) return 1 + pares1(v, ini + 1, fin);
	else return pares1(v, ini + 1, fin);
}

int pares2(std::vector<int> const & v, int ini, int fin) {
	if (ini >= fin) return 0;
	else if (v[fin-1] % 2 == 0) return 1 + pares2(v, ini, fin-1);
	else return pares2(v, ini, fin-1);
}

int pares3(std::vector<int> const & v, int ini, int fin) {
	int mitad = (ini + fin - 1) / 2;

	if (ini >= fin) return 0;
	else if (v[mitad] % 2 == 0) return 1 + pares3(v, ini, mitad) + pares3(v, mitad + 1, fin);
	else return pares3(v, ini, mitad) + pares3(v, mitad + 1, fin);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int n;
	std::cin >> n;

    if (! std::cin)
        return false;
    
	std::vector<int> v(n);
	for (int i = 0; i < n; ++i) std::cin >> v[i];

	std::cout << pares1(v, 0, n) << '\n' << pares2(v, 0, n) << '\n' << pares3(v, 0, n) << '\n';
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     //std::ifstream in("datos1.txt");
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