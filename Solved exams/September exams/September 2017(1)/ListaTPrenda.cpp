//Marcos Herrero

#include "ListaTPrenda.h"

void crear(tListaTPrenda & lista) {
	lista.cont = 0;
}

void liberar(tListaTPrenda & lista) {
	for (int i = 0; i < lista.cont; ++i) delete lista.v[i];
	lista.cont = 0;
}

bool generarLista(tListaTPrenda & lista, tListaInventario const & inventario, std::string const & tipo) {
	crear(lista);
	for (int i = 0; lista.cont < MAX_PRENDAS && i < inventario.cont; ++i) {
		if (inventario.punt[i].tipo == tipo) {
			lista.v[lista.cont] = new tPrenda;
			*lista.v[lista.cont] = inventario.punt[i];
			++lista.cont;
		}
	}

	if (lista.cont == MAX_PRENDAS) std::cout << "Hay demasiadas prendas del tipo especificado. Solo se tratan"<<MAX_PRENDAS<<'\n';

	return lista.cont != 0;

}

void particion(tListaTPrenda & lista, int ini, int fin, tPrenda* pivote, int & i, int & j) {
	i = ini, j = fin; int k = ini;
	while (k < j) {
		if (Compprecio()(lista.v[k], pivote)) {
			std::swap(lista.v[i], lista.v[k]);
			++i;
			++k;
		}
		else if (Compprecio()(pivote, lista.v[k])) {
			std::swap(lista.v[j-1], lista.v[k]);
			--j;
			++k;
		}
		else ++k;
	}
}

void quicksort(tListaTPrenda & lista, int ini, int fin) {
	if (ini < fin - 1) {
		int i, j;
		particion(lista, ini, fin, lista.v[ini], i, j);
		quicksort(lista, ini, i);
		quicksort(lista, j, fin);
	}
}

void ordenar(tListaTPrenda & lista) {  //utilizo el algoritmo de ordenacion quicksort porque es el más eficiente de los estudiados(nlog n),
	quicksort(lista, 0, lista.cont);   // ademas de tener una implementacion recursiva sencilla
}

void mostrar(tListaTPrenda const & lista) {
	std::cout << "Hay " << lista.cont << " modelos distintos:\n";
	for (int i = 0; i < lista.cont; ++i) std::cout << *lista.v[i] << '\n';
}