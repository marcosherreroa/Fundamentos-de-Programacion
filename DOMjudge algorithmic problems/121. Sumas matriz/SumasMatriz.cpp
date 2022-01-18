//Marcos Herrero


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

const std::vector<int> incF = { -1, -1, 0, 1, 1, 1, 0, -1 };
const std::vector<int> incC = { 0, 1, 1, 1, 0, -1, -1, -1 };
using  tMatriz = std::vector<std::vector<int>>;

bool comprobarCoord(tMatriz const & matriz, int x, int y){
	return (x >= 0 && x < matriz.size() && y >= 0 && y < matriz[0].size());
}

int sumas(tMatriz & matriz, int fila, int col){
	if (matriz[fila][col] <= 0) return 0;
	else{
		int suma = matriz[fila][col];
		matriz[fila][col] = -1;
		for (int i = 0; i < 8; ++i) {
			if (comprobarCoord(matriz, fila + incF[i], col + incC[i])){
				suma += sumas(matriz, fila + incF[i], col + incC[i]);
			}
		}

		return suma;
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int nfilas, ncolumnas;
	std::cin >> nfilas >> ncolumnas;

    if (! std::cin)
        return false;

	tMatriz matriz(nfilas, std::vector<int>(ncolumnas));
	for (int i = 0; i < nfilas; ++i){
		for (int j = 0; j < ncolumnas; ++j){
			std::cin >> matriz[i][j];
		}
	}
    
	int fila, col;
	std::cin >> fila >> col;
	while (fila != -1 || col != -1) {
		tMatriz aux = matriz;
		std::cout << sumas(aux, fila, col)<<'\n';
		std::cin >> fila >> col;
	}

    
    // escribir sol
    
    
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