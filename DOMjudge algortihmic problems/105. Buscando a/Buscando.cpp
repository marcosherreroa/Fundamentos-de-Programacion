// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

struct tPosicion {
	int fila;
	int columna;
};

using tMatriz = std::vector<std::vector<int>>;

bool comprobarPosicion(tMatriz const & imagen, tMatriz const & patron, tPosicion const & posicion) {
	bool OK = true;

	for (int i = 0; OK && i < patron.size(); ++i) {
		for (int j = 0; OK && j < patron[0].size(); ++j) {
			if (patron[i][j] != imagen[posicion.fila + i][posicion.columna + j]) OK = false;
		}
	}

	return OK;
}

// función que resuelve el problema
void resolver(tMatriz const & imagen, tMatriz const & patron, tPosicion & sol) {
	sol.fila = -1; sol.columna = -1;
	tPosicion posicion; bool encontrado = false;

	

	for (int i = 0; !encontrado && i < imagen.size() - patron.size() + 1; ++i) {
		posicion.fila = i;
		for (int j = 0; !encontrado && j < imagen[0].size()- patron[0].size() + 1; ++j) {
			posicion.columna = j;

			if (comprobarPosicion(imagen, patron, posicion)) {
				sol.fila = i;
				sol.columna = j;
				encontrado = true;
			}
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int filasim = 0, columnasim = 0;
	std::cin >> filasim >> columnasim;

    if (! std::cin)
        return false;

	tMatriz imagen(filasim, std::vector<int>(columnasim));
	for (int i = 0; i < filasim; ++i) {
		for (int j = 0; j < columnasim; ++j) {
			std::cin >> imagen[i][j];
		}
	}

	int filaspat = 0, columnaspat = 0;
	std::cin >> filaspat >> columnaspat;

	tMatriz patron(filaspat, std::vector<int>(columnaspat));
	for (int i = 0; i < filaspat; ++i) {
		for (int j = 0; j < columnaspat; ++j) {
			std::cin >> patron[i][j];
		}
	}

	tPosicion sol;
    resolver(imagen, patron, sol);
    
    // escribir sol
	if (sol.fila == -1 || sol.columna == -1) std::cout << "NO\n";
	else std::cout << sol.fila <<' '<< sol.columna<<'\n';
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    //#ifndef DOMJUDGE
    // std::ifstream in("datos1.txt");
   //  auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
   //  #endif 
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
   //  #ifndef DOMJUDGE // para dejar todo como estaba al principio
    // std::cin.rdbuf(cinbuf);
     system("PAUSE");
   //  #endif
    
    return 0;
}