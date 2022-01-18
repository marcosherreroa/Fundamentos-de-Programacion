// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<int> leerVector() {
	int tam;
	std::cin >> tam;

	std::vector<int> v(tam);
	for (int i = 0; i < tam; ++i) std::cin >> v[i];
	
	return v;
}

// función que resuelve el problema

template<typename T>
std::vector<T> resolver(std::vector<T> const & cromosRep, std::vector<T> const & cromosOtro) {
	std::vector<T> sol;

	int i = 0, j = 0;
	while (0 <= i && i < cromosOtro.size() && 0 <= j && j < cromosRep.size()) {
		if (cromosOtro[i] > cromosRep[j]) {
			if (sol.size() == 0 || cromosRep[j] != sol[sol.size() - 1]) sol.push_back(cromosRep[j]);
			++j;
		}

		else if( cromosOtro[i] == cromosRep[j]) ++j;

		else ++i;
	}

	for (int k = j; k < cromosRep.size(); ++k) {
		if (sol.size() == 0 || cromosRep[k] != sol[sol.size() - 1]) sol.push_back(cromosRep[k]);
	}

	return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	std::vector<int> cromosDavid = leerVector();
	std::vector<int> cromosRepDavid = leerVector();
	std::vector<int> cromosAna = leerVector();
	std::vector<int> cromosRepAna = leerVector();
    
	
	std::sort(cromosRepDavid.begin(), cromosRepDavid.end());
	std::sort(cromosRepAna.begin(), cromosRepAna.end());

    std::vector<int> sol1 = resolver(cromosRepDavid, cromosAna);
	std::vector<int> sol2 = resolver(cromosRepAna, cromosDavid);
	
    // escribir sol
	for (int i = 0; i < sol1.size(); ++i) std::cout << sol1[i]<<' ';
	std::cout << '\n';
	for (int i = 0; i < sol2.size(); ++i) std::cout << sol2[i]<<' ';
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