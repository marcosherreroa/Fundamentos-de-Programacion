// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

struct tPosicion {
	int i;
	int j;
};

using tMatriz = std::vector<std::vector<int>>;

// función que resuelve el problema
int gradoInteres(tMatriz const & matriz, tPosicion const & posicion) {
	int grado = 0;
	for (int j = 0; j < matriz[0].size(); ++j) grado += matriz[posicion.i][j];
	for (int i = 0; i < matriz.size(); ++i) grado += matriz[i][posicion.j];
	
	
	int i = posicion.i, j = posicion.j;
	while (0 <= i && i < matriz.size() && 0 <= j && j < matriz[0].size()) {
		grado -= matriz[i][j];
		--i;
		--j;
	}

	i = posicion.i; j = posicion.j;
	while (0 <= i && i < matriz.size() && 0 <= j && j < matriz[0].size()) {
		grado -= matriz[i][j];
		++i;
		++j;
	}
	
	i = posicion.i; j = posicion.j;
	while (0 <= i && i < matriz.size() && 0 <= j && j < matriz[0].size()) {
		grado -= matriz[i][j];
		++i;
		--j;
	}
	
	i = posicion.i; j = posicion.j;
	while (0 <= i && i < matriz.size() && 0 <= j && j < matriz[0].size()) {
		grado -= matriz[i][j];
		--i;
		++j;
	}
	
	grado += 2 * matriz[posicion.i][posicion.j];
	
	return grado;
}

void ordenarVector(std::vector<int> & vector) {
	int minpos = 0, maxpos = vector.size()-1;
	int minimo, maximo;
	int mini = 0, maxi = 0;

	for (int n = 0; n < vector.size() / 2; ++n) {
		maximo = vector[minpos]; minimo = vector[minpos];
		mini = minpos; maxi = minpos;

		for (int i = minpos; i <= maxpos; ++i) {
			if (vector[i] < minimo) {
				minimo = vector[i];
				mini = i; 
			}
			else if(vector[i] > maximo){
				maximo = vector[i];
				maxi = i;
			}
		}
		
		if (mini == maxpos && maxi == minpos) std::swap(vector[minpos], vector[maxpos]);
		else if (mini == maxpos) {
			std::swap(vector[maxi], vector[minpos]);
			std::swap(vector[minpos], vector[maxpos]);
		}
		else if (maxi == minpos) {
			std::swap(vector[mini], vector[maxpos]);
			std::swap(vector[minpos], vector[maxpos]);
		}
		else {
			if (maxi != maxpos) std::swap(vector[maxi], vector[maxpos]);
			if (mini != minpos) std::swap(vector[mini], vector[minpos]);
		}
		
		++minpos;
		--maxpos;
	}
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int nfilas = 0, ncolumnas = 0;
	std::cin >> nfilas >> ncolumnas;

    if (! std::cin)
        return false;
    
	tMatriz matriz(nfilas, std::vector<int>(ncolumnas));
	for (int i = 0; i < nfilas; ++i) {
		for (int j = 0; j < ncolumnas; ++j) {
			std::cin >> matriz[i][j];
		}
	}
	
	std::vector<int> grados;
	tPosicion posicion; int grado = 0;
	for (int i = 0; i < nfilas; ++i) {
		posicion.i = i;
		for (int j = 0; j < ncolumnas; ++j) {
			posicion.j = j;
			
			grado = gradoInteres(matriz, posicion);
			grados.push_back(grado);
		}
	}
    
	ordenarVector(grados);
	
    // escribir sol
	std::cout << grados[0];
	for (int i = 1; i < grados.size(); ++i) std::cout << ' ' << grados[i];
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
    // std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}