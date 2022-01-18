// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using tMatriz = std::vector<std::vector<char>>;
struct tCoordenada{
	int x;
	int y;
};

void uno(tMatriz & matriz, tCoordenada const & coord, int L){
	for (int i = coord.x; i < coord.x + L && i< matriz.size(); ++i){
		for (int j = coord.y + (i -coord.x); j < coord.y + L && j< matriz[0].size(); ++j){
			matriz[i][j] = '*';
		}
	}
}

void dos(tMatriz & matriz, tCoordenada const & coord, int L){
	for (int i = coord.x; i < coord.x + L && i< matriz.size(); ++i){
		for (int j = coord.y; j-coord.y <= i- coord.x && j< matriz[0].size() ; ++j){
			matriz[i][j] = '*';
		}
	}
}

void tres(tMatriz & matriz, tCoordenada const & coord, int L){
	std::vector<char> aux(L);

	for (int j = coord.y; j < coord.y + L; ++j) aux[j - coord.y] = matriz[coord.x + L - 1][j];

	for (int i = coord.x + L -1; i > coord.x; --i){
		for (int j = coord.y; j < coord.y + L; ++j){
			matriz[i][j] = matriz[i-1][j];
		}
	}

	for (int j = coord.y; j < coord.y + L; ++j) matriz[coord.x][j] = aux[j- coord.y];

}

void cuatro(tMatriz & matriz, tCoordenada const & coord, int L){
	std::vector<char> aux(L);

	for (int i = coord.x; i < coord.x + L; ++i) aux[i - coord.x] = matriz[i][coord.y + L - 1];

	for (int j = coord.y + L - 1; j > coord.y; --j){
		for (int i = coord.x; i < coord.x + L; ++i){
			matriz[i][j] = matriz[i][j - 1];
		}
	}

	for (int i = coord.x; i < coord.x + L; ++i) matriz[i][coord.y] = aux[i-coord.x];

}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int nfilas = 0, ncolumnas = 0, ntransformaciones = 0;
	std::cin >> nfilas >> ncolumnas >> ntransformaciones;
    
    if (! std::cin)
        return false;

	tMatriz matriz(nfilas, std::vector<char>(ncolumnas));

	for (int i = 0; i < nfilas; ++i){
		for (int j = 0; j < ncolumnas; ++j){
			std::cin >> matriz[i][j];
		}
	}

	int tTransformacion = 0; tCoordenada coord; int L = 0;
	for (int i = 0; i < ntransformaciones; ++i){
		std::cin >> tTransformacion >> coord.x >> coord.y >> L;
		switch (tTransformacion){
		case 1: uno(matriz, coord, L); break;
		case 2: dos(matriz, coord, L); break;
		case 3: tres(matriz, coord, L); break;
		case 4: cuatro(matriz, coord, L); break;
		}
	}
 
    
    // escribir sol
	for (int i = 0; i < nfilas; ++i){
		for (int j = 0; j < ncolumnas; ++j){
			std::cout << matriz[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos1.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}