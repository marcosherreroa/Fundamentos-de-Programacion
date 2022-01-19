// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using tMatriz = std::vector<std::vector<int>>;

// función que resuelve el problema
bool pSilla(tMatriz const & matriz) {
	int minfila = 0, maxfila = 0;
	bool encontrado = false;

	for (int i = 0; !encontrado && i < matriz.size(); ++i) {
		minfila = matriz[i][0];
		maxfila = matriz[i][0];

		for (int j = 0; j < matriz[0].size(); ++j) {
			if (matriz[i][j] < minfila) minfila = matriz[i][j];
			else if (matriz[i][j] > maxfila) maxfila = matriz[i][j];
		}

		for (int j = 0; !encontrado && j < matriz[0].size(); ++j) {

			if (matriz[i][j] == minfila && matriz[i][j] == maxfila) {
				bool OK1 = true, OK2 = true;
				for (int k = 0; (OK1 || OK2) && k < matriz.size(); ++k) {
					if (matriz[i][j] < matriz[k][j]) OK1 = false;
					if (matriz[i][j] > matriz[k][j]) OK2 = false;
				}
				if (OK1 || OK2) encontrado = true;
			}

			else if (matriz[i][j] == minfila) {
				bool OK = true;
				for (int k = 0; OK && k < matriz.size(); ++k) {
					if (matriz[i][j] < matriz[k][j]) OK = false;
				
				}
				if (OK) encontrado = true;
			}

			else if (matriz[i][j] == maxfila) {
				bool OK = true;
				for (int k = 0; OK && k < matriz.size(); ++k) {
					if (matriz[i][j] > matriz[k][j]) OK = false;
				}
				if (OK) encontrado = true;
			}
		}
	}
	return encontrado;
}
    
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int nfilas = 0, ncolumnas = 0;
	std::cin >> nfilas >> ncolumnas;

	if (nfilas == 0 || ncolumnas == 0)
        return false;

	tMatriz matriz(nfilas, std::vector<int>(ncolumnas));

	for (int i = 0; i < nfilas; ++i) {
		for (int j = 0; j < ncolumnas; ++j) {
			std::cin >> matriz[i][j];
		}
	}
    
    // escribir sol

	if (pSilla(matriz)) std::cout << "SI\n";
	else std::cout << "NO\n";

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
    // std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}