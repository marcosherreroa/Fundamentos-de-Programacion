
// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>

struct tPosicion {
	int fila;
	int columna;
};

using tMatriz = std::vector<std::vector<int>>;

// función que resuelve el problema
int alturaMaxima(tMatriz const & cuadricula, tPosicion & posicion) {
	int alturaMaxima = cuadricula[0][0];
	posicion.fila = 0; posicion.columna = 0;

	for (int i = 0; i < cuadricula.size(); ++i) {
		for (int j = 0; j < cuadricula[0].size(); ++j) {
			if (cuadricula[i][j] > alturaMaxima) {
				alturaMaxima = cuadricula[i][j];
				posicion.fila = i;
				posicion.columna = j;
			}
		}
	}

	return alturaMaxima;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int nfilas = 0, ncolumnas = 0;
	std::cin >> nfilas >> ncolumnas;

    if (! std::cin)
        return false;
    

	tMatriz cuadricula(nfilas, std::vector<int>(ncolumnas));
	
	for (int i = 0; i < nfilas; ++i) {
		for (int j = 0; j < ncolumnas; ++j) {
			std::cin >> cuadricula[i][j];
		}
	}

	tPosicion posicion;

	int altura = alturaMaxima(cuadricula, posicion);
	// escribir sol
	std::cout << altura <<' '<< posicion.fila <<' '<< posicion.columna << '\n';

    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    //#ifndef DOMJUDGE
     //std::ifstream in("datos1.txt");
    // auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
    // #endif 
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
  //   #ifndef DOMJUDGE // para dejar todo como estaba al principio
   //  std::cin.rdbuf(cinbuf);
     system("PAUSE");
   //  #endif
    
    return 0;
}