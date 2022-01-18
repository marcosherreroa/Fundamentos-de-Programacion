// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using tMatriz = std::vector<std::vector<int>>;

// función que resuelve el problema
tMatriz operator*(tMatriz const & a, tMatriz const & b) {
	tMatriz ab(a.size(), std::vector<int>(b[0].size(),0));
	
	for (int i = 0; i < ab.size(); ++i) {
		for (int j = 0; j < ab[0].size(); ++j){
			for (int k = 0; k < a[0].size(); ++k) {
				ab[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	return ab;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int njuguetes = 0, nproductos = 0;
	std::cin >> njuguetes >> nproductos;

    if (! std::cin)
        return false;
    
	tMatriz productosJuguetes(njuguetes, std::vector<int>(nproductos));
	for (int i = 0; i < njuguetes; ++i) {
		for (int j = 0; j < nproductos; ++j) {
			std::cin >> productosJuguetes[i][j];
		}
	}
	int nproveedores = 0;
	std::cin >> nproductos >> nproveedores;


	tMatriz precioProducto(nproductos, std::vector<int>(nproveedores));
	for (int i = 0; i < nproductos; ++i) {
		for (int j = 0; j < nproveedores; ++j) {
			std::cin >> precioProducto[i][j];
		}
	}


	tMatriz precioJuguetes(njuguetes, std::vector<int>(nproveedores, 0));
	precioJuguetes= productosJuguetes * precioProducto;
	
    // escribir sol
	for (int i = 0; i < njuguetes; ++i) {
		std::cout << precioJuguetes[i][0];
		for (int j = 1; j < nproveedores; ++j) {
			std::cout << ' ' << precioJuguetes[i][j];
		}
		std::cout << '\n';
	}
    
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
    // std::cin.rdbuf(cinbuf);
     system("PAUSE");
    // #endif
    
    return 0;
}