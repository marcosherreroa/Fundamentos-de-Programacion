// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using tMatriz = std::vector<std::vector<int>>;

const std::vector<int> incF = { 1,0,-1,0 };
const std::vector<int> incC = { 0,1,0,-1 };

// función que resuelve el problema
int resolver(tMatriz const & matriz, int & filamax) {
	int d = matriz.size();

	if (d == 1) return matriz[0][0];
	
	int maximo = matriz[0][0];
	maximo += matriz[1][0] + matriz[0][1];

	int suma = 0;
	for (int i = 1; i < d - 1; ++i) {
		suma = matriz[i][i];
		for (int k = 0; k < 4; ++k) {
			suma += matriz[i + incF[k]][i + incC[k]];
		}
		if (suma > maximo) {
			maximo = suma;
			filamax = i;
		}
	}

	suma = matriz[d - 1][d - 1];
	suma += matriz[d - 2][d - 1] + matriz[d - 1][d - 2];

	if (suma > maximo) {
		maximo = suma;
		filamax = d-1;
	}

	return maximo;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int d = 0;
	std::cin >> d;

    if (! std::cin)
        return false;
    
	tMatriz matriz(d, std::vector<int>(d, 0));

	for (int i = 0; i < d; ++i) std::cin >> matriz[i][i];
	for (int i = 1; i < d; ++i) std::cin >> matriz[i - 1][i];
	for (int i = 0; i < d - 1; ++i) std::cin >> matriz[i + 1][i];

	
	int filamax = 0;
    int maximo = resolver(matriz, filamax);
    
    // escribir sol
	std::cout << filamax<<' '<< maximo<<'\n';
    
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
   //  #ifndef DOMJUDGE // para dejar todo como estaba al principio
  //   std::cin.rdbuf(cinbuf);
    system("PAUSE");
 //    #endif
    
    return 0;
}