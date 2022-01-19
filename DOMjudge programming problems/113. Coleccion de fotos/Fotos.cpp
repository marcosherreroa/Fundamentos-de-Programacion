// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using tMatriz = std::vector<std::vector<int>>;

struct tFoto {
	std::string titulo;
	std::string tema;
	tMatriz matriz;
};

struct CompTitulo {
	bool operator() (tFoto* const & foto1, tFoto* const & foto2) {
		return(foto1->titulo < foto2->titulo);
	}
};

struct CompTema {
	bool operator() (tFoto* const & foto1, tFoto* const & foto2) {
		if (foto1->tema < foto2->tema) return true;
		else if (foto1->tema == foto2->tema && foto1->titulo < foto2->titulo) return true;
		else return false;
	}
};

template<typename T, typename Comp>
void ordenarInsercion(std::vector<T> & v, Comp ord) {
	int j;
	for (int i = 1; i < v.size(); ++i) {
		T elemento = v[i];
		j = i;
		while (j > 0 && ord(elemento, v[j - 1])) {
			v[j] = v[j - 1];
			--j;
		}
		v[j] = elemento;
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int nfotos;
	std::cin >> nfotos;
	std::cin.ignore(1);

	if (nfotos == 0)
		return false;

	std::vector<tFoto> fotos(nfotos);
	std::vector<tFoto*> ordenTitulo(nfotos);
	std::vector<tFoto*> ordenTema(nfotos);

	for (int i = 0; i < nfotos; ++i) getline(std::cin, fotos[i].titulo);
	for (int i = 0; i < nfotos; ++i) {
		getline(std::cin, fotos[i].tema);

		tMatriz matriz(50, std::vector<int>(50, i));
		fotos[i].matriz = matriz;

		ordenTitulo[i] = &fotos[i];
		ordenTema[i] = &fotos[i];
	}
	
	ordenarInsercion(ordenTitulo, CompTitulo());
	ordenarInsercion(ordenTema, CompTema());

	for (int i = 0; i < nfotos; ++i) std::cout << ordenTitulo[i]->titulo << '\n'; 
	std::cout << '\n';
	for (int i = 0; i < nfotos; ++i) std::cout << ordenTema[i]->tema << " - " << ordenTema[i]->titulo << '\n';
	
	return true;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	//std::ifstream in("datos1.txt");
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

