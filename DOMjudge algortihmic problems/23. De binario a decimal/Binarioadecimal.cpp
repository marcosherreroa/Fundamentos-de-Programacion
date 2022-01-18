// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>


// función que resuelve el problema
unsigned long long int resolver(std::string const & num) {
	unsigned long long int potencia = 1, sol = 0;
	for( int i= num.size()-1; i>=0;--i){
		sol += (int(num[i])-int('0'))*potencia;
		potencia *= 2;
	}
	return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	std::string num = "";

	std::cin >> num;
    
	unsigned long long int sol = resolver(num);
    // escribir sol
	std::cout << sol << '\n';
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
   std::ifstream in("datos1.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}