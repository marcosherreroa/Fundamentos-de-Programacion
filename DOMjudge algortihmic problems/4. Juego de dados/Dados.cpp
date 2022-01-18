// Nombre del alumno: Marcos Herrero
// Usuario del Juez : DG11


#include <iostream>
#include <iomanip>
#include <fstream>

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    // leer los datos de la entrada
	int D1J = 0, D2J = 0, D1A = 0, D2A = 0, J=0, A=0;

	std::cin >> D1J >> D2J >> D1A >> D2A;

	J = D1J + D2J;
	A = D1A + D2A;

    // escribir sol

	if (J > A)std::cout << "JORGE " << J << " ANA " << A << '\n';
	else if (A > J)std::cout << "ANA " << A << " JORGE " << J << '\n';
	else std::cout << "EMPATE " << J << '\n';  
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