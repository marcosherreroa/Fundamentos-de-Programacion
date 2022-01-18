// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>


// función que resuelve el problema
bool resolver( std::string palabra) {
	int a = 0, e = 0, i = 0, o = 0, u = 0;

	for (int k = 0; k < palabra.size(); k++) {
		switch (palabra[k]) {
		case 'a': a++; break;
		case 'e': e++; break;
		case 'i': i++; break;
		case 'o': o++; break;
		case 'u': u++;
		}
	}
	return(a != 0 && e != 0 && i != 0 && o != 0 && u != 0);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	std::string palabra = "";
    // leer los datos de la entrada

	std::cin >> palabra;
    
    // escribir sol
    
	if (resolver(palabra)) std::cout << "SI\n";
	else std::cout << "NO\n";
    
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