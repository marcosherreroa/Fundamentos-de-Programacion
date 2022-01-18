// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// función que resuelve el problema

void contador( float media, std::vector<float>  const & pesos, int & masquelamedia, int & menosquelamedia) {
	for (int i = 0; i < pesos.size(); ++i) {
		if (pesos[i] >= media) ++masquelamedia;
		else ++menosquelamedia;
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	float pesochild = 0, pesovector = 0, suma = 0;
	std::vector<float> pesos;

	std::cin >> pesochild;
	std::cin >> pesovector;

	while (pesovector != 0){
		suma += pesovector;
		pesos.push_back(pesovector);
		std::cin >> pesovector; 
	}
    
	float media = suma / pesos.size();
	int masquelamedia = 0, menosquelamedia = 0;

	contador(media, pesos, masquelamedia, menosquelamedia);

	if (pesochild >= media)std::cout << "MAYOR " << masquelamedia<<'\n';
	else std::cout << "MENOR " << menosquelamedia<< '\n';
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