//Marcos Herrero

#ifndef LISTAINVENTARIO_H
#define LISTAINVENTARIO_H

#include "Prenda.h"

struct tListaInventario {
	tPrenda* punt;
	int cont;
	int capacidad;
};

void crear(tListaInventario & lista, int tam);
void redimensionar(tListaInventario & lista);
void liberar(tListaInventario & lista);
tPrenda obtenerPrenda(tListaInventario const & lista, int pos);
bool cargar(tListaInventario & lista);
bool busqbinrecurs(tListaInventario const & lista, std::string const & identificador, int ini, int fin, int & pos);
bool buscar(tListaInventario const & lista, std::string const & identificador, int & pos);
void insertar(tListaInventario & lista, tPrenda const & insertado);
void eliminar(tListaInventario & lista, tPrenda const & eliminado);
int mayorMargen(tListaInventario const & lista);
void mostrar(tListaInventario const & lista);

#endif