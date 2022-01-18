// Nombre del alumno Marcos
// Usuario del Juez DG11


#include <iostream>
#include <iomanip>
#include <fstream>

    

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	int num = 0, sol = 0;
	std::cin >> num;

    // escribir sol
	for (int i = 1; i <= 10; i++) {
		//i tomará todos los valores del 1 al 10
		sol = num*i;
		std::cout << num << " * " << i << " = " << sol << '\n';
	} 
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