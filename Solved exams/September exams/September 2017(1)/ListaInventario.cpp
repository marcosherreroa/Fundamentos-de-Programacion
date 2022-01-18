//Marcos Herrero

#include "ListaInventario.h"

void crear(tListaInventario & lista, int tam) {
	lista.punt = new tPrenda[tam];
	lista.capacidad = tam;
	lista.cont = 0;
}

void redimensionar(tListaInventario & lista) {
	lista.capacidad *=2;
	tPrenda* aux = lista.punt;
	lista.punt = new tPrenda[lista.capacidad];

	for (int i = 0; i < lista.cont; ++i) lista.punt[i] = aux[i];
	delete[] aux;
}

void liberar(tListaInventario & lista) {
	delete[] lista.punt;
	lista.cont = 0;
	lista.capacidad = 0;
}

tPrenda obtenerPrenda(tListaInventario const & lista, int pos) {
	return lista.punt[pos];
}

bool cargar(tListaInventario & lista) {
	std::ifstream entrada;
	entrada.open("inventario.txt");
	if (!entrada.is_open()) return false;

	int nprendas;
	entrada >> nprendas;
	crear(lista, nprendas);
	tPrenda prenda;
	for (int i = 0; i < nprendas; ++i) {
		entrada >> prenda;
		insertar(lista, prenda);
	}

	entrada.close();
	return true;
}

bool busqbinrecurs(tListaInventario const & lista, std::string const & identificador, int ini, int fin, int & pos) {
	if (ini == fin) {
		pos = ini;
		return false;
	}
	else {
		int mitad = (ini + fin - 1) / 2;
		if (identificador < lista.punt[mitad].id) return busqbinrecurs(lista, identificador, ini, mitad, pos);
		else if (lista.punt[mitad].id < identificador) return busqbinrecurs(lista, identificador, mitad + 1, fin, pos);
		else {
			pos = mitad;
			return true;
		}
	}

}

bool buscar(tListaInventario const & lista, std::string const & identificador, int & pos) {
	return busqbinrecurs(lista, identificador, 0, lista.cont, pos);
}

void insertar(tListaInventario & lista, tPrenda const & insertado) {
	int pos = 0;
	if (!buscar(lista, insertado.id, pos)) {
		if (lista.cont == lista.capacidad) redimensionar(lista);
		int i = lista.cont;
		for (int i = lista.cont; i > pos; --i) lista.punt[i] = lista.punt[i - 1];
		lista.punt[pos] = insertado;
		++lista.cont;
	}
}

void eliminar(tListaInventario & lista, tPrenda const & eliminado) {
	int pos = 0;
	if (buscar(lista, eliminado.id, pos)) {
		for (int i = pos; i < lista.cont - 1; ++i) lista.punt[i] = lista.punt[i + 1];
		--lista.cont;
	}
}

int mayorMargen(tListaInventario const & lista) {
	int pos = 0;
	if (lista.cont > 0) {
		tPrenda max = lista.punt[0];
		for (int i = 1; i < lista.cont; ++i) {
			if (Compmargen()(max, lista.punt[i])) {
				max = lista.punt[i];
				pos = i;
			}
		}
	}

	return pos;
}

void mostrar(tListaInventario const & lista) {
	if (lista.cont == 0) std::cout << "No hay prendas en el inventario\n\n";
	else {
		std::cout << "\nINVENTARIO\n\n";
		for (int i = 0; i < lista.cont; ++i) std::cout << lista.punt[i] << '\n';
		std::cout << '\n';
	}
}