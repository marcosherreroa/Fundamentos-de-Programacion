// Nombre del alumno Flavius y Marcos
// Usuario del Juez DG11


#include <iostream>
#include <iomanip>
#include <fstream>


// función que resuelve el problema
int resolver(int anchcont, int largcont, int altcont,
int anchcaj, int largcaj, int altcaj) {
	int sol = 0;
	sol = (anchcont * 100 / anchcaj)*(largcont * 100 / largcaj)*(altcont * 100 / altcaj);
	return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	int anchcont = 0; int largcont = 0; int altcont = 0;
	int anchcaj = 0; int largcaj = 0; int altcaj = 0;
	std::cin >> anchcont >> largcont >> altcont >> anchcaj >> largcaj >> altcaj;
    int sol = resolver(anchcont, largcont, altcont, anchcaj, largcaj, altcaj);
    // escribir sol
	std::cout << sol<<'\n';
    
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