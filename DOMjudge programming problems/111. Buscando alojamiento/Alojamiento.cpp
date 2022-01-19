// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <functional>

struct tAlojamiento {
	std::string nombre;
	int puntuacion;
	int distancia;
	int precio;
};

std::string tolower(std::string const & cadena0) {
	std::string cadena;
	for (int i = 0; i < cadena0.size(); ++i) cadena.push_back(tolower(cadena0[i]));
	return cadena;
}

bool operator>(tAlojamiento const & aloj1, tAlojamiento const & aloj2) {
	//ordena por puntuación
	if (aloj1.puntuacion > aloj2.puntuacion) return true;
	else if (aloj1.puntuacion == aloj2.puntuacion && tolower(aloj1.nombre) < tolower(aloj2.nombre)) return true;
	else return false;
}

struct compDistancia {
	bool operator()(tAlojamiento const & aloj1, tAlojamiento const & aloj2) {
		if (aloj1.distancia < aloj2.distancia) return true;
		else if (aloj1.distancia == aloj2.distancia && tolower(aloj1.nombre) < tolower(aloj2.nombre)) return true;
		else return false;
	}
};

struct compPrecio {
	bool operator()(tAlojamiento const & aloj1, tAlojamiento const & aloj2) {
		if (aloj1.precio < aloj2.precio) return true;
		else if (aloj1.precio == aloj2.precio && tolower(aloj1.nombre) < tolower(aloj2.nombre)) return true;
		else return false;
	}
};

std::istream &operator>>(std::istream & flujo, tAlojamiento & aloj) {
	flujo >> aloj.nombre >> aloj.puntuacion >> aloj.distancia >> aloj.precio;
	return flujo;
}

template<typename T, typename Comp = std::greater<T>>
void ordenarInsercion(std::vector<T> & alojamientos, Comp ord= Comp()) {
	int j;
	for (int i = 1; i < alojamientos.size(); ++i) {
		T elemento = alojamientos[i];
		j = i;
		while (j > 0 && ord(elemento, alojamientos[j - 1])) {
			alojamientos[j] = alojamientos[j - 1];
			--j;
		}
		alojamientos[j] = elemento;
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int nalojamientos;
	std::cin >> nalojamientos;
    
    if (! std::cin)
        return false;

	std::vector<tAlojamiento> alojamientos(nalojamientos);

	for (int i = 0; i < nalojamientos; ++i) std::cin >> alojamientos[i];
    
	ordenarInsercion(alojamientos);
	for (int i = 0; i < nalojamientos; ++i) std::cout << alojamientos[i].nombre << ' ';
	std::cout << '\n';

	ordenarInsercion(alojamientos, compDistancia());
	for (int i = 0; i < nalojamientos; ++i) std::cout << alojamientos[i].nombre << ' ';
	std::cout << '\n';

	ordenarInsercion(alojamientos, compPrecio());
	for (int i = 0; i < nalojamientos; ++i) std::cout << alojamientos[i].nombre << ' ';
	std::cout << '\n';
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
    // std::ifstream in("datos1.txt");
    // auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
    // std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}