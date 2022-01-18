// Nombre del alumno Marcos Herrero
// Usuario del Juez DG11


#include <iostream>
#include <iomanip>
#include <fstream>


// función que resuelve el problema
int resolver(int anchpat, int altpat, int anchazul, int largazul) {

	int sol = 0;

		sol = (anchpat / anchazul)*(altpat / largazul);

		if (anchpat % anchazul != 0)sol += altpat / largazul;
		if (altpat % largazul != 0)sol += anchpat / anchazul;
		if (anchpat % anchazul != 0 && altpat % largazul != 0)sol += 1;

		return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	int anchpat = 0, altpat = 0, anchazul = 0, largazul = 0, sol = 0;

	std::cin >> anchpat >> altpat >> anchazul >> largazul;

    // escribir sol

	sol = resolver(anchpat, altpat, anchazul, largazul);

	if (anchpat % anchazul != 0 || altpat % largazul != 0)std::cout << sol << " NECESITA COMPRAR MAQUINA\n";
	else std::cout << sol << '\n';
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