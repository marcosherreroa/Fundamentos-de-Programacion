// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>



// función que resuelve el problema
long long int prod(long long int a, long long int b) {
	if (b == 0) return 0;
	else if (b == 1) return a;
	else if (b % 2 == 0)return prod(2 * a, b / 2);
	else return prod(2 * a, b / 2) + a;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	long long int num1, num2;
	std::cin >> num1 >> num2;

    if (! std::cin)
        return false;
    
	std::cout << prod(num1, num2)<<'\n';
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
    // std::ifstream in("datos1.txt");
    // auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
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