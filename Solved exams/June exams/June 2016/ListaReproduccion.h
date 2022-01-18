//Marcos Herrero

#ifndef LISTAREPRODUCCION_H
#define LISTAREPRODUCCION_H

#include "ListaTemas.h"

struct tElemento {
	tTema* punt;
	int valoracion;
};

struct tListaReproduccion {
	tElemento* v;
	int cont;
	int capacidad;
	std::string nombre;
};

tListaReproduccion nueva(std::string const & nombre, int dim);
void destruir(tListaReproduccion & lista);
void insertar(tListaReproduccion & lista, tElemento elemento);
bool busqsecrecurs(tListaReproduccion & lista, int ini, std::string const & titulo);
bool buscar(tListaReproduccion & lista, std::string const & titulo, int pos);
void mostrar(tListaReproduccion const & lista);
void modificarOrden(tListaReproduccion & lista, int origen, int destino);

#endif
