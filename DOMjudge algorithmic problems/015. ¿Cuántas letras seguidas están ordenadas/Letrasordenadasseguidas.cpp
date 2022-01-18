// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>


// función que resuelve el problema
int resolver(std::string const & palabra) {
	int  numrep = 1, numrepmax = 1;

	for (int i = 1; i < palabra.size(); i++){
		if (palabra[i-1] < palabra[i]) numrep++;
		else numrep = 1;
		if (numrep > numrepmax) numrepmax = numrep;
	}
	return numrepmax;
}    


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	std::string palabra = "";

	std::cin >> palabra;
    
    if (palabra=="XXX")
        return false;
    
    int sol = resolver(palabra);
    
    // escribir sol

	std::cout << palabra.size() << ' ' << sol<<'\n';
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     //std::ifstream in("datos.txt");
     //auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     //std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}