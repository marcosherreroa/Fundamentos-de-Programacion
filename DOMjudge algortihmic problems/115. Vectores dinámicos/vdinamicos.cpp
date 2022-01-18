
// Nombre del alumno Marcos Herrero
// Usuario del Juez DG11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

struct tObjeto {
	std::string nombre;
	int numero;
};

template<typename T>
struct vDinam {
	T* ptr;
	int cont;
	int capacidad;
};

template<typename T>
void ampliar(vDinam<T> & v) {
	v.capacidad *= 2;

	T* aux = v.ptr;
	v.ptr = new T[v.capacidad];
	for (int i = 0; i < v.cont; ++i) v.ptr[i] = aux[i];
	delete[] aux;
	
}

void aumentar(vDinam<tObjeto> & v, std::string const & nombre, int numero) {
	bool encontrado = false;

	for (int i = 0; !encontrado && i < v.cont; ++i) {
		if (v.ptr[i].nombre == nombre) {
			v.ptr[i].numero += numero;
			encontrado = true;
		}
	}

	if (!encontrado) {
		if (v.cont == v.capacidad) ampliar(v);

		v.ptr[v.cont].nombre = nombre;
		v.ptr[v.cont].numero = numero;
		++v.cont;
	}
}

void restar(vDinam<tObjeto> & v, std::string const & nombre, int numero) {
	bool encontrado = false;

	for (int i = 0; !encontrado && i < v.cont; ++i) {
		if (v.ptr[i].nombre == nombre) {
			if(v.ptr[i].numero>= numero) v.ptr[i].numero -= numero;
			else v.ptr[i].numero = 0;
			encontrado = true;
		}
	}
}

void listado(vDinam<tObjeto> const & v) {
	for (int i = 0; i < v.cont; ++i) std::cout << v.ptr[i].nombre <<' '<< v.ptr[i].numero << '\n';
	std::cout << "---\n";
}

int main() {
	vDinam<tObjeto> v;
	v.ptr = new tObjeto[3];
	v.cont = 0;
	v.capacidad = 3;
	
	char caracter;
	std::cin >> caracter;

	while (caracter != 'F') {
		switch (caracter) {
		case 'A': {
			std::string nombre; int numero;
			std::cin >> nombre >> numero;
			aumentar(v, nombre, numero) ;
			break;
		}
		case 'R': {
			std::string nombre; int numero;
			std::cin >> nombre >> numero;
			restar(v, nombre, numero);
			break;
		}
		case 'L': {listado(v); break; }
		}
		std::cin >> caracter;
	}

	delete[] v.ptr;

	return 0;
}

#endif