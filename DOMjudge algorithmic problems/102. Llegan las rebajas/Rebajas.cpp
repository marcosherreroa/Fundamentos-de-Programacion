// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using tMatriz = std::vector<std::vector<int>>;

// función que resuelve el problema
void resolver(tMatriz const & matriz, std::vector<int> & precios) {

	for (int i = 0; i < matriz.size(); ++i) {
		precios[i] = matriz[i][0];

		for (int j = 0; j < matriz[0].size(); ++j) {
			if (matriz[i][j] < precios[i]) precios[i] = matriz[i][j];
		}
	}
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int nobjetos = 0, ntiendas = 0;

	std::cin >> nobjetos >> ntiendas;

    if (! std::cin)
        return false;
    
	tMatriz matriz(nobjetos, std::vector<int>(ntiendas));

	for (int i = 0; i < nobjetos; ++i) {
		for (int j = 0; j < ntiendas; ++j) {
			std::cin >> matriz[i][j];
		}
	}

   std::vector<int> precios(nobjetos);
   resolver(matriz, precios);

    // escribir sol
   std::cout << precios[0];
   for (int i = 1; i < nobjetos; ++i) std::cout << ' '<< precios[i];
   std::cout << '\n';

    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
   // #ifndef DOMJUDGE
    // std::ifstream in("datos1.txt");
    // auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
    // #endif 
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
    // #ifndef DOMJUDGE // para dejar todo como estaba al principio
    // std::cin.rdbuf(cinbuf);
     system("PAUSE");
    // #endif
    
    return 0;
}