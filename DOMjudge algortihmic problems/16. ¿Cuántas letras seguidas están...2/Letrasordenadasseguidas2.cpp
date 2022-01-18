// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>


// función que resuelve el problema
std::string resolver(std::string const & palabra) {
	int inicio = 0, longitud = 1, iniciomax = 0, longitudmax = 1;

	for (int i = 1; i < palabra.size(); i++){
		if (palabra[i-1] < palabra[i]) ++longitud;
		else {
			inicio = i;
			longitud = 1;
		}
		if (longitud > longitudmax) {
			iniciomax = inicio;
			longitudmax = longitud;
		}
	}
	std::string caractord = palabra.substr(iniciomax, longitudmax);
	return caractord;
}    


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	std::string palabra = "";

	std::cin >> palabra;
    
    if (palabra=="XXX")
        return false;
    
    std::string sol = resolver(palabra);
    
    // escribir sol

	std::cout << palabra.size() << ' ' << sol.size()<<' '<<sol<<'\n';
    
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