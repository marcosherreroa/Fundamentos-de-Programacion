// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using tMatriz = std::vector<std::vector<int>>;

// función que resuelve el problema
void girar90(tMatriz & matriz) {
	int d = matriz.size(), aux = 0;

	for (int i = 0; i < d / 2; ++i) {
		for (int j = i; j < d - 1 - i; ++j) {
			aux = matriz[i][j];
			matriz[i][j] = matriz[d - 1 - j][i];
			matriz[d - 1 - j][i] = matriz[d - 1 - i][d - 1 - j];
			matriz[d - 1 - i][d - 1 - j] = matriz[j][d - 1 - i];
			matriz[j][d - 1 - i] = aux;
		}
	}
}

void girar180(tMatriz & matriz) {
	int d = matriz.size(), aux = 0;
	for (int i = 0; i < d / 2; ++i) {
		for (int j = 0; j < d; ++j) {
			std::swap(matriz[i][j], matriz[d - 1 - i][d - 1 - j]);
		}
	}
	if (d % 2 == 1) {
		int i = d / 2;
		for (int j = 0; j < d / 2; ++j) std::swap(matriz[i][j], matriz[i][d - 1 - j]);
	}
}

void girar270(tMatriz & matriz) {
	int d = matriz.size(), aux = 0;
	for (int i = 0; i < d / 2; ++i) {
		for (int j = i; j < d - 1 - i; ++j) {
			aux = matriz[i][j];
			matriz[i][j] = matriz[j][d - 1 - i];
			matriz[j][d - 1 - i] = matriz[d - 1 - i][d - 1 - j];
			matriz[d - i - 1][d - j - 1] = matriz[d - 1 - j][i];
			matriz[d - 1 - j][i] = aux;
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int d = 0;
	std::cin >> d >> d;

	if (!std::cin)
		return false;

	tMatriz matriz(d, std::vector<int>(d));
	for (int i = 0; i < d; ++i){
		for (int j = 0; j < d; ++j) {
			std::cin >> matriz[i][j];
		}
	}

	int ngiros = 0, giro = 0, girototal= 0;
	std::cin >> ngiros;

	for (int i = 0; i < ngiros; ++i) {
		std::cin >> giro;
		girototal += giro;
	}

	girototal %= 360;

	switch (girototal) {
	case 90:girar90(matriz); break;
	case 180:girar180(matriz); break;
	case 270: girar270(matriz); break;
	}

    // escribir sol
	for (int i = 0; i < d; ++i) {
		for (int j = 0; j < d; ++j) {
			std::cout << matriz[i][j]<<' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
   // #ifndef DOMJUDGE
    // std::ifstream in("datos1.txt");
    // auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
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