// Nombre del alumno Flavius y Marcos
// Usuario del Juez DG11


#include <iostream>
#include <iomanip>
#include <fstream>


// función que resuelve el problema
int resolver(int n1, int n2) {
	int nterm = n2 - n1 + 1;    //nterm es el numero de terminos de la progresion
	int sol = nterm*(n1 + n2) / 2;
	return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	int n1 = 0; int n2 = 0;
	std::cin >> n1 >> n2;
	int sol = resolver(n1,n2);
    // escribir sol
	std::cout << sol << '\n';
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
//     std::ifstream in("datos1.txt");
//     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
//     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}