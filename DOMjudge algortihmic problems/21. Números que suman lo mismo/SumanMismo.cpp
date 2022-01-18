// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>


// función que resuelve el problema
int sumadigitos (int n) {
	int suma = 0;
	while (n > 0){
		suma += n % 10;
		n /= 10;
	}
	return suma;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	int nelementos = 0, num = 0;
	std::cin >> nelementos >> num;

	int elemento = 0;
	for (int i = 0; i < nelementos; ++i){
		std::cin >> elemento;
		if (sumadigitos(num) == sumadigitos(elemento)) std::cout << elemento << ' ';
	}
	std::cout << '\n';
   
    
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