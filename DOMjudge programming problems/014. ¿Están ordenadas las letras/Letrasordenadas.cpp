// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>


// función que resuelve el problema
bool resolver(std::string const & palabra) {
	 bool ordenada = true;

	for (int i = 1; ordenada && i < palabra.size(); i++) {
		if (palabra[i] <= palabra[i-1]) ordenada = false;
	}
	return ordenada;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	std::string palabra = "";

	std::cin >> palabra;
    
    if (palabra=="XXX") return false;
    
    bool ordenada = resolver(palabra);
    
    // escribir sol
	if (ordenada)std::cout << "SI\n";
	else std::cout << "NO\n";
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
  //  #ifndef DOMJUDGE
    // std::ifstream in("datos1.txt");
   //  auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
  //   #endif 
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
   //  #ifndef DOMJUDGE // para dejar todo como estaba al principio
  //   std::cin.rdbuf(cinbuf);
     system("PAUSE");
 //    #endif
    
    return 0;
}