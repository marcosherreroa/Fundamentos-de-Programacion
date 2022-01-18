//Marcos Herrero

#ifndef LISTATPRENDA_H
#define LISTATPRENDA_H

#include "ListaInventario.h"

const int MAX_PRENDAS = 50;

struct tListaTPrenda {
	tPrenda* v[MAX_PRENDAS];
	int cont;
};

void crear(tListaTPrenda & lista);
void liberar(tListaTPrenda & lista);
bool generarLista(tListaTPrenda & lista, tListaInventario const & inventario, std::string const & tipo);
void particion(tListaTPrenda & lista, int ini, int fin, tPrenda* pivote, int & i, int & j);
void quicksort(tListaTPrenda & lista, int ini, int fin);
void ordenar(tListaTPrenda & lista);
void mostrar(tListaTPrenda const & lista);

#endif