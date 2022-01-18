//Marcos Herrero

#include "ListaReproduccion.h"
#include "checkML.h"

tListaReproduccion nueva(std::string const & nombre, int dim) {
	tListaReproduccion lista;

	lista.v = new tElemento[dim];
	lista.cont = 0;
	lista.capacidad = dim;
	lista.nombre = nombre;

	return lista;
}

void destruir(tListaReproduccion & lista) {
	delete[] lista.v;
	lista.cont = 0;
	lista.capacidad = 0;
	lista.nombre = "";
}

void insertar(tListaReproduccion & lista, tElemento elemento) {
		lista.v[lista.cont] = elemento;
		++lista.cont;
}

bool busqsecrecurs(tListaReproduccion & lista, int ini, std::string const & titulo) {

	if (ini >= lista.cont) return false;
	else return (lista.v[ini].punt->titulo == titulo) || busqsecrecurs(lista, ini + 1, titulo);
}

bool buscar(tListaReproduccion & lista, std::string const & titulo, int pos) {
	return busqsecrecurs(lista, pos, titulo);
}

void mostrar(tListaReproduccion const & lista) {
	std::cout <<std::setw(2)<<' '<<std::left<< std::setw(8) << "Lista: " << lista.nombre<<'\n';

	int tiempotot = 0;
	for (int i = 0; i < lista.cont; ++i) {
		std::cout << std::right<< std::setw(5) << i+1 << '-' << *lista.v[i].punt << std::setw(5) << '(' << lista.v[i].valoracion << ")\n";
		tiempotot += lista.v[i].punt->segundos;
	}

	std::cout << std::setw(2) << ' ' << std::left << std::setw(10) << "Tiempo de reproduccion: " << std::right << 
		std::setfill('0') << std::setw(2) << tiempotot / 60 << ':' << std::setw(2) << tiempotot % 60<< std::setfill(' ')<<"\n\n";
}

void modificarOrden(tListaReproduccion & lista, int origen, int destino) {
	if (origen < destino) {
		tElemento aux = lista.v[origen];
		for (int i = origen; i < destino; ++i) lista.v[i] = lista.v[i + 1];
		lista.v[destino] = aux;
	}

	else if (destino < origen) {
		tElemento aux = lista.v[origen];
		for (int i = origen; i > destino; --i) lista.v[i] = lista.v[i - 1];
		lista.v[destino] = aux;
	}
}
