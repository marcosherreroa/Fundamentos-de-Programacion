// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	int anchcont = 0, largcont = 0, altcont = 0,
		anchcaj = 0, largcaj = 0, altcaj = 0,
		paral = 0, perp = 0;

    std::cin >> anchcont >> largcont >> altcont >> anchcaj >> largcaj >> altcaj;

	// paral es el número de cajas que se pueden colocar en paralelo
	// perp es el númeor de cajas que se pueden colocar en perpendicular

	paral = (anchcont * 100 / anchcaj)*(largcont * 100 / largcaj)*(altcont * 100 / altcaj);
	perp = (anchcont * 100 / largcaj)*(largcont * 100 / anchcaj)*(altcont * 100 / altcaj);

    // escribir sol

	if (paral > perp)std::cout << paral << " EN PARALELO\n";
	else if (perp > paral)std::cout << perp << " EN PERPENDICULAR\n";
	else std::cout << paral << " DA IGUAL\n";  
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