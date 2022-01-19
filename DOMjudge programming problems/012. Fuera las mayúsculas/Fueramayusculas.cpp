// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>


// función que resuelve el problema
std::string resolver(std::string palabra) {
	for (int i = 0; i < palabra.size(); i++) {
		if(isupper(palabra[i])) palabra[i]=tolower(palabra[i]);
	}
	return palabra;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	std::string palabra = "";
    // leer los datos de la entrada
	std::cin >> palabra;
    
    std::string sol  = resolver(palabra);

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