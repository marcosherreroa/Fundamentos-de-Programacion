#include <iostream>
#include <vector>
#include <functional>

template<typename T, typename Comp= std::less()>
void ordenarInsercion(std::vector<T> & v, Comp ord= comp()) {
	for (int i = 1; i < v.size(); ++i) {
		T elemento = v[i];
		int j = i;
		while (j > 0 && ord(elemento, v[j-1])) {
			v[j] = v[j - 1];
			--j;
		}
		if(j!= i) v[j] = elemento;
	}
}

template<typename T, typename Comp = std::less()>
void ordenarSeleccion(std::vector<T> & v, Comp ord = comp()) {
	for (int i = 0; i < v.size() - 1; ++i) {
		int indmenor = i;
		for (int j = i+1; j < v.size(); ++j) {
			if (ord(v[j], v[indmenor])) indmenor = j;
		}
		if (i != indmenor) swap(v[i], v[indmenor]);
	}
}

template<typename T, typename Comp = std::less()>
void ordenarBurbuja(std::vector<T> & v, Comp ord = comp()) {
	bool intercambiado = true;
	for (int i = 0; intercambiado && i < v.size()-1; ++i) {
		intercambiado = false;
		for (int j = v.size(); j > i; --j) {
			if (ord(v[j], v[j - 1])) {
				swap(v[j], v[j - 1]);
				intercambiado = true;
			}
		}
	}
}

template<typename T, typename Comp = std::less()>
bool buscarSec(std::vector<T> const & v, T const & buscado, int & pos, Comp ord = Comp()) {
	bool encontrado = false; pos = 0;
	while (ord(v[pos], buscado) && pos < v.size()) ++pos;
	if (pos < v.size() && !ord(buscado),v[pos]) encontrado = true;
}

template<typename T, typename Comp = std::less()>
bool buscarBinaria(std::vector<T> const & v, T const & buscado, int & pos, Comp ord = Comp()) {
	int ini = 0, fin = v.size();
	bool encontrado = false;
	while (!encontrado && ini < fin) {
		mitad = (ini + fin - 1) / 2;
		if (ord(buscado, v[pos])) fin = mitad;
		else if ord(v[pos], buscado) ini = mitad + 1;
		else encontrado = true;
	}
	if (encontrado) pos = mitad;
	else pos = ini;
	return encontrado
}

template<typename T, typename Comp = std::less()>
bool insertarSR(std::vector<T> & v, T const & insertado, Comp ord = Comp()) {
	int pos = 0;
	if (!buscarBinaria(v, insertado, pos, ord)) {
		v.pushback(T);
		for (int i = v.size() - 1; i > pos; --i) v[i] = v[i - 1];
		v[pos] = insertado;
		return true;
	}
	else return false;
}

template<typename T, typename Comp = std::less()>
void insertarCR(std::vector<T> & v, T const & insertado, Comp ord = Comp()) {
	int pos = 0;
	v.push_back(T);
	while (i > 0 && ord(insertado, v[i-1])) {
		v[i] = v[i - 1];
		--i;
	}
	v[i] = insertado;
}

template<typename T, typename Comp= std::less()>
bool eliminar(std::vector<T> & v, T const & eliminado, Comp ord = Comp()) {
	int pos = 0;
	if (buscarBinaria(v, eliminado, pos, ord)) {
		for (int i = pos; i < v.size() - 1; ++i) v[i] = v[i + 1];
		v.pop_back();
		return true;
	}
	else return false;
}