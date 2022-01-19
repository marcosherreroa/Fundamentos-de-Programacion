// Nombre del alumno Marcos y Ángel
// Usuario del Juez DG11


#include <iostream>
#include <iomanip>
#include <fstream>

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	// F es el amigo de Jorge y Ana
	int D1J = 0, D2J = 0, D1A = 0, D2A = 0, D1F = 0, D2F = 0, J = 0, A = 0, F = 0;

	std::cin >> D1J >> D2J >> D1A >> D2A >> D1F >> D2F;
	//J, A y F son las puntuaciones de cada uno
	J = D1J + D2J;
	A = D1A + D2A;
	F = D1F + D2F;

	if (J > A && J > F)std::cout << "JORGE " << J<<'\n';
	else if (A > J && A > F)std::cout << "ANA " << A << '\n';
	else if (F > J && F > A)std::cout << "AMIGO " << F << '\n';
	else if (J == A && J > F)std::cout << "EMPATE ANA JORGE " << J << '\n';
	else if (J == F && J > A)std::cout << "EMPATE AMIGO JORGE " << J << '\n';
	else if (A == F && A > J)std::cout << "EMPATE AMIGO ANA " << A << '\n';
	else std::cout << "EMPATE AMIGO ANA JORGE " << J << '\n';
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