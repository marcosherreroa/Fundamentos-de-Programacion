//Marcos Herrero

#include "ListaLonja.h"
#include "checkML.h"

void inicializar(tListaLonja & lista) {
	lista.cont = 0;
}

int numlotes(tListaLonja const & lista) {
	return lista.cont;
}

bool insertar(tListaLonja & lista, tLotes const & insertado) {
	int pos = 0;
	if (lista.cont == MAXLOTES) return false;
	else if (lista.cont < MAXLOTES && !buscar(lista, insertado.id, insertado.tipo, pos)) {
		for (int i = lista.cont; i > pos; --i) lista.v[i] = lista.v[i - 1];
		lista.v[pos] = new tLotes;
		*lista.v[pos] = insertado;
		++lista.cont;
		return true;
	}
}

bool cargar(tListaLonja & lista) {
	std::ifstream entrada;
	entrada.open(FICHERO);
	if (!entrada.is_open()) {
		std::cout << "No se encuentra el fichero\n\n";
		return false;
	}

	inicializar(lista);
	tLotes lote; bool OK = true;
	while (OK && !entrada.eof()) {
		entrada >> lote;
		OK = insertar(lista, lote);
	}

	if (!OK) {
		std::cout << "Hay demasiados lotes\n\n";
		liberar(lista);
	}
	return OK;
}

bool busqbinrecurs(tListaLonja const & lista, tLotes const & buscado, int ini, int fin, int & pos) {
	if (ini == fin) {
		pos = ini;
		return false;
	}
	else {
		int mitad = (ini + fin - 1) / 2;

		if (buscado < *lista.v[mitad]) busqbinrecurs(lista, buscado, ini, mitad, pos);
		else if (*lista.v[mitad] < buscado) busqbinrecurs(lista, buscado, mitad + 1, fin, pos);
		else {
			pos = mitad;
			return true;
		}
	}
}

bool buscar(tListaLonja const & lista, std::string const & id, std::string const & tipo, int & pos) {
	tLotes buscado{ id, tipo };
	return busqbinrecurs(lista, buscado, 0, lista.cont, pos);
}

tLotes obtenerLote(tListaLonja const & lista, int pos) {
	return *lista.v[pos];
}

void mostrar(tListaLonja const & lista) {
	if (lista.cont == 0) std::cout << "La lista esta vacia\n\n";

	else for (int i = 0; i < lista.cont; ++i) mostrarPrecio(*lista.v[i]);
}

void liberar(tListaLonja & lista) {
	for (int i = 0; i < lista.cont; ++i) delete lista.v[i];
	lista.cont = 0;
}